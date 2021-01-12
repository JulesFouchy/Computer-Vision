#version 430

in vec2 vTexCoords;

uniform sampler2D u_TextureSlot;

void main() {
	gl_FragColor = texture(u_TextureSlot, vec2(vTexCoords.x, vTexCoords.y));
}