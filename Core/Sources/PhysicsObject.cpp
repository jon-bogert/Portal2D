#include "Pch.h"
#include "PhysicsObject.h"

sf::FloatRect* PhysicsObject::GetBoxCollider()
{
	return &boxCollider;
}

void PhysicsObject::UpdateCollider()
{
	boxCollider.left = transform.position.x - boxCollider.width * 0.5f;
	boxCollider.top = transform.position.x + boxCollider.height * 0.5f;
}

bool PhysicsObject::GetCollision(PhysicsObject* other)
{
	return boxCollider.intersects(*other->GetBoxCollider());
}
