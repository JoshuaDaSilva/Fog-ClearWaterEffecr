#version 430 core

layout (triangles) in;

in vec4 patch_vposition[];
in vec3 patch_normalVec[];
in vec3 patch_lightVec[];
in vec3 patch_viewVec[];
in vec2 patch_UV[];
// LAB TODO 2: add/modify tangent and bitanget values
in vec3 patch_tangentVec[];
in vec3 patch_bitangentVec[];

out vec4 tevposition;
out vec3 tenormalVec;
out vec3 telightVec;
out vec2 teUV;
out vec3 tetangentVec;
out vec3 tebitangentVec;
// LAB TODO 2: modify the in's in the fragment shader to match

// interpolations based on examples from : http://ogldev.atspace.co.uk/www/tutorial30/tutorial30.html
vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
   	return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
   	return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

vec4 interpolate4D(vec4 v0, vec4 v1, vec4 v2)
{
	 float offset = 0.0; 
	 if(patch_vposition[0].y > 0.0 // top curve
	 || patch_vposition[1].y > 0.0 && gl_TessCoord.z > 0.0 && (patch_normalVec[1].z != 0.0 || patch_normalVec[1].y != 0.0))   // sides top half curve
	 {
		 offset = sin( (gl_TessCoord.x + gl_TessCoord.z ) * 0.5);
	 }

   	 return gl_TessCoord.x * v0 + (gl_TessCoord.y * (vec4(v1.x, v1.y + offset, v1.z, v1.w))) + gl_TessCoord.z * v2;
}

float interpolatef(float f0, float f1, float f2)
{
   	return float(gl_TessCoord.x) * f0 + float(gl_TessCoord.y) * f1 + float( gl_TessCoord.z) * f2;
}

void main(void)
{
 	 gl_Position = interpolate4D(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position);
     tevposition = interpolate4D(patch_vposition[0], patch_vposition[1], patch_vposition[2]);
     tenormalVec = interpolate3D(patch_normalVec[0], patch_normalVec[1], patch_normalVec[2]);
	// LAB TODO 2: add/modify tangent and bitanget values
     tetangentVec = interpolate3D(patch_tangentVec[0], patch_tangentVec[1], patch_tangentVec[2]);
     tebitangentVec = interpolate3D(patch_bitangentVec[0], patch_bitangentVec[1], patch_bitangentVec[2]);

     telightVec = interpolate3D(patch_lightVec[0], patch_lightVec[1], patch_lightVec[2]);	
     teUV = interpolate2D(patch_UV[0], patch_UV[1], patch_UV[2]);
}                                                                 