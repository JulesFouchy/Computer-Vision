#pragma once

#include "Cool/OpenGL/Shader.h"

using namespace Cool;

class ShaderApply1DKernel {
public:
	ShaderApply1DKernel(unsigned int binding);
	~ShaderApply1DKernel() = default;

	inline Shader& operator*() { return m_shader; }
	inline Shader* operator->() { return &m_shader; }

private:
	Shader m_shader;
};