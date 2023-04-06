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
}

b2World& Physics::World()
{
	return Get().world;
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
		objA->OnTriggerEnter(objB);
		objB->OnTriggerEnter(objA);
		return;
	}

	objA->OnCollisionEnter(objB);
	objB->OnCollisionEnter(objA);
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
		objA->OnTriggerExit(objB);
		objB->OnTriggerExit(objA);
		return;
	}

	objA->OnCollisionExit(objB);
	objB->OnCollisionExit(objA);
}
