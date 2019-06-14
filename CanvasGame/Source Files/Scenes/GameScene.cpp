#pragma once
#include "GameScene.h"

using namespace KodeBoldsMath;

GameScene::GameScene() : mRayID(-1), mCubeCount(0), mLastCollided(-1)
{
	OnLoad();
}

GameScene::~GameScene()
{


}

void GameScene::CameraControls(const float& pDt)
{
	if (mInputManager->KeyHeld(KEY::KEY_A))
	{
		mEye += Vector4(-2, 0, 0, 0) * pDt;
		mLookAt += Vector4(-2, 0, 0, 0) * pDt;

	}
	if (mInputManager->KeyHeld(KEY::KEY_D))
	{
		mEye += Vector4(2, 0, 0, 0) * pDt;
		mLookAt += Vector4(2, 0, 0, 0) * pDt;
	}
	if (mInputManager->KeyHeld(KEY::KEY_W))
	{
		mEye += Vector4(0, 0, 2, 0) * pDt;
		mLookAt += Vector4(0, 0, 2, 0) * pDt;
	}
	if (mInputManager->KeyHeld(KEY::KEY_S))
	{
		mEye += Vector4(0, 0, -2, 0) * pDt;
		mLookAt += Vector4(0, 0, -2, 0) * pDt;
	}
	if (mInputManager->KeyHeld(KEY::KEY_LEFT_SHIFT))
	{
		mEye += Vector4(0, -2, 0, 0) * pDt;
		mLookAt += Vector4(0, -2, 0, 0) * pDt;
	}
	if (mInputManager->KeyHeld(KEY::KEY_SPACE))
	{
		mEye += Vector4(0, 2, 0, 0) * pDt;
		mLookAt += Vector4(0, 2, 0, 0) * pDt;
	}
	mEcsManager->TransformComp(mCameraID)->mTranslation = mEye;
	mEcsManager->CameraComp(mCameraID)->mLookAt = mLookAt;
	mView = LookAtLH(mEye, mLookAt, mUp);
}

/// <summary>
/// Reset the canvas and camera
/// </summary>
void GameScene::Reset()
{
	//Send a reset to everyone
	mNetworkManager->AddMessage("0:R");

	//Camera
	mEye = Vector4(0.0f, 0.0f, -40.0f, 1.0f);
	mLookAt = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	mUp = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

	mEcsManager->TransformComp(mCameraID)->mTranslation = mEye;
	mView = LookAtLH(mEye, mLookAt, mUp);


	//Cubes
	for (int i = 0; i < mEcsManager->EntityCount(); ++i)
	{
		if (mEcsManager->ColourComp(i))
		{
			mEcsManager->ColourComp(i)->mColour = GameValues::gColours[GameValues::gPlayerNumber - 1];
		}
		if (mEcsManager->WeightComp(i))
		{
			mEcsManager->WeightComp(i)->mWeight = KodeBoldsMath::Vector4(0, 0, 0, 0);
			switch (GameValues::gPlayerNumber)
			{
			case 1: //red
				mEcsManager->WeightComp(i)->mWeight.X = 1;
				break;
			case 2: //green
				mEcsManager->WeightComp(i)->mWeight.Y = 1;
				break;
			case 3: //blue
				mEcsManager->WeightComp(i)->mWeight.Z = 1;
				break;
			case 4: //yellow
				mEcsManager->WeightComp(i)->mWeight.W = 1;
				break;
			default:
				break;
			}
		}
	}


}

void GameScene::Render()
{
}

