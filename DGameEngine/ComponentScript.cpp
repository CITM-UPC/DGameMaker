#include "ComponentScript.h"

ComponentScript::ComponentScript() {

}

ComponentScript::~ComponentScript() {

}

void ComponentScript::update() {
    if (!this->Instance) {
        InstantiateFunction();
        this->Instance->o_gameObject = owner;
        if(StartFunction){ StartFunction(Instance); }
    }

    if(UpdateFunction){ UpdateFunction(Instance); }
}