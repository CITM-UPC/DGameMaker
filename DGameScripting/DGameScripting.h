#pragma once

#ifdef DGAMESCRIPTING_EXPORTS
#define DENGINE_API __declspec(dllexport)
#else
#define DENGINE_API __declspec(dllimport)
#endif

#define DSCRIPTING_ENGINE extern "C" DENGINE_API