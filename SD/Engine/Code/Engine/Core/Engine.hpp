#pragma once

class Engine;
class Renderer;

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

