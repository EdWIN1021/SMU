/* Engine */
#include "Engine/Math/RandomNumberGenerator.hpp"
#include "Engine/Math/Vec2.hpp"

#include "Engine/Core/ErrorWarningAssert.hpp"
#include "Engine/Core/StringUtils.hpp"

#include "Engine/Renderer/Renderer.hpp"
#include "Engine/Renderer/Camera.hpp"

#include "App.hpp"
#include "Game.hpp"
#include "PlayerShip.hpp"
#include "Asteroid.hpp"
#include "Bullet.hpp"
#include <Engine/Math/MathUtils.hpp>


Game::Game()
{
	m_playerShip = new PlayerShip(this, Vec2(WORLD_CENTER_X, WORLD_CENTER_Y));
	m_gameCamera = new Camera(Vec2(0, 0), Vec2(WORLD_SIZE_X, WORLD_SIZE_Y));
	SpawnRandomAsteroids();
}


Game::~Game()
{
	delete m_playerShip;
	m_playerShip = nullptr;

	delete g_rng;
	g_rng = nullptr;

	delete m_gameCamera;
	m_gameCamera = nullptr;
}


void Game::Update(float deltaSeconds)
{
	HandleInput();

	if(g_app->m_isPaused)
	{
		deltaSeconds = 0.f;
	}

	if(g_app->m_isSlowMo)
	{
		deltaSeconds /= 10.f;
	}

	UpdatePlayerShip(deltaSeconds);
	UpdateBullets(deltaSeconds);
	UpdateAsteroid(deltaSeconds);

	OnBeginOverlap();
}


void Game::UpdatePlayerShip(float deltaSeconds)
{
	m_playerShip->Update(deltaSeconds);
}


void Game::UpdateBullets(float deltaSeconds)
{
	for (int bulletIndex = 0; bulletIndex < MAX_BULLETS; ++bulletIndex)
	{
		if (m_bullets[bulletIndex] && m_bullets[bulletIndex]->m_isGarbage)
		{
			delete m_bullets[bulletIndex];
			m_bullets[bulletIndex] = nullptr;
			m_bulletSize--;
			continue;
		}
		
		
		if (m_bullets[bulletIndex])
		{
			m_bullets[bulletIndex]->Update(deltaSeconds);
		}
	}
}


void Game::UpdateAsteroid(float deltaSeconds)
{
	for (int asteroidIndex = 0; asteroidIndex < MAX_ASTEROIDS; ++ asteroidIndex)
	{
		if (m_asteroids[asteroidIndex] && m_asteroids[asteroidIndex]->m_isGarbage)
		{
			delete m_asteroids[asteroidIndex];
			m_asteroids[asteroidIndex] = nullptr;
			m_asteroidSize--;
			continue;
		}


		if (m_asteroids[asteroidIndex])
		{
			m_asteroids[asteroidIndex]->Update(deltaSeconds);
		}
	}
}


void Game::Render() const
{
	g_engine->m_render->BeginCamera(*m_gameCamera);

	RenderPlayerShip();
	RenderBullets();
	RenderAsteroid();
	DebugRenderAll();

	g_engine->m_render->EndCamera(*m_gameCamera);
}


void Game::RenderPlayerShip() const
{
	m_playerShip->Render();
}


void Game::RenderAsteroid() const
{
	for (int asteroidIndex = 0; asteroidIndex < MAX_ASTEROIDS; ++asteroidIndex)
	{
		if (m_asteroids[asteroidIndex])
		{
			m_asteroids[asteroidIndex]->Render();
			m_asteroids[asteroidIndex]->DebugRender();
		}
	}
}


void Game::RenderBullets() const
{
	for (int bulletIndex = 0; bulletIndex < MAX_BULLETS; ++bulletIndex)
	{
		if (Bullet* bullet = m_bullets[bulletIndex])
		{
			bullet->Render();
			bullet->DebugRender();
		}
	}
}


void Game::SpawnRandomAsteroid()
{
	for( int asteroidIndex = 0; asteroidIndex < MAX_ASTEROIDS; ++ asteroidIndex)
	{
		if(!m_asteroids[asteroidIndex])
		{
			m_asteroids[asteroidIndex] = CreateRandomAsteroid();
			m_asteroidSize++;
			return;
		}
	}
}

void Game::SpawnRandomAsteroids()
{
	while (m_asteroidSize < MAX_ASTEROIDS)
	{
		m_asteroids[m_asteroidSize++] = CreateRandomAsteroid();
	}
}


