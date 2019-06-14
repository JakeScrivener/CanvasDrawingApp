#include "NetworkUpdateSystem.h"
#include "GameScene.h"

NetworkUpdateSystem::NetworkUpdateSystem() : ISystem(ComponentType::COMPONENT_NONE), mConnectResponses(0), mIntegrityResponses(0), mOwnedWeight(160000), mActualTotalWeight(0), mSinglePeerStartingWeight(160000)
{
	//There is no mask or entity assignment as this system does not act on entities but on messages
	// (Should messages be treated as entities with a message component?)

	mAvailableNumbers.push_back(1);
	mAvailableNumbers.push_back(2);
	mAvailableNumbers.push_back(3);
	mAvailableNumbers.push_back(4);

	GameValues::gColours.emplace_back(KodeBoldsMath::Vector4(1, 0, 0, 1)); //Red
	GameValues::gColours.emplace_back(KodeBoldsMath::Vector4(0, 1, 0, 1)); //Green
	GameValues::gColours.emplace_back(KodeBoldsMath::Vector4(0, 0, 1, 1)); //Blue
	GameValues::gColours.emplace_back(KodeBoldsMath::Vector4(1, 1, 0, 1)); //Yellow

	mAllPeerStartingWeight = mSinglePeerStartingWeight * GameValues::gPlayerCount;

	mAntTweakManager->AddVariable("Stats", "Player Count", GameValues::gPlayerCount, "group=Game");
	mAntTweakManager->AddVariable("Stats", "Player Number", GameValues::gPlayerNumber, "group = Game");
	mAntTweakManager->AddVariable("Stats", "Owned Mass", mOwnedWeight, "group = Game");
	mAntTweakManager->AddVariable("Stats", "Starting Total Mass", mAllPeerStartingWeight, "group = Game");
	mAntTweakManager->AddVariable("Stats", "Actual Total Mass", mActualTotalWeight, "group = Game");
}


NetworkUpdateSystem::~NetworkUpdateSystem() = default;

/// <summary>
/// Do not implement assign or reassign as this system does not act on entities
/// </summary>
void NetworkUpdateSystem::AssignEntity(const Entity & pEntity)
{
}
/// <summary>
/// Do not implement assign or reassign as this system does not act on entities
/// </summary>
void NetworkUpdateSystem::ReassignEntity(const Entity & pEntity)
{
}

