#pragma once
#include <Server/Core/server_base.hpp>
#include <DataManager/data_manager.hpp>
#include "Reader/reader.hpp"

namespace server
{

struct Server:ServerBase{
using ServerBase::ServerBase;
  using Reader = reader::Reader;
  using ReaderPtr = std::shared_ptr<Reader>;

  Server(const data::DataManager& data_manager);
  
  void Handler(SocketPtr socket) override final;
  private:
  ReaderPtr reader;

};



}
