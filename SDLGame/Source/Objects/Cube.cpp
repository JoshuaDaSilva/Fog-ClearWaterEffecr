#include "Cube.h"
#include "..\ShaderManager.h"
#include "..\Utils.h"
#include "..\EventHandler.h"
#include "..\vmath.h"

Cube::Cube()
{
}


Cube::~Cube()
{
}

void Cube::Init()
{
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	velocity.z = 0.0f;

	transform.position.z = -2;
	transform.position.y = -0.75;
	transform.position.x = -1.5;

	dimensions.x = 5.0;	// width
	dimensions.y = 5.0;	// height
	dimensions.z = 5.0;	// length

	static const GLfloat CubeVB[] =
	{
		-0.25f, -0.25f, -0.25f, //back bottom/left
		-0.25f,  0.25f, -0.25f,
		0.25f, -0.25f, -0.25f,

		0.25f, -0.25f, -0.25f,
		-0.25f,  0.25f, -0.25f, //back top/right
		0.25f,  0.25f, -0.25f,

		0.25f, -0.25f, -0.25f,// right side back / bottom
		0.25f,  0.25f, -0.25f,
		0.25f, -0.25f,  0.25f,

		0.25f, -0.25f,  0.25f,
		0.25f,  0.25f, -0.25f, // right side front / top
		0.25f,  0.25f,  0.25f,

		0.25f, -0.25f,  0.25f, // front - bottom right
		0.25f,  0.25f,  0.25f,
		-0.25f, -0.25f,  0.25f,

		-0.25f, -0.25f,  0.25f,
		0.25f,  0.25f,  0.25f, // front - left top
		-0.25f,  0.25f,  0.25f,

		-0.25f, -0.25f,  0.25f, // left side - front bottom
		-0.25f,  0.25f,  0.25f,
		-0.25f, -0.25f, -0.25f,

		-0.25f, -0.25f, -0.25f,
		-0.25f,  0.25f,  0.25f, // left side - back top
		-0.25f,  0.25f, -0.25f,

		0.25f,  0.25f, -0.25f,
		-0.25f,  0.25f, -0.25f, // top back right
		0.25f,  0.25f, 0.25f,

		-0.25f,  0.25f, 0.25f,
		0.25f,  0.25f, 0.25f, // top  front left
		-0.25f,  0.25f, -0.25f,

		-0.25f,  -0.25f, -0.25f, // bottom back right
		0.25f,  -0.25f, -0.25f,
		0.25f,  -0.25f, 0.25f,

		0.25f,  -0.25f, 0.25f, // bottom front left
		-0.25f,  -0.25f, 0.25f,
		-0.25f,  -0.25f, -0.25f,
	};

	static const GLfloat uvVB[] = {
		0.33f, 0.66f, 
		0.33f, 1.00f,
		0.00f, 0.66f,

		0.00f, 0.66f, 
		0.33f, 1.00f,
		0.00f, 1.00f,

		0.33f, 0.66f, 
		0.33f, 1.00f,
		0.00f, 0.66f,

		0.00f, 0.66f, 
		0.33f, 1.00f,
		0.00f, 1.00f,

		0.33f, 0.66f, 
		0.33f, 1.00f,
		0.00f, 0.66f,

		0.00f, 0.66f, 
		0.33f, 1.00f,
		0.00f, 1.00f,

		0.33f, 0.66f, 
		0.33f, 1.00f,
		0.00f, 0.66f,

		0.00f, 0.66f, 
		0.33f, 1.00f,
		0.00f, 1.00f,


		0.66f, 0.66f,
		0.33f, 0.66f, 
		0.66f, 0.33f,

		0.33f, 0.33f,
		0.66f, 0.33f,
		0.33f, 0.66f,

		0.66f, 0.66f, 
		0.66f, 0.33f,
		1.00f, 0.33f,

		1.00f, 0.33f, 
		1.00f, 0.66f,
		0.66f, 0.66f,
	};

	static const GLfloat normalsVB[] =
	{
		0.0f, 0.0f, -0.25f, //back bottom/left
		0.0f, 0.0f, -0.25f, //back bottom/left
		0.0f, 0.0f, -0.25f, //back bottom/left

		0.0f, 0.0f, -0.25f, //back top/right
		0.0f, 0.0f, -0.25f, //back top/right
		0.0f, 0.0f, -0.25f, //back top/right

		0.25f, 0.0f, 0.0f, // right side back / bottom
		0.25f, 0.0f, 0.0f, // right side back / bottom
		0.25f, 0.0f, 0.0f, // right side back / bottom

		0.25f, 0.0f, 0.0f, // right side front / top
		0.25f, 0.0f, 0.0f, // right side front / top
		0.25f, 0.0f, 0.0f, // right side front / top

		0.0f, 0.0f, 0.25f, // front - bottom right
		0.0f, 0.0f, 0.25f, // front - bottom right
		0.0f, 0.0f, 0.25f, // front - bottom right

		0.0f, 0.0f,  0.25f, // front - left top
		0.0f, 0.0f,  0.25f, // front - left top
		0.0f, 0.0f,  0.25f, // front - left top

		-0.25f, 0.0f, 0.0f, // left side - front bottom
		-0.25f, 0.0f, 0.0f, // left side - front bottom
		-0.25f, 0.0f, 0.0f, // left side - front bottom

		-0.25f, 0.0f, 0.0f, // left side - back top
		-0.25f, 0.0f, 0.0f, // left side - back top
		-0.25f, 0.0f, 0.0f, // left side - back top

		0.0f,  0.25f, 0.0f, // top back right 5
		0.0f,  0.25f, 0.0f, // top back right 5
		0.0f,  0.25f, 0.0f, // top back right 5

		0.0f,  0.25f, 0.0f, // top  front left 5
		0.0f,  0.25f, 0.0f, // top  front left 5
		0.0f,  0.25f, 0.0f, // top  front left 5

		0.0f, -0.25f, 0.0f, // bottom back right 6
		0.0f, -0.25f, 0.0f, // bottom back right 6
		0.0f, -0.25f, 0.0f, // bottom back right 6

		0.0f, -0.25f, 0.0f, // bottom front left 6
		0.0f, -0.25f, 0.0f, // bottom front left 6
		0.0f, -0.25f, 0.0f, // bottom front left 6
	};
	const int size = sizeof(CubeVB) / sizeof(float);

	GLfloat tangentsVB[size];
	GLfloat bitangentsVB[size];

	// the following functionality is derived from http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/ and modified to fit the needs of the current application
	
	for (int i = 0; i < size/3; i += 3) {

		// Shortcuts for vertices
		int vertOffset = i * 3;
		vmath::vec3 v0 = vmath::vec3( CubeVB[vertOffset], CubeVB[vertOffset + 1], CubeVB[vertOffset + 2]);
		vmath::vec3 v1 = vmath::vec3( CubeVB[vertOffset +3], CubeVB[vertOffset + 4], CubeVB[vertOffset + 5]);
		vmath::vec3 v2 = vmath::vec3( CubeVB[vertOffset + 6], CubeVB[vertOffset + 7], CubeVB[vertOffset + 8]);

		// Shortcuts for UVs
		int uvOffset = i * 2;
		vmath::vec2 uv0 = vmath::vec2( uvVB[uvOffset], uvVB[uvOffset +1] );
		vmath::vec2 uv1 = vmath::vec2( uvVB[uvOffset +2], uvVB[uvOffset + 3]);
		vmath::vec2 uv2 = vmath::vec2( uvVB[uvOffset +4], uvVB[uvOffset + 5]);

		// Edges of the triangle : position delta
		vmath::vec3 deltaPos1 = v1 - v0;
		vmath::vec3 deltaPos2 = v2 - v0;

		// UV delta
		vmath::vec2 deltaUV1 = uv1 - uv0;
		vmath::vec2 deltaUV2 = uv2 - uv0;

		// compute the tangent and the bitangent
		float r = 1.0f / (deltaUV1[0] * deltaUV2[1] - deltaUV2[0] * deltaUV1[1]);
		vmath::vec3 tangent = (deltaUV2[1] * deltaPos1 - deltaUV1[1] * deltaPos2)*r;
		vmath::vec3 bitangent = (-deltaUV2[0] * deltaPos1 + -deltaUV1[0] * deltaPos2)*r;

		// apply the new computations into an array to store for the Vertex Buffers
		for (int j = 0; j < 3; j++)
		{
			tangentsVB[(i*3)+(j*3)] = tangent[0];
			tangentsVB[(i * 3) + (j * 3) + 1] = tangent[1];
			tangentsVB[(i * 3) + (j * 3) + 2] = tangent[2];

			bitangentsVB[(i * 3) + (j * 3)] = bitangent[0];
			bitangentsVB[(i * 3) + (j * 3) + 1] = bitangent[1];
			bitangentsVB[(i * 3) + (j * 3) + 2] = bitangent[2];
		}

	}

	ShaderManager::GetInstance()->LoadVertices(&CubeVB[0], sizeof(CubeVB));
	ShaderManager::GetInstance()->LoadUVs(&uvVB[0], sizeof(uvVB));
	ShaderManager::GetInstance()->LoadNormals(&normalsVB[0], &tangentsVB[0], &bitangentsVB[0], sizeof(normalsVB) );
	LoadTexture();
}

