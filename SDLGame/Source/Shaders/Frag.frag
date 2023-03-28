#version 430 core

out vec4 color;   

in vec2 teUV;
in vec3 tenormalVec;
// LAB TODO 1: create ins for tangents and bitangents using the normals as an example
in vec3 tetangentVec;
in vec3 tebitangentVec;

in vec3 telightVec;

uniform sampler2D normalMap;
uniform sampler2D texture0;
uniform vec3 ambientLight = vec3(0.2,0.2,0.2);
uniform vec3 diffuse_albedo = vec3(1.0, 1.0, 1.0);

void main(void)                                                   
{                               
    // Normalize the incoming N, L and V vectors
    vec3 N = normalize(tenormalVec);
	// LAB TODO 1: Normalize ins for tangents and bitangents using the normals as an example.
	vec3 T = normalize(tetangentVec);
	vec3 B = normalize(tebitangentVec);

    vec3 L = normalize(telightVec);
	
	// LAB TODO 1: create your TBN matrix here...
	mat3 TBN = mat3(-T, B, N );

	// LAB TODO 1: grab the normals at the current pixel point from the normalMap
	vec3 ImgNormal = texture(normalMap, teUV).rgb;
    //LAB TODO 1: convert the range from 0-1 to be -1 -> +1
	ImgNormal = normalize(ImgNormal * 2.0 - 1.0);
	N = ImgNormal * TBN;

	//the dot product of the normals and the light vector identifies whether the angle to the light is direct or not.
	float Reflection = dot(N, L);

	// Compute the diffuse based off the materials properties and the amount the face is visible to the light
    vec3 diffuse = max(Reflection, 0.0) * diffuse_albedo;
	
	color = texture( texture0, teUV )* vec4(diffuse_albedo - diffuse + ambientLight, 1.0f);
}                                 