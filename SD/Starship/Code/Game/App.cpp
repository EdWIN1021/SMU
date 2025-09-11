/*Engine*/
#include "Engine/Core/Engine.hpp"
#include "Engine/Renderer/Renderer.hpp"
#include "Engine/Renderer/Camera.hpp"

#include "App.hpp"
#include "Game.hpp"
#include "Bullet.hpp"

App* g_app = nullptr;


App::App()
{
	g_engine = new Engine();
	m_game = new Game();
}


App::~App()
{
	delete m_game;
	m_game = nullptr;

	delete g_engine;
	g_engine = nullptr;
}


void App::RunFrame()
{
	float fakeDeltaSecond = 1.f / 60.f;
	Update(fakeDeltaSecond);
	Render();
}


void App::Update(float deltaSeconds)
{
	m_game->Update(deltaSeconds);
	UpdateLastFrameKeys();
}


void App::Render() const
{
	g_engine->m_render->ClearScreen(Rgba8(0, 0, 0));
	m_game->Render();
}


void App::SetIsQuitting()
{
	m_isQuitting = true;
}


bool App::IsQuitting()
{
	return m_isQuitting;
}


void App::OnKeyDown(unsigned char keyCode)
{
	m_isKeyDownArray[keyCode] = true;
}


void App::OnKeyUp(unsigned char keyCode)
{
	m_isKeyDownArray[keyCode] = false;
}

bool App::IsKeyDown(unsigned char keyCode)
{
	return m_isKeyDownArray[keyCode];
}


bool App::WasKeyJustPressed(unsigned char keyCode)
{
	return m_isKeyDownArray[keyCode] && !m_wasKeydowPrevArray[keyCode];
}


bool App::WasKeyJustReleased(unsigned char keyCode)
{
	return !m_isKeyDownArray[keyCode] && m_wasKeydowPrevArray[keyCode];
}


bool App::IsKeyHeld(unsigned char keyCode)
{
	return m_isKeyDownArray[keyCode] && m_wasKeydowPrevArray[keyCode];
}

void App::UpdateLastFrameKeys()
{
	for( int i = 0; i < 256; ++ i )
	{
		m_wasKeydowPrevArray[i] = m_isKeyDownArray[i];
	}
}

