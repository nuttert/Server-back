#include "thread_pool.hpp"
#include <boost/asio.hpp>
#include <Utils/Exceptions/file_exceptions.hpp>
namespace
{
namespace ex = exceptions;
namespace ba = boost::asio;
} // namespace
namespace pools
{

ThreadPool::ThreadPool(const ConfigPtr &config_ptr, const std::string name) : config_ptr(config_ptr)
{
  if (!config_ptr)
    throw ex::BadConfig{"Can't read from config!"};
  const auto size = config_ptr->type_to_size[name];
  thread_pool_ptr = std::make_shared<NativeThreadPool>(size);
}

void ThreadPool::ToThread(const Task &task)
{
  if (!thread_pool_ptr)
    std::runtime_error("Need to initialize thread_pool!");
  ba::post(*thread_pool_ptr, task);
}

} // namespace pools
