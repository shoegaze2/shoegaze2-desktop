//
// Created by iashi on 13.02.2022.
//

#include <Shoegaze2Desktop/GUI/RenderingContext.h>

#include <utility>

using namespace Shoegaze2Desktop;

Canvas::Canvas(RenderingContext *ctx, Shoegaze2::Position pos, Shoegaze2::Size size, std::shared_ptr<ICanvas> parent) : ICanvas(ctx, pos, size, std::move(parent)), ctx(ctx)
{
}

std::shared_ptr<Shoegaze2::IPath> Canvas::CreatePath()
{
    return std::make_shared<Path>(ctx->GetVGContext());
}

std::shared_ptr<Shoegaze2::IBrush> Canvas::CreateBrush()
{
    return std::make_shared<Brush>(ctx->GetVGContext());
}

std::shared_ptr<Shoegaze2::IPaint> Canvas::CreatePaint()
{
    return std::make_shared<Paint>();
}

void Canvas::MakeCurrent()
{
    Shoegaze2::ICanvas::MakeCurrent();
}
