#pragma once
class GameObject;
class CollisionListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
};

class Physics
{
	Physics();
	static Physics& Get();

	b2Vec2 gravity = { 0.f, -10.f };
	b2World world = b2World(gravity);

	CollisionListener _listener;

public:

	static void TimeStep(const float& deltaTime, int velIter, int posItr);
	static b2World& World();
};

struct PhysicsMaterial
{
	float friction = 0.5f;
	float density = 1.f;
	float restitution = 0.f;
};

class Rigidbody
{
public:
	enum Type {Static, Dynamic, Kinematic};

private:
	Type _type = Type::Static;
	Transform* _transformRef = nullptr;
	b2Body* _body = nullptr;

public:
	b2Body* operator->();
	b2Body& operator*();

	Rigidbody() = default;
	Rigidbody(Type type, Transform* transformRef);
	~Rigidbody();

	void Setup(Type type, Transform* transformRef);
	void UpdateTransform();

	Type GetType() const;

};

class BoxCollider
{
	b2PolygonShape _shape;
	
public:
	b2PolygonShape* operator->();
	b2PolygonShape& operator*();

	BoxCollider() = default;
	BoxCollider(xe::Vector2 dimensions, GameObject* user, Rigidbody& rigidbodyRef, PhysicsMaterial material = PhysicsMaterial(), bool isTrigger = false);

	void Setup(xe::Vector2 dimensions, GameObject* user, Rigidbody& rigidbodyRef, PhysicsMaterial material = PhysicsMaterial(), bool isTrigger = false);
};