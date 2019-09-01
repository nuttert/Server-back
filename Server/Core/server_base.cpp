#include "server_base.hpp"
#include <future>
#include <vector>
#include <iostream>
#include <boost/range.hpp>

namespace{
  using ProcessorType = server::yc::ThreadPool::ProcessorType;
}
namespace server
{

ServerBase::ServerBase(const data::DataManager& data_manager):
processor(data_manager, ProcessorType::kMain)
{
  const auto configs =  data_manager.GetConfigs();
  config = configs->GetStructure<yaml::configs::ServerInfo>();
  
  kNumberOfServiceThreadsForAccepting = config->amount_of_service_threads_for_accepting;
  kNumberOfServicesForWorking = config->amount_of_services_for_working;

  services_for_sockets = Services(kNumberOfServicesForWorking);

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
      auto socket_ptr = std::make_shared<Socket>(GetfServiceForWorking());
      acceptor->async_accept(*socket_ptr, std::bind(call_handler, socket_ptr));
    };

    //async function________call_handler
    call_handler = [accept_handler_ptr,
                    call_handler_ptr,
                    this](SocketPtr socket_ptr) {
      auto Handler = [socket_ptr,
                      this]() { this->Handler(socket_ptr); };

      processor.ToThread(Handler);

      auto &accept_handler = *accept_handler_ptr;
      accept_handler();
    };
    //async function________call_handler
    accept_handler();

  AsyncServicesLauncher();
}

void ServerBase::AsyncServicesLauncher()
{
  SimpleFutures tasks{};
  
  for (size_t index = 0;index!=kNumberOfServiceThreadsForAccepting;++index)
    tasks.emplace_back(std::async(std::launch::async, [this]() {
      main_service.run();
    }));
  
  for(auto& service: services_for_sockets)
     tasks.emplace_back(std::async(std::launch::async, [&service]() {
      auto work = Work(service);
      service.run();
    }));
}

void ServerBase::SetAcceptor()
{
  using Reuser = socket_options::boolean<SOL_SOCKET, SO_REUSEPORT>;
  acceptor = std::make_shared<Acceptor>(main_service);
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

ServerBase::Service& ServerBase::GetfServiceForWorking(){
  return services_for_sockets[GetIndexOfServiceForWorking()];
}

size_t ServerBase::GetIndexOfServiceForWorking(){
  static size_t index{0};
  return index++ % kNumberOfServicesForWorking;
}

} // namespace server
