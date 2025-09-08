#pragma once

class App;
extern App* g_app;

class Game;
class Camera;


class App
{
public:
	bool     m_isQuitting = false;
	bool     m_isPaused = false;
	bool     m_isSlowMo = false;
	bool     m_pauseAfterNextUpdate = false;
	Game*    m_game;
	Camera*  m_gameCamera;

private:
	bool currentlyDown[256]{};
	bool wasDownLastFrame[256]{};

public:
	App();
	~App();

	void RunFrame();
	void Update( float deltaSeconds );
	void Render() const;

	void SetIsQuitting();
	bool IsQuitting();

	void OnKeyDown(unsigned char keyCode);
	void OnKeyUp(unsigned char keyCode);

	bool IsKeyDown(unsigned char keyCode);
	bool WasKeyJustPressed(unsigned char keyCode);  // ??
};