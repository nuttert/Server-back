cmake_minimum_required(VERSION 3.0.0)
#Ищем все исполняемые файлы
file(GLOB_RECURSE _SOURSCES "*.cpp")
file(GLOB_RECURSE _HEADERS "*.hpp")

add_library(Data STATIC ${_SOURSCES} ${_HEADERS})
target_include_directories(Data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

