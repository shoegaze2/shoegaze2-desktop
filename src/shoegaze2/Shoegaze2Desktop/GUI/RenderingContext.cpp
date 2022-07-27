
#include <Shoegaze2Desktop/GUI/RenderingContext.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>
#include <nanovg_gl_utils.h>

using namespace Shoegaze2Desktop;

RenderingContext::RenderingContext(GLFWwindow *window) {
    vg = nvgCreateGL3(NVG_STENCIL_STROKES | NVG_DEBUG); //nvglCreate(NVG_AUTOW_DEFAULT | NVG_SRGB);
    this->window = window;
}

void RenderingContext::SetDrawingSurface(std::shared_ptr<Shoegaze2::IImage> image) {
    if (image == nullptr)
        nvgluBindFramebuffer(nullptr);
    else
        nvgluBindFramebuffer(dynamic_cast<Image*>(image.get())->fb);
}
