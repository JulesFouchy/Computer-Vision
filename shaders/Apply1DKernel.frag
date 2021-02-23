#version 430

uniform int u_kernelSize;
uniform bool u_bHorizontal; // decide if we do an horizontal or vertical pass

in vec2 vTexCoords;
uniform sampler2D u_TextureSlot;

layout(std430, binding=0) buffer gaussKernel{
   float kernel[];
};

void main() {
	vec2 uv = vTexCoords;
	vec2 texelSize = 1.0 / vec2(textureSize(u_TextureSlot, 0));
	vec2 off = u_bHorizontal ? vec2(texelSize.x, 0) : vec2(0, texelSize.y);
	vec4 col = vec4(0);
	for (int i = 0; i < u_kernelSize; ++i) {
		col += kernel[i] * texture(u_TextureSlot, uv + float(i-u_kernelSize/2) * off);
	}
	gl_FragColor = col;
}