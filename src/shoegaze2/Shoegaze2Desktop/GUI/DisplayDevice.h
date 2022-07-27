#pragma once

#include <Shoegaze2/System/Interface/GUI/IDisplayDevice.h>

#include <glad/gl.h>
#include <glfw/glfw3.h>

#include <cstdio>

#include <Shoegaze2Desktop/GUI/RenderingContext.h>

namespace Shoegaze2Desktop
{
    class DisplayDevice : public Shoegaze2::IDisplayDevice
    {
    private:
        GLFWwindow *window;
        int width, height;
        RenderingContext *renderingContext;

    public:
        DisplayDevice(int width, int height) : width(width), height(height)
        {
        }

        bool Initialize() override
        {
            if (!glfwInit())
                return false;

            // MSAA
            glfwWindowHint(GLFW_SAMPLES, 4);
            window = glfwCreateWindow(width, height, "Shoegaze2", nullptr, nullptr);
            if (!window)
            {
                glfwTerminate();
                return false;
            }

            glfwMakeContextCurrent(window);

            int version = gladLoadGL(glfwGetProcAddress);
            if (version == 0)
            {
                printf("Failed to initialize OpenGL context\n");
                return false;
            }

            printf("Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

            // MSAA
            glEnable(GL_MULTISAMPLE);
            renderingContext = (RenderingContext*)CreateRenderingContext();
            return true;
        }

        Shoegaze2::IRenderingContext *CreateRenderingContext() override { return new RenderingContext(window); }

        RenderingContext *GetRenderingContext() { return renderingContext; }

        GLFWwindow *GetWindow()
        {
            return window;
        }
    };
}