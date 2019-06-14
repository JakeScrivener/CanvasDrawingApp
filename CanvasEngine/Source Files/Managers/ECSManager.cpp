#include "ECSManager.h"

using namespace std;

/// <summary>
/// Assigns given entity to all appropriate systems
/// </summary>
/// <param name="pEntity">The given entity to assign to systems</param>
void ECSManager::AssignEntity(const Entity & pEntity)
{
	for (auto & system : mRenderSystems)
	{
		system->AssignEntity(pEntity);
	}

	for (auto & system : mUpdateSystems)
	{
		system->AssignEntity(pEntity);
	}
}

void ECSManager::ReassignEntity(const Entity & pEntity)
{
	for (auto & system : mRenderSystems)
	{
		system->ReassignEntity(pEntity);
	}

	for (auto & system : mUpdateSystems)
	{
		system->ReassignEntity(pEntity);
	}
}

/// <summary>
/// Constructor for ECS Manager
/// Resizes entity and component vectors upon construction to a reasonably large size to avoid performance overhead of resizing
/// </summary>
ECSManager::ECSManager()
	:mNextEntityID(0)
{
	mEntities.reserve(300000);
	mTransforms.resize(300000);
	mVelocities.resize(300000);
	mBoxColliders.resize(300000);
	mSphereColliders.resize(300000);
	mGeometries.resize(300000);
	mTextures.resize(300000);
	mShaders.resize(300000);
	mCameras.resize(300000);
	mLights.resize(300000);
	mGravities.resize(300000);
	mAudios.resize(300000);
	mAIs.resize(300000);
	mRayColliders.resize(300000);
	mCollisions.resize(300000);
	mColours.resize(300000);
	mWeights.resize(300000);
}

/// <summary>
/// Default destructor
/// </summary>
ECSManager::~ECSManager()
{
}

/// <summary>
/// Creates a singleton instance of ECS Manager if one hasn't been created before
/// Returns pointer to the instance of ECS Manager
/// </summary>
/// <returns>Shared pointer to the ECS Manager instance</returns>
std::shared_ptr<ECSManager> ECSManager::Instance()
{
	static std::shared_ptr<ECSManager> instance{ new ECSManager };
	return instance;
}

/// <summary>
/// Creates an entity with the given name
/// Appends (nameCount) to the end of the entity name if entity name is duplicate
/// </summary>
/// <param name="pEntityName">Given name of the entity to create</param>
const int ECSManager::CreateEntity()
{
	int id = mNextEntityID;
	if (mFreeIDs.empty())
	{
		mEntities.emplace_back(Entity{ id, ComponentType::COMPONENT_NONE });
		mNextEntityID++;
		return id;
	}

	id = mFreeIDs.back();
	mEntities[id] = Entity{ id, ComponentType::COMPONENT_NONE };
	mFreeIDs.pop_back();
	return id;
}

