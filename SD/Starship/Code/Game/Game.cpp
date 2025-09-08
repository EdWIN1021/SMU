#include "Game.hpp"
#include "PlayerShip.hpp"

Game::Game()
{
	m_playerShip = new PlayerShip(this, Vec2(WORLD_CENTER_X, WORLD_CENTER_Y));
}

Game::~Game()
{
	delete m_playerShip;
	m_playerShip = nullptr;
}
