#pragma once

#pragma once

//#include "..\..\..\Alien Engine\GameObject.h"
///*-----------------COMPONENTS-------------------*/
//#include "..\..\..\Alien Engine\ComponentScript.h"
//#include "..\..\..\Alien Engine\ComponentTransform.h"
//#include "..\..\..\Alien Engine\ComponentCamera.h"
//#include "..\..\..\Alien Engine\ComponentLight.h"
//#include "..\..\..\Alien Engine\ComponentMaterial.h"
//#include "..\..\..\Alien Engine\ComponentMesh.h"
///*-----------------COMPONENTS-------------------*/
//
///*-----------------MATH-------------------*/
//#include "..\..\..\Alien Engine\MathGeoLib\include\Math\float3.h"
//#include "..\..\..\Alien Engine\MathGeoLib\include\Math\Quat.h"
//#include "..\..\..\Alien Engine\MathGeoLib\include\Math\float4x4.h"
///*-----------------MATH-------------------*/
//
///*-----------------HELPERS-------------------*/
//#include "..\..\..\Alien Engine\StaticInput.h"
//#include "..\..\..\Alien Engine\Maths.h"
//#include "..\..\..\Alien Engine\Debug.h"
//#include "..\..\..\Alien Engine\RandomHelper.h"
//#include "..\..\..\Alien Engine\Time.h"
//#include "..\..\..\Alien Engine\Camera.h"
//#include "..\..\..\Alien Engine\Gizmos.h"
//#include "..\..\..\Alien Engine\Color.h"
//#include "..\..\..\Alien Engine\Prefab.h"
//#include "..\..\..\Alien Engine\SceneManager.h"
//#include "..\..\..\Alien Engine\AlienEngine.h"
//#include "..\..\..\Alien Engine\RayCreator.h"
//#include "..\..\..\Alien Engine\Screen.h"
/*-----------------HELPERS-------------------*/

#ifdef ALIENENGINESCRIPTS_EXPORTS
#define ALIEN_ENGINE_API __declspec(dllexport)
#else
#define ALIEN_ENGINE_API __declspec(dllimport)
#endif

// define it next to the CreateClass/StructFunct to be able to use the class/struct
#define ALIEN_FACTORY extern "C" ALIEN_ENGINE_API

// ------------INSPECTOR MACROS----------------\\
/*--------------------int--------------------*/
#define SHOW_IN_INSPECTOR_AS_INPUT_INT(INT_) ComponentScript::InspectorInputInt(&INT_, #INT_)
#define SHOW_IN_INSPECTOR_AS_DRAGABLE_INT(INT_) ComponentScript::InspectorDragableInt(&INT_, #INT_)
#define SHOW_IN_INSPECTOR_AS_SLIDER_INT(INT_, MIN_, MAX_) ComponentScript::InspectorSliderInt(&INT_, #INT_, MIN_, MAX_)
/*--------------------float--------------------*/
#define SHOW_IN_INSPECTOR_AS_INPUT_FLOAT(FLOAT_) ComponentScript::InspectorInputFloat(&FLOAT_, #FLOAT_)
#define SHOW_IN_INSPECTOR_AS_DRAGABLE_FLOAT(FLOAT_) ComponentScript::InspectorDragableFloat(&FLOAT_, #FLOAT_)
#define SHOW_IN_INSPECTOR_AS_SLIDER_FLOAT(FLOAT_, MIN_, MAX_) ComponentScript::InspectorSliderFloat(&FLOAT_, #FLOAT_, MIN_, MAX_)
/*--------------------bool--------------------*/
#define SHOW_IN_INSPECTOR_AS_CHECKBOX_BOOL(BOOL_) ComponentScript::InspectorBool(&BOOL_, #BOOL_)
/*--------------------prefab--------------------*/
#define SHOW_IN_INSPECTOR_AS_PREFAB(PREFAB_) ComponentScript::InspectorPrefab(&PREFAB_, #PREFAB_)
/*--------------------gameobject--------------------*/
#define SHOW_IN_INSPECTOR_AS_GAMEOBJECT(GAMEOBJECT_) ComponentScript::InspectorGameObject(&GAMEOBJECT_, #GAMEOBJECT_)
// ------------INSPECTOR MACROS----------------\\

#define VARAIBLE_TO_STRING(VAR_) #VAR_

#define LOG(format, ...) Debug::Log(__FILE__, __LINE__, format, __VA_ARGS__);

