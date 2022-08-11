#pragma once
#include "Entity.h"
class Game : public Entity
{
public:
	void Start() override;
	void Update(const float& deltaTime) override;
	void Draw() override;
	void OnDestroy() override;
};

