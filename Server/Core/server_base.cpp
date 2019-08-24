#include "server_base.hpp"
#include <future>
#include <vector>
#include <iostream>

namespace server
{
extern size_t kNumberOfServices = 2;
extern size_t kNumberOfAcceptors = 2;

ServerBase::ServerBase(AddressType type, size_t port)
{
  auto tcp_type = type == AddressType::kV4 ? TCP::v4() : TCP::v6();
  address_info = TCP::endpoint(tcp_type, port);
  services = Services(kNumberOfServices);
  SetAcceptors();
}

void ServerBase::Start()
{
  for (size_t current_acceptor_i = 0; current_acceptor_i < kNumberOfAcceptors; ++current_acceptor_i)
  {
    using RecursiveCaller = std::function<void(SocketPtr)>;
    using SimpleRecursiveCaller = std::function<void()>;

    auto current_service_i = current_acceptor_i % kNumberOfServices;
    auto &current_service = services[current_service_i];
    auto &current_acceptor = acceptors[current_acceptor_i];

    auto accept_handler_ptr = std::make_shared<SimpleRecursiveCaller>();
    auto call_handler_ptr = std::make_shared<RecursiveCaller>();

    auto &accept_handler = *accept_handler_ptr;
    auto &call_handler = *call_handler_ptr;


    accept_handler = [&current_service, &call_handler, &current_acceptor]() {
      auto socket_ptr = std::make_shared<Socket>(current_service);
        using namespace std::chrono_literals;
      // std::this_thread::sleep_for(5s);
      current_acceptor.async_accept(*socket_ptr, std::bind(call_handler, socket_ptr));
    };

    call_handler = [accept_handler_ptr,
                    call_handler_ptr,
                    this](SocketPtr socket_ptr) {
      std::cout << "THREAD ID-------: " << std::this_thread::get_id() <<std::endl;
      auto Handler = [socket_ptr,
                      this]() { this->Handler(socket_ptr); };

      auto handler_task = std::thread(Handler);
      handler_task.join();
      std::cout << "ACCCEEEPT" <<std::endl;
      auto &accept_handler = *accept_handler_ptr;
      accept_handler();
    };

    accept_handler();
  }
  AsyncServicesLauncher();
}

void ServerBase::AsyncServicesLauncher()
{
  SimpleFutures tasks{};
  std::mutex mutex;
  for (auto &service : services)
    tasks.emplace_back(std::async(std::launch::async, [&service, &mutex]() {
      service.run();
    }));
}

void ServerBase::SetAcceptors()
{
  using Reuser = socket_options::boolean<SOL_SOCKET, SO_REUSEPORT>;

  for (size_t current_acceptor_i = 0; current_acceptor_i < kNumberOfAcceptors; ++current_acceptor_i)
  {
    auto current_service_i = current_acceptor_i % kNumberOfServices;
    auto &current_service = services[current_service_i];
    auto acceptor = TCP::acceptor(current_service);

    acceptor.open(address_info.protocol());
    Reuser reuse_port(true);
    acceptor.set_option(reuse_port);
    acceptor.bind(address_info);
    acceptor.listen();

    acceptors.emplace_back(std::move(acceptor));
  }
}

std::string ServerBase::GetAddress() const
{
  return address_info.address().to_string();
}

size_t ServerBase::GetPort() const
{
  return address_info.port();
}

} // namespace server
