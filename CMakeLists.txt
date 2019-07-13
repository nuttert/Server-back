cmake_minimum_required(VERSION 3.0.0)
project(PROJECT VERSION 0.1.0)

#Ищем все исполняемые файлы
file(GLOB _SOURSCES "*.cpp")

#Добавляем в сборку исполняемые файлы
add_executable(${PROJECT_NAME} ${_SOURSCES})

#Добавляем поддиректорию для поиска подфайла Cmake
add_subdirectory(Matr)

#Линкуем
target_link_libraries(${PROJECT_NAME} Matr)

message(MESSAGEEEE ${_SOURSCES})