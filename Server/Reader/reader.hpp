#pragma once
#include <boost/asio.hpp>
#include <Configs/structures/Reader/reader.hpp>

namespace server::reader{
  namespace asio = boost::asio;
  namespace ip = asio::ip;
  namespace bs = boost::system;

  using TCP = ip::tcp;
  using Socket = TCP::socket;
  using SocketPtr = std::shared_ptr<Socket>;


  struct Reader{
    using Config = yaml::configs::Reader;
    using ConfigPtr = std::shared_ptr<Config>;

  Reader(const ConfigPtr& config_ptr);
  std::string Read(const SocketPtr& socket_ptr);

  private:
  ConfigPtr config;
  };




  

}
