cmake_minimum_required(VERSION 3.10)
project(genesis-core)

find_package(PkgConfig)
pkg_search_module(DRM libdrm)
pkg_search_module(GBM gbm)
pkg_search_module(EGL egl)
pkg_search_module(GLES glesv2)

file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(${PROJECT_NAME} SHARED ${sources} ${headers})

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Genesis> 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Genesis/Core>  
  # ${CMAKE_SOURCE_DIR}/vendor/entt/src/entt
  # ${CMAKE_SOURCE_DIR}/vendor/glad/include
  ${CMAKE_SOURCE_DIR}/vendor/spdlog/include
  ${CMAKE_SOURCE_DIR}/vendor/glm
    
  )

# link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC      
  # glad    
  glm
  # EnTT
  spdlog
)



if (DRM_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${DRM_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${DRM_LIBRARIES})
endif()

if (GBM_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${GBM_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${GBM_LIBRARIES})
endif()

if (EGL_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${EGL_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${EGL_LIBRARIES})
endif()

if (GLES_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${GLES_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${GLES_LIBRARIES})
endif()

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/Genesis DESTINATION include)
