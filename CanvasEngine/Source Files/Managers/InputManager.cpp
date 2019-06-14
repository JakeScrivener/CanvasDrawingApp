#include "InputManager.h"
#include <algorithm>

using namespace KodeBoldsMath;

InputManager::InputManager()
{
}

Vector4 InputManager::MouseWorld(const Matrix4 & pView, const Matrix4 & pProj, const float & pWidth, const float & pHeight) const
{
	//Fix inverse location
	Matrix4 invView = Inverse(pView);
	Matrix4 invProj = Inverse(pProj);

	const Vector4 mousePos( (2.0f * mMousePosition.X) / pWidth - 1.0f, 
							1.0f - (2.0f * mMousePosition.Y) / pHeight,
							1.0f,
							1.0f);

	Vector4 mouseWorld = mousePos * invProj;
	mouseWorld.Z = 1.0f;
	mouseWorld.W = 0.0f;

	mouseWorld *= invView;
	mouseWorld.W = 0.0f;
	
	return mouseWorld.Normalise();
}

InputManager::~InputManager()
{
}

bool InputManager::KeyDown(const KEY & pButton)
{
	const auto key = std::find_if(mKeyPresses.begin(), mKeyPresses.end(), 
		[&](const std::pair<KEY, KEY_STATE>& pKeyDown) {return pKeyDown.first == pButton && pKeyDown.second == KEY_STATE::KEY_DOWN; });

	return (key != mKeyPresses.end());
}

bool InputManager::KeyUp(const KEY & pButton)
{
	const auto key = std::find_if(mKeyPresses.begin(), mKeyPresses.end(),
		[&](const std::pair<KEY, KEY_STATE>& pKeyDown) {return pKeyDown.first == pButton && pKeyDown.second == KEY_STATE::KEY_UP; });

	return (key != mKeyPresses.end());
}

bool InputManager::KeyHeld(const KEY & pButton)
{
	const auto key = std::find_if(mKeyPresses.begin(), mKeyPresses.end(),
		[&](const std::pair<KEY, KEY_STATE>& pKeyDown) {return pKeyDown.first == pButton && pKeyDown.second == KEY_STATE::KEY_HELD; });

	return (key != mKeyPresses.end());
}
