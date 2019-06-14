#include "RayCubeCollisionSystem.h"

/// <summary>
/// 
/// </summary>
RayCubeCollisionSystem::RayCubeCollisionSystem() : ISystem(ComponentType::COMPONENT_BOXCOLLIDER)
{
	mEntities = std::vector<Entity>(200000, Entity{ -1, ComponentType::COMPONENT_NONE });
	mRays = std::vector<Entity>(200000, Entity{ -1, ComponentType::COMPONENT_NONE });
}

/// <summary>
/// 
/// </summary>
RayCubeCollisionSystem::~RayCubeCollisionSystem()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="pEntity"></param>
void RayCubeCollisionSystem::AssignEntity(const Entity & pEntity)
{
	if ((pEntity.mComponentMask & mMask) == mMask)
	{
		mEntities[pEntity.mID] = pEntity;
	}
	else if ((pEntity.mComponentMask & ComponentType::COMPONENT_RAYCOLLIDER) == ComponentType::COMPONENT_RAYCOLLIDER)
	{
		mRays[pEntity.mID] = pEntity;
	}
}

void RayCubeCollisionSystem::ReassignEntity(const Entity & pEntity)
{
	if ((pEntity.mComponentMask & mMask) == mMask)
	{
		mEntities[pEntity.mID] = pEntity;
	}
	else if ((pEntity.mComponentMask & ComponentType::COMPONENT_RAYCOLLIDER) == ComponentType::COMPONENT_RAYCOLLIDER)
	{
		mRays[pEntity.mID] = pEntity;
	}
	else
	{
		mEntities[pEntity.mID].mID = -1;
		mEntities[pEntity.mID].mComponentMask = ComponentType::COMPONENT_NONE;
		mRays[pEntity.mID].mID = -1;
		mRays[pEntity.mID].mComponentMask = ComponentType::COMPONENT_NONE;
	}
}

/// <summary>
/// 
/// </summary>
void RayCubeCollisionSystem::Process()
{
	for (const Entity& ray : mRays)
	{
		if (ray.mID == -1)
			continue;

		RayCollider* rayCollider = mEcsManager->RayColliderComp(ray.mID);
		const KodeBoldsMath::Vector3 invDirection(1 / rayCollider->mDirection.X, 1 / rayCollider->mDirection.Y, 1 / rayCollider->mDirection.Z);

		for (const Entity& entity : mEntities)
		{
			if (entity.mID == -1)
				continue;

			//check mouse ray against all collidables
			BoxCollider* boxCollider = mEcsManager->BoxColliderComp(entity.mID);

			float txMin;
			float txMax;

			//check x bounds
			if (invDirection.X >= 0)
			{
				txMin = (boxCollider->mMinBounds.X - rayCollider->mOrigin.X) * invDirection.X;
				txMax = (boxCollider->mMaxBounds.X - rayCollider->mOrigin.X) * invDirection.X;
			}
			else
			{
				txMin = (boxCollider->mMaxBounds.X - rayCollider->mOrigin.X) * invDirection.X;
				txMax = (boxCollider->mMinBounds.X - rayCollider->mOrigin.X) * invDirection.X;
			}

			float highestMin;
			float lowestMax;

			float tyMin;
			float tyMax;

			//check y bounds
			if (invDirection.Y >= 0)
			{
				tyMin = (boxCollider->mMinBounds.Y - rayCollider->mOrigin.Y) * invDirection.Y;
				tyMax = (boxCollider->mMaxBounds.Y - rayCollider->mOrigin.Y) * invDirection.Y;
			}
			else
			{
				tyMin = (boxCollider->mMaxBounds.Y - rayCollider->mOrigin.Y) * invDirection.Y;
				tyMax = (boxCollider->mMinBounds.Y - rayCollider->mOrigin.Y) * invDirection.Y;
			}

			//if no hit then continue
			if (txMin > tyMax || tyMin > txMax)
				continue;

			//update highest min and lowest max
			if (tyMin > txMin)
				highestMin = tyMin;
			else
				highestMin = txMin;

			if (tyMax < txMax)
				lowestMax = tyMax;
			else
				lowestMax = txMax;

			float tzMin;
			float tzMax;

			//check z bounds
			if (invDirection.Z >= 0)
			{
				tzMin = (boxCollider->mMinBounds.Z - rayCollider->mOrigin.Z) * invDirection.Z;
				tzMax = (boxCollider->mMaxBounds.Z - rayCollider->mOrigin.Z) * invDirection.Z;
			}
			else
			{
				tzMin = (boxCollider->mMaxBounds.Z - rayCollider->mOrigin.Z) * invDirection.Z;
				tzMax = (boxCollider->mMinBounds.Z - rayCollider->mOrigin.Z) * invDirection.Z;
			}

			//if no hit then continue
			if (highestMin > tzMax || tzMin > lowestMax)
				continue;

			//update highest min and lowest max
			if (tzMin > highestMin)
				highestMin = tzMin;
			if (tzMax < lowestMax)
				lowestMax = tzMax;

			//Create collision component
			Collision coll{ entity.mID, rayCollider->mOrigin + rayCollider->mDirection * highestMin };
			mEcsManager->AddCollisionComp(coll, ray.mID);
			break;
		}
	}
}
