#include "InputManager_DX.h"
#include "KodeBoldsMath.h"
#include "Vector2.h"
#include "AntTweakManager.h"

InputManager_DX::InputManager_DX() : InputManager()
{
	mKeyboard = std::make_shared<DirectX::Keyboard>();
	mMouse = std::make_shared<DirectX::Mouse>();
}

InputManager_DX::~InputManager_DX()
{
}

std::shared_ptr<InputManager_DX> InputManager_DX::Instance()
{
	static std::shared_ptr<InputManager_DX> instance{ new InputManager_DX };
	return instance;
}

void InputManager_DX::CenterCursor()
{
	//SetCursorPos(CLIENT_WIDTH / 2, CLIENT_HEIGHT / 2);
}

void InputManager_DX::CursorVisible(const bool pVisible)
{
	mMouse->SetVisible(pVisible);
}

////--------------------------------------------------------------------------------------
//// Called every time the application receives a message
////--------------------------------------------------------------------------------------
LRESULT CALLBACK InputManager_DX::WndProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
		// Send event message to AntTweakBar
	//if (TwEventWin(hWnd, message, wParam, lParam))
		//return 0; // Event has been handled by AntTweakBar

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_ACTIVATEAPP:
		DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
		DirectX::Mouse::ProcessMessage(message, wParam, lParam);
		break;

		// MOUSE
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		DirectX::Mouse::ProcessMessage(message, wParam, lParam);
		break;

		// KEYBOARD
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void InputManager_DX::Update()
{
	mKeyPresses.clear();

	mKeyboardState = mKeyboard->GetState();
	mKeyboardTracker.Update(mKeyboardState);

	mMouseState = mMouse->GetState();
	mMouseTracker.Update(mMouseState);

	//Mouse position
	mMousePosition = KodeBoldsMath::Vector2(static_cast<float>(mMouse->GetState().x), static_cast<float>(mMouse->GetState().y));

	//Scroll wheel
	mMouseWheelValue = mMouse->GetState().scrollWheelValue;

	HeldDownKeys(); // Registers every frame that a key is pressed
	SinglePressKeys(); // Registers once
	ReleasedKeys();
}


void InputManager_DX::ReleasedKeys()
{
	//Letters
	if (mKeyboardTracker.released.A)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_A, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.B)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_B, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.C)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_C, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.D)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_D, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.E)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_E, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.F)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.G)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_G, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.H)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_H, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.I)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_I, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.J)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_J, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.K)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_K, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.L)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_L, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.M)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_M, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.N)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_N, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.O)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_O, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.P)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_P, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.Q)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_Q, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.R)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_R, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.S)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_S, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.T)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_T, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.U)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_U, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.V)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_V, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.W)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_W, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.X)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_X, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.Y)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_Y, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.Z)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_Z, KEY_STATE::KEY_UP));
	}

	//Numpad
	if (mKeyboardTracker.released.NumPad0)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_0, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.NumPad1)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_1, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.NumPad2)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_2, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.NumPad3)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_3, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.NumPad4)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_4, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.NumPad5)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_5, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.NumPad6)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_6, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.NumPad7)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_7, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.NumPad8)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_8, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.NumPad9)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_9, KEY_STATE::KEY_UP));
	}

	//Numbers
	if (mKeyboardTracker.released.D0)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_0, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.D1)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_1, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.D2)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_2, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.D3)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_3, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.D4)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_4, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.D5)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_5, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.D6)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_6, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.D7)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_7, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.D8)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_8, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.D9)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_9, KEY_STATE::KEY_UP));
	}

	//Maths symbols
	if (mKeyboardTracker.released.Add)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_ADD, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.Subtract)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_SUBTRACT, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.Multiply)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_MULTIPLY, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.Divide)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_DIVIDE, KEY_STATE::KEY_UP));
	}

	//Arrow keys
	if (mKeyboardTracker.released.Up)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_UP_ARROW, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.Left)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_LEFT_ARROW, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.Right)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_RIGHT_ARROW, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.Down)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_DOWN_ARROW, KEY_STATE::KEY_UP));
	}

	//F keys
	if (mKeyboardTracker.released.F1)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F1, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.F2)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F2, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.F3)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F3, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.F4)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F4, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.F5)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F5, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.F6)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F6, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.F7)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F7, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.F8)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F8, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.F9)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F9, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.F10)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F10, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.F11)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F11, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.F12)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F12, KEY_STATE::KEY_UP));
	}

	//Other keys
	if (mKeyboardTracker.released.Back)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_BACKSPACE, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.CapsLock)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_CAPS_LOCK, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.Delete)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_DELETE, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.Enter)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_ENTER, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.Escape)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_ESC, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.LeftAlt)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_LEFT_ALT, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.LeftControl)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_LEFT_CTRL, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.LeftShift)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_LEFT_SHIFT, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.LeftWindows)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_LEFT_WINDOWS, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.RightAlt)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_RIGHT_ALT, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.RightControl)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_RIGHT_CTRL, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.RightShift)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_RIGHT_SHIFT, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.RightWindows)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_RIGHT_WINDOWS, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.Space)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_SPACE, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.Tab)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_TAB, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.OemPeriod)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_PERIOD, KEY_STATE::KEY_UP));
	}
	if (mKeyboardTracker.released.OemComma)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_COMMA, KEY_STATE::KEY_UP));
	}

	using ButtonState = DirectX::Mouse::ButtonStateTracker::ButtonState;
	
	//Mouse buttons up
	if (mMouseTracker.leftButton == ButtonState::RELEASED)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::MOUSE_BUTTON_LEFT, KEY_STATE::KEY_UP));
	}
	if (mMouseTracker.rightButton == ButtonState::RELEASED)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::MOUSE_BUTTON_RIGHT, KEY_STATE::KEY_UP));
	}
	if (mMouseTracker.middleButton == ButtonState::RELEASED)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::MOUSE_BUTTON_MIDDLE, KEY_STATE::KEY_UP));
	}
}

