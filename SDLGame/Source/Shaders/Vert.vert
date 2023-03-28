#version 430 core

layout(location = 0) in vec3 VertPos;
layout(location = 1) in vec2 UVs;
layout(location = 2) in vec3 normal;
// LAB TODO 1: create tangents and bitangents using the normals as an example.
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform vec3 CamPos;

out vec2 UV;
out vec3 normalVec;
// LAB TODO 1: create tangents and bitangents using the normals as an example.
out vec3 tangentVec;
out vec3 bitangentVec;

out vec3 lightVec;
out vec4 vposition;

vec3 light_pos = vec3(-50.0, 50.0, 50.0);

void main(void)                                                   
{                                             
	UV = UVs;	
	
    // Calculate normal in view-space
    normalVec = mat3(mv_matrix) * normal;
	// LAB TODO 1: modify tangents and bitangents using the normals as an example.
	tangentVec = mat3(mv_matrix) * tangent;
	bitangentVec = mat3(mv_matrix) * bitangent;

	// new position using the projection and modelview matrices in addition to the position of each vertices
	// we  pass in 300 cubes, each cube is assigned a new gl_InstanceID, based off that we need to determine it's XY & Z
	float cubeX = VertPos.x + (mod((gl_InstanceID/20),20)/2.0f);	// use mod 10 then /10 to find offset as we have a 10x10 area
	float cubeY = VertPos.y+ ((gl_InstanceID/400)/2.0f);			// use /100 as we have 100 cubes per layer
	float cubeZ = VertPos.z -(mod(gl_InstanceID , 20)/2);			// use mod 10 to determine the depth as we only have 10 depth max

	vposition = vec4(cubeX, cubeY, cubeZ, 1.0);

	vec4 P = proj_matrix * mv_matrix * vec4( cubeX, cubeY, cubeZ, 1.0f);
	
    // Calculate light vector
    lightVec = light_pos;
	
	gl_Position = P;
}         
