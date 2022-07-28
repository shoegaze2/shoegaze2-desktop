//
// Created by user on 27.07.2022.
//

#include "Mouse.h"
#include <Shoegaze2Desktop/GUI/UISystem.h>
#include <GLFW/glfw3.h>

using namespace Shoegaze2Desktop;

Mouse::Mouse(GLFWwindow *window) : x(0), y(0) {
    glfwSetCursorPosCallback(window, positionCallback);
    glfwSetMouseButtonCallback(window, buttonCallback);
}

void Mouse::positionCallback(GLFWwindow* window, double x, double y) {
    auto ui = static_cast<UISystem*>(glfwGetWindowUserPointer(window));
    auto mouse = ui->GetMouse();
    MouseEventArgs args;
    mouse->x = args.x = x;
    mouse->y = args.y = y;
    args.eventType = Move;
    ui->GetMouse()->OnEvent.Invoke(args);
}

void Mouse::buttonCallback(GLFWwindow* window, int button, int action, int mods) {
    auto ui = static_cast<UISystem*>(glfwGetWindowUserPointer(window));
    auto mouse = ui->GetMouse();
    MouseEventArgs args;
    args.x = mouse->x; // TODO: set with the latest mouse position
    args.y = mouse->y;
    args.eventType = (action == GLFW_PRESS) ? Press : Release;

    MouseButton mouseButton = None;
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            mouseButton = Left;
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            mouseButton = Right;
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            mouseButton = Middle;
            break;
        default:
            mouseButton = None;
            break;
    }
    args.button = mouseButton;
    ui->GetMouse()->OnEvent.Invoke(args);
}
