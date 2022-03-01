cmake_minimum_required(VERSION 3.0.0)
project(Quail_Engine VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)
find_package(freetype REQUIRED)
find_package(imgui REQUIRED)
find_package(OpenVR REQUIRED)
find_package(fmt REQUIRED)
find_package(tinyobjloader REQUIRED)

find_path(STB_INCLUDE_DIRS "stb.h") 

set (CMAKE_CXX_STANDARD 20)


set(ENGSRC Quail\ Engine/src/Engine)
set(ENGINE_SOURCES ${ENGSRC}/Behaviour.h ${ENGSRC}/Behaviour.cpp ${ENGSRC}/Console.h ${ENGSRC}/Console.cpp ${ENGSRC}/Engine.h ${ENGSRC}/Engine.cpp ${ENGSRC}/GameTime.h ${ENGSRC}/Input.h ${ENGSRC}/OpenVRApplication.cpp ${ENGSRC}/OpenVRApplication.h)

set(RENDSRC Quail\ Engine/src/Rendering)
set(RENDERING_SOURCES ${RENDSRC}/DesktopRenderer.cpp ${RENDSRC}/DesktopRenderer.h ${RENDSRC}/FrameBuffer.cpp ${RENDSRC}/FrameBuffer.h ${RENDSRC}/GLHeaders.h ${RENDSRC}/IndexBuffer.cpp ${RENDSRC}/IndexBuffer.h ${RENDSRC}/Light.cpp ${RENDSRC}/Light.h ${RENDSRC}/Material.cpp ${RENDSRC}/Material.h ${RENDSRC}/MaterialProperty.h ${RENDSRC}/Mesh.cpp ${RENDSRC}/Mesh.h ${RENDSRC}/OpenVRRenderer.cpp ${RENDSRC}/OpenVRRenderer.h ${RENDSRC}/RenderBuffer.cpp ${RENDSRC}/RenderBuffer.h ${RENDSRC}/Renderer.cpp ${RENDSRC}/Renderer.h ${RENDSRC}/Shader.cpp ${RENDSRC}/Shader.h ${RENDSRC}/Skybox.cpp ${RENDSRC}/Skybox.h ${RENDSRC}/Texture.cpp ${RENDSRC}/Texture.h ${RENDSRC}/VertexArray.cpp ${RENDSRC}/VertexArray.h ${RENDSRC}/VertexBuffer.cpp ${RENDSRC}/VertexBuffer.h ${RENDSRC}/VertexBufferLayout.h)

set(RESSRC Quail\ Engine/src/Resources)
set(RESOURCE_SOURCES ${RESSRC}/Resources.cpp ${RESSRC}/Resources.h)

set(SCENESRC Quail\ Engine/src/Scene)
set(SCENE_SOURCES ${SCENESRC}/Camera.cpp ${SCENESRC}/Camera.h ${SCENESRC}/Debug.h ${SCENESRC}/GameObject.cpp ${SCENESRC}/GameObject.h ${SCENESRC}/OVRCamera.cpp ${SCENESRC}/OVRCamera.h ${SCENESRC}/PerspectiveCamera.cpp ${SCENESRC}/PerspectiveCamera.h ${SCENESRC}/Scene.cpp ${SCENESRC}/Scene.h ${SCENESRC}/Transform.cpp ${SCENESRC}/Transform.h)

set(UTILSSRC Quail\ Engine/src/Utils)
set(UTILS_SOURCES ${UTILSSRC}/EngineUI.h ${UTILSSRC}/NoClipController.h ${UTILSSRC}/RotateBehaviour.h ${UTILSSRC}/Utils.h)

set(DEMOSRC Quail\ Engine/Examples)
set(DEMO_SOURCES ${DEMOSRC}/Demo1/ExampleGame.cpp ${DEMOSRC}/Demo1/ExampleGame.h ${DEMOSRC}/Demo2/Demo2.cpp ${DEMOSRC}/Demo2/Demo2.h ${DEMOSRC}/VRDemo.cpp ${DEMOSRC}/VRDemo.h)



set(MAIN_SOURCE Quail\ Engine/src/main.cpp)
add_executable(Quail_Engine ${MAIN_SOURCE} ${ENGINE_SOURCES} ${RENDERING_SOURCES} ${RESOURCE_SOURCES} ${SCENE_SOURCES} ${UTILS_SOURCES})


target_include_directories(
    Quail_Engine PRIVATE
    Quail\ Engine/src/Engine
    Quail\ Engine/src/Rendering
    Quail\ Engine/src/Resources
    Quail\ Engine/src/Scene
    Quail\ Engine/src/Utils
    Quail\ Engine/src/Resources/Shaders
    Quail\ Engine/Examples/Demo1
    Quail\ Engine/Examples/Demo2
    Quail\ Engine/Examples/VRDemo
    )
target_include_directories(Quail_Engine PRIVATE ${STB_INCLUDE_DIRS})

target_link_libraries(
  Quail_Engine
  PRIVATE
    glfw
    glad::glad
    glm::glm
    imgui::imgui
    OpenVR::OpenVR
    fmt::fmt
    tinyobjloader::tinyobjloader
)