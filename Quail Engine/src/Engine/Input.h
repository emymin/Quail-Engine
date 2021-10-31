#pragma once
#include <iostream>
#include "GLHeaders.h"


enum KeyAction : int {
	PRESS = GLFW_PRESS,
	RELEASE = GLFW_RELEASE,
	REPEAT = GLFW_REPEAT
};

enum Key : int{
	Unknown = GLFW_KEY_UNKNOWN,
	LeftShift = GLFW_KEY_LEFT_SHIFT,
	RightShift = GLFW_KEY_RIGHT_SHIFT,
	LeftCtrl = GLFW_KEY_LEFT_CONTROL,
	RightCtrl = GLFW_KEY_RIGHT_CONTROL,
	LeftAlt = GLFW_KEY_LEFT_ALT,
	RightAlt = GLFW_KEY_RIGHT_ALT,
	LeftSuper = GLFW_KEY_LEFT_SUPER,
	RightSuper = GLFW_KEY_RIGHT_SUPER,
	Enter = GLFW_KEY_ENTER,
	Esc = GLFW_KEY_ESCAPE,
	Up = GLFW_KEY_UP,
	Down = GLFW_KEY_DOWN,
	Left = GLFW_KEY_LEFT,
	Right = GLFW_KEY_RIGHT,
	Home = GLFW_KEY_HOME,
	End = GLFW_KEY_END,
	PageUp = GLFW_KEY_PAGE_UP,
	PageDown = GLFW_KEY_PAGE_DOWN,
	Backspace = GLFW_KEY_BACKSPACE,
	Insert = GLFW_KEY_INSERT,
	Delete = GLFW_KEY_DELETE,
	F1 = GLFW_KEY_F1,
	F2 = GLFW_KEY_F2,
	F3 = GLFW_KEY_F3,
	F4 = GLFW_KEY_F4,
	F5 = GLFW_KEY_F5,
	F6 = GLFW_KEY_F6,
	F7 = GLFW_KEY_F7,
	F8 = GLFW_KEY_F8,
	F9 = GLFW_KEY_F9,
	F10 = GLFW_KEY_F10,
	F11 = GLFW_KEY_F11,
	F12 = GLFW_KEY_F12,
	Space = GLFW_KEY_SPACE,
	Tab = GLFW_KEY_TAB,
	Quote = GLFW_KEY_APOSTROPHE,
	Comma = GLFW_KEY_COMMA,
	Period = GLFW_KEY_PERIOD,
	Minus = GLFW_KEY_MINUS,
	Slash = GLFW_KEY_SLASH,
	Semicolon = GLFW_KEY_SEMICOLON,
	Equal = GLFW_KEY_EQUAL,
	LeftBracket = GLFW_KEY_LEFT_BRACKET,
	RightBracket = GLFW_KEY_RIGHT_BRACKET, 
	Backslash = GLFW_KEY_BACKSLASH,
	Backquote = GLFW_KEY_GRAVE_ACCENT, 
	World1 = GLFW_KEY_WORLD_1,
	World2 = GLFW_KEY_WORLD_2,
	Zero = GLFW_KEY_0,
	One = GLFW_KEY_1,
	Two = GLFW_KEY_2,
	Three = GLFW_KEY_3,
	Four = GLFW_KEY_4,
	Five = GLFW_KEY_5,
	Six = GLFW_KEY_6,
	Seven = GLFW_KEY_7,
	Eight = GLFW_KEY_8,
	Nine = GLFW_KEY_9,
	A = GLFW_KEY_A,
	B = GLFW_KEY_B,
	C = GLFW_KEY_C,
	D = GLFW_KEY_D,
	E = GLFW_KEY_E,
	F = GLFW_KEY_F,
	G = GLFW_KEY_G,
	H = GLFW_KEY_H,
	I = GLFW_KEY_I,
	J = GLFW_KEY_J,
	K = GLFW_KEY_K,
	L = GLFW_KEY_L,
	M = GLFW_KEY_M,
	N = GLFW_KEY_N,
	O = GLFW_KEY_O,
	P = GLFW_KEY_P,
	Q = GLFW_KEY_Q,
	R = GLFW_KEY_R,
	S = GLFW_KEY_S,
	T = GLFW_KEY_T,
	U = GLFW_KEY_U,
	V = GLFW_KEY_V,
	W = GLFW_KEY_W,
	X = GLFW_KEY_X,
	Y = GLFW_KEY_Y,
	Z = GLFW_KEY_Z,
	CapsLock = GLFW_KEY_CAPS_LOCK,
	ScrollLock = GLFW_KEY_SCROLL_LOCK,
	NumLock = GLFW_KEY_NUM_LOCK,
	PrintScreen = GLFW_KEY_PRINT_SCREEN,
	Pause = GLFW_KEY_PAUSE,
	Menu = GLFW_KEY_MENU,
	NumZero = GLFW_KEY_KP_0,
	NumOne = GLFW_KEY_KP_1,
	NumTwo = GLFW_KEY_KP_2,
	NumThree = GLFW_KEY_KP_3,
	NumFour = GLFW_KEY_KP_4,
	NumFive = GLFW_KEY_KP_5,
	NumSix = GLFW_KEY_KP_6,
	NumSeven = GLFW_KEY_KP_7,
	NumEight = GLFW_KEY_KP_8,
	NumNine = GLFW_KEY_KP_9,
	NumDecimal = GLFW_KEY_KP_DECIMAL,
	NumDivide = GLFW_KEY_KP_DIVIDE,
	NumMultiply = GLFW_KEY_KP_MULTIPLY,
	NumSubtract = GLFW_KEY_KP_SUBTRACT,
	NumAdd = GLFW_KEY_KP_ADD,
	NumEnter = GLFW_KEY_KP_ENTER,
	NumEqual = GLFW_KEY_KP_EQUAL
};


class KeyEvent
{
public:
	KeyEvent(int key,int action) :key((Key)key), action((KeyAction)action) {}
	Key key;
	KeyAction action;
	static std::string GetName(Key key) {
		const char* key_name = glfwGetKeyName(key, 0);
		return std::string(key_name);
	}
};

class MouseInfo {
public:
	double xPos;
	double yPos;
	MouseInfo(){}
	MouseInfo(double x, double y) :xPos(x), yPos(y) {}
};