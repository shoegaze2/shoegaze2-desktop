//
// Created by user on 27.07.2022.
//

#include "UISystem.h"
#include <iostream>

Shoegaze2Desktop::UISystem::UISystem() {
    display = new DisplayDevice(1500, 1000);
    mouse = nullptr;
    if (!display->Initialize()) return;

    glfwSetWindowUserPointer(display->GetWindow(), this);

    mouse = new Mouse(display->GetWindow());

    mouse->OnEvent = [&](Mouse::MouseEventArgs args) {
        if (args.eventType == Mouse::Release) {
            OnClick.Invoke(Shoegaze2::Position(args.x, args.y));
        }
    };
}

Shoegaze2Desktop::UISystem::~UISystem() {
    delete display;
    delete mouse;
}
