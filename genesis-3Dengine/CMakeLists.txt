cmake_minimum_required(VERSION 3.10)
project(genesis-3Dengine)

find_package(PkgConfig)

file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

file(GLOB_RECURSE EGLFile ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/EGL/*.cpp)

add_library(${PROJECT_NAME} SHARED ${sources} ${headers} ${EGLFile}
  ${CMAKE_SOURCE_DIR}/vendor/stb_image/stb_image.cpp ${CMAKE_SOURCE_DIR}/vendor/stb_image/stb_truetype.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Genesis3D> 
  #$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Genesis/Core>
  ${CMAKE_SOURCE_DIR}/genesis-core/include/Genesis
  # ${CMAKE_SOURCE_DIR}/vendor/entt/src/entt
  ${CMAKE_SOURCE_DIR}/vendor/glad/include
  ${CMAKE_SOURCE_DIR}/vendor/stb_image
    
  )

# link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC      
  genesis-core
)


install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/Genesis3D DESTINATION include)
