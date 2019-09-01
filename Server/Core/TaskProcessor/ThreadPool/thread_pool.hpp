#include <Configs/configs_manager.hpp>
#include <Configs/structures/ThreadPool/thread_pool.hpp>

namespace boost::asio{

  class thread_pool;
}

namespace pools
{

namespace asio = boost::asio;

class ThreadPool
{
  using NativeThreadPool = asio::thread_pool;
  using NativeThreadPoolPtr = std::shared_ptr<NativeThreadPool>;

  using Config = yaml::configs::ThreadPool;
  using ConfigPtr = std::shared_ptr<Config>;

  using Task = std::function<void()>;
public:
  ThreadPool(const ConfigPtr& config, const std::string name);

  void ToThread(const Task& task);
private:
  NativeThreadPoolPtr thread_pool_ptr;
  ConfigPtr config_ptr;
};

} // namespace server::clietns_pool
