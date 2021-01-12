#version 430

in vec2 vTexCoords;
uniform sampler2D u_TextureSlot;

uniform float sigma;
uniform bool u_bHorizontal;

vec4 lookup(vec2 uv) {
	return texture(u_TextureSlot, uv);
}

void main() {
	vec2 uv = vTexCoords;
	vec2 texelSize = 1.0 / vec2(textureSize(u_TextureSlot, 0));
	const int N = 101;
	float normalizationConstant = sigma * 2.50662827;
	float twoSigmaSq = 2. * sigma * sigma;
	float[N] gaussKernel;
	for (int i = 0; i < N; ++i) {
		float t = float(i - N/2);
		gaussKernel[i] = exp(-t*t/twoSigmaSq) / normalizationConstant;
	}
	vec4 col = vec4(0);
	vec2 off = u_bHorizontal ? vec2(texelSize.x, 0) : vec2(0, texelSize.y);
	for (int i = 0; i < N; ++i) {
		col += gaussKernel[i] * lookup(uv + float(i-N/2) * off);
	}
	gl_FragColor = col;
}