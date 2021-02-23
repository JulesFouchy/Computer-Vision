#pragma once

#include <vector>
#include <Cool/OpenGL/SSBO.h>
#include "Kernel/Kernel1D.h"

using namespace Cool;

class GaussKernel : public Kernel1D {
public:
	GaussKernel(unsigned int binding, float sigma);
	~GaussKernel() = default;

	void setSigma(float sigma);
	void ImGui();

private:
	SSBO<float> m_kernelSSBO;
	float m_sigma;
};