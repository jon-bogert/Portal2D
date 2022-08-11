#include "Pch.h"
#include "GameObject.h"

void Transform::FixRotation()
{
	while (rotation >= 360.f) rotation -= 360.f;
	while (rotation < 0.f) rotation += 360.f;
}
