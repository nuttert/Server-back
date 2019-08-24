cmake_minimum_required(VERSION 3.0.0)
#Ищем все исполняемые файлы
file(GLOB_RECURSE ${PROJECT_NAME}_UTILS_SOURCES "*.cpp")
file(GLOB_RECURSE ${PROJECT_NAME}_UTILS_HEADERS "*.hpp")


add_library(Utils STATIC ${${PROJECT_NAME}_UTILS_SOURCES} ${${PROJECT_NAME}_UTILS_HEADERS})

