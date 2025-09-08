#include "Entity.hpp"
#include "GameCommon.hpp"
#include <Engine/Math/MathUtils.hpp>
#include "Engine/Math/Vec2.hpp"

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
