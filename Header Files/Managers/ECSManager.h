#pragma once
#include <memory>
#include <vector>
#include "Components.h"
#include "ISystem.h"
#include "Entity.h"
#include <algorithm>
#include <string>
#include <chrono>
#include "ThreadManager.h"

class ECSManager
{
private:
	std::vector<Entity> mEntities;
	std::vector<int> mFreeIDs;
	std::vector<Transform> mTransforms;
	std::vector<Velocity> mVelocities;
	std::vector<BoxCollider> mBoxColliders;
	std::vector<SphereCollider> mSphereColliders;
	std::vector<Geometry> mGeometries;
	std::vector<Texture> mTextures;
	std::vector<Shader> mShaders;
	std::vector<Camera> mCameras;
	std::vector<Light> mLights;
	std::vector<Gravity> mGravities;
	std::vector<Audio> mAudios;
	std::vector<AI> mAIs;
	std::vector<Colour> mColours;
	std::vector<RayCollider> mRayColliders;
	std::vector<Collision> mCollisions;
	std::vector<Weight> mWeights;

	std::vector<std::shared_ptr<ISystem>> mRenderSystems;
	std::vector<std::shared_ptr<ISystem>> mUpdateSystems;
	int mNextEntityID;

	ECSManager();

	//Entity management
	void AssignEntity(const Entity& pEntity);
	void ReassignEntity(const Entity& pEntity);

public:
	~ECSManager();

	//Singleton pattern
	//Deleted copy constructor and assignment operator so no copies of the singleton instance can be made
	ECSManager(ECSManager const&) = delete;
	ECSManager& operator=(ECSManager const&) = delete;	
	static std::shared_ptr<ECSManager> Instance();

	//Entity creation
	const int CreateEntity();
	void DestroyEntity(const int& pEntityID);

	//System management
	void AddUpdateSystem(std::shared_ptr<ISystem> pSystem);
	void AddRenderSystem(std::shared_ptr<ISystem> pSystem);
	void ProcessSystems();

	//Add/Remove methods for components
	void AddAIComp(const AI& pAI, const int& pEntityID);
	void RemoveAIComp(const int& pEntityID);
	void AddAudioComp(const Audio& pAudio, const int& pEntityID);
	void RemoveAudioComp(const int& pEntityID);
	void AddBoxColliderComp(const BoxCollider& pBoxCollider, const int& pEntityID);
	void RemoveBoxColliderComp(const int& pEntityID);
	void AddCameraComp(const Camera& pCamera, const int& pEntityID);
	void RemoveCameraComp(const int& pEntityID);
	void AddGeometryComp(const Geometry& pGeometry, const int& pEntityID);
	void RemoveGeometryComp(const int& pEntityID);
	void AddGravityComp(const Gravity& pGravity, const int& pEntityID);
	void RemoveGravityComp(const int& pEntityID);
	void AddLightComp(const Light& pLight, const int& pEntityID);
	void RemoveLightComp(const int& pEntityID);
	void AddShaderComp(const Shader& pShader, const int& pEntityID);
	void RemoveShaderComp(const int& pEntityID);
	void AddSphereColliderComp(const SphereCollider& pSphereCollider, const int& pEntityID);
	void RemoveSphereColliderComp(const int& pEntityID);
	void AddTextureComp(const Texture& pTexture, const int& pEntityID);
	void RemoveTextureComp(const int& pEntityID);
	void AddTransformComp(const Transform& pTransform, const int& pEntityID);
	void RemoveTransformComp(const int& pEntityID);
	void AddVelocityComp(const Velocity& pVelocity, const int& pEntityID);
	void RemoveVelocityComp(const int& pEntityID);
	void AddRayColliderComp(const RayCollider& pRayCollider, const int& pEntityID);
	void RemoveRayColliderComp(const int& pEntityID);
	void AddCollisionComp(const Collision& pCollision, const int& pEntityID);
	void RemoveCollisionComp(const int& pEntityID);
	void AddColourComp(const Colour& pColour, const int& pEntityID);
	void RemoveColourComp(const int& pEntityID);
	void AddWeightComp(const Weight& pWeight, const int& pEntityID);
	void RemoveWeightComp(const int& pEntityID);

	//Accessors
	AI* const AIComp(const int& pEntityID);
	Audio* const AudioComp(const int& pEntityID);
	BoxCollider* const BoxColliderComp(const int& pEntityID);
	Camera* const CameraComp(const int& pEntityID);
	Geometry* const GeometryComp(const int& pEntityID);
	Gravity* const GravityComp(const int& pEntityID);
	Light* const LightComp(const int& pEntityID);
	Shader* const ShaderComp(const int& pEntityID);
	SphereCollider* const SphereColliderComp(const int& pEntityID);
	Texture* const TextureComp(const int& pEntityID);
	Transform* const TransformComp(const int& pEntityID);
	Velocity* const VelocityComp(const int& pEntityID);
	RayCollider* const RayColliderComp(const int& pEntityID);
	Collision* const CollisionComp(const int& pEntityID);
	Colour* const ColourComp(const int& pEntityID);
	Weight* const WeightComp(const int& pEntityID);

	int EntityCount() const;
};
