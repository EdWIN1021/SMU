#include "Engine.hpp"
#include "../Renderer/Renderer.hpp"


Engine* g_engine = nullptr;

Engine::Engine()
{
	m_render = new Renderer();
	m_render->Startup();
}

Engine::~Engine()
{
	m_render->Shutdown();

	delete m_render;
	m_render = nullptr;
}

void Engine::BeginFrame()
{
	m_render->BeginFrame();
}

void Engine::EndFrame()
{
	m_render->EndFrame();
}
