#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include "Console.h"

void APIENTRY glDebugOutput(GLenum source,
    GLenum type,
    unsigned int id,
    GLenum severity,
    GLsizei length,
    const char* message,
    const void* userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    Console::Error("========== OPENGL ERROR ==========");
    Console::Error(fmt::format("Debug message ( {} ): {}", id, message));

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:             Console::Error("Source: API"); break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   Console::Error("Source: Window System"); break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: Console::Error("Source: Shader Compiler"); break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     Console::Error("Source: Third Party"); break;
    case GL_DEBUG_SOURCE_APPLICATION:     Console::Error("Source: Application"); break;
    case GL_DEBUG_SOURCE_OTHER:           Console::Error("Source: Other"); break;
    }

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:               Console::Error("Type: Error"); break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: Console::Error("Type: Deprecated Behaviour"); break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  Console::Error("Type: Undefined Behaviour"); break;
    case GL_DEBUG_TYPE_PORTABILITY:         Console::Error("Type: Portability"); break;
    case GL_DEBUG_TYPE_PERFORMANCE:         Console::Error("Type: Performance"); break;
    case GL_DEBUG_TYPE_MARKER:              Console::Error("Type: Marker"); break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          Console::Error("Type: Push Group"); break;
    case GL_DEBUG_TYPE_POP_GROUP:           Console::Error("Type: Pop Group"); break;
    case GL_DEBUG_TYPE_OTHER:               Console::Error("Type: Other"); break;
    }

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:         Console::Error("Severity: high"); break;
    case GL_DEBUG_SEVERITY_MEDIUM:       Console::Error("Severity: medium"); break;
    case GL_DEBUG_SEVERITY_LOW:          Console::Error("Severity: low"); break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: Console::Error("Severity: notification"); break;
    }
}
