#pragma once
#include "GameObject.h"

class Portal;

struct PortalPair
{
	std::unique_ptr<Portal> blue = nullptr;
	std::unique_ptr<Portal> orange = nullptr;
};

class PortalGun : public GameObject
{
	PortalPair _portals;

public:
	PortalGun();

	void Start() override;
	void OnDestroy() override;

private:
	void ShootBlue();
	void ShootOrange();

	void LinkPortals();
};