void InputManager_DX::SinglePressKeys()
{
	//Letters
	if (mKeyboardTracker.pressed.A)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_A, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.B)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_B, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.C)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_C, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.D)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_D, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.E)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_E, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.F)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.G)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_G, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.H)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_H, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.I)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_I, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.J)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_J, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.K)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_K, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.L)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_L, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.M)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_M, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.N)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_N, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.O)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_O, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.P)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_P, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.Q)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_Q, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.R)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_R, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.S)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_S, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.T)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_T, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.U)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_U, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.V)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_V, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.W)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_W, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.X)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_X, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.Y)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_Y, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.Z)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_Z, KEY_STATE::KEY_DOWN));
	}

	//Numpad
	if (mKeyboardTracker.pressed.NumPad0)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_0, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.NumPad1)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_1, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.NumPad2)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_2, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.NumPad3)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_3, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.NumPad4)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_4, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.NumPad5)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_5, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.NumPad6)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_6, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.NumPad7)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_7, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.NumPad8)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_8, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.NumPad9)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_9, KEY_STATE::KEY_DOWN));
	}

	//Numbers
	if (mKeyboardTracker.pressed.D0)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_0, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.D1)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_1, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.D2)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_2, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.D3)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_3, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.D4)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_4, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.D5)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_5, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.D6)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_6, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.D7)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_7, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.D8)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_8, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.D9)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_9, KEY_STATE::KEY_DOWN));
	}

	//Maths symbols
	if (mKeyboardTracker.pressed.Add)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_ADD, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.Subtract)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_SUBTRACT, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.Multiply)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_MULTIPLY, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.Divide)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_DIVIDE, KEY_STATE::KEY_DOWN));
	}

	//Arrow keys
	if (mKeyboardTracker.pressed.Up)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_UP_ARROW, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.Left)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_LEFT_ARROW, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.Right)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_RIGHT_ARROW, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.Down)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_DOWN_ARROW, KEY_STATE::KEY_DOWN));
	}

	//F keys
	if (mKeyboardTracker.pressed.F1)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F1, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.F2)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F2, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.F3)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F3, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.F4)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F4, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.F5)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F5, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.F6)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F6, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.F7)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F7, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.F8)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F8, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.F9)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F9, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.F10)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F10, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.F11)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F11, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.F12)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F12, KEY_STATE::KEY_DOWN));
	}

	//Other keys
	if (mKeyboardTracker.pressed.Back)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_BACKSPACE, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.CapsLock)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_CAPS_LOCK, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.Delete)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_DELETE, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.Enter)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_ENTER, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.Escape)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_ESC, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.LeftAlt)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_LEFT_ALT, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.LeftControl)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_LEFT_CTRL, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.LeftShift)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_LEFT_SHIFT, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.LeftWindows)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_LEFT_WINDOWS, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.RightAlt)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_RIGHT_ALT, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.RightControl)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_RIGHT_CTRL, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.RightShift)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_RIGHT_SHIFT, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.RightWindows)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_RIGHT_WINDOWS, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.Space)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_SPACE, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.pressed.Tab)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_TAB, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.released.OemPeriod)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_PERIOD, KEY_STATE::KEY_DOWN));
	}
	if (mKeyboardTracker.released.OemComma)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_COMMA, KEY_STATE::KEY_DOWN));
	}

	using ButtonState = DirectX::Mouse::ButtonStateTracker::ButtonState;
	//Mouse buttons down
	if (mMouseTracker.leftButton == ButtonState::PRESSED)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::MOUSE_BUTTON_LEFT, KEY_STATE::KEY_DOWN));
	}
	if (mMouseTracker.rightButton == ButtonState::PRESSED)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::MOUSE_BUTTON_RIGHT, KEY_STATE::KEY_DOWN));
	}
	if (mMouseTracker.middleButton == ButtonState::PRESSED)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::MOUSE_BUTTON_MIDDLE, KEY_STATE::KEY_DOWN));
	}
}

