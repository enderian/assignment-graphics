#version 330
layout(location = 0) out vec4 out_color;

uniform sampler2D uniform_texture;
uniform mat4 uniform_projection_inverse_matrix;

in vec2 f_texcoord;

void main(void)
{
	vec3 color = texture2D(uniform_texture, f_texcoord).rgb;
	//vec2 uv = f_texcoord;
	
	//vec2 texSize = textureSize(uniform_texture, 0);
	//printf("Here\n");
	out_color = vec4(color, 1.0);	
}