#include "pch.h"
#include "InputManager.h"

void InputManager::Init(HWND hwnd)
{
    _hwnd = hwnd;
    _keyStates.resize(KEY_TYPE_COUNT, KEY_STATE::NONE);
}

void InputManager::Update()
{
    HWND hwnd = GetActiveWindow();
    if (_hwnd != hwnd)
    {
        for (uint32 key = 0; key < KEY_TYPE_COUNT; ++key)
        {
            _keyStates[key] = KEY_STATE::NONE;
        }

        return;
    }

    BYTE asciiKeys[KEY_TYPE_COUNT] = {};
    if (::GetKeyboardState(asciiKeys) == false)
    {
        return;
    }

    for (uint32 key = 0; key < KEY_TYPE_COUNT; ++key)
    {
        // ASCII 범위 내의 값인지 확인하는 방법 = 0x80 AND 처리하기
        if (asciiKeys[key] & 0x80)
        {
            KEY_STATE& state = _keyStates[key];

            if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
            {
                state = KEY_STATE::PRESS;
            }
            else
            {
                state = KEY_STATE::DOWN;
            }
        }
        else
        {
            KEY_STATE& state = _keyStates[key];

            if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
            {
                state = KEY_STATE::UP;
            }
            else
            {
                state = KEY_STATE::DOWN;
            }
        }
    }

    ::GetCursorPos(&_mousePos);
    ::ScreenToClient(hwnd, &_mousePos);
}