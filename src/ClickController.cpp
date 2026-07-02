#include "ClickController.h"

bool ClickController::BindUnderMouse(std::wstring& error) {
    POINT screen_point{};
    if (!GetCursorPos(&screen_point)) {
        error = L"获取鼠标位置失败。";
        return false;
    }
    HWND target = WindowFromPoint(screen_point);
    if (!target) {
        error = L"未找到鼠标所在窗口。";
        return false;
    }
    POINT client_point = screen_point;
    if (!ScreenToClient(target, &client_point)) {
        error = L"坐标转换失败。";
        return false;
    }
    target_window_ = target;
    target_client_point_ = client_point;
    has_target_ = true;
    return true;
}

bool ClickController::ClickBoundTarget(std::wstring& error) {
    if (!has_target_ || !target_window_ || !IsWindow(target_window_)) {
        Reset();
        error = L"原窗口已经失效，请重新绑定。";
        return false;
    }
    POINT screen_point = target_client_point_;
    if (!ClientToScreen(target_window_, &screen_point)) {
        error = L"目标坐标转换失败。";
        return false;
    }
    if (!SetCursorPos(screen_point.x, screen_point.y)) {
        error = L"移动鼠标失败。";
        return false;
    }
    INPUT inputs[2]{};
    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    inputs[1].type = INPUT_MOUSE;
    inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    if (SendInput(2, inputs, sizeof(INPUT)) != 2) {
        error = L"模拟点击失败。";
        return false;
    }
    return true;
}

void ClickController::Reset() {
    target_window_ = nullptr;
    target_client_point_ = POINT{0, 0};
    has_target_ = false;
}
