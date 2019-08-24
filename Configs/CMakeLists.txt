cmake_minimum_required(VERSION 3.0.0)
#Ищем все исполняемые файлы
file(GLOB_RECURSE ${PROJECT_NAME}_MATR_SOURSCES "*.cpp")

add_library(Configs STATIC ${${PROJECT_NAME}_MATR_SOURSCES})

