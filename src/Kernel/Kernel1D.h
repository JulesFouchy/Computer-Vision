#pragma once

#include "Kernel/ShaderApply1DKernel.h"

namespace Cool {
	class Texture;
	class TextureFB;
	class Renderer_Fullscreen;
}

class Kernel1D {
public:
	Kernel1D(unsigned int binding);
	~Kernel1D() = default;

	void apply(Texture& inputTexture, Renderer_Fullscreen& renderer, bool bHorizontal);
	void apply(TextureFB& inputTextureFB, Renderer_Fullscreen& renderer, bool bHorizontal);

protected:
	int m_kernelSize;
private:
	ShaderApply1DKernel m_shader;
};