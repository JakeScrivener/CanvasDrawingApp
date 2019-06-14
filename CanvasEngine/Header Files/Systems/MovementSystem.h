#pragma once
#include "ECSManager.h"
#include "SceneManager.h"
#include "Components.h"
#include "ISystem.h"
#include "Vector4.h"

class MovementSystem : public ISystem
{
private:
	const float mGravityAccel = -9.81f;

	std::shared_ptr<ECSManager> mEcsManager = ECSManager::Instance();
	std::shared_ptr<SceneManager> mSceneManager = SceneManager::Instance();
public:
	MovementSystem();
	virtual ~MovementSystem();

	void AssignEntity(const Entity& pEntity) override;
	void Process() override;
};