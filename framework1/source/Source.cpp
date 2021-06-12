#include <Utils.hpp>
#include <Triangles.hpp>
#include <RendererDirectX.hpp>
#include <DisplayWin32.hpp>

using namespace GraphicsFramework;

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

int WINAPI WinMain(
  _In_ HINSTANCE hInstance,
  _In_opt_ HINSTANCE hPrevInstance,
  _In_ LPSTR lpCmdline,
  _In_ int nShowCmd) {

#if _DEBUG
    Utils::EnableConsole();
#endif // _DEBUG

    InputDevice inputDevice;
    inputDevice.addOnKeyPressedCallback(InputDevice::Key::W, [] {
        Utils::DebugWrite::info("PRESSED W\n");
    });
    inputDevice.addOnKeyPressedCallback(InputDevice::Key::LEFT_MOUSE_BUTTON, [] {
        Utils::DebugWrite::info("PRESSED LEFT MOUSE BUTTON\n");
    });
    // inputDevice.addOnMouseMoveCallback([](InputDevice::MousePosition position) {
    //     Utils::DebugWrite::info("MOUSE {} {}\n", position.x, position.y);
    // });

    DisplayWin32 display{ "Triangles", hInstance, inputDevice };
    RendererDirectX renderer{ display };

    Triangles triangles{ renderer, inputDevice };
    renderer.init();
    triangles.init();

    triangles.run();

    return 0;
}