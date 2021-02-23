#include "GaussKernel1D.h"

#include <cmath>

GaussKernel1D::GaussKernel1D(unsigned int binding, float sigma)
	: m_kernelSSBO(binding)
{
	setSigma(sigma);
}

void GaussKernel1D::setSigma(float sigma) {
	m_sigma = sigma;
	// Choose kernel size
	int N = std::ceil(5.f * sigma);
	if (N % 2 == 0)
		N++;
	m_size = N;
	std::vector<float> kernel;
	kernel.resize(N);
	// Compute values
	float normalizationConstant = sigma * 2.50662827;
	float twoSigmaSq = 2. * sigma * sigma;
	for (int i = 0; i < N; ++i) {
		float t = i - N / 2;
		kernel[i] = exp(-t * t / twoSigmaSq) / normalizationConstant;
	}
	// Uploda data to the SSBO
	m_kernelSSBO.uploadData(kernel, GL_STATIC_READ);
}

void GaussKernel1D::ImGui() {
	float sigma = m_sigma;
	if (ImGui::SliderFloat("Sigma", &sigma, 0.5f, 100.f)) {
		setSigma(sigma);
	}
}