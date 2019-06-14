#pragma once
#include "ECSManager.h"
#include "Components.h"
#include "ISystem.h"
#include "Vector4.h"
#include <queue>
#include "NetworkManager.h"
#include "AntTweakManager.h"
#include <sstream>  

class NetworkUpdateSystem : public ISystem
{
private:
	std::shared_ptr<ECSManager> mEcsManager = ECSManager::Instance();
	std::shared_ptr<NetworkManager> mNetworkManager = NetworkManager::Instance();
	std::shared_ptr<AntTweakManager> mAntTweakManager = AntTweakManager::Instance();
	std::queue<std::string> mReceivedMessages;

	int mConnectResponses;
	std::vector<int> mAvailableNumbers;
	std::vector<int> mTotalCubeWeights; //used for integrity checks
	int mIntegrityResponses;
	int mOwnedWeight;
	int mAllPeerStartingWeight;
	int mActualTotalWeight;
	int mSinglePeerStartingWeight;

	void PrintCanvas() const;

	void ConnectResponse(const int pTakenNumber);
	void CubeStolen(const int pStolenCube, const int pReplyAddress);
	void StealCube(const int pStolenCube, const int pColourStolen);

public:
	NetworkUpdateSystem();
	virtual ~NetworkUpdateSystem();

	void AssignEntity(const Entity& pEntity) override;
	void ReassignEntity(const Entity& pEntity) override;
	void Process() override;

};
