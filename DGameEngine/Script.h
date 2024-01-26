#pragma once

#include <functional>

class Script
{
public:
	Script();
	virtual ~Script();

	virtual void OnStart() {}

	virtual void OnUpdate() {}

private:

};