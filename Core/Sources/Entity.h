#pragma once
class Entity
{
public:
	Entity() {}
	virtual  ~Entity() {}

	virtual void Start() = 0;
	virtual void Update(const float& deltaTime) = 0;
	virtual void Draw() = 0;
	virtual void OnDestroy() = 0;
};

