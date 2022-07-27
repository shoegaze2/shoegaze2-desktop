#pragma once

#include <Shoegaze2/System/Interface/GUI/IBrush.h>

#include <nanovg.h>

namespace Shoegaze2Desktop
{
    class Brush : public Shoegaze2::IBrush
    {
        private:
            NVGcontext *vg;
        public:
            Brush(NVGcontext *vg)
            {
                this->vg = vg;
            }

            void SetCurrent() override
            {
                //if (paint != nullptr)
                    //paint->SetCurrent();
                nvgStrokeWidth(vg, strokeWidth);
            }
    };
}