#include "server_base.hpp"
#include <future>
#include <vector>
#include <iostream>
#include <boost/range.hpp>

namespace server
{

ServerBase::ServerBase(const data::DataManager& data_manager):
processor(data_manager)
{
  const auto configs =  data_manager.GetConfigs();
  config = configs->GetStructure<yaml::configs::ServerInfo>();
  
  kNumberOfServices = config->amount_of_service_threads;
  auto tcp_type = config->address_type ==  Config::AddressType::kV4 ? TCP::v4() : TCP::v6();
  const auto port = config->port;
  address_info = TCP::endpoint(tcp_type, port);
  SetAcceptor();
}

void ServerBase::Start()
{
    using RecursiveCaller = std::function<void(SocketPtr)>;
    using SimpleRecursiveCaller = std::function<void()>;


    auto accept_handler_ptr = std::make_shared<SimpleRecursiveCaller>();
    auto call_handler_ptr = std::make_shared<RecursiveCaller>();

    auto &accept_handler = *accept_handler_ptr;
    auto &call_handler = *call_handler_ptr;


    accept_handler = [this, &call_handler]() {
      auto socket_ptr = std::make_shared<Socket>(service);
      acceptor->async_accept(*socket_ptr, std::bind(call_handler, socket_ptr));
    };

    call_handler = [accept_handler_ptr,
                    call_handler_ptr,
                    this](SocketPtr socket_ptr) {
      auto Handler = [socket_ptr,
                      this]() { this->Handler(socket_ptr); };
                      std::cout << std::endl;
      auto handler_task = std::thread(Handler);
      handler_task.detach();

      auto &accept_handler = *accept_handler_ptr;
      accept_handler();
    };
    accept_handler();

  AsyncServicesLauncher();
}

void ServerBase::AsyncServicesLauncher()
{
  SimpleFutures tasks{};
  std::mutex mutex;
  
  for (size_t index = 0;index!=kNumberOfServices;++index)
    tasks.emplace_back(std::async(std::launch::async, [this, &mutex]() {
      service.run();
    }));
}

void ServerBase::SetAcceptor()
{
  using Reuser = socket_options::boolean<SOL_SOCKET, SO_REUSEPORT>;
  acceptor = std::make_shared<Acceptor>(service);
  acceptor->open(address_info.protocol());
  Reuser reuse_port(true);
  acceptor->set_option(reuse_port);
  acceptor->bind(address_info);
  acceptor->listen();
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