/// <summary>
/// Destroys an entity with the given name and all components owned by it
/// </summary>
/// <param name="pEntityName">Given name of the entity to delete</param>
void ECSManager::DestroyEntity(const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	//Removes all components owned by this entity
	//AI Comp
	if ((entity->mComponentMask & ComponentType::COMPONENT_AI) == ComponentType::COMPONENT_AI)
	{
		RemoveAIComp(pEntityID);
	}
	//Audio Comp
	if ((entity->mComponentMask & ComponentType::COMPONENT_AUDIO) == ComponentType::COMPONENT_AUDIO)
	{
		RemoveAudioComp(pEntityID);
	}
	//BoxCollider Comp
	if ((entity->mComponentMask & ComponentType::COMPONENT_BOXCOLLIDER) == ComponentType::COMPONENT_BOXCOLLIDER)
	{
		RemoveBoxColliderComp(pEntityID);
	}
	//Camera Comp
	if ((entity->mComponentMask & ComponentType::COMPONENT_CAMERA) == ComponentType::COMPONENT_CAMERA)
	{
		RemoveCameraComp(pEntityID);
	}
	//Geometry Comp
	if ((entity->mComponentMask & ComponentType::COMPONENT_GEOMETRY) == ComponentType::COMPONENT_GEOMETRY)
	{
		RemoveGeometryComp(pEntityID);
	}
	//Gravity Comp
	if ((entity->mComponentMask & ComponentType::COMPONENT_GRAVITY) == ComponentType::COMPONENT_GRAVITY)
	{
		RemoveGravityComp(pEntityID);
	}
	//Light Comp
	if ((entity->mComponentMask & ComponentType::COMPONENT_LIGHT) == ComponentType::COMPONENT_LIGHT)
	{
		RemoveLightComp(pEntityID);
	}
	//Shader Comp
	if ((entity->mComponentMask & ComponentType::COMPONENT_SHADER) == ComponentType::COMPONENT_SHADER)
	{
		RemoveShaderComp(pEntityID);
	}
	//SphereCollider Comp
	if ((entity->mComponentMask & ComponentType::COMPONENT_SPHERECOLLIDER) == ComponentType::COMPONENT_SPHERECOLLIDER)
	{
		RemoveSphereColliderComp(pEntityID);
	}
	//Texture Comp
	if ((entity->mComponentMask & ComponentType::COMPONENT_TEXTURE) == ComponentType::COMPONENT_TEXTURE)
	{
		RemoveTextureComp(pEntityID);
	}
	//Transform Comp
	if ((entity->mComponentMask & ComponentType::COMPONENT_TRANSFORM) == ComponentType::COMPONENT_TRANSFORM)
	{
		RemoveTransformComp(pEntityID);
	}
	//Velocity Comp
	if ((entity->mComponentMask & ComponentType::COMPONENT_VELOCITY) == ComponentType::COMPONENT_VELOCITY)
	{
		RemoveVelocityComp(pEntityID);
	}
	//RayCollider Comp
	if ((entity->mComponentMask & ComponentType::COMPONENT_RAYCOLLIDER) == ComponentType::COMPONENT_RAYCOLLIDER)
	{
		RemoveRayColliderComp(pEntityID);
	}
	//Collision Comp
	if ((entity->mComponentMask & ComponentType::COMPONENT_COLLISION) == ComponentType::COMPONENT_COLLISION)
	{
		RemoveCollisionComp(pEntityID);
	}
	//Colour Comp
	if ((entity->mComponentMask & ComponentType::COMPONENT_COLOUR) == ComponentType::COMPONENT_COLOUR)
	{
		RemoveColourComp(pEntityID);
	}
	//Weight Comp
	if ((entity->mComponentMask & ComponentType::COMPONENT_WEIGHT) == ComponentType::COMPONENT_WEIGHT)
	{
		RemoveWeightComp(pEntityID);
	}

	//Finds the entity with the matching name and removes it from the entities vector
	mEntities[pEntityID] = Entity();
	mFreeIDs.push_back(pEntityID);
}

/// <summary>
/// Adds the given system to the update system vector
/// </summary>
/// <param name="pSystem">Pointer to the given system</param>
void ECSManager::AddUpdateSystem(shared_ptr<ISystem> pSystem)
{
	mUpdateSystems.push_back(pSystem);
}

/// <summary>
/// Adds the given system to the render system vector
/// </summary>
/// <param name="pSystem">Pointer to the given system</param>
void ECSManager::AddRenderSystem(shared_ptr<ISystem> pSystem)
{
	mRenderSystems.push_back(pSystem);
}

/// <summary>
/// Calls the process method for all systems in the ECS
/// </summary>
void ECSManager::ProcessSystems()
{

	for (auto & system : mUpdateSystems)
	{
		system->Process();
	}

	//for (auto & system : mRenderSystems)
	//{
	//	system->Process();
	//}
}

/// <summary>
/// Adds an AI component to the entity with a given name
/// </summary>
/// <param name="pAI">AI component to add</param>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::AddAIComp(const AI & pAI, const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	mAIs[pEntityID] = pAI;
	entity->mComponentMask |= ComponentType::COMPONENT_AI;
	AssignEntity(*entity);

}

/// <summary>
/// Removes an AI component from the entity with a given name
/// </summary>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::RemoveAIComp(const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	entity->mComponentMask = entity->mComponentMask &= ~ComponentType::COMPONENT_AI; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
	ReassignEntity(*entity);
}

/// <summary>
/// Adds an Audio component to the entity with a given name
/// </summary>
/// <param name="pAudio">Audio component to add</param>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::AddAudioComp(const Audio & pAudio, const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	mAudios[pEntityID] = pAudio;
	entity->mComponentMask |= ComponentType::COMPONENT_AUDIO;
	AssignEntity(*entity);
}

/// <summary>
/// Removes an Audio component from the entity with a given name
/// </summary>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::RemoveAudioComp(const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	entity->mComponentMask = entity->mComponentMask &= ~ComponentType::COMPONENT_AUDIO; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
	ReassignEntity(*entity);
}

