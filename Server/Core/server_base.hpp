#pragma once
#include <boost/asio.hpp>
#include <string>
#include <Configs/structures/Server/server_info.hpp>
#include <Configs/structures/Server/server.hpp>
#include <Configs/configs_manager.hpp>
#include "TaskProcessor/task_processor.hpp"

namespace server
{

namespace asio = boost::asio;
namespace ip = asio::ip;
namespace socket_options = asio::detail::socket_option;
namespace yc = yaml::configs;

using TCP = ip::tcp;

struct ServerBase
{
  using AddressInfo = TCP::endpoint;

  using Service = asio::io_service;

  using Acceptor = TCP::acceptor;
  using AcceptorPtr = std::shared_ptr<Acceptor>;

  using Socket = TCP::socket;
  using SocketPtr = std::shared_ptr<Socket>;

  using Sockets = std::vector<Socket>;

  using SimpleFuture = std::future<void>;
  using SimpleFutures = std::vector<SimpleFuture>;

  using Config = yaml::configs::Server;
  using ConfigPtr = std::shared_ptr<Config>;

  using Processor = processor::TaskProcessor;
public:
  ServerBase(const data::DataManager& data_manager);
  size_t GetPort() const;
  std::string GetAddress() const;
  void Start();

private:
  void SetAcceptor();
  void AsyncServicesLauncher();
  virtual void Handler(SocketPtr socket) = 0;

private:
  AddressInfo address_info{};
  Service service;
  AcceptorPtr acceptor;
  size_t kNumberOfServices;
  ConfigPtr config;
  Processor processor;
};

}
