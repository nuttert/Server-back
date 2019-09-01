#pragma once
#include <memory>
#include <DataManager/data_manager.hpp>

namespace pools{
  class ThreadPool;
}
namespace processor{
  
class TaskProcessor{
  using ThreadPoolPtr = std::shared_ptr<pools::ThreadPool>;
  public:
  TaskProcessor(const data::DataManager& data_manager);
  public:
  template<typename Task>
  void ToThread(Task& task);
  private:
  ThreadPoolPtr thread_pool;
};

}
