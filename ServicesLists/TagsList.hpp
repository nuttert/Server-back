#pragma once
#include <Utils/Containers/types_container.hpp>

namespace yaml::configs::container::tags{
  struct ByName{};
  struct ByGroup{};
  struct ByPointer{};

  using Tags =  utils::containers::TypesContainer<ByName, ByGroup, ByPointer>;
}

