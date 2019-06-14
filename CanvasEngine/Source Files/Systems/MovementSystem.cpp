#include "MovementSystem.h"

/// <summary>
/// 
/// </summary>
MovementSystem::MovementSystem() : ISystem(ComponentType::COMPONENT_TRANSFORM | ComponentType::COMPONENT_VELOCITY)
{

}

/// <summary>
/// 
/// </summary>
MovementSystem::~MovementSystem()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="pEntity"></param>
void MovementSystem::AssignEntity(const Entity & pEntity)
{
	//Finds if an entity that matches given entities ID exists and returns it
	auto entity = find_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mID == pEntity.mID; });

	if ((pEntity.mComponentMask & mMask) == mMask)
	{
		//If entity is not already assigned to this system add it to list
		if (entity == mEntities.end())
		{
			mEntities.push_back(pEntity);
		}
		//If entity is already assigned to this system update it's mask
		else
		{
			entity->mComponentMask = pEntity.mComponentMask;
		}
	}
	//If entity mask does not match system mask, remove from list
	else
	{
		mEntities.erase(remove_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mID == pEntity.mID; }), mEntities.end());
	}
}

/// <summary>
/// 
/// </summary>
void MovementSystem::Process()
{
	for(const Entity& entity : mEntities)
	{		
		//Check if entity has gravity component
		if ((entity.mComponentMask & ComponentType::COMPONENT_GRAVITY) == ComponentType::COMPONENT_GRAVITY)
		{
			//Modify velocity by gravity acceleration
			mEcsManager->VelocityComp(entity.mID)->mVelocity.Y += mGravityAccel * static_cast<float>(mSceneManager->DeltaTime());
		}

		//Modify velocity by acceleration
		mEcsManager->VelocityComp(entity.mID)->mVelocity += mEcsManager->VelocityComp(entity.mID)->mAcceleration * static_cast<float>(mSceneManager->DeltaTime());

		//Clamp velocity magnitude to max speed of entity
		if (mEcsManager->VelocityComp(entity.mID)->mVelocity.Magnitude() > mEcsManager->VelocityComp(entity.mID)->maxSpeed)
		{
			mEcsManager->VelocityComp(entity.mID)->mVelocity.Clamp(mEcsManager->VelocityComp(entity.mID)->maxSpeed);
		}

		//Modify translation by velocity
		mEcsManager->TransformComp(entity.mID)->mTranslation += mEcsManager->VelocityComp(entity.mID)->mVelocity * static_cast<float>(mSceneManager->DeltaTime());
	}
}
