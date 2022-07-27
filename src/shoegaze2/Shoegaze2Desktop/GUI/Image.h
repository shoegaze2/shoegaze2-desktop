//
// Created by iashi on 13.02.2022.
//

#ifndef SHOEGAZE2_IMAGE_H
#define SHOEGAZE2_IMAGE_H

#include <Shoegaze2/System/Interface/GUI/IImage.h>
#include <Shoegaze2Desktop/GUI/RenderingContext.h>

#include <nanovg_gl_utils.h>

namespace Shoegaze2Desktop
{
    class Image : public Shoegaze2::IImage
    {
    private:
        NVGcontext *ctx;
    public:
        NVGLUframebuffer *fb;
        Image(NVGcontext * ctx, int width, int height) : IImage(width, height), ctx(ctx)
        {
            //fb = nvgluCreateFramebufferMS(ctx, width, height, 4, NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY);
            fb = nvgluCreateFramebuffer(ctx, width, height, 0);
        }

        void Clear(const Shoegaze2::Color &clearColor) override
        {
            SetCurrent();
            glViewport(0, 0, width, height);
            glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
            glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        }

        void StartDraw()
        {
            SetCurrent();
            nvgBeginFrame(ctx, (float)width, (float)height, 1.0f);
        }

        void EndDraw()
        {
            nvgEndFrame(ctx);
        }

        void ReadData() override {}
        void WriteData() override {}

        void SetCurrent()
        {
            nvgluBindFramebuffer(fb);
        }

        ~Image() override
        {
            nvgluDeleteFramebuffer(fb);
        }

    protected:
        void SetCurrent(Shoegaze2::IRenderingContext *ctx) override
        {
            SetCurrent();
        }
    };
};

#endif //SHOEGAZE2_IMAGE_H
