#pragma once
#include "GameCommon.hpp"


class Asteroid;
class Bullet;
class Camera;
class PlayerShip;


class Game
{
public:
	PlayerShip*   m_playerShip = nullptr;
	Asteroid*     m_asteroids[MAX_ASTEROIDS] = { nullptr };
	Bullet*       m_bullets[MAX_BULLETS] = { nullptr };
	Camera*       m_gameCamera;
	unsigned int  m_asteroidSize = 0;
	unsigned int  m_bulletSize = 0;

	Game();
	~Game();

	void Render() const;
	void RenderPlayerShip() const;
	void RenderBullets() const;
	void RenderAsteroid() const;

	void Update( float deltaSeconds );
	void UpdatePlayerShip( float deltaSeconds );
	void UpdateBullets( float deltaSeconds );
	void UpdateAsteroid( float deltaSeconds );

#pragma region Debug
	void DebugRenderAll() const;
	void DebugDrawLines() const;
#pragma endregion

	void SpawnRandomAsteroid();
	void SpawnRandomAsteroids();
	Asteroid* CreateRandomAsteroid();

	/* Physics */
	void OnBeginOverlap();
	void CheckBulletHitAsteroid();

	/* input */
	void HandleInput();
};