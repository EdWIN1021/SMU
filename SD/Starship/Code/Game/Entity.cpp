#include "Entity.hpp"
#include "GameCommon.hpp"
#include <Engine/Math/MathUtils.hpp>
#include "Engine/Math/Vec2.hpp"
#include "Engine/Core/Rgba8.hpp"

Entity::Entity(Game* game, const Vec2& position)
	: m_game(game)
	, m_position(position)
{

}


Entity::~Entity()
{

}


void Entity::DebugRender() const
{
	if(m_isDead)
	{
		return;
	}

	DebugDrawRing(m_position, m_physicsRadius, 0.2f, Rgba8(0, 255, 255));
	DebugDrawRing(m_position, m_cosmeticRadius, 0.2f, Rgba8(255, 0, 255));

	/* forward */
	DebugDrawLine(m_position, m_position + GetForwardNormal() * m_cosmeticRadius, 0.1f, Rgba8(255, 0, 0));

	/* left */
	Vec2 leftVector = GetForwardNormal().GetRotatedBy90Degrees();
	DebugDrawLine(m_position, m_position + leftVector * m_cosmeticRadius, 0.1f, Rgba8(0, 255, 0));

	/* velocity */
	DebugDrawLine(m_position, m_position + m_velocity, 0.1f, Rgba8(255, 255, 0));
}


bool Entity::IsOffscreen() const
{
	if( m_position.x > WORLD_SIZE_X + m_cosmeticRadius )
		return true;

	if( m_position.y > WORLD_SIZE_Y + m_cosmeticRadius )
		return true;

	if( m_position.x < - m_cosmeticRadius )
		return true;

	if( m_position.y < -m_cosmeticRadius )
		return true;

	return false;
}


Vec2 Entity::GetForwardNormal() const
{
	return Vec2(CosDegrees(m_orientationDegrees), SinDegrees(m_orientationDegrees));
}

bool Entity::IsAlive() const
{
	return !m_isDead;
}

