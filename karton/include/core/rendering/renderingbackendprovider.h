#ifndef RENDERINGBACKENDPROVIDER_H
#define RENDERINGBACKENDPROVIDER_H

#include <utils/enums.h>
#include <rendering/renderer/renderer.h>
#include <rendering/renderer/openglrenderer.h>
#include <rendering/renderfactory/renderfactory.h>
#include <rendering/renderfactory/openglrenderfactory.h>
#include <rendering/window/window.h>
#include <rendering/window/glfwwindow.h>

class RenderingBackendProvider
{
public:
    static std::shared_ptr<RenderFactory> CreateFactory(BackendType backend)
    {
        switch (backend)
        {
        case BackendType::OpenGL:
            return std::make_shared<OpenGLRenderFactory>();
            // case BackendType::Vulkan:
            //     return std::make_unique<VulkanRenderFactory>();
            // case BackendType::DirectX:
            //     return std::make_unique<DirectXRenderFactory>();
        default:
            return nullptr;
        }
    }

    static std::unique_ptr<Window> CreateWindow(BackendType backend)
    {
        switch (backend)
        {
        case BackendType::OpenGL:
            return std::make_unique<GLFWWindow>();
            // ...
        default:
            return nullptr;
        }
    }

    static std::unique_ptr<Renderer> CreateRenderer(BackendType backend)
    {
        switch (backend)
        {
        case BackendType::OpenGL:
            return std::make_unique<OpenGLRenderer>();
            // ...
        default:
            return nullptr;
        }
    }
};

#endif // !RENDERINGBACKENDPROVIDER_H
