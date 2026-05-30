#pragma once
// STL
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <functional>
#include <filesystem>
#include <chrono>
#include <algorithm>

// Rise Engine
#include "RiseEngineCore/Core/CoreTypes.hpp"

// GLM
#include <vendor/glm/glm.hpp>
#include <vendor/glm/gtc/matrix_transform.hpp>
#include <vendor/glm/gtc/type_ptr.hpp>

// GLAD
#include <vendor/OpenGL/glad/include/glad/glad.h>
// #include <vendor/OpenGL/GLFW/include/GLFW/glfw3.h>. I don't think I'll ever use it but I lose nothing keeping it here.

// DEAR IMGUI
#include <vendor/imgui/imgui.h>
#include <vendor/imgui/backends/imgui_impl_glfw.h>
#include <vendor/imgui/backends/imgui_impl_opengl3.h>

/*
You can uncomment this and setup the preprocessor definitions once you start
* implementing the other renderers.
* 
#ifdef RISE_RENDERER_OPENGL
	#include <vendor/imgui/backends/imgui_impl_opengl3.h>
#elifdef RISE_RENDERER_DX11
	#include <vendor/imgui/backends/imgui_impl_dx11.h>
#elifdef RISE_RENDERER_DX12
	#include <vendor/imgui/backends/imgui_impl_dx12.h>
#elifdef RISE_RENDERER_VULKAN
#include <vendor/imgui/backends/imgui_impl_vulkan.h>
#endif
*/

// STB IMAGE
#define STB_IMAGE_IMPLEMENTATION
#include <vendor/stb/stb_image.h>

// JSON
#include <vendor/nlohmann/json.hpp>