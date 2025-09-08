#include "Asteroid.hpp"
#include "GameCommon.hpp"



Asteroid::Asteroid(Game* owner, Vec2 const& startPos)
	: Entity ( owner, startPos )
{
	m_health = 3;
	m_physicsRadius = ASTEROID_PHYSICS_RADIUS;
	m_cosmeticRadius = ASTEROID_COSMETIC_RADIUS;
	InitializeLocalVerts();
}

Asteroid::~Asteroid()
{

}

void Asteroid::Update(float deltaSeconds)
{
}

void Asteroid::Render() const
{
}

void Asteroid::DebugRender() const
{
}

void Asteroid::InitializeLocalVerts()
{
	/*float asteroidRadii[NUM_ASTEROID_SIDES] = {};
	for( int sideNum = 0; sideNum < NUM_ASTEROID_SIDES; ++ sideNum )
	{
		asteroidRadii[NUM_ASTEROID_SIDES] = 
	}*/

}

