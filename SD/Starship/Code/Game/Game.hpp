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
	Asteroid*     m_asteroids[MAX_ASTEROIDS] = {};
	Bullet*       m_bullets[MAX_BULLETS] = {};
	Camera*       m_gameCamera;

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




	void SpawnRandomAsteroids();
	Asteroid* CreateRandomAsteroid();
	Asteroid* SpawnNewRandomAsteroid();
	
	Bullet* CreateBullet();

	void DestroyGarbageEntities();

	/* Physics */
	void OnBeginOverlap();
	void DetectShipAsteroidCollision();
	void DetectBulletAsteroidCollision();

	/* input */
	void HandleGameInput();

private:
#pragma region Debug
	void DebugRenderAll() const;
	void DebugDrawLines() const;
#pragma endregion
};