#version 430 core

layout (vertices = 3) out;

in vec4 vposition[];
in vec3 normalVec[];
// LAB TODO 2: add/modify tangent and bitanget values
in vec3 lightVec[];
in vec2 UV[];
in vec3 tangentVec[];
in vec3 bitangentVec[];

out vec4 patch_vposition[];
out vec3 patch_normalVec[];
// LAB TODO 2: add/modify tangent and bitanget values
out vec3 patch_lightVec[];
out vec2 patch_UV[];
out vec3 patch_tangentVec[];
out vec3 patch_bitangentVec[];


void main(void)
{
	gl_TessLevelInner[0] = 1.0; 
	gl_TessLevelOuter[0] = 1.0;
	gl_TessLevelOuter[1] = 1.0;
	gl_TessLevelOuter[2] = 1.0;

	if( vposition[gl_InvocationID].y > 0 )
	{
		gl_TessLevelInner[0] = 5.0; 
		gl_TessLevelOuter[0] = 8.0;
		gl_TessLevelOuter[1] = 8.0;
		gl_TessLevelOuter[2] = 8.0;
	}	
	
	patch_normalVec[gl_InvocationID] = normalVec[gl_InvocationID];
	// LAB TODO 2: add/modify tangent and bitanget values
	patch_tangentVec[gl_InvocationID] = tangentVec[gl_InvocationID];
	patch_bitangentVec[gl_InvocationID] = bitangentVec[gl_InvocationID];

	patch_lightVec[gl_InvocationID] = lightVec[gl_InvocationID];
	patch_UV[gl_InvocationID] = UV[gl_InvocationID];	
	patch_vposition[gl_InvocationID] = vposition[gl_InvocationID];

	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}                                                                 