void Cube::LoadTexture()
{
	// create a handle for the texture so openGL has an area allocated to manage all our binary image data.
	glGenTextures(1, &material.DiffuseTexture);

	// now tell OpenGL this is the texture we are currently using for all subsequent texture calls.
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, material.DiffuseTexture);

	unsigned int width, height;
	unsigned char* imgData = Utils::loadBMP("Data\\Art\\grass.bmp", width, height);

	// load our texture data up here
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, imgData);

	// configure mipmapping levels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenTextures(1, &material.NormalMap);
	// now tell OpenGL this is the texture we are currently using for all subsequent texture calls.
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, material.NormalMap);

	width, height;
	unsigned char* imgData2 = Utils::loadBMP("Data\\Art\\grassNormals.bmp", width, height);

	// load our texture data up here
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, imgData2);

	// configure mipmapping levels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	glGenTextures(1, &material.DiffuseAlbedo);
	// now tell OpenGL this is the texture we are currently using for all subsequent texture calls.
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, material.DiffuseAlbedo);

	width, height;
	unsigned char* imgData3 = Utils::loadBMP("Data\\Art\\grass.bmp", width, height);

	// load our texture data up here
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, imgData2);

	// configure mipmapping levels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);
}

void Cube::Draw()
{
	ShaderManager::GetInstance()->Render(material, transform.position);
}

void Cube::Update()
{
}