Asteroid* Game::CreateRandomAsteroid()
{
	float randomPositionX = g_rng->RollRandomFloatInRange(0, WORLD_SIZE_X);
	float randomPositionY = g_rng->RollRandomFloatInRange(0, WORLD_SIZE_Y);
	float randomOrientation = g_rng->RollRandomFloatInRange(0, 360.f);
	float randomAngularVelocity = g_rng->RollRandomFloatInRange(-200, 200);
	Vec2  fowardVector = Vec2::MakeFromPolarDegrees(randomOrientation);

	Asteroid* asteroid = new Asteroid(this, Vec2(randomPositionX, randomPositionY));

	asteroid->m_health = 3;
	asteroid->m_orientationDegrees = randomOrientation;
	asteroid->m_angularVelocity = randomAngularVelocity;
	asteroid->m_velocity = fowardVector * ASTEROID_SPEED;

	return asteroid;
}


void Game::OnBeginOverlap()
{
	for ( int asteroidIndx = 0; asteroidIndx < MAX_ASTEROIDS; ++ asteroidIndx)
	{
		Asteroid* asteroid = m_asteroids[asteroidIndx];
		if(asteroid)
		{
			bool isPlayerShipOverlapped = DoDiscsOverlap(
				m_playerShip->m_position,
				m_playerShip->m_physicsRadius,
				asteroid->m_position,
				asteroid->m_physicsRadius
			);

			if (isPlayerShipOverlapped)
			{
				m_playerShip->m_isDead = true;
				asteroid->m_isDead = true;
				asteroid->m_isGarbage = true;
			}
		}
	}

	CheckBulletHitAsteroid();
}

void Game::CheckBulletHitAsteroid()
{
	for (int asteroidIndx = 0; asteroidIndx < MAX_ASTEROIDS; ++asteroidIndx)
	{
		for (int bulletIndex = 0; bulletIndex < MAX_BULLETS; ++bulletIndex)
		{
			if (m_bullets[bulletIndex] && m_asteroids[asteroidIndx])
			{
				bool isAsteroidHit = DoDiscsOverlap(
					m_asteroids[asteroidIndx]->m_position,
					m_asteroids[asteroidIndx]->m_physicsRadius,
					m_bullets[bulletIndex]->m_position,
					m_bullets[bulletIndex]->m_physicsRadius
				);

				if (isAsteroidHit)
				{
					m_asteroids[asteroidIndx]->m_health--;
					if( m_asteroids[asteroidIndx]->m_health <= 0 )
					{
						m_asteroids[asteroidIndx]->m_isDead = true;
						m_asteroids[asteroidIndx]->m_isGarbage = true;
					}

					m_bullets[bulletIndex]->m_isDead = true;
					m_bullets[bulletIndex]->m_isGarbage = true;
				}
			}
		}
	}
}

void Game::HandleInput()
{
	if( g_app->WasKeyJustPressed('P') )
	{
		g_app->m_isPaused = !g_app->m_isPaused;
	}

	if( g_app->WasKeyJustPressed('O') )
	{
		g_app->m_pauseAfterNextUpdate = true;
		g_app->m_isPaused = false;
	}

	if (g_app->IsKeyHeld('T'))
	{
		g_app->m_isSlowMo = true;
	}

	if (g_app->WasKeyJustReleased('T'))
	{
		g_app->m_isSlowMo = false;
	}

	if ( g_app->WasKeyJustPressed('I') )
	{
		if(m_asteroidSize < MAX_ASTEROIDS)
		{
			SpawnRandomAsteroid();
		}
		else
		{
			RecoverableWarning(
				__FILE__,
				__FUNCTION__,
				__LINE__,
				Stringf("Cannot spawn more asteroids! Maximum allowed is %i.", MAX_ASTEROIDS),
				"Size of asteroids > MAX_ASTEROIDS"
			);
		}
	}
}


/* Debug */
void Game::DebugRenderAll() const
{
	DebugDrawLines();
	m_playerShip->DebugRender();
}

void Game::DebugDrawLines() const
{
	if(!m_playerShip->IsAlive())
	{
		return;
	}

	for (int asteroidIndex = 0; asteroidIndex < MAX_ASTEROIDS; ++asteroidIndex)
	{
		if(m_asteroids[asteroidIndex] && m_asteroids[asteroidIndex]->IsAlive())
		{
			DebugDrawLine(m_playerShip->m_position, m_asteroids[asteroidIndex]->m_position, 0.1f, Rgba8(50, 50, 50));
		}
	}

	for (int bulletIndex = 0; bulletIndex < MAX_BULLETS; ++bulletIndex)
	{
		if (m_bullets[bulletIndex] && m_bullets[bulletIndex]->IsAlive())
		{
			DebugDrawLine(m_playerShip->m_position, m_bullets[bulletIndex]->m_position, 0.1f, Rgba8(50, 50, 50));
		}
	}
}
