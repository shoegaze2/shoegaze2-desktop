#include <iostream>

#include <Shoegaze2Desktop/GUI/DisplayDevice.h>
#include <Shoegaze2Desktop/GUI/RenderingContext.h>
#include <Shoegaze2/System/System.h>
#include <Shoegaze2/Apps/DemoApp/DemoApp.h>
#include <Shoegaze2Desktop/GUI/UISystem.h>

using namespace Shoegaze2Desktop;
using namespace Shoegaze2;

int main() {
    UISystem ui;
    System system(&ui);

    auto ctx = ui.GetDisplay()->GetRenderingContext();
    auto window = ui.GetDisplay()->GetWindow();
    Font font("fonts/Montserrat-BoldItalic.ttf");
    Font::DEFAULT = &font;

    glfwMakeContextCurrent(window);
    glfwSetTime(0);
    system.LaunchApp<DemoApp>();

    std::cout << "Shoegaze2 :: Hello World!" << std::endl;

    while (!glfwWindowShouldClose(window)) {
        system.Update();

        ctx->StartFrame();
        ctx->Clear();
        system.Render();
        ctx->EndFrame();
        ctx->SwapBuffers();

        /* Poll for and process events */
        glfwPollEvents();
    }
}
