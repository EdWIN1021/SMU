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

private:
	bool m_isKeyDownArray[256]{};
	bool m_wasKeydowPrevArray[256]{};

public:
	App();
	~App();

	void RunFrame();
	void Update( float deltaSeconds );
	void Render() const;

	void SetIsQuitting();
	bool IsQuitting();

	void UpdateLastFrameKeys();

#pragma region Input
	bool IsKeyDown(unsigned char keyCode);
	void OnKeyDown(unsigned char keyCode);
	void OnKeyUp(unsigned char keyCode);
	bool WasKeyJustPressed(unsigned char keyCode);
	bool WasKeyJustReleased(unsigned char keyCode);
	bool IsKeyHeld(unsigned char keyCode);
#pragma endregion
}; 