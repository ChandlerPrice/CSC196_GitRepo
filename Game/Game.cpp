#include "core.h"
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
#include <iostream>
#include <string>
#include <list>

nc::Scene scene;

float frametime;
float spawnTime = 0;

bool Update(float dt)
{
	frametime = dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	spawnTime += dt;
	if (spawnTime >= 3.0f)
	{
		spawnTime = 0.0f;

		Enemy* enemy = new Enemy;
		enemy->Load("Enemy.txt");
		enemy->SetTarget(scene.GetActor<Player>());
		enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
		scene.AddActor(enemy);
	}

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		int x, y;
		Core::Input::GetMousePos(x, y);

		nc::Color colors[] = { nc::Color::red, nc::Color::green, nc::Color::blue };
		nc::Color color = colors[rand() % 3];

		g_particleSystem.Create({ x,y }, 0, 180, 30, color, 1, 100, 200);
	}

	g_particleSystem.Update(dt);
	scene.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 0, 1, 0 });
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());

	g_particleSystem.Draw(graphics);
	scene.Draw(graphics);
}

int main()
{
	scene.Startup();
	g_particleSystem.Startup();

	Player* player = new Player;
	player->Load("Player.txt");
	scene.AddActor(player);

	for (size_t i = 0; i < 1; i++)
	{
		Enemy* enemy = new Enemy;
		enemy->Load("Enemy.txt");
		enemy->SetTarget(scene.GetActor<Player>());
		enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
		scene.AddActor(enemy);
	}

	char name[] = "CSC196";
	Core::Init(name, 800, 600, 90);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();

	scene.Shutdown();
	g_particleSystem.Shutdown();
}
