cmake_minimum_required(VERSION 3.0.0)
#Ищем все исполняемые файлы
file(GLOB ${PROJECT_NAME}_MATR_SOURSCES "*.cpp")

message(STATUS EE${${PROJECT_NAME}_MATR_SOURSCES})

add_library(Matr STATIC ${${PROJECT_NAME}_MATR_SOURSCES})