#pragma once
#include <memory>
#include "InputManager.h"

class InputManager_GL : public InputManager
{
private:
	InputManager_GL();

	//std::shared_ptr<DirectX::Keyboard> mKeyboard;
	//DirectX::Keyboard::State mKeyboardState;
	//DirectX::Keyboard::KeyboardStateTracker mKeyboardTracker;

	//std::shared_ptr<DirectX::Mouse> mMouse;
	//DirectX::Mouse::ButtonStateTracker mMouseTracker;
	//DirectX::Mouse::State mMouseState;

	void SinglePressKeys() override;
	void ReleasedKeys() override;
	void HeldDownKeys() override;

public:
	//static LRESULT CALLBACK WndProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam);
	~InputManager_GL();
	void Update() override;

	//Singleton pattern
	//Deleted copy constructor and assignment operator so no copies of the singleton instance can be made
	InputManager_GL(const InputManager_GL&) = delete;
	InputManager_GL& operator=(const InputManager_GL&) = delete;
	static std::shared_ptr<InputManager_GL> Instance();

	void CenterCursor() override;
	void CursorVisible(const bool pVisible) override;
};