#pragma once

enum class KEY_TYPE
{
    UP = VK_UP,
    DOWN = VK_DOWN,
    LEFT = VK_LEFT,
    RIGHT = VK_RIGHT,

    W = 'W',
    A = 'A',
    S = 'S',
    D = 'D',

    Q = 'Q',
    E = 'E',
    Z = 'Z',
    C = 'C',

    KEY_1 = '1',
    KEY_2 = '2',
    KEY_3 = '3',
    KEY_4 = '4',

    LBUTTON = VK_LBUTTON,
    RBUTTON = VK_RBUTTON,
};

enum class KEY_STATE
{
    NONE,
    PRESS,
    DOWN,
    UP,
    END
};

enum
{
    KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) + 1,
    KEY_STATE_COUNT = static_cast<int32>(KEY_STATE::END) + 1,
};

class InputManager
{
public:
    void Init(HWND hwnd);
    void Update();

    bool GetButton(KEY_TYPE key) { return _keyStates[static_cast<int32>(key)] == KEY_STATE::PRESS; }
    bool GetButtonDown(KEY_TYPE key) { return _keyStates[static_cast<int32>(key)] == KEY_STATE::DOWN; }
    bool GetButtonUp(KEY_TYPE key) { return _keyStates[static_cast<int32>(key)] == KEY_STATE::UP; }

    const POINT& GetMousePos() { return _mousePos; }

private:
    HWND _hwnd;
    vector<KEY_STATE> _keyStates;
    POINT _mousePos = {};
};