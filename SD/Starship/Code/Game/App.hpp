#pragma once


class Game;
class Camera;
class App;
extern App* g_app;

constexpr float FAKE_DELTASECOND = 1.f / 60.f;

class App
{
public:
	bool     m_isQuitting = false;
	bool     m_isPaused = false;
	bool     m_isSlowMo = false;
	bool     m_pauseAfterNextUpdate = false;
	bool     m_IsDebugMode = false;
	Game* m_game;

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
	void ResetGame();

#pragma region Input
	void HandleAppInput();
	bool IsKeyDown(unsigned char keyCode);
	void OnKeyDown(unsigned char keyCode);
	void OnKeyUp(unsigned char keyCode);
	bool IsKeyHeld(unsigned char keyCode);
	bool WasKeyJustPressed(unsigned char keyCode);
	bool WasKeyJustReleased(unsigned char keyCode);
	void UpdateLastFrameKeys();
#pragma endregion
}; 