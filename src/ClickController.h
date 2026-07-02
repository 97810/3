#pragma once

#include <windows.h>
#include <string>

class ClickController {
public:
    bool BindUnderMouse(std::wstring& error);
    bool ClickBoundTarget(std::wstring& error);
    void Reset();

    bool HasTarget() const { return has_target_; }
    HWND TargetWindow() const { return target_window_; }
    POINT TargetClientPoint() const { return target_client_point_; }

private:
    HWND target_window_ = nullptr;
    POINT target_client_point_{0, 0};
    bool has_target_ = false;
};
