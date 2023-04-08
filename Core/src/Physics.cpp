#include "Pch.h"
#include "Physics.h"
#include "GameObject.h"

Physics::Physics()
{
	world.SetContactListener(&_listener);
}

Physics& Physics::Get()
{
	static Physics inst;
	return inst;
}

void Physics::TimeStep(const float& deltaTime, int velIter, int posItr)
{
	Get().world.Step(deltaTime, velIter, posItr);
	Get().CollisionCallbacks();
}

void Physics::AddCollisionPair(GameObject* a, GameObject* b, bool isTrigger, bool isExit)
{
	Get()._collisionPairs.push_back({ a, b, isTrigger, isExit });
}

b2World& Physics::World()
{
	return Get().world;
}

void Physics::CollisionCallbacks()
{
	for (CollisionPair& cp : Get()._collisionPairs)
	{
		if (cp.isTrigger && cp.isExit)
		{
			cp.a->OnTriggerExit(cp.b);
			cp.b->OnTriggerExit(cp.a);
		}
		else if (cp.isTrigger)
		{
			cp.a->OnTriggerEnter(cp.b);
			cp.b->OnTriggerEnter(cp.a);
		}
		else if (cp.isExit)
		{
			cp.a->OnCollisionExit(cp.b);
			cp.b->OnCollisionExit(cp.a);
		}
		else
		{
			cp.a->OnCollisionEnter(cp.b);
			cp.b->OnCollisionEnter(cp.a);
		}
	}
	_collisionPairs.clear();
}

b2Body* Rigidbody::operator->()
{
	return _body;
}

b2Body& Rigidbody::operator*()
{
	return *_body;
}

Rigidbody::Rigidbody(Type type, Transform* transformRef)
{
	Setup(type, transformRef);
}

Rigidbody::~Rigidbody()
{
	//Physics::World().DestroyBody(_body);
}

void Rigidbody::Setup(Type type, Transform* transformRef)
{
	_type = type;
	_transformRef = transformRef;

	b2BodyDef def;
	switch (_type)
	{
	case Type::Static:
		def.type = b2_staticBody;
		break;
	case Type::Dynamic:
		def.type = b2_dynamicBody;
		break;
	case Type::Kinematic:
		def.type = b2_dynamicBody;
		break;
	}
	def.position.Set(_transformRef->position.x, _transformRef->position.y);
	def.angle = -_transformRef->rotation.GetRad();
	_body = Physics::World().CreateBody(&def);
}

void Rigidbody::UpdateTransform()
{
	_transformRef->position = _body->GetPosition();
	_transformRef->rotation.SetRad(-_body->GetAngle());
}

Rigidbody::Type Rigidbody::GetType() const
{
	return _type;
}

xe::Vector2 Rigidbody::GetVelocity() const
{
	return _body->GetLinearVelocity();
}

BoxCollider::BoxCollider(xe::Vector2 dimensions, GameObject* user, Rigidbody& rigidbodyRef, PhysicsMaterial material, bool isTrigger)
{
	Setup(dimensions, user, rigidbodyRef, material, isTrigger);
}

b2PolygonShape* BoxCollider::operator->()
{
	return &_shape;
}

b2PolygonShape& BoxCollider::operator*()
{
	return _shape;
}

void BoxCollider::Setup(xe::Vector2 dimensions, GameObject* user, Rigidbody& rigidbodyRef, PhysicsMaterial material, bool isTrigger)
{
	_shape.SetAsBox(dimensions.x * 0.5f, dimensions.y * 0.5f);
	b2FixtureDef fixDef;
	fixDef.shape = &_shape;

	fixDef.friction = material.friction;
	fixDef.density = material.density;
	fixDef.restitution = material.restitution;

	fixDef.isSensor = isTrigger;
	fixDef.userData.pointer = (uintptr_t)user;

	rigidbodyRef->CreateFixture(&fixDef);
}

void CollisionListener::BeginContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	GameObject* objA = (GameObject*)fixtureA->GetUserData().pointer;
	GameObject* objB = (GameObject*)fixtureB->GetUserData().pointer;

	// Check if one of the fixtures is a sensor
	if (fixtureA->IsSensor() || fixtureB->IsSensor())
	{
		Physics::AddCollisionPair(objA, objB, true);
		return;
	}

	Physics::AddCollisionPair(objA, objB);
}

void CollisionListener::EndContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	GameObject* objA = (GameObject*)fixtureA->GetUserData().pointer;
	GameObject* objB = (GameObject*)fixtureB->GetUserData().pointer;

	// Check if one of the fixtures is a sensor
	if (fixtureA->IsSensor() || fixtureB->IsSensor())
	{
		Physics::AddCollisionPair(objA, objB, true, true);
		return;
	}

	Physics::AddCollisionPair(objA, objB, false, true);
}
