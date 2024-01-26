#pragma once

#include "DGameScripting.h"
#include "..\DGameEngine\Script.h"

class DENGINE_API MovementScript : Script
{
public:
	MovementScript();
	~MovementScript();

	void OnUpdate();
	void OnStart();

private:

};