#include <iostream>
#include <vector>
#include <DataManager/data_manager.hpp>
#include <Configs/structures/Server/server_info.hpp>
#include <Configs/structures/ThreadPool/thread_pool_info.hpp>
#include <Server/server.hpp>
#include <Utils/Containers/multi_index_container.hpp>

// std::string operator"" _s(const char *string, size_t size)
// {
//   std::string str;
//   str.resize(size);
//   str = string;
//   return str;
// }
struct ByName
{
};
struct ByGroup
{
};
struct C
{
  std::string name = "bb";
  std::string group = "aa";
  using Tags = utils::containers::TypesContainer<ByName, ByGroup>;
  using PtrsToMembers = utils::containers::PtrContainer<&C::name, &C::group>;
};
struct A : C
{

  std::string name = "mk";
  std::string group = "dk";
};
struct B : C
{

  std::string name = "pp";
  std::string group = "dd";
};

using Cont = boost::multi_index_container<
    C,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<boost::multi_index::tag<ByName>,
                                           boost::multi_index::member<C, std::string, &C::name>>,
        boost::multi_index::ordered_unique<boost::multi_index::tag<ByGroup>,
                                           boost::multi_index::member<C, std::string, &C::group>>>>;

int main()
{
  data::DataManager data;
  data.LoadConfigs();

  server::Server processor(data);

  processor.Start();

  return 0;
}
