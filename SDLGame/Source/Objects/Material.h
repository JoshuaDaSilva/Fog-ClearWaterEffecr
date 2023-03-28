#pragma once

// new OpenGL/GLEW headers:
#define GL3_PROTOTYPES 1
#include "glew.h"

struct Material
{
	GLuint DiffuseTexture;
	GLuint DiffuseAlbedo;
	GLuint NormalMap;
};