void InputManager_DX::HeldDownKeys()
{
	//Letters
	if (mKeyboardState.A)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_A, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.B)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_B, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.C)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_C, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.D)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_D, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.E)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_E, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.F)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.G)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_G, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.H)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_H, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.I)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_I, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.J)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_J, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.K)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_K, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.L)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_L, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.M)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_M, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.N)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_N, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.O)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_O, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.P)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_P, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.Q)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_Q, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.R)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_R, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.S)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_S, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.T)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_T, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.U)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_U, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.V)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_V, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.W)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_W, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.X)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_X, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.Y)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_Y, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.Z)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_Z, KEY_STATE::KEY_HELD));
	}

	//Numpad
	if (mKeyboardState.NumPad0)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_0, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.NumPad1)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_1, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.NumPad2)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_2, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.NumPad3)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_3, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.NumPad4)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_4, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.NumPad5)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_5, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.NumPad6)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_6, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.NumPad7)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_7, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.NumPad8)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_8, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.NumPad9)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::NUM_PAD_KEY_9, KEY_STATE::KEY_HELD));
	}

	//Numbers
	if (mKeyboardState.D0)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_0, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.D1)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_1, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.D2)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_2, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.D3)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_3, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.D4)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_4, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.D5)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_5, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.D6)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_6, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.D7)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_7, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.D8)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_8, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.D9)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_9, KEY_STATE::KEY_HELD));
	}

	//Arrow keys
	if (mKeyboardState.Up)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_UP_ARROW, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.Left)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_LEFT_ARROW, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.Right)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_RIGHT_ARROW, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.Down)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_DOWN_ARROW, KEY_STATE::KEY_HELD));
	}

	//Maths symbols
	if (mKeyboardState.Multiply)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_MULTIPLY, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.Subtract)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_SUBTRACT, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.Add)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_ADD, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.Divide)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_DIVIDE, KEY_STATE::KEY_HELD));
	}

	//F keys
	if (mKeyboardState.F1)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F1, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.F2)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F2, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.F3)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F3, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.F4)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F4, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.F5)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F5, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.F6)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F6, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.F7)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F7, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.F8)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F8, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.F9)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F9, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.F10)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F10, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.F11)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F11, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.F12)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_F12, KEY_STATE::KEY_HELD));
	}

	//Other keys
	if (mKeyboardState.Back)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_BACKSPACE, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.CapsLock)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_CAPS_LOCK, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.Delete)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_DELETE, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.Enter)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_ENTER, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.Escape)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_ESC, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.LeftAlt)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_LEFT_ALT, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.LeftControl)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_LEFT_CTRL, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.LeftShift)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_LEFT_SHIFT, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.LeftWindows)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_LEFT_WINDOWS, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.RightAlt)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_RIGHT_ALT, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.RightControl)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_RIGHT_CTRL, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.RightShift)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_RIGHT_SHIFT, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.RightWindows)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_RIGHT_WINDOWS, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.Space)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_SPACE, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.Tab)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_TAB, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.OemPeriod)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_PERIOD, KEY_STATE::KEY_HELD));
	}
	if (mKeyboardState.OemComma)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::KEY_COMMA, KEY_STATE::KEY_HELD));
	}

	//Mouse buttons held
	if (mMouseState.leftButton)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::MOUSE_BUTTON_LEFT, KEY_STATE::KEY_HELD));
	}
	if (mMouseState.rightButton)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::MOUSE_BUTTON_RIGHT, KEY_STATE::KEY_HELD));
	}
	if (mMouseState.middleButton)
	{
		mKeyPresses.emplace_back(std::pair<KEY, KEY_STATE>(KEY::MOUSE_BUTTON_MIDDLE, KEY_STATE::KEY_HELD));
	}
}