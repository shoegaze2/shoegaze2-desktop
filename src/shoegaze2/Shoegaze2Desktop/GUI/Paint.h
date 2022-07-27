#pragma once

#include <Shoegaze2/System/Interface/GUI/IPaint.h>
#include <nanovg.h>

namespace Shoegaze2Desktop
{
    class Paint : public Shoegaze2::IPaint
    {
    public:
        Paint() : IPaint()
        {

        }

        Paint(const Shoegaze2::Color &color) : IPaint(color)
        {

        }
    };
}