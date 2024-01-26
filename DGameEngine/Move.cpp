#include "Move.h"
//#include "Tank.h"

Move2::Move2() //: Alien()
{

}

Move2::~Move2()
{

}

void Move2::Start()
{
	/*bullet.ConvertToGameObject(transform->GetGlobalPosition());


	time2 = Time::GetGameTime();

	if (test_object != nullptr) {
		LOG(test_object->GetName());
	}*/
}

void Move2::Update()
{
	/*GameObject** untags = nullptr;
	GameObject** players = nullptr;
	GameObject** enemies = nullptr;
	uint s_untags = GameObject::FindGameObjectsWithTag("UnTagged", &untags);
	uint s_players = GameObject::FindGameObjectsWithTag("Player", &players);
	uint s_enemies = GameObject::FindGameObjectsWithTag("Enemy", &enemies);
	uint count = 0;
	for (uint i = 0; i < s_untags; ++i) {
		if (untags[i] != nullptr && untags[i]->IsEnabled()) {
			count++;
			LOG(untags[i]->GetName());
		}
	}
	LOG("%i", count);
	GameObject::FreeArrayMemory((void***)&untags);*/
}

void Move2::OnDrawGizmos()
{
	/*LOG("GIZMO :D");
	Gizmos::DrawCube(transform->GetGlobalPosition(), { 4,2,3 }, Color::Yellow());*/
}
