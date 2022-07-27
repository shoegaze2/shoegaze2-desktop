//
// Created by user on 27.07.2022.
//

#include "Mouse.h"
#include <Shoegaze2Desktop/GUI/UISystem.h>

using namespace Shoegaze2Desktop;

void Mouse::positionCallback(GLFWwindow* window, double x, double y) {
    auto ui = static_cast<UISystem*>(glfwGetWindowUserPointer(window));
    MouseEventArgs args;
    args.x = x;
    args.y = y;
    args.eventType = Move;
    ui->GetMouse()->OnEvent.Invoke(args);
}

void Mouse::buttonCallback(GLFWwindow* window, int button, int action, int mods) {
    auto ui = static_cast<UISystem*>(glfwGetWindowUserPointer(window));
    MouseEventArgs args;
    args.x = 0; // TODO: set with the latest mouse position
    args.y = 0;
    args.eventType = (action == GLFW_PRESS) ? Press : Release;

    MouseButton mouseButton = Left;
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            mouseButton = Left;
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            mouseButton = Right;
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            mouseButton = Middle;
    }
    args.button = mouseButton;
    ui->GetMouse()->OnEvent.Invoke(args);
}