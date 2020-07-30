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
#include "Game.h"
#include <iostream>
#include <string>
#include <list>

Game game;

bool Update(float dt)
{
	bool quit = game.Update(dt);
	return quit;
}

void Draw(Core::Graphics& graphics)
{
	game.Draw(graphics);
}

int main()
{
	game.Startup();

	char name[] = "CSC196";
	Core::Init(name, 800, 600, 90);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();

	game.Shutdown();
}
