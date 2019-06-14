#pragma once
#include <vector>
#include "Components.h"
#include "Entity.h"

class ISystem
{
protected:
	std::vector<Entity> mEntities;
	const ComponentType mMask;
	ISystem(const ComponentType& pMask) : mMask(pMask) {};

public:
	virtual ~ISystem() {};
	virtual void Process() = 0;
	virtual void AssignEntity(const Entity& pEntity) = 0;
	virtual void ReassignEntity(const Entity& pEntity) = 0;
};