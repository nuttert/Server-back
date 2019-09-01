cmake_minimum_required(VERSION 3.0.0)
project(PROJECT VERSION 0.1.0)

#Год плюсов
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-stdlib=libc++ -std=c++17")


#Ищем все исполняемые файлы
file(GLOB _SOURSCES "*.cpp")
file(GLOB _HEADERS "*.hpp")


#Добавляем в сборку исполняемые файлы
add_executable(${PROJECT_NAME} ${_SOURSCES})

##########
find_package(YAML-CPP) 

if(YAML-CPP_FOUND)
    message(FOUND\ LIBRARY: YAML-CPP)
    include_directories(${YAML_CPP_INCLUDE_DIR}) 
    target_link_libraries(${PROJECT_NAME} ${YAML_CPP_LIBRARIES})
endif()
##########

find_package(fmt) 

if(fmt_FOUND)
    message(FOUND\ LIBRARY: fmt)
    include_directories(${fmt_INCLUDE_DIR}) 
    target_link_libraries(${PROJECT_NAME} ${fmt_LIBRARIES})
endif()
##########

find_package(spdlog) 

if(fmt_FOUND)
    message(FOUND\ LIBRARY: spdlog)
    include_directories(${spdlog_INCLUDE_DIR}) 
    target_link_libraries(${PROJECT_NAME} ${spdlog_LIBRARIES})
endif()
##########

##########
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS system thread filesystem)

if(Boost_FOUND)
    message(FOUND\ LIBRARY: Boost)
    include_directories(${Boost_INCLUDE_DIR})
    target_link_libraries(
        ${PROJECT_NAME}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY})
endif()
##########



#Добавляем поддиректорию для поиска подфайла Cmake
add_subdirectory(Configs)
add_subdirectory(Server)
add_subdirectory(Utils)
add_subdirectory(DataManager)

cmake_policy(SET CMP0063 NEW)
#Линкуем
target_link_libraries(${PROJECT_NAME} Utils Configs Server Data)






