#pragma once

#include <vector>
#include <Cool/OpenGL/SSBO.h>

using namespace Cool;

class GaussKernel1D {
public:
	GaussKernel1D(float sigma);
	~GaussKernel1D() = default;
	void setSigma(float sigma);
	inline const SSBO<float>& get() { return m_kernelSSBO; }
	inline int getSize() { return m_size; }
	void ImGui();

private:
	SSBO<float> m_kernelSSBO;
	float m_sigma;
	int m_size;
};