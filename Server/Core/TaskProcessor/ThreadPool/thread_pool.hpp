#include <boost/asio.hpp>
#include <Configs/configs_manager.hpp>
#include <Configs/structures/ThreadPool/thread_pool.hpp>

namespace pools
{

namespace asio = boost::asio;

class ThreadPool
{
  using NativeThreadPool = asio::thread_pool;
  using Config = yaml::configs::ThreadPool;
  using ConfigPtr = std::shared_ptr<Config>;
public:
  ThreadPool(const ConfigPtr& config);
  
private:
  NativeThreadPool thread_pool;
  ConfigPtr config;
};

} // namespace server::clietns_pool
