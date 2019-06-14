#pragma once
#include "ECSManager.h"
#include "InputManager_DX.h"
#include "Components.h"
#include "ISystem.h"
#include "Vector4.h"

class RayCubeCollisionSystem : public ISystem
{
private:
	std::shared_ptr<ECSManager> mEcsManager = ECSManager::Instance();

#ifdef DIRECTX
	std::shared_ptr<InputManager_DX> mInputManager = InputManager_DX::Instance();
#elif OPENGL
	std::shared_ptr<InputManager_GL> mInputManager = InputManager_GL::Instance();
#endif

	std::vector<Entity> mRays;

public:
	RayCubeCollisionSystem();
	virtual ~RayCubeCollisionSystem();

	void AssignEntity(const Entity& pEntity) override;
	void ReassignEntity(const Entity& pEntity) override;
	void Process() override;
};