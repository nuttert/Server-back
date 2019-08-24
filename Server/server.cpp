#include "server.hpp"
#include <Utils/server_utils.hpp>
#include <iostream>
#include <chrono>


namespace server
{

void Server::Handler(SocketPtr socket)
{

  const auto buffer_length = utils::GetBufferLength(*socket);
  std::string buffer{};
  buffer.resize(buffer_length);
  boost::system::error_code error;
  size_t length = socket->read_some(asio::buffer(buffer), error);

  std::cout << "LENGTH" << length<<std::endl;
  if (error){
      std::cout << "ERROR" << error.message() << std::endl;
      return; // Connection closed
  }
  std::cout << "NEW THREAD: "<< std::this_thread::get_id()<< std::endl;
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(8s);
  std::cout << socket->remote_endpoint().address().to_string()<< std::endl;
  socket->write_some(asio::buffer(buffer, length));

  

}
}
