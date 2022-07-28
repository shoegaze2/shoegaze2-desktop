//
// Created by user on 27.07.2022.
//

#ifndef SHOEGAZE2_DESKTOP_MOUSE_H
#define SHOEGAZE2_DESKTOP_MOUSE_H

#include <Shoegaze2/System/Interface/Input/IMouse.h>

struct GLFWwindow;

namespace Shoegaze2Desktop {
    class UISystem;
    class Mouse : public Shoegaze2::IMouse {
    private:
        float x, y;
        static void positionCallback(GLFWwindow* window, double x, double y);
        static void buttonCallback(GLFWwindow* window, int button, int action, int mods);
    public:
        explicit Mouse(GLFWwindow* window);
    };
}


#endif //SHOEGAZE2_DESKTOP_MOUSE_H
