/* Engine */
#include "Engine/Core/ErrorWarningAssert.hpp"
#include "Engine/Core/StringUtils.hpp"
#include "Engine/Renderer/Renderer.hpp"
#include "Engine/Renderer/Camera.hpp"
#include "Engine/Math/MathUtils.hpp"
#include "Engine/Math/RandomNumberGenerator.hpp"
#include "Engine/Math/Vec2.hpp"

#include "App.hpp"
#include "Game.hpp"
#include "PlayerShip.hpp"
#include "Asteroid.hpp"
#include "Bullet.hpp"


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
	HandleGameInput();

	UpdatePlayerShip(deltaSeconds);
	UpdateBullets(deltaSeconds);
	UpdateAsteroid(deltaSeconds);

	OnBeginOverlap();

	DestroyGarbageEntities();
}


void Game::UpdatePlayerShip(float deltaSeconds)
{
	m_playerShip->Update(deltaSeconds);
}


void Game::UpdateBullets(float deltaSeconds)
{
	for (int bulletIndex = 0; bulletIndex < MAX_BULLETS; ++bulletIndex)
	{
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

	if(g_app->m_IsDebugMode)
	{
		DebugRenderAll();
	}
	

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


Asteroid* Game::SpawnNewRandomAsteroid()
{
	for (int asteroidIndex = 0; asteroidIndex < MAX_ASTEROIDS; ++asteroidIndex)
	{
		if (!m_asteroids[asteroidIndex])
		{
			m_asteroids[asteroidIndex] = CreateRandomAsteroid();
			return m_asteroids[asteroidIndex];
		}
	}

	ERROR_RECOVERABLE("Cannot spawn more asteroids! Maximum allowed is 12");
	return nullptr;
}

Bullet* Game::CreateBullet()
{
	for ( int bulletIndex = 0; bulletIndex < MAX_BULLETS; ++ bulletIndex )
	{
		if (!m_bullets[bulletIndex])
		{
			m_bullets[bulletIndex] = new Bullet(this, m_playerShip->m_position + m_playerShip->GetForwardNormal());
			m_bullets[bulletIndex]->m_orientationDegrees = m_playerShip->m_orientationDegrees;
			m_bullets[bulletIndex]->m_velocity = m_playerShip->GetForwardNormal() * BULLET_SPEED;
			return m_bullets [bulletIndex];
		}
	}

	ERROR_RECOVERABLE("Cannot fire more bullets! Maximum allowed is 20.");
	return nullptr;
}

void Game::DestroyGarbageEntities()
{
	for (int asteroidIndex = 0; asteroidIndex < MAX_ASTEROIDS; ++ asteroidIndex )
	{
		if(m_asteroids[asteroidIndex] && m_asteroids[asteroidIndex]->m_isGarbage)
		{
			delete m_asteroids[asteroidIndex];
			m_asteroids[asteroidIndex] = nullptr;
		}
	}

	for (int bulletIndex = 0; bulletIndex < MAX_BULLETS; ++ bulletIndex)
	{
		if (m_bullets[bulletIndex] && m_bullets[bulletIndex]->m_isGarbage)
		{
			delete m_bullets[bulletIndex];
			m_bullets[bulletIndex] = nullptr;
		}
	}
}

void Game::SpawnRandomAsteroids()
{
	for ( int asteroidIndex = 0; asteroidIndex < NUM_STARTING_ASTEROIDS; ++ asteroidIndex )
	{
		m_asteroids[asteroidIndex] = SpawnNewRandomAsteroid();
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
	DetectShipAsteroidCollision();
	DetectBulletAsteroidCollision();
}


void Game::DetectShipAsteroidCollision()
{
	for (int asteroidIndx = 0; asteroidIndx < MAX_ASTEROIDS; ++asteroidIndx)
	{
		Asteroid* asteroid = m_asteroids[asteroidIndx];
		if (asteroid)
		{
			bool isPlayerShipOverlapped = DoDiscsOverlap(
				m_playerShip->m_position,
				m_playerShip->m_physicsRadius,
				asteroid->m_position,
				asteroid->m_physicsRadius
			);

			if (isPlayerShipOverlapped)
			{
				m_playerShip->Die();
				asteroid->m_isDead = true;
				asteroid->m_isGarbage = true;
			}
		}
	}
}

void Game::DetectBulletAsteroidCollision()
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

void Game::HandleGameInput()
{
	if ( g_app->WasKeyJustPressed('I') )
	{
		SpawnNewRandomAsteroid();
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
