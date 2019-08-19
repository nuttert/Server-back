#ifndef MATR_CPP
#define MATR_CPP

#include "configs.hpp"

namespace yaml{
namespace configs{

Server::Server(const YAML::Node& node){
  const auto kName = GetPropertyName(Properties::kName);
  const auto kIpv4 = GetPropertyName(Properties::kIpv4);
  name = node[kName].as<std::string>();
  ipv4 = node[kIpv4].as<std::string>();
}

std::string Server::GetDocumentName(){
  static std::string kName = "Server";
  return kName;
}

 std::string Server::GetPropertyName(Properties property)const{
   return properties_names.at(property);
 }

  const std::string Server::GetName()const{
      return name;
  }
  const std::string Server::GetIpv4()const{
      return ipv4;
  }


template <typename Document>
Config<Document>::Config(const std::string& path):
kName(Document::GetDocumentName()),
root(YAML::LoadFile(path))
{
  document_ = std::make_unique<Document>(root[kName]);
}


template <typename Document>
Document const& Config<Document>::GetServer() const {
		return *document_;
}


}
}

#endif
