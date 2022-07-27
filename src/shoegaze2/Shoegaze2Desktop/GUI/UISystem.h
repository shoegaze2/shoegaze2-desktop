//
// Created by user on 27.07.2022.
//

#ifndef SHOEGAZE2_DESKTOP_UISYSTEM_H
#define SHOEGAZE2_DESKTOP_UISYSTEM_H

#include <Shoegaze2/System/Interface/GUI/IUISystem.h>
#include <Shoegaze2Desktop/GUI/DisplayDevice.h>
#include <Shoegaze2Desktop/Input/Mouse.h>

namespace Shoegaze2Desktop {
    class UISystem : public Shoegaze2::IUISystem {
    private:
        DisplayDevice* display;
        Mouse* mouse;
    public:
        UISystem() {
            display = new DisplayDevice(1000, 500);
            mouse = nullptr;
            if (!display->Initialize()) return;

            glfwSetWindowUserPointer(display->GetWindow(), this);

            mouse = new Mouse(display->GetWindow());
        }

        void Update() override {}
        void Render() override {}

        DisplayDevice* GetDisplay() { return display; }
        Mouse* GetMouse() { return mouse; }

        ~UISystem() {
            delete display;

            if (mouse != nullptr)
                delete mouse;
        }
    };
}


#endif //SHOEGAZE2_DESKTOP_UISYSTEM_H
