#include "Pch.h"
#include "PortalGun.h"

#include "Portal.h"
#include "XephTools/InputSystem.h"
#include "Game.h"
#include "Window.h"

PortalGun::PortalGun()
{
	Game::AddGameObject(this);

	_portals.blue = std::make_unique<Portal>(xe::Vector2(5, 0), Direction::Up, Portal::Color::Blue);
	_portals.orange = std::make_unique<Portal>(xe::Vector2(15, 5), Direction::Up, Portal::Color::Orange);
	LinkPortals();
	
}

void PortalGun::Start()
{
	xe::InputSystem::Subscribe(xe::Mouse::Left, xe::Pressed, XE_CALLBACK(PortalGun::ShootBlue, this));
	xe::InputSystem::Subscribe(xe::Mouse::Right, xe::Pressed, XE_CALLBACK(PortalGun::ShootOrange, this));
}

void PortalGun::OnDestroy()
{
	xe::InputSystem::Unsubscribe(xe::Mouse::Left, xe::Pressed, this);
	xe::InputSystem::Unsubscribe(xe::Mouse::Right, xe::Pressed, this);
}

//Called On LeftClick
void PortalGun::ShootBlue()
{
	_portals.blue = std::make_unique<Portal>(Window::PixelToUnit(xe::InputSystem::MousePosition()), Direction::Up, Portal::Color::Blue);
	LinkPortals();
}

//Called On RightClick
void PortalGun::ShootOrange()
{
	_portals.blue = std::make_unique<Portal>(Window::PixelToUnit(xe::InputSystem::MousePosition()), Direction::Up, Portal::Color::Orange);
	LinkPortals();
}

void PortalGun::LinkPortals()
{
	if (!_portals.blue && !_portals.orange)
		return;
	if (!_portals.blue)
	{
		_portals.orange->SetPartner(nullptr);
		return;
	}
	if (!_portals.orange)
	{
		_portals.blue->SetPartner(nullptr);
		return;
	}

	_portals.blue->SetPartner(_portals.orange.get());
	_portals.orange->SetPartner(_portals.blue.get());
}
