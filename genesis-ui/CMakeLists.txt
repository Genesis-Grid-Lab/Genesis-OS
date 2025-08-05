cmake_minimum_required(VERSION 3.10)
project(genesis-ui)

find_package(PkgConfig)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/genesis-core/include
  ${CMAKE_SOURCE_DIR}/genesis-core/include/Genesis
  ${CMAKE_SOURCE_DIR}/genesis-3Dengine/include/Genesis3D
  ${CMAKE_SOURCE_DIR}/vendor/glm    
  )

# link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
  genesis-core
  genesis-3Dengine
  glm
  # EnTT     
)


install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
