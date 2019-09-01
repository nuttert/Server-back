#pragma once
#include <memory>
#include <DataManager/data_manager.hpp>
#include <Configs/structures/ThreadPool/thread_pool_info.hpp>
#include <Configs/structures/ThreadPool/thread_pool.hpp>

namespace pools{
  class ThreadPool;
}
namespace processor{
using ProcessorType = yaml::configs::ThreadPool::ProcessorType;

class TaskProcessor{
  using ThreadPoolPtr = std::shared_ptr<pools::ThreadPool>;
  using Task = std::function<void()>;
  public:
  TaskProcessor(const data::DataManager& data_manager,const ProcessorType type);
  public:
  void ToThread(const Task& task);
  private:
  ThreadPoolPtr thread_pool_ptr;
};

}
