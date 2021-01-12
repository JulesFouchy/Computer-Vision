#version 430

in vec2 vTexCoords;
uniform sampler2D u_TextureSlot;

uniform float sigma;

vec4 lookup(vec2 uv) {
	return texture(u_TextureSlot, uv);
}

void main() {
	vec2 uv = vTexCoords;
	vec2 texelSize = 1.0 / vec2(textureSize(u_TextureSlot, 0));
	const int N = 31;
	float normalizationConstant = sigma * 2.50662827;
	float twoSigmaSq = 2. * sigma * sigma;
	float[N] gaussKernel;
	for (int i = 0; i < N; ++i) {
		float t = float(i - N/2);
		gaussKernel[i] = exp(-t*t/twoSigmaSq) / normalizationConstant;
	}
	vec4 col = vec4(0);
	// X pass
	for (int i = 0; i < N; ++i) {
		col += gaussKernel[i] * lookup(uv + vec2((i-N/2) * texelSize.x, 0));
	}
	// Y pass
	for (int i = 0; i < N; ++i) {
		col += gaussKernel[i] * lookup(uv + vec2(0, (i-N/2) * texelSize.y));
	}
	gl_FragColor = col;
}