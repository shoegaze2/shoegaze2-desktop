#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <nanovg.h>


#include <Shoegaze2/System/Interface/GUI/IRenderingContext.h>
#include <Shoegaze2Desktop/GUI/Canvas.h>
#include <Shoegaze2Desktop/GUI/Image.h>


namespace Shoegaze2Desktop
{
    class RenderingContext : public Shoegaze2::IRenderingContext
    {
    private:
        GLFWwindow *window;
        NVGcontext *vg;
        int width = 0, height = 0;
    public:
        explicit RenderingContext(GLFWwindow *window);

        std::shared_ptr<Shoegaze2::ICanvas> CreateCanvas(Shoegaze2::Position pos, Shoegaze2::Size size, std::shared_ptr<Shoegaze2::ICanvas> parent = nullptr) override
        {
            return std::make_shared<Canvas>(this, pos, size, parent);
        }

        std::shared_ptr<Shoegaze2::IImage> CreateImage(int image_width, int image_height) override
        {
            return std::make_shared<Image>(vg, image_width, image_height);
        }

        std::shared_ptr<Shoegaze2::IBrush> CreateBrush() override
        {
            return std::make_shared<Brush>(vg);
        }

        std::shared_ptr<Shoegaze2::IPaint> CreatePaint() override
        {
            return std::make_shared<Paint>();
        }

        std::shared_ptr<Shoegaze2::IPath> CreatePath() override
        {
            return std::make_shared<Path>(vg);
        }

        Shoegaze2::Matrix GetMatrix() override
        {
            float m[6] = {};
            nvgCurrentTransform(vg, m);
            return {m};
        }

        void SetMatrix(Shoegaze2::Matrix &matrix) override
        {
            float m[6] = {matrix[0][0], matrix[1][0], matrix[0][1], matrix[1][1], matrix[0][2], matrix[1][2]};
            nvgSetTransform(vg, m);
        }

        // TODO: DELETE THIS AFTER TESTS (or maybe нет)
        inline NVGcontext * GetVGContext() { return vg; }


        bool Initialize() override
        {
            return true;
        }
        
        void StartFrame() override
        {
            
            glfwGetWindowSize(window, &width, &height);
            int fbWidth = 0, fbHeight = 0;
            glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
            // Calculate pixel ration for hi-dpi devices.
            float pxRatio = (float)fbWidth / (float)width;

            glViewport(0, 0, fbWidth, fbHeight);

            nvgBeginFrame(vg, width, height, pxRatio);
        }

        void EndFrame() override
        {
            nvgEndFrame(vg);
        }

        void Clear() override
        {
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        }

        void SwapBuffers() override
        {
            glfwSwapBuffers(window);
        }

        int GetWidth() override
        {
            return width;
        }

        int GetHeight() override
        {
            return height;
        }

        void SetDrawingSurface(std::shared_ptr<Shoegaze2::IImage> image);
    };
}