/// <summary>
/// Adds a BoxCollider component to the entity with a given name
/// </summary>
/// <param name="pBoxCollider">BoxCollider component to add</param>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::AddBoxColliderComp(const BoxCollider & pBoxCollider, const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	mBoxColliders[pEntityID] = pBoxCollider;
	entity->mComponentMask |= ComponentType::COMPONENT_BOXCOLLIDER;
	AssignEntity(*entity);
}

/// <summary>
/// Removes a BoxCollider component from the entity with a given name
/// </summary>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::RemoveBoxColliderComp(const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	entity->mComponentMask = entity->mComponentMask &= ~ComponentType::COMPONENT_BOXCOLLIDER; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
	ReassignEntity(*entity);
}

/// <summary>
/// Adds a Camera component to the entity with a given name
/// </summary>
/// <param name="pCamera">Camera component to add</param>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::AddCameraComp(const Camera & pCamera, const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	mCameras[pEntityID] = pCamera;
	entity->mComponentMask |= ComponentType::COMPONENT_CAMERA;
	AssignEntity(*entity);
}

/// <summary>
/// Removes a Camera component from the entity with a given name
/// </summary>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::RemoveCameraComp(const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	entity->mComponentMask = entity->mComponentMask &= ~ComponentType::COMPONENT_CAMERA; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
	ReassignEntity(*entity);
}

/// <summary>
/// Adds a Geometry component to the entity with a given name
/// </summary>
/// <param name="pGeometry">Geometry component to add</param>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::AddGeometryComp(const Geometry & pGeometry, const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	mGeometries[pEntityID] = pGeometry;
	entity->mComponentMask |= ComponentType::COMPONENT_GEOMETRY;
	AssignEntity(*entity);

}

/// <summary>
/// Removes a Geometry component from the entity with a given name
/// </summary>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::RemoveGeometryComp(const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	entity->mComponentMask = entity->mComponentMask &= ~ComponentType::COMPONENT_GEOMETRY; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
	ReassignEntity(*entity);
}

/// <summary>
/// Adds a Gravity component to the entity with a given name
/// </summary>
/// <param name="pGravity">Gravity component to add</param>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::AddGravityComp(const Gravity & pGravity, const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	mGravities[pEntityID] = pGravity;
	entity->mComponentMask |= ComponentType::COMPONENT_GRAVITY;
	AssignEntity(*entity);
}

/// <summary>
/// Removes a Gravity component from the entity with a given name
/// </summary>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::RemoveGravityComp(const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	entity->mComponentMask = entity->mComponentMask &= ~ComponentType::COMPONENT_GRAVITY; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
	ReassignEntity(*entity);
}

/// <summary>
/// Adds a Light component to the entity with a given name
/// </summary>
/// <param name="pLight">Light component to add</param>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::AddLightComp(const Light & pLight, const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	mLights[pEntityID] = pLight;
	entity->mComponentMask |= ComponentType::COMPONENT_LIGHT;
	AssignEntity(*entity);
}

/// <summary>
/// Removes a light component from the entity with a given name
/// </summary>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::RemoveLightComp(const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	entity->mComponentMask = entity->mComponentMask &= ~ComponentType::COMPONENT_LIGHT; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
	ReassignEntity(*entity);
}

/// <summary>
/// Adds a Shader component to the entity with a given name
/// </summary>
/// <param name="pShader">Shader component to add</param>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::AddShaderComp(const Shader & pShader, const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	mShaders[pEntityID] = pShader;
	entity->mComponentMask |= ComponentType::COMPONENT_SHADER;
	AssignEntity(*entity);

}

/// <summary>
/// Removes a Shader component from the entity with a given name
/// </summary>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::RemoveShaderComp(const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	entity->mComponentMask = entity->mComponentMask &= ~ComponentType::COMPONENT_SHADER; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
	ReassignEntity(*entity);
}

/// <summary>
/// Adds a SphereCollider component to the entity with a given name
/// </summary>
/// <param name="pSphereCollider">SphereCollider component to add</param>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::AddSphereColliderComp(const SphereCollider & pSphereCollider, const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	mSphereColliders[pEntityID] = pSphereCollider;
	entity->mComponentMask |= ComponentType::COMPONENT_SPHERECOLLIDER;
	AssignEntity(*entity);
}

/// <summary>
/// Removes a SphereCollider component from the entity with a given name
/// </summary>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::RemoveSphereColliderComp(const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	entity->mComponentMask = entity->mComponentMask &= ~ComponentType::COMPONENT_SPHERECOLLIDER; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
	ReassignEntity(*entity);

}

