#pragma once

#include <Shoegaze2/System/Interface/GUI/ICanvas.h>
#include <Shoegaze2Desktop/GUI/Path.h>
#include <Shoegaze2Desktop/GUI/Brush.h>
#include <Shoegaze2Desktop/GUI/Paint.h>

namespace Shoegaze2Desktop
{
    class RenderingContext;
    class Canvas : public Shoegaze2::ICanvas
    {
    private:
        RenderingContext *ctx;
    public:
        Canvas(RenderingContext *ctx, Shoegaze2::Position pos, Shoegaze2::Size size, std::shared_ptr<Shoegaze2::ICanvas> parent = nullptr);

        std::shared_ptr<Shoegaze2::IPath> CreatePath() override;
        std::shared_ptr<Shoegaze2::IBrush> CreateBrush() override;
        std::shared_ptr<Shoegaze2::IPaint> CreatePaint() override;

        void StartDraw() override
        {

        }

        void EndDraw() override
        {

        }

        void MakeCurrent() override;
    };
}