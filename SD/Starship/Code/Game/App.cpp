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

	Update(FAKE_DELTASECOND);
	Render();
}


void App::Update(float deltaSeconds)
{
	HandleAppInput();

	if (m_isPaused)
	{
		deltaSeconds = 0.f;
	}

	if (m_isSlowMo)
	{
		deltaSeconds /= 10.f;
	}

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
	constexpr int NUM_KEYS = 256;
	for( int i = 0; i < NUM_KEYS; ++ i )
	{
		m_wasKeydowPrevArray[i] = m_isKeyDownArray[i];
	}
}


void App::ResetGame()
{
	delete m_game;
	m_game = nullptr;
	m_game = new Game();
}


void App::HandleAppInput()
{
	if (g_app->WasKeyJustPressed('O'))
	{
		g_app->m_pauseAfterNextUpdate = true;
		g_app->m_isPaused = false;
	}

	if (WasKeyJustPressed('P'))
	{
		m_isPaused = !m_isPaused;
	}

	if (WasKeyJustPressed('Q'))
	{
		SetIsQuitting();
	}

	if (IsKeyHeld('T'))
	{
		m_isSlowMo = true;
	}

	if (WasKeyJustReleased('T'))
	{
		m_isSlowMo = false;
	}

	if (WasKeyJustPressed(VK_F1))
	{
		m_IsDebugMode = !m_IsDebugMode;
	}

	if (WasKeyJustPressed(VK_F8))
	{
		ResetGame();
	}
}


