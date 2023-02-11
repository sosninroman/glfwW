#include "events.h"

namespace glfwW
{

int toGlfwAction(Action action)
{
    int result = GLFW_PRESS;
    switch(action)
    {
    case Action::PRESS:
        result = GLFW_PRESS;
        break;
    case Action::RELEASE:
        result = GLFW_RELEASE;
        break;
    case Action::REPEAT:
        result = GLFW_REPEAT;
        break;
    }
    return result;
}

Action fromGlfwAction(int action)
{
    if(action == GLFW_PRESS)
    {
        return Action::PRESS;
    }
    else if(action == GLFW_RELEASE)
    {
        return Action::RELEASE;
    }
    else if(action == GLFW_REPEAT)
    {
        return Action::REPEAT;
    }
    return Action::PRESS;
}

int toGlfwKey(Key key)
{
    int result = GLFW_KEY_UNKNOWN;
    switch (key) {
    case Key::KEY_UNKNOWN:
    {
        result = GLFW_KEY_UNKNOWN;
        break;
    }

    /* Printable keys */
    case Key::KEY_SPACE:
    {
        result = GLFW_KEY_SPACE;
        break;
    }
    case Key::KEY_APOSTROPHE:
    {
        result = GLFW_KEY_APOSTROPHE;
        break;
    }
    case Key::KEY_COMMA:
    {
        result = GLFW_KEY_COMMA;
        break;
    }
    case Key::KEY_MINUS:
    {
        result = GLFW_KEY_MINUS;
        break;
    }
    case Key::KEY_PERIOD:
    {
        result = GLFW_KEY_PERIOD;
        break;
    }
    case Key::KEY_SLASH:
    {
        result = GLFW_KEY_SLASH;
        break;
    }
    case Key::KEY_0:
    {
        result = GLFW_KEY_0;
        break;
    }
    case Key::KEY_1:
    {
        result = GLFW_KEY_1;
        break;
    }
    case Key::KEY_2:
    {
        result = GLFW_KEY_2;
        break;
    }
    case Key::KEY_3:
    {
        result = GLFW_KEY_3;
        break;
    }
    case Key::KEY_4:
    {
        result = GLFW_KEY_4;
        break;
    }
    case Key::KEY_5:
    {
        result = GLFW_KEY_5;
        break;
    }
    case Key::KEY_6:
    {
        result = GLFW_KEY_6;
        break;
    }
    case Key::KEY_7:
    {
        result = GLFW_KEY_7;
        break;
    }
    case Key::KEY_8:
    {
        result = GLFW_KEY_8;
        break;
    }
    case Key::KEY_9:
    {
        result = GLFW_KEY_9;
        break;
    }
    case Key::KEY_SEMICOLON:
    {
        result = GLFW_KEY_SEMICOLON;
        break;
    }
    case Key::KEY_EQUAL:
    {
        result = GLFW_KEY_EQUAL;
        break;
    }
    case Key::KEY_A:
    {
        result = GLFW_KEY_A;
        break;
    }
    case Key::KEY_B:
    {
        result = GLFW_KEY_B;
        break;
    }
    case Key::KEY_C:
    {
        result = GLFW_KEY_C;
        break;
    }
    case Key::KEY_D:
    {
        result = GLFW_KEY_D;
        break;
    }
    case Key::KEY_E: {
        result = GLFW_KEY_E;
        break;
    }
    case Key::KEY_F:
    {
        result = GLFW_KEY_F;
        break;
    }
    case Key::KEY_G:
    {
        result = GLFW_KEY_G;
        break;
    }
    case Key::KEY_H:
    {
        result = GLFW_KEY_H;
        break;
    }
    case Key::KEY_I:
    {
        result = GLFW_KEY_I;
        break;
    }
    case Key::KEY_J:
    {
        result = GLFW_KEY_J;
        break;
    }
    case Key::KEY_K:
    {
        result = GLFW_KEY_K;
        break;
    }
    case Key::KEY_L:
    {
        result = GLFW_KEY_L;
        break;
    }
    case Key::KEY_M:
    {
        result = GLFW_KEY_M;
        break;
    }
    case Key::KEY_N:
    {
        result = GLFW_KEY_N;
        break;
    }
    case Key::KEY_O:
    {
        result = GLFW_KEY_O;
        break;
    }
    case Key::KEY_P:
    {
        result = GLFW_KEY_P;
        break;
    }
    case Key::KEY_Q:
    {
        result = GLFW_KEY_Q;
        break;
    }
    case Key::KEY_R:
    {
        result = GLFW_KEY_R;
        break;
    }
    case Key::KEY_S:
    {
        result = GLFW_KEY_S;
        break;
    }
    case Key::KEY_T:
    {
        result = GLFW_KEY_T;
        break;
    }
    case Key::KEY_U:
    {
        result = GLFW_KEY_U;
        break;
    }
    case Key::KEY_V:
    {
        result = GLFW_KEY_V;
        break;
    }
    case Key::KEY_W:
    {
        result = GLFW_KEY_W;
        break;
    }
    case Key::KEY_X:
    {
        result = GLFW_KEY_X;
        break;
    }
    case Key::KEY_Y:
    {
        result = GLFW_KEY_Y;
        break;
    }
    case Key::KEY_Z:
    {
        result = GLFW_KEY_Z;
        break;
    }
    case Key::KEY_LEFT_BRACKET:
    {
        result = GLFW_KEY_LEFT_BRACKET;
        break;
    }
    case Key::KEY_BACKSLASH:
    {
        result = GLFW_KEY_BACKSLASH;
        break;
    }
    case Key::KEY_RIGHT_BRACKET:
    {
        result = GLFW_KEY_RIGHT_BRACKET;
        break;
    }
    case Key::KEY_GRAVE_ACCENT:
    {
        result = GLFW_KEY_GRAVE_ACCENT;
        break;
    }
    case Key::KEY_WORLD_1:
    {
        result = GLFW_KEY_WORLD_1;
        break;
    }
    case Key::KEY_WORLD_2:
    {
        result = GLFW_KEY_WORLD_2;
        break;
    }

    /* Function keys */
    case Key::KEY_ESCAPE:
    {
        result = GLFW_KEY_ESCAPE;
        break;
    }
    case Key::KEY_ENTER:
    {
        result = GLFW_KEY_ENTER;
        break;
    }
    case Key::KEY_TAB:
    {
        result = GLFW_KEY_TAB;
        break;
    }
    case Key::KEY_BACKSPACE:
    {
        result = GLFW_KEY_BACKSPACE;
        break;
    }
    case Key::KEY_INSERT:
    {
        result = GLFW_KEY_INSERT;
        break;
    }
    case Key::KEY_DELETE:
    {
        result = GLFW_KEY_DELETE;
        break;
    }
    case Key::KEY_RIGHT:
    {
        result = GLFW_KEY_RIGHT;
        break;
    }
    case Key::KEY_LEFT:
    {
        result = GLFW_KEY_LEFT;
        break;
    }
    case Key::KEY_DOWN:
    {
        result = GLFW_KEY_DOWN;
        break;
    }
    case Key::KEY_UP:
    {
        result = GLFW_KEY_UP;
        break;
    }
    case Key::KEY_PAGE_UP:
    {
        result = GLFW_KEY_PAGE_UP;
        break;
    }
    case Key::KEY_PAGE_DOWN:
    {
        result = GLFW_KEY_PAGE_DOWN;
        break;
    }
    case Key::KEY_HOME:
    {
        result = GLFW_KEY_HOME;
        break;
    }
    case Key::KEY_END:
    {
        result = GLFW_KEY_END;
        break;
    }
    case Key::KEY_CAPS_LOCK:
    {
        result = GLFW_KEY_CAPS_LOCK;
        break;
    }
    case Key::KEY_SCROLL_LOCK:
    {
        result = GLFW_KEY_SCROLL_LOCK;
        break;
    }
    case Key::KEY_NUM_LOCK: {
        result = GLFW_KEY_NUM_LOCK;
        break;
    }
    case Key::KEY_PRINT_SCREEN:
    {
        result = GLFW_KEY_PRINT_SCREEN;
        break;
    }
    case Key::KEY_PAUSE:
    {
        result = GLFW_KEY_PAUSE;
        break;
    }
    case Key::KEY_F1:
    {
        result = GLFW_KEY_F1;
        break;
    }
    case Key::KEY_F2:
    {
        result = GLFW_KEY_F2;
        break;
    }
    case Key::KEY_F3:
    {
        result = GLFW_KEY_F3;
        break;
    }
    case Key::KEY_F4:
    {
        result = GLFW_KEY_F4;
        break;
    }
    case Key::KEY_F5:
    {
        result = GLFW_KEY_F5;
        break;
    }
    case Key::KEY_F6:
    {
        result = GLFW_KEY_F6;
        break;
    }
    case Key::KEY_F7:
    {
        result = GLFW_KEY_F7;
        break;
    }
    case Key::KEY_F8:
    {
        result = GLFW_KEY_F8;
        break;
    }
    case Key::KEY_F9:
    {
        result = GLFW_KEY_F9;
        break;
    }
    case Key::KEY_F10:
    {
        result = GLFW_KEY_F10;
        break;
    }
    case Key::KEY_F11:
    {
        result = GLFW_KEY_F11;
        break;
    }
    case Key::KEY_F12:
    {
        result = GLFW_KEY_F12;
        break;
    }
    case Key::KEY_F13:
    {
        result = GLFW_KEY_F13;
        break;
    }
    case Key::KEY_F14:
    {
        result = GLFW_KEY_F14;
        break;
    }
    case Key::KEY_F15:
    {
        result = GLFW_KEY_F15;
        break;
    }
    case Key::KEY_F16:
    {
        result = GLFW_KEY_F16;
        break;
    }
    case Key::KEY_F17:
    {
        result = GLFW_KEY_F17;
        break;
    }
    case Key::KEY_F18:
    {
        result = GLFW_KEY_F18;
        break;
    }
    case Key::KEY_F19:
    {
        result = GLFW_KEY_F19;
        break;
    }
    case Key::KEY_F20:
    {
        result = GLFW_KEY_F20;
        break;
    }
    case Key::KEY_F21:
    {
        result = GLFW_KEY_F21;
        break;
    }
    case Key::KEY_F22:
    {
        result = GLFW_KEY_F22;
        break;
    }
    case Key::KEY_F23:
    {
        result = GLFW_KEY_F23;
        break;
    }
    case Key::KEY_F24:
    {
        result = GLFW_KEY_F24;
        break;
    }
    case Key::KEY_F25:
    {
        result = GLFW_KEY_F25;
        break;
    }
    case Key::KEY_KP_0:
    {
        result = GLFW_KEY_KP_0;
        break;
    }
    case Key::KEY_KP_1:
    {
        result = GLFW_KEY_KP_1;
        break;
    }
    case Key::KEY_KP_2:
    {
        result = GLFW_KEY_KP_2;
        break;
    }
    case Key::KEY_KP_3:
    {
        result = GLFW_KEY_KP_3;
        break;
    }
    case Key::KEY_KP_4:
    {
        result = GLFW_KEY_KP_4;
        break;
    }
    case Key::KEY_KP_5:
    {
        result = GLFW_KEY_KP_5;
        break;
    }
    case Key::KEY_KP_6:
    {
        result = GLFW_KEY_KP_6;
        break;
    }
    case Key::KEY_KP_7:
    {
        result = GLFW_KEY_KP_7;
        break;
    }
    case Key::KEY_KP_8:
    {
        result = GLFW_KEY_KP_8;
        break;
    }
    case Key::KEY_KP_9:
    {
        result = GLFW_KEY_KP_9;
        break;
    }
    case Key::KEY_KP_DECIMAL:
    {
        result = GLFW_KEY_KP_DECIMAL;
        break;
    }
    case Key::KEY_KP_DIVIDE: {
        result = GLFW_KEY_KP_DIVIDE;
        break;
    }
    case Key::KEY_KP_MULTIPLY:
    {
        result = GLFW_KEY_KP_MULTIPLY;
        break;
    }
    case Key::KEY_KP_SUBTRACT:
    {
        result = GLFW_KEY_KP_SUBTRACT;
        break;
    }
    case Key::KEY_KP_ADD:
    {
        result = GLFW_KEY_KP_ADD;
        break;
    }
    case Key::KEY_KP_ENTER:
    {
        result = GLFW_KEY_KP_ENTER;
        break;
    }
    case Key::KEY_KP_EQUAL:
    {
        result = GLFW_KEY_KP_EQUAL;
        break;
    }
    case Key::KEY_LEFT_SHIFT:
    {
        result = GLFW_KEY_LEFT_SHIFT;
        break;
    }
    case Key::KEY_LEFT_CONTROL:
    {
        result = GLFW_KEY_LEFT_CONTROL;
        break;
    }
    case Key::KEY_LEFT_ALT:
    {
        result = GLFW_KEY_LEFT_ALT;
        break;
    }
    case Key::KEY_LEFT_SUPER:
    {
        result = GLFW_KEY_LEFT_SUPER;
        break;
    }
    case Key::KEY_RIGHT_SHIFT:
    {
        result = GLFW_KEY_RIGHT_SHIFT;
        break;
    }
    case Key::KEY_RIGHT_CONTROL:
    {
        result = GLFW_KEY_RIGHT_CONTROL;
        break;
    }
    case Key::KEY_RIGHT_ALT:
    {
        result = GLFW_KEY_RIGHT_ALT;
        break;
    }
    case Key::KEY_RIGHT_SUPER:
    {
        result = GLFW_KEY_RIGHT_SUPER;
        break;
    }
    case Key::KEY_MENU:
    {
        result = GLFW_KEY_MENU;
        break;
    }
    case Key::KEY_LAST:
    {
        result = GLFW_KEY_LAST;
    }
    }
    return result;
}

Key fromGlfwKey(int key)
{
    Key result = Key::KEY_UNKNOWN;
    if (key == GLFW_KEY_SPACE) {
        result = Key::KEY_SPACE;
    } else if (key == GLFW_KEY_APOSTROPHE) {
        result = Key::KEY_APOSTROPHE;
    } else if (key == GLFW_KEY_COMMA) {
        result = Key::KEY_COMMA;
    } else if (key == GLFW_KEY_MINUS) {
        result = Key::KEY_MINUS;
    } else if (key == GLFW_KEY_PERIOD) {
        result = Key::KEY_PERIOD;
    } else if (key == GLFW_KEY_SLASH) {
        result = Key::KEY_SLASH;
    } else if (key == GLFW_KEY_0) {
        result = Key::KEY_0;
    } else if (key == GLFW_KEY_1) {
        result = Key::KEY_1;
    } else if (key == GLFW_KEY_2) {
        result = Key::KEY_2;
    } else if (key == GLFW_KEY_3) {
        result = Key::KEY_3;
    } else if (key == GLFW_KEY_4) {
        result = Key::KEY_4;
    } else if (key == GLFW_KEY_5) {
        result = Key::KEY_5;
    } else if (key == GLFW_KEY_6) {
        result = Key::KEY_6;
    } else if (key == GLFW_KEY_7) {
        result = Key::KEY_7;
    } else if (key == GLFW_KEY_8) {
        result = Key::KEY_8;
    } else if (key == GLFW_KEY_9) {
        result = Key::KEY_9;
    } else if (key == GLFW_KEY_SEMICOLON) {
        result = Key::KEY_SEMICOLON;
    } else if (key == GLFW_KEY_EQUAL) {
        result = Key::KEY_EQUAL;
    } else if (key == GLFW_KEY_A) {
        result = Key::KEY_A;
    } else if (key == GLFW_KEY_B) {
        result = Key::KEY_B;
    } else if (key == GLFW_KEY_C) {
        result = Key::KEY_C;
    } else if (key == GLFW_KEY_D) {
        result = Key::KEY_D;
    } else if (key == GLFW_KEY_E) {
        result = Key::KEY_E;
    } else if (key == GLFW_KEY_F) {
        result = Key::KEY_F;
    } else if (key == GLFW_KEY_G) {
        result = Key::KEY_G;
    } else if (key == GLFW_KEY_H) {
        result = Key::KEY_H;
    } else if (key == GLFW_KEY_I) {
        result = Key::KEY_I;
    } else if (key == GLFW_KEY_J) {
        result = Key::KEY_J;
    } else if (key == GLFW_KEY_K) {
        result = Key::KEY_K;
    } else if (key == GLFW_KEY_L) {
        result = Key::KEY_L;
    } else if (key == GLFW_KEY_M) {
        result = Key::KEY_M;
    } else if (key == GLFW_KEY_N) {
        result = Key::KEY_N;
    } else if (key == GLFW_KEY_O) {
        result = Key::KEY_O;
    } else if (key == GLFW_KEY_P) {
        result = Key::KEY_P;
    } else if (key == GLFW_KEY_Q) {
        result = Key::KEY_Q;
    } else if (key == GLFW_KEY_R) {
        result = Key::KEY_R;
    } else if (key == GLFW_KEY_S) {
        result = Key::KEY_S;
    } else if (key == GLFW_KEY_T) {
        result = Key::KEY_T;
    } else if (key == GLFW_KEY_U) {
        result = Key::KEY_U;
    } else if (key == GLFW_KEY_V) {
        result = Key::KEY_V;
    } else if (key == GLFW_KEY_W) {
        result = Key::KEY_W;
    } else if (key == GLFW_KEY_X) {
        result = Key::KEY_X;
    } else if (key == GLFW_KEY_Y) {
        result = Key::KEY_Y;
    } else if (key == GLFW_KEY_Z) {
        result = Key::KEY_Z;
    } else if (key == GLFW_KEY_LEFT_BRACKET) {
        result = Key::KEY_LEFT_BRACKET;
    } else if (key == GLFW_KEY_BACKSLASH) {
        result = Key::KEY_BACKSLASH;
    } else if (key == GLFW_KEY_RIGHT_BRACKET) {
        result = Key::KEY_RIGHT_BRACKET;
    } else if (key == GLFW_KEY_GRAVE_ACCENT) {
        result = Key::KEY_GRAVE_ACCENT;
    } else if (key == GLFW_KEY_WORLD_1) {
        result = Key::KEY_WORLD_1;
    } else if (key == GLFW_KEY_WORLD_2) {
        result = Key::KEY_WORLD_2;
    }

    /* Function keys */
    else if (key == GLFW_KEY_ESCAPE) {
        result = Key::KEY_ESCAPE;
    } else if (key == GLFW_KEY_ENTER) {
        result = Key::KEY_ENTER;
    } else if (key == GLFW_KEY_TAB) {
        result = Key::KEY_TAB;
    } else if (key == GLFW_KEY_BACKSPACE) {
        result = Key::KEY_BACKSPACE;
    } else if (key == GLFW_KEY_INSERT) {
        result = Key::KEY_INSERT;
    } else if (key == GLFW_KEY_DELETE) {
        result = Key::KEY_DELETE;
    } else if (key == GLFW_KEY_RIGHT) {
        result = Key::KEY_RIGHT;
    } else if (key == GLFW_KEY_LEFT) {
        result = Key::KEY_LEFT;
    } else if (key == GLFW_KEY_DOWN) {
        result = Key::KEY_DOWN;
    } else if (key == GLFW_KEY_UP) {
        result = Key::KEY_UP;
    } else if (key == GLFW_KEY_PAGE_UP) {
        result = Key::KEY_PAGE_UP;
    } else if (key == GLFW_KEY_PAGE_DOWN) {
        result = Key::KEY_PAGE_DOWN;
    } else if (key == GLFW_KEY_HOME) {
        result = Key::KEY_HOME;
    } else if (key == GLFW_KEY_END) {
        result = Key::KEY_END;
    } else if (key == GLFW_KEY_CAPS_LOCK) {
        result = Key::KEY_CAPS_LOCK;
    } else if (key == GLFW_KEY_SCROLL_LOCK) {
        result = Key::KEY_SCROLL_LOCK;
    } else if (key == GLFW_KEY_NUM_LOCK) {
        result = Key::KEY_NUM_LOCK;
    } else if (key == GLFW_KEY_PRINT_SCREEN) {
        result = Key::KEY_PRINT_SCREEN;
    } else if (key == GLFW_KEY_PAUSE) {
        result = Key::KEY_PAUSE;
    } else if (key == GLFW_KEY_F1) {
        result = Key::KEY_F1;
    } else if (key == GLFW_KEY_F2) {
        result = Key::KEY_F2;
    } else if (key == GLFW_KEY_F3) {
        result = Key::KEY_F3;
    } else if (key == GLFW_KEY_F4) {
        result = Key::KEY_F4;
    } else if (key == GLFW_KEY_F5) {
        result = Key::KEY_F5;
    } else if (key == GLFW_KEY_F6) {
        result = Key::KEY_F6;
    } else if (key == GLFW_KEY_F7) {
        result = Key::KEY_F7;
    } else if (key == GLFW_KEY_F8) {
        result = Key::KEY_F8;
    } else if (key == GLFW_KEY_F9) {
        result = Key::KEY_F9;
    } else if (key == GLFW_KEY_F10) {
        result = Key::KEY_F10;
    } else if (key == GLFW_KEY_F11) {
        result = Key::KEY_F11;
    } else if (key == GLFW_KEY_F12) {
        result = Key::KEY_F12;
    } else if (key == GLFW_KEY_F13) {
        result = Key::KEY_F13;
    } else if (key == GLFW_KEY_F14) {
        result = Key::KEY_F14;
    } else if (key == GLFW_KEY_F15) {
        result = Key::KEY_F15;
    } else if (key == GLFW_KEY_F16) {
        result = Key::KEY_F16;
    } else if (key == GLFW_KEY_F17) {
        result = Key::KEY_F17;
    } else if (key == GLFW_KEY_F18) {
        result = Key::KEY_F18;
    } else if (key == GLFW_KEY_F19) {
        result = Key::KEY_F19;
    } else if (key == GLFW_KEY_F20) {
        result = Key::KEY_F20;
    } else if (key == GLFW_KEY_F21) {
        result = Key::KEY_F21;
    } else if (key == GLFW_KEY_F22) {
        result = Key::KEY_F22;
    } else if (key == GLFW_KEY_F23) {
        result = Key::KEY_F23;
    } else if (key == GLFW_KEY_F24) {
        result = Key::KEY_F24;
    } else if (key == GLFW_KEY_F25) {
        result = Key::KEY_F25;
    } else if (key == GLFW_KEY_KP_0) {
        result = Key::KEY_KP_0;
    } else if (key == GLFW_KEY_KP_1) {
        result = Key::KEY_KP_1;
    } else if (key == GLFW_KEY_KP_2) {
        result = Key::KEY_KP_2;
    } else if (key == GLFW_KEY_KP_3) {
        result = Key::KEY_KP_3;
    } else if (key == GLFW_KEY_KP_4) {
        result = Key::KEY_KP_4;
    } else if (key == GLFW_KEY_KP_5) {
        result = Key::KEY_KP_5;
    } else if (key == GLFW_KEY_KP_6) {
        result = Key::KEY_KP_6;
    } else if (key == GLFW_KEY_KP_7) {
        result = Key::KEY_KP_7;
    } else if (key == GLFW_KEY_KP_8) {
        result = Key::KEY_KP_8;
    } else if (key == GLFW_KEY_KP_9) {
        result = Key::KEY_KP_9;
    } else if (key == GLFW_KEY_KP_DECIMAL) {
        result = Key::KEY_KP_DECIMAL;
    } else if (key == GLFW_KEY_KP_DIVIDE) {
        result = Key::KEY_KP_DIVIDE;
    } else if (key == GLFW_KEY_KP_MULTIPLY) {
        result = Key::KEY_KP_MULTIPLY;
    } else if (key == GLFW_KEY_KP_SUBTRACT) {
        result = Key::KEY_KP_SUBTRACT;
    } else if (key == GLFW_KEY_KP_ADD) {
        result = Key::KEY_KP_ADD;
    } else if (key == GLFW_KEY_KP_ENTER) {
        result = Key::KEY_KP_ENTER;
    } else if (key == GLFW_KEY_KP_EQUAL) {
        result = Key::KEY_KP_EQUAL;
    } else if (key == GLFW_KEY_LEFT_SHIFT) {
        result = Key::KEY_LEFT_SHIFT;
    } else if (key == GLFW_KEY_LEFT_CONTROL) {
        result = Key::KEY_LEFT_CONTROL;
    } else if (key == GLFW_KEY_LEFT_ALT) {
        result = Key::KEY_LEFT_ALT;
    } else if (key == GLFW_KEY_LEFT_SUPER) {
        result = Key::KEY_LEFT_SUPER;
    } else if (key == GLFW_KEY_RIGHT_SHIFT) {
        result = Key::KEY_RIGHT_SHIFT;
    } else if (key == GLFW_KEY_RIGHT_CONTROL) {
        result = Key::KEY_RIGHT_CONTROL;
    } else if (key == GLFW_KEY_RIGHT_ALT) {
        result = Key::KEY_RIGHT_ALT;
    } else if (key == GLFW_KEY_RIGHT_SUPER) {
        result = Key::KEY_RIGHT_SUPER;
    } else if (key == GLFW_KEY_MENU) {
        result = Key::KEY_MENU;
    }

    return result;
}

int toGlfwMouseButton(MouseButton button)
{
    int result = GLFW_MOUSE_BUTTON_1;
    switch(button)
    {
    case MouseButton::LEFT_BUTTON:
        result = GLFW_MOUSE_BUTTON_1;
        break;
    case MouseButton::RIGHT_BUTTON:
        result = GLFW_MOUSE_BUTTON_2;
        break;
    case MouseButton::MIDDLE_BUTTON:
        result = GLFW_MOUSE_BUTTON_3;
        break;
    case MouseButton::BUTTON_4:
        result = GLFW_MOUSE_BUTTON_4;
        break;
    case MouseButton::BUTTON_5:
        result = GLFW_MOUSE_BUTTON_5;
        break;
    case MouseButton::BUTTON_6:
        result = GLFW_MOUSE_BUTTON_6;
        break;
    case MouseButton::BUTTON_7:
        result = GLFW_MOUSE_BUTTON_7;
        break;
    case MouseButton::BUTTON_8:
        result = GLFW_MOUSE_BUTTON_8;
        break;
    }
    return result;
}

MouseButton fromGlfwMouseButton(int val)
{
    MouseButton result = MouseButton::LEFT_BUTTON;
    if(val == GLFW_MOUSE_BUTTON_1)
    {
        result = MouseButton::LEFT_BUTTON;
    }
    else if(val == GLFW_MOUSE_BUTTON_2)
    {
        result = MouseButton::RIGHT_BUTTON;
    }
    else if(val == GLFW_MOUSE_BUTTON_3)
    {
        result = MouseButton::MIDDLE_BUTTON;
    }
    else if(val == GLFW_MOUSE_BUTTON_4)
    {
        result = MouseButton::BUTTON_4;
    }
    else if(val == GLFW_MOUSE_BUTTON_5)
    {
        result = MouseButton::BUTTON_5;
    }
    else if(val == GLFW_MOUSE_BUTTON_6)
    {
        result = MouseButton::BUTTON_6;
    }
    else if(val == GLFW_MOUSE_BUTTON_7)
    {
        result = MouseButton::BUTTON_7;
    }
    else if(val == GLFW_MOUSE_BUTTON_8)
    {
        result = MouseButton::BUTTON_8;
    }
    return result;
}

}
