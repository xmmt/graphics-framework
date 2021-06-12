#include <Display.hpp>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace GraphicsFramework {

class DisplayWin32 : public Display {
public:
    DisplayWin32(std::string title, HINSTANCE hInstance, InputDevice& inputDevice);
    ~DisplayWin32() override = default;

public:
    void runLoop(std::function<void(float)> runFrame) const override;

public:
    Size size() const override;
    void show() override;
    void setTitle(std::string title) override;

    HWND hWnd() const;

private:
    static LRESULT CALLBACK wndProc_(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

private:
    HINSTANCE hInstance_;
    HWND hWnd_{};
    WNDCLASSEX wc_{};
};

} // namespace GraphicsFramework