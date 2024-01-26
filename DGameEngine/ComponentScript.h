#pragma once
#include "ScripteableGO.h"

#include "..\DGameScripting\DGameScripting.h"

#include <functional>

class __declspec(dllexport) ComponentScript : public Component
{

public:
	ComponentScript();
	~ComponentScript();

	void update() override;

	Type getType() const override {
		return Type::SCRIPT;
	}

	ScripteableGo* Instance = nullptr;

	std::function<void()> InstantiateFunction;
	std::function<void()> DestroyInstanciatedFunction;

	std::function<void(ScripteableGo*)> StartFunction;
	std::function<void(ScripteableGo*)> PreUpdateFunction;
	std::function<void(ScripteableGo*)> UpdateFunction;
	std::function<void(ScripteableGo*)> PostUpdateFunction;
	
	template<typename T>
	void Bind()
	{
		InstantiateFunction = [&]() { Instance = new T(); };
		DestroyInstanciatedFunction = [&]() { delete (T*)Instance; Instance = nullptr; };

		StartFunction = [](ScripteableGo* instance) { ((T*)instance)->OnStart(); };		
		UpdateFunction = [](ScripteableGo* instance) { ((T*)instance)->OnUpdate(); };
	}
};

