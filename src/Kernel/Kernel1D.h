#pragma once

#include "Kernel/ShaderApply1DKernel.h"

namespace Cool {
	class TextureFB;
	class Renderer_Fullscreen;
}

class Kernel1D {
public:
	Kernel1D(unsigned int binding);
	~Kernel1D() = default;

	void apply(GLuint textureID, Renderer_Fullscreen& renderer, bool bHorizontal);
	/// Applies in both directions
	void apply(GLuint inputTextureID, Renderer_Fullscreen& renderer, TextureFB& intermediateTextureFB);

protected:
	int m_kernelSize;
private:
	ShaderApply1DKernel m_shader;
};