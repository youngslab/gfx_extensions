

#include <iostream>
#include <string.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#include <fmt/format.h>

auto split(std::string const &str, std::string const &delemeter)
    -> std::vector<std::string> {

  auto extensions = std::vector<std::string>();
  size_t s = 0;
  size_t e = 0;

  while ((e = str.find(delemeter, s)) != std::string::npos) {
    auto token = str.substr(s, e - s);
    extensions.push_back(token);
    s = e + delemeter.size(); // including a delemeter
  }

  return extensions;
}

int main() {

  auto display = eglGetDisplay(nullptr);
  eglInitialize(display, nullptr, nullptr);

  auto str = std::string(eglQueryString(display, EGL_EXTENSIONS));
  auto es = split(str, " ");

  std::cout << "EGL_EXTENSIONS: \n";
  for (auto &e : es) {
    std::cout << "\t* " << e << "\n";
  }

  static const EGLint config_attribs[] = {EGL_RENDERABLE_TYPE,
					  EGL_OPENGL_ES3_BIT_KHR, EGL_NONE};
  EGLConfig cfg;
  EGLint count;

  auto res = eglChooseConfig(display, config_attribs, &cfg, 1, &count);
  if (res == EGL_FALSE) {
    throw std::runtime_error("Failed to choose EGL config");
  }

  res = eglBindAPI(EGL_OPENGL_ES_API);
  if (res == EGL_FALSE) {
    throw std::runtime_error("Failed to bind EGL API");
  }

  static const EGLint attribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
  EGLContext context = eglCreateContext(display, cfg, EGL_NO_CONTEXT, attribs);
  if (context == EGL_NO_CONTEXT) {
    throw std::runtime_error("Failed to create EGL context");
  }

  // SURFACELESS
  res = eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, context);
  if (res == EGL_FALSE) {
    throw std::runtime_error("Failed to make current");
  }

  auto raw = (const char *)glGetString(GL_EXTENSIONS);
  if (!raw) {
    throw std::runtime_error("Failed to get GL extension string");
  }

  str = std::string(raw);
  es = split(str, " ");

  std::cout << "GLES_EXTENSIONS: \n";
  for (auto &e : es) {
    std::cout << "\t* " << e << "\n";
  }
}
