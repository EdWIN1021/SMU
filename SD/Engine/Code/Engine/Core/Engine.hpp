#pragma once


class Renderer;
class Engine;
extern Engine* g_engine;


class Engine
{
public:
	Engine();
	~Engine();

	void BeginFrame();
	void EndFrame();

public:
	Renderer* m_render = nullptr;
};

