cmake_minimum_required(VERSION 3.0.0)
#Ищем все исполняемые файлы
file(GLOB_RECURSE ${PROJECT_NAME}_TAGS_SOURCES "*.cpp")
file(GLOB_RECURSE ${PROJECT_NAME}_TAGS_HEADERS "*.hpp")


target_include_directories(Tags PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.. )
