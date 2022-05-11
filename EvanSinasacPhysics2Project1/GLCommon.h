#pragma once

// These have to be included in a certain order
//	or the build fails (it's a thing with GFLW)

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
//#define GLEW_STATIC
#include <GLFW/glfw3.h>