void GameScene::Update()
{
	const float dt = static_cast<float>(mSceneManager->DeltaTime());
	CameraControls(dt);
	if (mInputManager->KeyDown(KEY::KEY_R))
	{
		Reset();
	}
	if (mInputManager->KeyDown(KEY::KEY_Y))
	{
		FrequencyValues::gNetFreq++;
	}
	if (mInputManager->KeyDown(KEY::KEY_H))
	{
		FrequencyValues::gNetFreq--;
	}
	if (mInputManager->KeyDown(KEY::KEY_U))
	{
		FrequencyValues::gRenderFreq++;
	}
	if (mInputManager->KeyDown(KEY::KEY_J))
	{
		FrequencyValues::gRenderFreq--;
	}
	if (mInputManager->KeyDown(KEY::KEY_M))
	{
		mIntegrityMode = !mIntegrityMode;
		if (mIntegrityMode)
		{
			//Integrity Check
			mNetworkManager->AddMessage("0:I:" + std::to_string(GameValues::gPlayerNumber));
		}
		else
		{
			for (int i = 0; i < mEcsManager->EntityCount(); ++i)
			{
				if (mEcsManager->WeightComp(i) && mEcsManager->ColourComp(i))
				{
					//calculate colour based on new weight
					KodeBoldsMath::Vector4 newColour(0, 0, 0, 0);
					int totalWeight = 0;

					if (mEcsManager->WeightComp(i)->mWeight.X > 0.1f)
					{
						newColour += GameValues::gColours[0];
						totalWeight++;
					}
					if (mEcsManager->WeightComp(i)->mWeight.Y > 0.1f)
					{
						newColour += GameValues::gColours[1];
						totalWeight++;
					}
					if (mEcsManager->WeightComp(i)->mWeight.Z > 0.1f)
					{
						newColour += GameValues::gColours[2];
						totalWeight++;
					}
					if (mEcsManager->WeightComp(i)->mWeight.W > 0.1f)
					{
						newColour += GameValues::gColours[3];
						totalWeight++;
					}

					if (totalWeight != 0)
					{
						newColour /= static_cast<float>(totalWeight);
						newColour.W = 1.0f;
					}

					mEcsManager->ColourComp(i)->mColour = newColour;

				}
			}
		}
	}

	//if a ray has collided
	if (mRayID != -1)
	{
		Collision* collision = mEcsManager->CollisionComp(mRayID);

		if (collision)
		{
			if (collision->mCollidedWithID != mLastCollided)
			{
				/*const Colour col{ Vector4(0.0f, 0.0f, 0.0f, 1.0f) };
				mEcsManager->AddColourComp(col, collision->mCollidedWithID);*/
				int targetPeer = GameValues::gPlayerNumber;
				const int rndMax = GameValues::gPlayerCount;
				while (targetPeer == GameValues::gPlayerNumber)
				{
					targetPeer = rand() % rndMax + 1;
				}

				mNetworkManager->AddMessage(std::to_string(targetPeer) + ":S:" + std::to_string(collision->mCollidedWithID) + ":" + std::to_string(GameValues::gPlayerNumber));
				mLastCollided = collision->mCollidedWithID;
			}

		}
		mEcsManager->DestroyEntity(mRayID);
		mRayID = -1;
	}

	if (!mIntegrityMode)
	{
		//Left click to cast ray at mouse position
		if (mInputManager->KeyHeld(KEY::MOUSE_BUTTON_LEFT))
		{
			const Vector4 dir = mInputManager->MouseWorld(mView, mProj, mWidth, mHeight);
			mRayID = mEcsManager->CreateEntity();
			const RayCollider ray{ mEye, dir };
			mEcsManager->AddRayColliderComp(ray, mRayID);
		}
	}

}

void GameScene::OnLoad()
{
	mCameraID = mEcsManager->CreateEntity();

	//Camera
	Transform transform;
	mEye = Vector4(0.0f, 0.0f, -40.0f, 1.0f);
	mLookAt = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	mUp = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	const float fov = 60;
	const float nearPlane = 1;
	const float farPlane = 500;
	mWidth = mSceneManager->Width();
	mHeight = mSceneManager->Height();
	float aspectRatio = mWidth / mHeight;
	transform.mTranslation = mEye;
	mEcsManager->AddTransformComp(transform, mCameraID);
	Camera camera{ mLookAt, mUp, fov, nearPlane, farPlane };
	mView = LookAtLH(mEye, mLookAt, mUp);
	mProj = ProjectionLH(1.0472f, aspectRatio, nearPlane, farPlane);
	mEcsManager->AddCameraComp(camera, mCameraID);

	//Cube
	for (int k = 0; k < 4; ++k)
	{
		for (int i = -100; i < 100; ++i)
		{
			for (int j = -100; j < 100; ++j)
			{
				++mCubeCount;
				int cubeId = mEcsManager->CreateEntity();
				transform.mTranslation = Vector4(static_cast<float>(j) / 5, static_cast<float>(i) / 5, static_cast<float>(k) / 5, 1.0f);
				transform.mTransform = TranslationMatrix(transform.mTranslation) * ScaleMatrix(Vector4(0.1f, 0.1f, 0.1f, 1.0f));
				mEcsManager->AddTransformComp(transform, cubeId);
				Geometry geometry{ L"cube.obj" };
				mEcsManager->AddGeometryComp(geometry, cubeId);
				Shader shader{ L"defaultShader.fx", BlendState::NOBLEND, CullState::NONE, DepthState::NONE };
				mEcsManager->AddShaderComp(shader, cubeId);
				Colour col{ Vector4(0.0f, 0.0f, 0.0f, 0.0f) };
				mEcsManager->AddColourComp(col, cubeId);
				Weight w{ Vector4(0.0f, 0.0f, 0.0f, 0.0f) };
				mEcsManager->AddWeightComp(w, cubeId);
				BoxCollider boxCollider{ Vector3(transform.mTranslation.X - 0.1f, transform.mTranslation.Y - 0.1f, transform.mTranslation.Z - 0.1f),
										Vector3(transform.mTranslation.X + 0.1f, transform.mTranslation.Y + 0.1f, transform.mTranslation.Z + 0.1f) };
				mEcsManager->AddBoxColliderComp(boxCollider, cubeId);
			}
		}
	}

	//Light
	int lightId = mEcsManager->CreateEntity();
	transform.mTranslation = Vector4(5.0f, 0.0f, -5.0f, 1.0f);
	mEcsManager->AddTransformComp(transform, lightId);
	Light light{ Vector4(1.0f, 1.0f, 1.0f, 1.0f) };
	mEcsManager->AddLightComp(light, lightId);
}
