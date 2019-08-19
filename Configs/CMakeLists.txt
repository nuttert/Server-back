cmake_minimum_required(VERSION 3.0.0)
#Ищем все исполняемые файлы
file(GLOB ${PROJECT_NAME}_MATR_SOURSCES "*.cpp")
find_package(YAML-CPP) 

include_directories(${UTILS_HEADERS}) 
add_library(Configs STATIC ${${PROJECT_NAME}_MATR_SOURSCES} ${UTILS_HEADERS})


