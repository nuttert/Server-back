#pragma once
#include "server_base.hpp"

namespace server
{

struct Server:ServerBase{
using ServerBase::ServerBase;

  void Handler(SocketPtr socket) override final;

};



}
