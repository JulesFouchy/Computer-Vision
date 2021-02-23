#include "Kernel1D.h"

#include "Cool/OpenGL/TextureFB.h"
#include "Cool/Renderer_Fullscreen/Renderer_Fullscreen.h"

Kernel1D::Kernel1D(unsigned int binding)
	: m_shader(binding)
{}

void Kernel1D::apply(GLuint textureID, Renderer_Fullscreen& renderer, bool bHorizontal) {
	m_shader->bind();
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, textureID));
	m_shader->setUniform1i("u_TextureSlot", 0);
	m_shader->setUniform1i("u_bHorizontal", bHorizontal ? 1 : 0);
	m_shader->setUniform1i("u_kernelSize", m_kernelSize);
	renderer.render();
}

void Kernel1D::apply(GLuint inputTextureID, Renderer_Fullscreen& renderer, TextureFB& intermediateTextureFB) {
	// X pass
	apply(inputTextureID, renderer, true);
	renderer.renderBuffer().blitTo(intermediateTextureFB);
	// Y pass
	renderer.begin();
	apply(intermediateTextureFB.textureID(), renderer, false);
}