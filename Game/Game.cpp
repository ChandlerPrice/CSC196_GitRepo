#include "Game.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include "Object/Actor.h"
#include "Actors/Enemy.h"
#include "Actors/Player.h"
#include "Object/Scene.h"
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include <iostream>
#include <string>
#include <list>

static const int WIDTH = 800;
static const int HEIGHT = 800;
nc::Color colors[] = { nc::Color::red, nc::Color::green, nc::Color::yellow };
nc::Color color;

void Game::Startup()
{
	m_scene.Startup();
	g_particleSystem.Startup();
	g_audioSystem.Startup();
	m_scene.SetGame(this);
	m_state = eState::INIT;
}

void Game::Shutdown()
{
	m_scene.Shutdown();
	g_particleSystem.Shutdown();
	g_audioSystem.Shutdown();
}

bool Game::Update(float dt)
{
	m_frametime = dt;
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	Player* p;

	switch (m_state)
	{
	case Game::eState::INIT:
		g_audioSystem.AddAudio("Shoot", "Laser_Shoot.wav");
		g_audioSystem.AddAudio("Explosion", "Explosion.wav");
		m_state = eState::TITLE;
		break;
	case Game::eState::TITLE:
		color = colors[rand() % 3];
		if (Core::Input::IsPressed(VK_SPACE))
		{
			m_state = eState::START_GAME;
		}
		break;
	case Game::eState::START_GAME:
	{
		Player* player = new Player;
		player->Load("Player.txt");
		m_scene.AddActor(player);
		m_scene.GetGame()->ResetPoints();
		m_scene.GetGame()->ResetLives();

		for (size_t i = 0; i < 5; i++)
		{
			Enemy* enemy = new Enemy;
			enemy->Load("Enemy.txt");
			enemy->SetTarget(m_scene.GetActor<Player>());
			enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
			m_scene.AddActor(enemy);
		}
		m_state = eState::GAME;
	}
		break;
	case Game::eState::GAME:
	{
		m_spawnTime += dt; 
		m_spawnTimeBoss += dt;
		p = m_scene.GetActor<Player>();
		if (m_spawnTime >= 1.5f)
		{
			m_spawnTime = 0.0f;

			Enemy* enemy = new Enemy;
			enemy->Load("Enemy.txt");
			enemy->SetTarget(p);
			enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
			m_scene.AddActor(enemy);
		}
		if (m_spawnTimeBoss >= 10)
		{
			m_spawnTimeBoss = 0.0f;

			Enemy* enemy = new Enemy;
			enemy->Load("EnemyBoss.txt");
			enemy->SetTarget(p);
			enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
			m_scene.AddActor(enemy);
			enemy->SetFireRate(0.1f);
		}
		m_scene.Update(dt);
	}
		break;
	case Game::eState::GAME_OVER:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			m_scene.Shutdown();
			m_state = eState::START_GAME;
		}
		break;
	default:
		break;
	}

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		int x, y;
		Core::Input::GetMousePos(x, y);

		nc::Color colors[] = { nc::Color::red, nc::Color::green, nc::Color::yellow };

		color = colors[rand() % 3];

		g_particleSystem.Create({ x,y }, 0, 180, 30, color, 1, 100, 200);
	}

	g_particleSystem.Update(dt);
	g_audioSystem.Update(dt);

	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 0, 1, 0 });
	graphics.DrawString(10, 10, std::to_string(m_frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / m_frametime).c_str());
	nc::Color colors[] = { nc::Color::red, nc::Color::green, nc::Color::yellow };

	g_particleSystem.Draw(graphics);

	switch (m_state)
	{
	case Game::eState::INIT:
		color = colors[rand() % 3];
		graphics.SetColor(color);
		break;
	case Game::eState::TITLE:
		color = colors[rand() % 3];
		graphics.SetColor(color);
		graphics.DrawString(400, 300, "NEVER BRING A GUN TO A KNIFE FIGHT");
		graphics.DrawString(400, 320, "PRESS SPACE TO START");
		break;
	case Game::eState::START_GAME:
		color = colors[rand() % 3];
		graphics.SetColor(color);
		graphics.DrawString(750, 20, std::to_string(m_score).c_str());
		graphics.DrawString(750, 30, std::to_string(m_lives).c_str());
		graphics.DrawString(700, 20, "SCORE: ");
		graphics.DrawString(700, 30, "LIVES: ");
		m_scene.Draw(graphics);
		break;
	case Game::eState::GAME:
		graphics.SetColor(color);
		graphics.DrawString(750, 20, std::to_string(m_score).c_str());
		graphics.DrawString(750, 30, std::to_string(m_lives).c_str());
		graphics.DrawString(700, 20, "SCORE: ");
		graphics.DrawString(700, 30, "LIVES: ");
		m_scene.Draw(graphics);
		break;
	case Game::eState::GAME_OVER:
		color = colors[rand() % 3];
		graphics.SetColor(color);
		graphics.DrawString(400, 300, "GAME OVER");
		graphics.DrawString(400, 320, "PRESS SPACE TO RESTART");
		graphics.DrawString(450, 340, std::to_string(m_score).c_str());
		graphics.DrawString(400, 340, "SCORE: ");
		break;
	default:
		break;
	}
}
