#pragma once
#include "core.h"
#include <Object\Scene.h>

class Game
{
public:
	enum class eState
	{
		INIT,
		TITLE,
		START_GAME,
		GAME,
		GAME_OVER
	};

public:
	void Startup();
	void Shutdown();

	bool Update(float dt);
	void Draw(Core::Graphics& graphics);

	void AddPoints(int points) { m_score += points; }
	void ResetPoints() { m_score = 0; }

	float GetLives() { return m_lives; }
	void AddLife(float life) { m_lives = m_lives+life; }
	void ResetLives() { m_lives = 3; }

	void SetState(eState state) { m_state = state; }
	eState GetState() { return m_state; }

protected:
	eState m_state{eState::INIT};
	int m_lives{ 3 };
	int m_score{ 0 };
	nc::Scene m_scene;
	float m_frametime;
	float m_spawnTime = 0;
	float m_spawnTimeBoss = 0;

	static const int WIDTH;
	static const int HEIGHT;
};

