#pragma once
#include <boost/asio.hpp>
#include <string>

namespace server
{

namespace asio = boost::asio;
namespace ip = asio::ip;
namespace socket_options = asio::detail::socket_option;

using TCP = ip::tcp;
 enum class AddressType
  {
    kV4,
    kV6
  };

struct ServerBase
{
  using AddressInfo = TCP::endpoint;

  using Service = asio::io_service;
  using Acceptor = TCP::acceptor;
  using Socket = TCP::socket;
  using SocketPtr = std::shared_ptr<Socket>;

  using Acceptors = std::vector<Acceptor>;
  using Services = std::vector<Service>;
  using Sockets = std::vector<Socket>;

  using SimpleFuture = std::future<void>;
  using SimpleFutures = std::vector<SimpleFuture>;

  using ThreadPool = asio::thread_pool;

public:
  ServerBase(AddressType type, size_t port);
  size_t GetPort() const;
  std::string GetAddress() const;
  void Start();

private:
  void SetAcceptors();
  void AsyncServicesLauncher();
  virtual void Handler(SocketPtr socket) = 0;

private:
  AddressInfo address_info{};
  Services services{};
  Acceptors acceptors{};
  ThreadPool pool;

};

}
