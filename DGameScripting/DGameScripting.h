#pragma once

#ifdef SCRIPTING_EXPORTS
#define SCRIPTING_API __declspec(dllexport)
#else
#define SCRIPTING_API __declspec(dllimport)
#endif // SCRIPTING_EXPORTS

#define DSCRIPTING_LIB extern "C" SCRIPTING_API

