#pragma once
class Scene
{
protected:
	Scene() = default;

public:
	virtual ~Scene() {};
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void OnLoad() = 0;
};

