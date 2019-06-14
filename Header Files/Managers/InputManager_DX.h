#pragma once
#include <windows.h>
#include <Keyboard.h>
#include <DirectXMath.h>
#include <Mouse.h>
#include <memory>
#include "InputManager.h"

class InputManager_DX : public InputManager
{
private:
	InputManager_DX();

	std::shared_ptr<DirectX::Keyboard> mKeyboard;
	DirectX::Keyboard::State mKeyboardState;
	DirectX::Keyboard::KeyboardStateTracker mKeyboardTracker;

	std::shared_ptr<DirectX::Mouse> mMouse;
	DirectX::Mouse::ButtonStateTracker mMouseTracker;
	DirectX::Mouse::State mMouseState;

	void SinglePressKeys() override;
	void ReleasedKeys() override;
	void HeldDownKeys() override;

public:
	static LRESULT CALLBACK WndProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam);
	~InputManager_DX();
	void Update() override;

	//Singleton pattern
	//Deleted copy constructor and assignment operator so no copies of the singleton instance can be made
	InputManager_DX(const InputManager_DX&) = delete;
	InputManager_DX& operator=(const InputManager_DX&) = delete;
	static std::shared_ptr<InputManager_DX> Instance();

	void CenterCursor() override;
	void CursorVisible(const bool pVisible) override;

};