/// <summary>
/// Adds a Texture component to the entity with a given name
/// </summary>
/// <param name="pTexture">Texture component to add</param>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::AddTextureComp(const Texture & pTexture, const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	mTextures[pEntityID] = pTexture;
	entity->mComponentMask |= ComponentType::COMPONENT_TEXTURE;
	AssignEntity(*entity);
}

/// <summary>
/// Removes a Texture component from the entity with a given name
/// </summary>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::RemoveTextureComp(const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	entity->mComponentMask = entity->mComponentMask &= ~ComponentType::COMPONENT_TEXTURE; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
	ReassignEntity(*entity);
}

/// <summary>
/// Adds a Transform component to the entity with a given name
/// </summary>
/// <param name="pTransform">Transform component to add</param>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::AddTransformComp(const Transform & pTransform, const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	mTransforms[pEntityID] = pTransform;
	entity->mComponentMask |= ComponentType::COMPONENT_TRANSFORM;
	AssignEntity(*entity);
}

/// <summary>
/// Removes a Transform component from the entity with a given name
/// </summary>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::RemoveTransformComp(const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	entity->mComponentMask = entity->mComponentMask &= ~ComponentType::COMPONENT_TRANSFORM; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
	ReassignEntity(*entity);
}

/// <summary>
/// Adds a Velocity component to the entity with a given name
/// </summary>
/// <param name="pVelocity">Velocity component to add</param>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::AddVelocityComp(const Velocity & pVelocity, const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	mVelocities[pEntityID] = pVelocity;
	entity->mComponentMask |= ComponentType::COMPONENT_VELOCITY;
	AssignEntity(*entity);
}

/// <summary>
/// Removes a Velocity component from the entity with a given name
/// </summary>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::RemoveVelocityComp(const int& pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	entity->mComponentMask = entity->mComponentMask &= ~ComponentType::COMPONENT_VELOCITY; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
	ReassignEntity(*entity);
}

void ECSManager::AddRayColliderComp(const RayCollider & pRayCollider, const int & pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	mRayColliders[pEntityID] = pRayCollider;
	entity->mComponentMask |= ComponentType::COMPONENT_RAYCOLLIDER;
	AssignEntity(*entity);
}

void ECSManager::RemoveRayColliderComp(const int & pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	entity->mComponentMask = entity->mComponentMask &= ~ComponentType::COMPONENT_RAYCOLLIDER; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
	ReassignEntity(*entity);
}

void ECSManager::AddCollisionComp(const Collision & pCollision, const int & pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	mCollisions[pEntityID] = pCollision;
	entity->mComponentMask |= ComponentType::COMPONENT_COLLISION;
	AssignEntity(*entity);
}

void ECSManager::RemoveCollisionComp(const int & pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	entity->mComponentMask = entity->mComponentMask &= ~ComponentType::COMPONENT_COLLISION; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
	ReassignEntity(*entity);
}

void ECSManager::AddColourComp(const Colour & pColour, const int & pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	mColours[pEntityID] = pColour;
	entity->mComponentMask |= ComponentType::COMPONENT_COLOUR;
	AssignEntity(*entity);
}

void ECSManager::RemoveColourComp(const int & pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	entity->mComponentMask = entity->mComponentMask &= ~ComponentType::COMPONENT_COLOUR; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
	ReassignEntity(*entity);
}

void ECSManager::AddWeightComp(const Weight & pWeight, const int & pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	mWeights[pEntityID] = pWeight;
	entity->mComponentMask |= ComponentType::COMPONENT_WEIGHT;
	AssignEntity(*entity);
}

void ECSManager::RemoveWeightComp(const int & pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	entity->mComponentMask = entity->mComponentMask &= ~ComponentType::COMPONENT_WEIGHT; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
	ReassignEntity(*entity);
}

