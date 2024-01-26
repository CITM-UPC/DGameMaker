#pragma once

#include "Entity.h"

class ScripteableGo
{
public:
	template<typename T>
	T& GetComponent() {
		return o_gameObject->GetComponent<T>();
	}

	Entity& gameObj_ref;

private:

};