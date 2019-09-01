#include "thread_pool.hpp"
#include <Utils/Exceptions/file_exceptions.hpp>
namespace{
  namespace ex = exceptions;
}
namespace pools{

 ThreadPool::ThreadPool(const ConfigPtr& config):
config(config)
{
  if(!config)
    throw ex::BadConfig{"Can't read from config!"};
  std::cout << config->amount_of_threads;
  // thread_pool()
}


}
