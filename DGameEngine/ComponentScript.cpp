#include "ComponentScript.h"

ComponentScript::ComponentScript() {

}

ComponentScript::~ComponentScript() {

}

void ComponentScript::update() {
    attached_script->OnUpdate();
}

void ComponentScript::LoadData(void* ptr) {    
    data_ptr = ptr;
    attached_script = (Script*)data_ptr;
}