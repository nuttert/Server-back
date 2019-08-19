cmake_minimum_required(VERSION 3.0.0)
project(PROJECT VERSION 0.1.0)

#Год плюсов
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++14)

#Ищем все исполняемые файлы
file(GLOB _SOURSCES "*.cpp")
file(GLOB _HEADERS "*.hpp")
file(GLOB UTILS_HEADERS "Utils/*.hpp")

set(FILES ${UTILS_HEADERS} ${_SOURSCES} ${_HEADERS})

#Добавляем в сборку исполняемые файлы
add_executable(${PROJECT_NAME} ${FILES})

include_directories(${UTILS_HEADERS}) 

##########
find_package(YAML-CPP) 

if(YAML-CPP_FOUND)
    message(FOUND\ LIBRARY: YAML-CPP)
    include_directories(${YAML_CPP_INCLUDE_DIR}) 
    target_link_libraries(${PROJECT_NAME} ${YAML_CPP_LIBRARIES})
endif()
##########


#Добавляем поддиректорию для поиска подфайла Cmake
add_subdirectory(Configs)
add_subdirectory(Server)


target_include_directories(Server PUBLIC "./Utils")
target_include_directories(Configs PUBLIC "./Utils")

#Линкуем
target_link_libraries(${PROJECT_NAME} Configs Server)







