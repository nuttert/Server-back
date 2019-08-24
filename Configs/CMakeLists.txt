cmake_minimum_required(VERSION 3.0.0)
#Ищем все исполняемые файлы
file(GLOB_RECURSE ${PROJECT_NAME}_MATR_SOURSCES "*.cpp")

add_library(Configs STATIC ${${PROJECT_NAME}_MATR_SOURSCES})


target_include_directories(Configs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.. )
