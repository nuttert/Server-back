#pragma once
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <unordered_map>

namespace yaml{
namespace configs{

class Server{
  enum class Properties;
  using PropertiesNames =  std::map<Properties, std::string>;
private:
  enum class Properties{kName,kIpv4};
public:
  Server(const YAML::Node& node);
  static std::string GetDocumentName();
  const std::string GetName()const;
  const std::string GetIpv4()const;

private:
  std::string GetPropertyName(Properties property) const;
private:
  std::string name;
  std::string ipv4;
  size_t port;
  static const PropertiesNames properties_names;
};

const Server::PropertiesNames Server::properties_names{
  {Properties::kName, "name"},
  {Properties::kIpv4, "ipv4"}
};


template <typename Document>
class Config {
public:
	Config(const std::string& path);

	Document const &GetServer() const;
private:
	std::unique_ptr<Document> document_;
  YAML::Node root;
  const std::string kName;
};

}
}

#include "configs.cpp"
