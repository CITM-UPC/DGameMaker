#pragma once

#include "Graphic.h"
#include "EngineGlobals.h"
#include "Texture2D.h"

struct Cube : public Graphic 
{
	static const int NUM_FACES = 6;
	static const int NUM_TRIANGLES = NUM_FACES * 2;
	static const int NUM_VERTEXS = NUM_TRIANGLES * 3;

	const vec3 a;
	const vec3 b;
	const vec3 c;
	const vec3 d;
	const vec3 e;
	const vec3 f;
	const vec3 g;
	const vec3 h;
	//const vec3 i;
	//const vec3 j;
	//const vec3 k;
	//const vec3 l;

	const vec3 red;
	const vec3 green;
	const vec3 blue;
	const vec3 yellow;
	const vec3 white;
	const vec3 black;

	GLuint my_id = 0;

	//Texture2D texture;

	Cube();

	void draw() override;
};

