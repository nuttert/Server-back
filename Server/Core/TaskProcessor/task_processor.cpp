#include "task_processor.hpp"
#include "ThreadPool/thread_pool.hpp"
#include <DataManager/data_manager.hpp>

namespace{
  namespace ba = boost::asio;
  namespace yc = yaml::configs;
}

namespace processor{
  TaskProcessor::TaskProcessor(const data::DataManager& data_manager, const ProcessorType type){
    const auto configs =  data_manager.GetConfigs();
    auto thread_pool_config_strucutre = configs->GetStructure<yaml::configs::ThreadPoolInfo>();
    const auto& name = yc::ThreadPool::processor_types_names.at(type);

    thread_pool_ptr = std::make_shared<pools::ThreadPool>(thread_pool_config_strucutre, name);
  }

  void TaskProcessor::ToThread(const Task& task){
      if(!thread_pool_ptr)
           std::runtime_error("Need to initialize thread_pool!");
      thread_pool_ptr->ToThread(task);
  }


 

}
