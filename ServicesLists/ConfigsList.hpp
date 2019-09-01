#pragma once
#include <Configs/structures/Server/server_info.hpp>
#include <Configs/structures/Server/server.hpp>

#include <Configs/structures/ThreadPool/thread_pool_info.hpp>
#include <Configs/structures/ThreadPool/thread_pool.hpp>

#include <Configs/configs_manager.hpp>


namespace yaml::configs::list{
  using ConfigsManager = yaml::configs::ConfigsManager<ThreadPoolInfo, ServerInfo>;
}
