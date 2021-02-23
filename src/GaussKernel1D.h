#pragma once

#include <vector>
#include <Cool/OpenGL/SSBO.h>
#include "Kernel/ShaderApply1DKernel.h"

namespace Cool {
	class Texture;
	class TextureFB;
	class Renderer_Fullscreen;
}

using namespace Cool;

class GaussKernel1D {
public:
	GaussKernel1D(unsigned int binding, float sigma);
	~GaussKernel1D() = default;
	void apply(Texture& inputTexture, Renderer_Fullscreen& renderer, bool bHorizontal);
	void apply(TextureFB& inputTextureFB, Renderer_Fullscreen& renderer, bool bHorizontal);
	void setSigma(float sigma);
	inline const SSBO<float>& get() { return m_kernelSSBO; }
	inline int getSize() { return m_size; }
	void ImGui();

private:
	SSBO<float> m_kernelSSBO;
	ShaderApply1DKernel m_shader;
	float m_sigma;
	int m_size;
};