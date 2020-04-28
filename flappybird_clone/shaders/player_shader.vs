# version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 TexCoord;
out vec3 Color;

void main(){
	gl_Position=vec4(position, 1.0);
	Color=vec3(1.0, 0.0, 0.0);
	TexCoord=texCoord;
}