/// <summary>
/// Returns a modifiable handle to the AI component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to AI component</returns>
AI * const ECSManager::AIComp(const int & pEntityID)
{
	if ((mEntities[pEntityID].mComponentMask & ComponentType::COMPONENT_AI) == ComponentType::COMPONENT_AI)
		return &mAIs[pEntityID];
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Audio component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Audio component</returns>
Audio * const ECSManager::AudioComp(const int & pEntityID)
{
	if ((mEntities[pEntityID].mComponentMask & ComponentType::COMPONENT_AUDIO) == ComponentType::COMPONENT_AUDIO)
		return &mAudios[pEntityID];
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the BoxCollider component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to BoxCollider component</returns>
BoxCollider * const ECSManager::BoxColliderComp(const int & pEntityID)
{
	if ((mEntities[pEntityID].mComponentMask & ComponentType::COMPONENT_BOXCOLLIDER) == ComponentType::COMPONENT_BOXCOLLIDER)
		return &mBoxColliders[pEntityID];
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Camera component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Camera component</returns>
Camera * const ECSManager::CameraComp(const int & pEntityID)
{
	if ((mEntities[pEntityID].mComponentMask & ComponentType::COMPONENT_CAMERA) == ComponentType::COMPONENT_CAMERA)
		return &mCameras[pEntityID];
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Geometry component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Geometry component</returns>
Geometry * const ECSManager::GeometryComp(const int & pEntityID)
{
	if ((mEntities[pEntityID].mComponentMask & ComponentType::COMPONENT_GEOMETRY) == ComponentType::COMPONENT_GEOMETRY)
		return &mGeometries[pEntityID];
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Gravity component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Gravity component</returns>
Gravity * const ECSManager::GravityComp(const int & pEntityID)
{
	if ((mEntities[pEntityID].mComponentMask & ComponentType::COMPONENT_GRAVITY) == ComponentType::COMPONENT_GRAVITY)
		return &mGravities[pEntityID];
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Light component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to AI component</returns>
Light * const ECSManager::LightComp(const int & pEntityID)
{
	if ((mEntities[pEntityID].mComponentMask & ComponentType::COMPONENT_LIGHT) == ComponentType::COMPONENT_LIGHT)
		return &mLights[pEntityID];
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Shader component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Shader component</returns>
Shader * const ECSManager::ShaderComp(const int & pEntityID)
{
	if ((mEntities[pEntityID].mComponentMask & ComponentType::COMPONENT_SHADER) == ComponentType::COMPONENT_SHADER)
		return &mShaders[pEntityID];
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the SphereCollider component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to SphereCollider component</returns>
SphereCollider * const ECSManager::SphereColliderComp(const int & pEntityID)
{
	if ((mEntities[pEntityID].mComponentMask & ComponentType::COMPONENT_SPHERECOLLIDER) == ComponentType::COMPONENT_SPHERECOLLIDER)
		return &mSphereColliders[pEntityID];
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Texture component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Texture component</returns>
Texture * const ECSManager::TextureComp(const int & pEntityID)
{
	if ((mEntities[pEntityID].mComponentMask & ComponentType::COMPONENT_TEXTURE) == ComponentType::COMPONENT_TEXTURE)
		return &mTextures[pEntityID];
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Transform component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Transform component</returns>
Transform * const ECSManager::TransformComp(const int & pEntityID)
{
	if ((mEntities[pEntityID].mComponentMask & ComponentType::COMPONENT_TRANSFORM) == ComponentType::COMPONENT_TRANSFORM)
		return &mTransforms[pEntityID];
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Velocity component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Velocity component</returns>
Velocity * const ECSManager::VelocityComp(const int & pEntityID)
{
	if ((mEntities[pEntityID].mComponentMask & ComponentType::COMPONENT_VELOCITY) == ComponentType::COMPONENT_VELOCITY)
		return &mVelocities[pEntityID];
	return nullptr;
}

RayCollider * const ECSManager::RayColliderComp(const int & pEntityID)
{
	if ((mEntities[pEntityID].mComponentMask & ComponentType::COMPONENT_RAYCOLLIDER) == ComponentType::COMPONENT_RAYCOLLIDER)
		return &mRayColliders[pEntityID];
	return nullptr;
}

Collision * const ECSManager::CollisionComp(const int & pEntityID)
{
	if ((mEntities[pEntityID].mComponentMask & ComponentType::COMPONENT_COLLISION) == ComponentType::COMPONENT_COLLISION)
		return &mCollisions[pEntityID];
	return nullptr;
}

Colour * const ECSManager::ColourComp(const int & pEntityID)
{
	if ((mEntities[pEntityID].mComponentMask & ComponentType::COMPONENT_COLOUR) == ComponentType::COMPONENT_COLOUR)
		return &mColours[pEntityID];
	return nullptr;
}

Weight * const ECSManager::WeightComp(const int & pEntityID)
{
	if ((mEntities[pEntityID].mComponentMask & ComponentType::COMPONENT_WEIGHT) == ComponentType::COMPONENT_WEIGHT)
		return &mWeights[pEntityID];
	return nullptr;
}

int ECSManager::EntityCount() const
{
	return mEntities.size();
}
