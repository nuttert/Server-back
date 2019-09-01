#include "task_processor.hpp"
#include "ThreadPool/thread_pool.hpp"
#include <DataManager/data_manager.hpp>

namespace{
  namespace ba = boost::asio;
}

namespace processor{
  TaskProcessor::TaskProcessor(const data::DataManager& data_manager){
    const auto configs =  data_manager.GetConfigs();
    auto thread_pool_config_strucutre = configs->GetStructure<yaml::configs::ThreadPoolInfo>();
    thread_pool = std::make_shared<pools::ThreadPool>(thread_pool_config_strucutre);
  }

template<typename Task>
  void TaskProcessor::ToThread(Task& task){
      ba::post(thread_pool, task); 
  }

}
