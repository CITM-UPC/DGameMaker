#pragma once

#include "GameObject.h"

class ScripteableGo
{
public:
	template<typename T>
	T& GetComponent() {
		return o_gameObject->GetComponent<T>();
	}

	std::shared_ptr<GameObject> o_gameObject;

private:

};