#pragma once
#define GL_GLES2
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <errno.h>
#include <vector>
#include <xf86drm.h>
#include <xf86drmMode.h>
#include <unordered_map>
#include <gbm.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/select.h>
#include <memory>

// #include "glad/egl.h"
#include "EGL/egl.h"
#include <EGL/eglext.h>
#include "glad/gles2.h"
#include <EGL/egl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifdef GC_DEBUG
#include <signal.h>
#define GC_DEBUGBREAK() raise(SIGTRAP)
#define GC_ENABLE_ASSERTS
#else
#define GC_DEBUGBREAK()
#endif

#define GC_EXPAND_MACRO(x) x
#define GC_STRINGIFY_MACRO(x) #x


//--------------------- Scope = unique pointer --------------------
template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args){

  return std::make_unique<T>(std::forward<Args>(args)...);
}

//--------------------- Ref = shared pointer -----------------------
template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args){

  return std::make_shared<T>(std::forward<Args>(args)...);
}
