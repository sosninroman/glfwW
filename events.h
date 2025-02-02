#ifndef GLFWW_EVENTS_H
#define GLFWW_EVENTS_H

#include "defs.h"

namespace glfwW
{

enum class Action
{
    RELEASE,
    PRESS,
    REPEAT
};

int toGlfwAction(Action action);
Action fromGlfwAction(int action);

enum class Key
{
    KEY_UNKNOWN,

    /* Printable keys */
    KEY_SPACE,
    KEY_APOSTROPHE,
    KEY_COMMA,
    KEY_MINUS,
    KEY_PERIOD,
    KEY_SLASH,
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_SEMICOLON,
    KEY_EQUAL,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_LEFT_BRACKET,
    KEY_BACKSLASH,
    KEY_RIGHT_BRACKET,
    KEY_GRAVE_ACCENT,
    KEY_WORLD_1,
    KEY_WORLD_2,

    /* Function keys */
    KEY_ESCAPE,
    KEY_ENTER,
    KEY_TAB,
    KEY_BACKSPACE,
    KEY_INSERT,
    KEY_DELETE,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_DOWN,
    KEY_UP,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,
    KEY_HOME,
    KEY_END,
    KEY_CAPS_LOCK,
    KEY_SCROLL_LOCK,
    KEY_NUM_LOCK,
    KEY_PRINT_SCREEN,
    KEY_PAUSE,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_F13,
    KEY_F14,
    KEY_F15,
    KEY_F16,
    KEY_F17,
    KEY_F18,
    KEY_F19,
    KEY_F20,
    KEY_F21,
    KEY_F22,
    KEY_F23,
    KEY_F24,
    KEY_F25,
    KEY_KP_0,
    KEY_KP_1,
    KEY_KP_2,
    KEY_KP_3,
    KEY_KP_4,
    KEY_KP_5,
    KEY_KP_6,
    KEY_KP_7,
    KEY_KP_8,
    KEY_KP_9,
    KEY_KP_DECIMAL,
    KEY_KP_DIVIDE,
    KEY_KP_MULTIPLY,
    KEY_KP_SUBTRACT,
    KEY_KP_ADD,
    KEY_KP_ENTER,
    KEY_KP_EQUAL,
    KEY_LEFT_SHIFT,
    KEY_LEFT_CONTROL,
    KEY_LEFT_ALT,
    KEY_LEFT_SUPER,
    KEY_RIGHT_SHIFT,
    KEY_RIGHT_CONTROL,
    KEY_RIGHT_ALT,
    KEY_RIGHT_SUPER,
    KEY_MENU,

    KEY_LAST,
};

int toGlfwKey(Key key);
Key fromGlfwKey(int key);

enum KeyModifier
{
    SHIFT,
    CONTROL,
    ALT,
    SUPER,
    CAPS_LOCK,
    NUM_LOCK
};

struct KeyEvent
{
    bool hasModifier(KeyModifier mod)
    {
        if(modifierBits < 0)
        {
            return false;
        }
        switch(mod)
        {
        case KeyModifier::SHIFT:
            return modifierBits | GLFW_MOD_SHIFT;
        case KeyModifier::CONTROL:
            return modifierBits | GLFW_MOD_CONTROL;
        case KeyModifier::ALT:
            return modifierBits | GLFW_MOD_ALT;
        case KeyModifier::SUPER:
            return modifierBits | GLFW_MOD_SUPER;
        case KeyModifier::CAPS_LOCK:
            return modifierBits | GLFW_MOD_CAPS_LOCK;
        case KeyModifier::NUM_LOCK:
            return modifierBits | GLFW_MOD_NUM_LOCK;
        }
    }
    Key key = Key::KEY_UNKNOWN;
    int scancode = -1;
    Action action = Action::PRESS;
    int modifierBits = -1;
};

enum class MouseButton
{
    LEFT_BUTTON,
    RIGHT_BUTTON,
    MIDDLE_BUTTON,
    BUTTON_4,
    BUTTON_5,
    BUTTON_6,
    BUTTON_7,
    BUTTON_8,
};

int toGlfwMouseButton(MouseButton button);
MouseButton fromGlfwMouseButton(int val);

struct MouseButtonEvent
{
    MouseButton button = MouseButton::LEFT_BUTTON;
    Action action = Action::PRESS; // PRESS or RELEASE
    int modifierBits = -1;
};

}

#endif
