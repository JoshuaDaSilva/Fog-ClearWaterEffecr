#pragma once
#include "SDL.h"

// new OpenGL/GLEW headers:
#define GL3_PROTOTYPES 1
#include "glew.h"
#include "Math.h"
#include "Objects\\Material.h"


class ShaderManager
{
public:
	static ShaderManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new ShaderManager();
		}
		return instance;
	}

	void Init();

	void Startup();

	void LoadShaders(bool recompiled = false);

	void Render(Material objMaterial, Vec3 position);

	void Update();

	void Shutdown();

	void LoadShaderFromFile(const char * shaderfile, GLenum type);
	void LoadVertices(static const GLfloat CubeVB[], int numVerts);
	void LoadUVs(static const GLfloat CubeVB[], int numUVs);
	void LoadNormals(static const GLfloat NormalsVB[], GLfloat TangentsVB[], GLfloat BiTangentsVB[], int numNormals);

private:

	ShaderManager();
	~ShaderManager();

	void ProcessShaderFile(GLuint shader, char *shaderData, GLenum type);
	void FindUniformHandles();

	GLuint programObj;
	GLuint vao;

	GLint CamPosUniformHandle;
	GLint TextureUniformHandle;
	GLint NormalMapUniformHandle;
	GLint DiffuseAlbedoUniformHandle;
	GLint ProjectionUniformHandle;
	GLint AmbientUniformHandle;
	GLint ModelViewUniformHandle;

	GLuint verticesHandle;
	GLuint UVHandle;
	GLuint NormalsHandle;
	// LAB TODO :  create buffers to pass in the tangents and bitangents using the normals as an example.
	GLuint TangentHandle;
	GLuint BiTangentHandle;
	
	
	static ShaderManager* instance;
};

