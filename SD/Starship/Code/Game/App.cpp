#include "App.hpp"
#include "Engine/Core/Engine.hpp"
#include "Game.hpp"
#include <Engine/Renderer/Renderer.cpp>
#include "Engine/Renderer/Camera.hpp"
#include "PlayerShip.hpp"


App* g_app = nullptr;


App::App()
{
	g_engine = new Engine();
	m_game = new Game();
	m_gameCamera = new Camera(Vec2(0, 0), Vec2(WORLD_SIZE_X, WORLD_SIZE_Y));
}

App::~App()
{
	delete m_game;
	m_game = nullptr;

	delete g_engine;
	g_engine = nullptr;

	delete m_gameCamera;
	m_gameCamera = nullptr;
}

void App::RunFrame()
{
	float fakeDeltaSecond = 1.f / 60.f;

	Update(fakeDeltaSecond);
	Render();
}

void App::Update(float deltaSeconds)
{
	m_game->m_playerShip->Update(deltaSeconds);
}

void App::Render() const
{
	g_engine->m_render->BeginCamera(*m_gameCamera);
	g_engine->m_render->ClearScreen(Rgba8(0, 0, 0));
	m_game->m_playerShip->Render();
}

void App::SetIsQuitting()
{
	m_isQuitting = true;
}

bool App::IsKeyDown(unsigned char keyCode)
{
	return currentlyDown[keyCode];
}

bool App::IsQuitting()
{
	return m_isQuitting;
}

void App::OnKeyDown(unsigned char keyCode)
{
	currentlyDown[keyCode] = true;
}

void App::OnKeyUp(unsigned char keyCode)
{
	currentlyDown[keyCode] = false;
}
