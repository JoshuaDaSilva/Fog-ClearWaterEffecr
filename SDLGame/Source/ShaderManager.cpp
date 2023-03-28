#include "ShaderManager.h"
#include <cstdio>
#include <iostream>
#include "Utils.h"
#include "vmath.h"
#include "CameraManager.h"
#include "EventHandler.h"

using namespace std;

ShaderManager* ShaderManager::instance = nullptr;

#define LOG_COMPILE_SHADERS 1

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

void ShaderManager::Init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glewExperimental = GL_TRUE;
}

// function to call post Init
void ShaderManager::Startup()
{
	// remove these for lab
	programObj = glCreateProgram();
}

void ShaderManager::LoadVertices(static const GLfloat CubeVB[], int numVerts)
{
	glBindBuffer(GL_ARRAY_BUFFER, verticesHandle);
	glBufferData(GL_ARRAY_BUFFER, numVerts, CubeVB, GL_STATIC_DRAW);
}

void ShaderManager::LoadUVs(static const GLfloat uvVB[], int numUVs)
{
	glBindBuffer(GL_ARRAY_BUFFER, UVHandle);
	glBufferData(GL_ARRAY_BUFFER, numUVs, uvVB, GL_STATIC_DRAW);
}

void ShaderManager::LoadNormals(static const GLfloat NormalsVB[], GLfloat TangentsVB[], GLfloat BiTangentsVB[], int numNormals)
{
	glBindBuffer(GL_ARRAY_BUFFER, NormalsHandle);
	glBufferData(GL_ARRAY_BUFFER, numNormals, NormalsVB, GL_STATIC_DRAW);

	// LAB TODO 1:  create buffers to pass in the tangents and bitangents using the normals as an example.
	glBindBuffer(GL_ARRAY_BUFFER, TangentHandle);
	glBufferData(GL_ARRAY_BUFFER, numNormals, TangentsVB, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, BiTangentHandle);
	glBufferData(GL_ARRAY_BUFFER, numNormals, BiTangentsVB, GL_STATIC_DRAW);
}

void ShaderManager::FindUniformHandles()
{
	TextureUniformHandle = glGetUniformLocation(programObj, "texture0");// Get the initial matrices references from the program.
	NormalMapUniformHandle = glGetUniformLocation(programObj, "normalMap");// Get the initial matrices references from the program.

	DiffuseAlbedoUniformHandle = glGetUniformLocation(programObj, "diffuse_albedo");// Get the initial matrices references from the program.

	ModelViewUniformHandle = glGetUniformLocation(programObj, "mv_matrix");

	ProjectionUniformHandle = glGetUniformLocation(programObj, "proj_matrix");

	AmbientUniformHandle = glGetUniformLocation(programObj, "ambientLight"); 

	CamPosUniformHandle = glGetUniformLocation(programObj, "CamPos");
}

void ShaderManager::LoadShaderFromFile(const char * shaderfile, GLenum type)
{
	GLuint shaderObj = 0;
	FILE * filePtr;
	
#ifdef LOG_COMPILE_SHADERS
	string newStr = "Source\\Shaders\\glslangValidator.exe ";
	newStr.append(shaderfile);
	cout << newStr.c_str();
	system(newStr.c_str());
#endif

	if (fopen_s(&filePtr, shaderfile, "rb"))
	{
		cout << "error opening shader file: " << shaderfile << endl;
		return;
	}

	fseek(filePtr, 0, SEEK_END);
	int size = ftell(filePtr);
	fseek(filePtr, 0, SEEK_SET);

	char *data = new char[size + 1];

	if (!data)
	{
		cout << "No Data inside shader file: " << shaderfile << endl;
		return;
	}

	fread(data, 1, size, filePtr);
	data[size] = 0;
	fclose(filePtr);

	ProcessShaderFile(shaderObj, data, type);

	delete[] data;
}

void ShaderManager::ProcessShaderFile(GLuint shader, char *shaderData, GLenum type)
{

	shader = glCreateShader(type);

	if (!shader)
	{
		cout << "error creating shader: " << shader << endl;
		return;
	}

	glShaderSource(shader, 1, &shaderData, NULL);
	glCompileShader(shader);
	glAttachShader(programObj, shader);
	glDeleteShader(shader);
}

void ShaderManager::LoadShaders(bool recompiled)
{
	LoadShaderFromFile("Source\\Shaders\\Vert.vert", GL_VERTEX_SHADER);
	// LAB TODO 2:  Add the two new tessellation shaders to our program object
	LoadShaderFromFile("Source\\Shaders\\Frag.frag" , GL_FRAGMENT_SHADER);
	LoadShaderFromFile("Source\\Shaders\\TessControl.tesc", GL_TESS_CONTROL_SHADER);
	LoadShaderFromFile("Source\\Shaders\\TessEval.tese", GL_TESS_EVALUATION_SHADER);

	glLinkProgram(programObj);


	if (!recompiled)
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &verticesHandle);
		glGenBuffers(1, &UVHandle);
		glGenBuffers(1, &NormalsHandle);

		// LAB TODO 1:  Generate buffers to pass in the tangents and bitangents using the normals as an example.
		glGenBuffers(1, &TangentHandle);
		glGenBuffers(1, &BiTangentHandle);
	}
	FindUniformHandles();
}

void ShaderManager::Render(Material objMaterial, Vec3 position)
{
	glUseProgram(programObj);

	//pass in the vertices for our cube
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, verticesHandle);
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, UVHandle);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, NormalsHandle);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// LAB TODO 1:  Pass in the tangents and bitangents using the normals as an example.
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, TangentHandle);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, BiTangentHandle);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// pass our data to openGL to store for the shaders use.
	glUniform1i(TextureUniformHandle, objMaterial.DiffuseTexture);
	glUniform1i(DiffuseAlbedoUniformHandle, objMaterial.DiffuseAlbedo);

	// pass our data to openGL to store for the shaders use.
	glUniform1i(NormalMapUniformHandle, objMaterial.NormalMap);

	// pass our data to openGL to store for the shaders use.
	float CamPos[3] = { CameraManager::GetInstance()->GetCamPosition().x, CameraManager::GetInstance()->GetCamPosition().y, CameraManager::GetInstance()->GetCamPosition().z };
	glUniform3fv(CamPosUniformHandle, 1, &CamPos[0]);

	vmath::mat4 proj_matrix = CameraManager::GetInstance()->getModifiedProjectionMatrix();
	glUniformMatrix4fv(ProjectionUniformHandle, 1, GL_FALSE, proj_matrix);

	vmath::mat4 mv_matrix = vmath::translate(position.x, position.y, position.z);
	glUniformMatrix4fv(ModelViewUniformHandle, 1, GL_FALSE, mv_matrix);

	float LightVals[3] = { 0.5f, 0.5f, 0.5f };
	glUniform3fv(AmbientUniformHandle, 1, &LightVals[0]);

	// LAB TODO 2:  Draw patches.
	glDrawArraysInstanced(GL_TRIANGLES, 0, 12 * 3, 10*10*3);
	glDrawArraysInstanced(GL_PATCHES, 0, 12 * 3, 10 * 10 * 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	// LAB TODO 1:  disable the attribs added
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
}

void ShaderManager::Update()
{
	if (EventHandler::events[ControlsEvents::R_PRESSED])
	{
		glDeleteProgram(programObj);
		glCreateProgram();
		LoadShaders(true);
	}
}

void ShaderManager::Shutdown()
{
	glDeleteProgram(programObj);
	glDeleteVertexArrays(1, &vao);
}