/// <summary>
/// Process network messages
/// </summary>
void NetworkUpdateSystem::Process()
{
	GameValues::gPlayerCount = mNetworkManager->Connections() + 1;
	mAllPeerStartingWeight = mSinglePeerStartingWeight * GameValues::gPlayerCount;

	mReceivedMessages = mNetworkManager->ReceivedMessages();
	while (!mReceivedMessages.empty())
	{
		std::string msg = mReceivedMessages.front();
		std::istringstream stringStream(msg);
		std::vector<std::string> words;
		std::string word;
		const auto delimiter = ':';

		//split string
		while (std::getline(stringStream, word, delimiter))
		{
			words.push_back(word);
		}

		//Connect messages do not require an addressed player as they are sent to everyone
		if (words[1] == "C") //connect
		{
			if (GameValues::gPlayerNumber == 0)
			{
				GameValues::gPlayerNumber = 1;
				GameValues::gPlayerNumber = GameValues::gPlayerNumber;


				for (int i = 0; i < mEcsManager->EntityCount(); ++i)
				{
					if (mEcsManager->ColourComp(i))
					{
						mEcsManager->ColourComp(i)->mColour = GameValues::gColours[GameValues::gPlayerNumber-1];
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
			mNetworkManager->AddMessage("0:CR:" + std::to_string(GameValues::gPlayerNumber));
		}
		//don't need to know who told you to reset, just do it
		if (words[1] == "R")
		{
			for (int i = 0; i < mEcsManager->EntityCount(); ++i)
			{
				if (mEcsManager->ColourComp(i))
				{
					mEcsManager->ColourComp(i)->mColour = GameValues::gColours[GameValues::gPlayerNumber-1];
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
		if (words[1] == "I")
		{
			std::string ownedWeight = "";
			for (int i = 0; i < mEcsManager->EntityCount(); ++i)
			{
				if (mEcsManager->WeightComp(i))
				{
					const int totalWeight = mEcsManager->WeightComp(i)->mWeight.X + mEcsManager->WeightComp(i)->mWeight.Y + mEcsManager->WeightComp(i)->mWeight.Z + mEcsManager->WeightComp(i)->mWeight.W;
					ownedWeight += ":" + std::to_string(totalWeight);
				}
			}
			mNetworkManager->AddMessage(words[2] + ":IR" + ownedWeight);
		}

		//if this message doesn't belong to me then skip it
		if (std::stoi(words[0]) != GameValues::gPlayerNumber)
		{
			mReceivedMessages.pop();
			continue;
		}

		//process message
		if (words[1] == "CR") //connect response
		{
			//process connect response
			ConnectResponse(std::stoi(words[2]));
			//if all connections have responded, removing their number, then take the next available number
			if (mConnectResponses == mNetworkManager->Connections())
			{
				GameValues::gPlayerNumber = mAvailableNumbers[0];
				GameValues::gPlayerNumber = GameValues::gPlayerNumber;

				for (int i = 0; i < mEcsManager->EntityCount(); ++i)
				{
					if (mEcsManager->ColourComp(i))
					{
						mEcsManager->ColourComp(i)->mColour = GameValues::gColours[GameValues::gPlayerNumber-1];
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
		}
		else if (words[1] == "S") //Selected cube / Steal
		{
			//Colour the stolen cube
			const int stolenCube = std::stoi(words[2]);

			if (mEcsManager->WeightComp(stolenCube)->mWeight.X < 0.1f &&
				mEcsManager->WeightComp(stolenCube)->mWeight.Y < 0.1f &&
				mEcsManager->WeightComp(stolenCube)->mWeight.Z < 0.1f &&
				mEcsManager->WeightComp(stolenCube)->mWeight.W < 0.1f)
			{
				//tell them you have none to give
				mNetworkManager->AddMessage(words[3] + ":SR:" + std::to_string(stolenCube) + ":N");
			}
			else
			{
				const int replyAddress = std::stoi(words[3]);
				CubeStolen(stolenCube, replyAddress);

			}
		}
		else if (words[1] == "SR") //Steal response
		{
			int stolenCube = std::stoi(words[2]);
			//if the player had none to give, keep asking random players until you have found some
			if (words[3] == "N")
			{
				int targetPeer = GameValues::gPlayerNumber;
				int totalWeight = 0;
				if (mEcsManager->WeightComp(stolenCube)->mWeight.X > 0.1f)
				{
					totalWeight++;
				}
				if (mEcsManager->WeightComp(stolenCube)->mWeight.Y > 0.1f)
				{
					totalWeight++;
				}
				if (mEcsManager->WeightComp(stolenCube)->mWeight.Z > 0.1f)
				{
					totalWeight++;
				}
				if (mEcsManager->WeightComp(stolenCube)->mWeight.W > 0.1f)
				{
					totalWeight++;
				}
				if (GameValues::gPlayerCount != totalWeight) //Only keep searching for a cube if you don't already own them all
				{
					const int rndMax = GameValues::gPlayerCount;
					while (targetPeer == GameValues::gPlayerNumber)
					{
						targetPeer = rand() % rndMax + 1;
					}
					//Failed so try someone else
					mNetworkManager->AddMessage(std::to_string(targetPeer) + ":S:" + std::to_string(stolenCube) + ":" + std::to_string(GameValues::gPlayerNumber));
				}
			}
			else
			{
				const int stolenColour = std::stoi(words[3]);
				StealCube(stolenCube, stolenColour);
			}
		}
		else if (words[1] == "IR")
		{
			mIntegrityResponses++;
			if (static_cast<int>(mTotalCubeWeights.size()) < mEcsManager->EntityCount())
			{
				mTotalCubeWeights.resize(mEcsManager->EntityCount());
			}
			int wordCounter = 2;
			for (int i = 0; i < mEcsManager->EntityCount(); ++i)
			{
				if (mEcsManager->WeightComp(i))
				{
					mTotalCubeWeights[i] += std::stoi(words[wordCounter]);
					wordCounter++;
				}
			}
			if (mIntegrityResponses == mNetworkManager->Connections())
			{
				mIntegrityResponses = 0;
				mActualTotalWeight = 0;
				//set colours
				for (int i = 0; i < mEcsManager->EntityCount(); ++i)
				{
					if (mEcsManager->WeightComp(i))
					{
						mTotalCubeWeights[i] += mEcsManager->WeightComp(i)->mWeight.X + mEcsManager->WeightComp(i)->mWeight.Y + mEcsManager->WeightComp(i)->mWeight.Z + mEcsManager->WeightComp(i)->mWeight.W;
						mActualTotalWeight += mTotalCubeWeights[i];
					}
					if (mEcsManager->ColourComp(i))
					{
						if (mTotalCubeWeights[i] > GameValues::gPlayerCount)
						{
							mEcsManager->ColourComp(i)->mColour = KodeBoldsMath::Vector4(1, 0, 0, 1);
						}
						else if (mTotalCubeWeights[i] < GameValues::gPlayerCount)
						{
							mEcsManager->ColourComp(i)->mColour = KodeBoldsMath::Vector4(0, 0, 1, 1);
						}
						else
						{
							mEcsManager->ColourComp(i)->mColour = KodeBoldsMath::Vector4(0.7, 0.7, 0.7, 1);
						}
					}
				}
				std::fill(mTotalCubeWeights.begin(), mTotalCubeWeights.end(), 0);
			}
		}

		mReceivedMessages.pop();
	}
}

/// <summary>
/// processes a connect response
/// </summary>
/// <param name="pTakenNumber"> the player number of the responder </param>
void NetworkUpdateSystem::ConnectResponse(const int pTakenNumber)
{
	mAvailableNumbers.erase(std::remove_if(mAvailableNumbers.begin(), mAvailableNumbers.end(), [&](const int pNum) { return pNum == pTakenNumber; }), mAvailableNumbers.end());
	mConnectResponses++;
}

/// <summary>
/// add a stolen cube to the system
/// </summary>
/// <param name="pStolenCube">the id of the cube which was stolen</param>
/// <param name="pColourStolen"> the number of the colour/player that the cube was stolen from</param>
void NetworkUpdateSystem::StealCube(const int pStolenCube, const int pColourStolen)
{
	mOwnedWeight++;
	//steal a cube + average colour
	const auto stolenColour = GameValues::gColours[pColourStolen - 1];

	switch (pColourStolen)
	{
	case 1: //red
		mEcsManager->WeightComp(pStolenCube)->mWeight.X = 1;
		break;
	case 2: //green
		mEcsManager->WeightComp(pStolenCube)->mWeight.Y = 1;
		break;
	case 3: //blue
		mEcsManager->WeightComp(pStolenCube)->mWeight.Z = 1;
		break;
	case 4: //yellow
		mEcsManager->WeightComp(pStolenCube)->mWeight.W = 1;
		break;
	default:
		break;
	}

	//calculate colour based on new weight
	KodeBoldsMath::Vector4 newColour(0, 0, 0, 0);
	int totalWeight = 0;

	if (mEcsManager->WeightComp(pStolenCube)->mWeight.X > 0.1f)
	{
		newColour += GameValues::gColours[0];
		totalWeight++;
	}
	if (mEcsManager->WeightComp(pStolenCube)->mWeight.Y > 0.1f)
	{
		newColour += GameValues::gColours[1];
		totalWeight++;
	}
	if (mEcsManager->WeightComp(pStolenCube)->mWeight.Z > 0.1f)
	{
		newColour += GameValues::gColours[2];
		totalWeight++;
	}
	if (mEcsManager->WeightComp(pStolenCube)->mWeight.W > 0.1f)
	{
		newColour += GameValues::gColours[3];
		totalWeight++;
	}

	if (totalWeight != 0)
	{
		newColour /= static_cast<float>(totalWeight);
		newColour.W = 1.0f;
	}

	mEcsManager->ColourComp(pStolenCube)->mColour = newColour;
}

void NetworkUpdateSystem::PrintCanvas() const
{
	for (int i = 0; i < mEcsManager->EntityCount(); ++i)
	{
		if (mEcsManager->ColourComp(i) && mEcsManager->WeightComp(i))
		{
			OutputDebugString(L"Colour:");
			OutputDebugString(std::to_wstring(mEcsManager->ColourComp(i)->mColour.X).c_str());
			OutputDebugString(L",");
			OutputDebugString(std::to_wstring(mEcsManager->ColourComp(i)->mColour.Y).c_str());
			OutputDebugString(L",");
			OutputDebugString(std::to_wstring(mEcsManager->ColourComp(i)->mColour.Z).c_str());
			OutputDebugString(L",");
			OutputDebugString(std::to_wstring(mEcsManager->ColourComp(i)->mColour.W).c_str());
			OutputDebugString(L"	Weight:");
			OutputDebugString(std::to_wstring(mEcsManager->WeightComp(i)->mWeight.X).c_str());
			OutputDebugString(L",");
			OutputDebugString(std::to_wstring(mEcsManager->WeightComp(i)->mWeight.Y).c_str());
			OutputDebugString(L",");
			OutputDebugString(std::to_wstring(mEcsManager->WeightComp(i)->mWeight.Z).c_str());
			OutputDebugString(L",");
			OutputDebugString(std::to_wstring(mEcsManager->WeightComp(i)->mWeight.W).c_str());
			OutputDebugString(L",");
		}
	}
}

/// <summary>
/// Implement effects of having a cube stolen
/// </summary>
/// <param name="pStolenCube"> the cube that was stolen </param>
/// <param name="pReplyAddress"> the address of the player to send the cube to </param>
void NetworkUpdateSystem::CubeStolen(const int pStolenCube, const int pReplyAddress)
{
	mOwnedWeight--;
	//decrease the weight
	if (mEcsManager->WeightComp(pStolenCube)->mWeight.X > 0.1f) //Check against 0.1 to ensure it is over 0 with floating point inaccuracy
	{
		mEcsManager->WeightComp(pStolenCube)->mWeight.X = 0;
		mNetworkManager->AddMessage(std::to_string(pReplyAddress) + ":SR:" + std::to_string(pStolenCube) + ":1");
	}
	else if (mEcsManager->WeightComp(pStolenCube)->mWeight.Y > 0.1f)
	{
		mEcsManager->WeightComp(pStolenCube)->mWeight.Y = 0;
		mNetworkManager->AddMessage(std::to_string(pReplyAddress) + ":SR:" + std::to_string(pStolenCube) + ":2");
	}
	else if (mEcsManager->WeightComp(pStolenCube)->mWeight.Z > 0.1f)
	{
		mEcsManager->WeightComp(pStolenCube)->mWeight.Z = 0;
		mNetworkManager->AddMessage(std::to_string(pReplyAddress) + ":SR:" + std::to_string(pStolenCube) + ":3");
	}
	else if (mEcsManager->WeightComp(pStolenCube)->mWeight.W > 0.1f)
	{
		mEcsManager->WeightComp(pStolenCube)->mWeight.W = 0;
		mNetworkManager->AddMessage(std::to_string(pReplyAddress) + ":SR:" + std::to_string(pStolenCube) + ":4");
	}

	//calculate colour based on new weight
	KodeBoldsMath::Vector4 newColour(0, 0, 0, 0);
	int totalWeight = 0;

	if (mEcsManager->WeightComp(pStolenCube)->mWeight.X > 0.1f)
	{
		newColour += GameValues::gColours[0];
		totalWeight++;
	}
	if (mEcsManager->WeightComp(pStolenCube)->mWeight.Y > 0.1f)
	{
		newColour += GameValues::gColours[1];
		totalWeight++;
	}
	if (mEcsManager->WeightComp(pStolenCube)->mWeight.Z > 0.1f)
	{
		newColour += GameValues::gColours[2];
		totalWeight++;
	}
	if (mEcsManager->WeightComp(pStolenCube)->mWeight.W > 0.1f)
	{
		newColour += GameValues::gColours[3];
		totalWeight++;
	}

	if (totalWeight == 0)
	{
		newColour = KodeBoldsMath::Vector4(0, 0, 0, 0);
	}
	else
	{
		newColour /= static_cast<float>(totalWeight);
	}

	mEcsManager->ColourComp(pStolenCube)->mColour = newColour;
}
