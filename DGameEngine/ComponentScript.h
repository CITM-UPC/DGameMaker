#pragma once

#include "Components.h"
#include "Script.h"

class ComponentScript : public Component
{

public:

	ComponentScript();
	~ComponentScript();

	void update() override;

	Type getType() const override {
		return Type::SCRIPT;
	}

	Script* attached_script;
	void* data_ptr;

	void LoadData(void* ptr);

};