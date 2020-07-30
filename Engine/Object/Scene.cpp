#include "pch.h"
#include "Scene.h"

namespace nc 
{
	void nc::Scene::Startup()
	{
		m_dtMultiplier = 1;
	}

	void nc::Scene::Shutdown()
	{
		RemoveAllActor();
	}

	void nc::Scene::Update(float dt)
	{
		//check actor collisions
		std::vector<Actor*> actors{ m_actors.begin(), m_actors.end() };
		for (size_t i = 0; i < actors.size(); i++)
		{
			for (size_t j = i + 1; j < actors.size(); j++)
			{
				float distance = Vector2::Distance(actors[i]->GetTransform().position, actors[j]->GetTransform().position);
				if (distance <= (actors[i]->GetRadius() + actors[j]->GetRadius()))
				{
					actors[i]->OnCollision(actors[j]);
					actors[j]->OnCollision(actors[i]);
				}
			}
		}

		//remove destroyed actors
		auto iter = m_actors.begin();
		while (iter != m_actors.end())
		{
			if ((*iter)->IsDestroy())
			{
				delete* iter;
				iter = m_actors.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		for (nc::Actor* actor : m_actors)
		{
			if (actor->GetType() != Actor::eType::PLAYER)
			{
				actor->Update(dt * m_dtMultiplier);
			}
			else
			{
				actor->Update(dt);
			}
		}
	}

	void nc::Scene::Draw(Core::Graphics& graphics)
	{
		for (nc::Actor* actor : m_actors)
		{
			actor->Draw(graphics);
		}
	}

	void nc::Scene::AddActor(Actor* actor)
	{
		actor->SetScene(this);
		m_actors.push_back(actor);
	}

	void nc::Scene::RemoveActor(Actor* object)
	{
		auto iter = std::find(m_actors.begin(), m_actors.end(), object);
		if (iter != m_actors.end())
		{
			delete* iter;
			m_actors.erase(iter);
		}
	}

	void Scene::RemoveAllActor()
	{
		for (Actor* actor : m_actors)
		{
			delete actor;
		}
		m_actors.clear();
	}

	void Scene::RemoveAllActorOfType(Actor::eType eType)
	{
		for (Actor* actor : m_actors)
		{
			if (actor->GetType() == eType && !actor->IsDestroy())
			{
				actor->SetDestroy();
			}	
		}
	}
}