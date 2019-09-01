#include "server.hpp"
#include <Utils/server_utils.hpp>
#include <iostream>
#include <chrono>
#include <Configs/structures/Reader/reader_info.hpp>

namespace server
{
Server::Server(const data::DataManager& data_manager):
ServerBase(data_manager){
   const auto configs =  data_manager.GetConfigs();
   auto reader_config = configs->GetStructure<yaml::configs::ReaderInfo>();
   reader = std::make_shared<Reader>(reader_config);
   std::cout <<"INIT";
}

void Server::Handler(SocketPtr socket)
{

  // const auto buffer_length = utils::GetBufferLength(*socket);
  // std::string buffer{};
  // buffer.resize(buffer_length);
  // boost::system::error_code error;
  // size_t length = socket->read_some(asio::buffer(buffer), error);

  // if (error){
  //     std::cout << "ERROR: " << error.message() << std::endl;
  //     return; // Connection closed
  // }
  // std::cout << "NEW THREAD: "<< std::this_thread::get_id()<< std::endl;
  // using namespace std::chrono_literals;
  // std::this_thread::sleep_for(8s);
  // std::cout << socket->remote_endpoint().address().to_string()<< std::endl;

  auto result = reader->Read(socket);
  socket->write_some(asio::buffer(result, result.size()));
  std::cout << std::endl;
  std::cout << result <<std::endl;
}
}
