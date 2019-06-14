#pragma once
#include <vector>
#include <string>
#include "KodeBoldsMath.h"
#include "Vector2.h"
#include "AntTweakBar.h"
#include <map>

class AntTweakManager
{
private:
	AntTweakManager();

	std::map<std::string, TwBar*> mBars;
	bool mHide = false;
public:
	~AntTweakManager();

	//Singleton pattern
	//Deleted copy constructor and assignment operator so no copies of the singleton instance can be made
	AntTweakManager(const AntTweakManager&) = delete;
	AntTweakManager& operator=(const AntTweakManager&) = delete;

	//pass device as void pointer to make it platform independant
	void Init(void* const pDevice, const int& pWidth, const int& pHeight) const;
	void Cleanup();

	void AddBar(const std::string& pName);
	void AddVariable(const std::string& pBarName, const std::string& pVarName, const float& pVariable, const std::string& pParameters);
	void AddVariable(const std::string& pBarName, const std::string& pVarName, const int& pVariable, const std::string& pParameters);

	void AddWritableVariable(const std::string& pBarName, const std::string& pVarName, const float& pVariable, const std::string& pParameters);
	void AddWritableVariable(const std::string& pBarName, const std::string& pVarName, const int& pVariable, const std::string& pParameters);
	void AddWritableVariable(const std::string& pBarName, const std::string& pVarName, const KodeBoldsMath::Vector4& pVariable, const std::string& pParameters);

	void ToggleVisible();

	void DrawBars();

	static std::shared_ptr<AntTweakManager> Instance();
};