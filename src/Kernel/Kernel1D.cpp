#include "Kernel1D.h"

#include "Cool/OpenGL/Texture.h"
#include "Cool/OpenGL/TextureFB.h"
#include "Cool/Renderer_Fullscreen/Renderer_Fullscreen.h"

Kernel1D::Kernel1D(unsigned int binding)
	: m_shader(binding)
{}

void Kernel1D::apply(Texture& inputTexture, Renderer_Fullscreen& renderer, bool bHorizontal) {
	m_shader->bind();
	inputTexture.attachToSlot(0);
	m_shader->setUniform1i("u_TextureSlot", 0);
	m_shader->setUniform1i("u_bHorizontal", bHorizontal ? 1 : 0);
	m_shader->setUniform1i("u_kernelSize", m_kernelSize);
	renderer.render();
}

void Kernel1D::apply(TextureFB& inputTextureFB, Renderer_Fullscreen& renderer, bool bHorizontal) {
	m_shader->bind();
	inputTextureFB.attachTextureToSlot(0);
	m_shader->setUniform1i("u_TextureSlot", 0);
	m_shader->setUniform1i("u_bHorizontal", bHorizontal ? 1 : 0);
	m_shader->setUniform1i("u_kernelSize", m_kernelSize);
	renderer.render();
}