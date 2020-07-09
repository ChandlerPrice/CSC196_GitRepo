#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include "Object/Actor.h"
#include <iostream>
#include <string>

float speed = 300.0f;

nc::Actor player;
nc::Actor enemy;

nc::Transform transform{ {400, 300}, 4 };

float t{ 0 };

float frametime;
float roundTime{ 0 };
bool gameOver{ false };

DWORD prevTime;
DWORD deltaTime;

std::string playerFileName = "Player.txt";
std::string enemyFileName = "Enemy.txt";

bool Update(float dt)
{

	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	t = t + dt;

	frametime = dt;
	roundTime += dt;

	if (roundTime >= 30.0f) gameOver = true;

	if(gameOver) dt = dt * 0.25f;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x, y;
	Core::Input::GetMousePos(x, y);

	//nc::Vector2 target = nc::Vector2{ x, y };
	//nc::Vector2 direction = target - position;
	//direction.Normalize();
	
	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * (dt * speed); }
	nc::Vector2 direction = force;
	direction = nc::Vector2::Rotate(direction, player.GetTransform().angle);
	player.GetTransform().position += direction;

	if (Core::Input::IsPressed('A')) { player.GetTransform().angle = player.GetTransform().angle - (dt * nc::DegreesToRadians(240.0f)); }
	if (Core::Input::IsPressed('D')) { player.GetTransform().angle = player.GetTransform().angle + (dt * nc::DegreesToRadians(240.0f)); }

	player.GetTransform().position = nc::Clamp(player.GetTransform().position, { 10,10 }, { 790, 590 });

	//player.GetTransform().position.x = nc::Clamp(player.GetTransform().position.x, 10.0f, 790.0f);
	//player.GetTransform().position.y = nc::Clamp(player.GetTransform().position.y, 10.0f, 590.0f);

	//if (Core::Input::IsPressed('A')) { position += nc::Vector2::left * speed * dt; }
	//if (Core::Input::IsPressed('D')) { position += nc::Vector2::right * speed * dt; }
	//if (Core::Input::IsPressed('W')) { position += nc::Vector2::up * speed * dt; }
	//if (Core::Input::IsPressed('S')) { position += nc::Vector2::down * speed * dt; }

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime / 1000.0f).c_str());

	float v = (std::sin(t) + 1.0f) * 0.5f;

	nc::Color c = nc::Lerp(nc::Color{ 1, 0, 0}, nc::Color{ 1, 0, 1 }, v);
	graphics.SetColor(c);	

	nc::Vector2 p = nc::Lerp(nc::Vector2{ 300, 100 }, nc::Vector2{ 200, 150 }, v);
	graphics.DrawString(p.x, p.y, "Never Bring a Gun to a Knife Fight!");

	if (gameOver) graphics.DrawString(400, 300, "Game Over");

	enemy.Draw(graphics);
	player.Draw(graphics);
}

int main()
{
	DWORD ticks = GetTickCount(); //how many ticks in a sec
	std::cout << ticks / 1000 / 60 / 60 << std::endl;
	prevTime = GetTickCount();

	player.Load(playerFileName);
	enemy.Load(enemyFileName);

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
