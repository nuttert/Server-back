#include <boost/asio.hpp>
#include <Configs/configs_manager.hpp>

namespace server::clietns_pool
{

namespace asio = boost::asio;

class ThreadPool final : public asio::thread_pool
{
  ThreadPool();
};

} // namespace server::clietns_pool
