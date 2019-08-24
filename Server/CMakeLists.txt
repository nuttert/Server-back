cmake_minimum_required(VERSION 3.0.0)
#Ищем все исполняемые файлы
file(GLOB_RECURSE ${PROJECT_NAME}_MATR_SOURSCES "*.cpp")
file(GLOB_RECURSE ${PROJECT_NAME}_MATR_HEADERS "*.hpp")


add_library(Server STATIC ${${PROJECT_NAME}_MATR_SOURSCES} ${${PROJECT_NAME}_MATR_HEADERS})

target_include_directories(Server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.. )

