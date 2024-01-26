#include "Movement.h"

#include <iostream>

MovementScript::MovementScript()
{
}

MovementScript::~MovementScript()
{
}

void MovementScript::OnStart() {

}

void MovementScript::OnUpdate() {
	std::cout << "Test" << std::endl;
}