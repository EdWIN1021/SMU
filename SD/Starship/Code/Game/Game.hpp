#pragma once
#include "GameCommon.hpp"
#include "PlayerShip.hpp"


class Asteroid;
class Bullet;


class Game
{
public:
	PlayerShip* m_playerShip = nullptr;
	Asteroid* m_asteroids[MAX_ASTEROIDS] = {};
	Bullet* m_bullets[MAX_BULLETS] = {};

	Game();
	~Game();
};