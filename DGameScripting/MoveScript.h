#pragma once

#include "DGameScripting.h"
#include "..\DGameEngine\ScripteableGO.h"

#include <iostream>

class SCRIPTING_API MoveScript : public ScripteableGo
{
public:
	void OnStart();

	void OnUpdate();

};