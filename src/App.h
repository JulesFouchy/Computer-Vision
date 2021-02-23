#pragma once

#include <Cool/App/IApp.h>
#include <Cool/OpenGL/Shader.h>
#include <Cool/OpenGL/Texture.h>
#include <Cool/OpenGL/TextureFB.h>
#include <Cool/Renderer_Fullscreen/Renderer_Fullscreen.h>
#include <Cool/Exporter.h>

#include "GaussKernel1D.h"

using namespace Cool;

class App : public Cool::IApp {
public:
	App();
	~App() = default;

	void update() override;
	void render();
	void exportImage();
	void ImGuiWindows() override;
	void ImGuiMenus() override;
	void onKeyboardEvent(int key, int scancode, int action, int mods) override;

private:
	Renderer_Fullscreen m_renderer;
	Texture m_imageTex;
	TextureFB m_texFB;
	Shader m_shaderApplyGaussKernel1D;
	GaussKernel1D m_gaussKernel;
	Exporter m_exporter;
	glm::vec3 m_bgColor = glm::vec3(0.478f, 0.674f, 0.792f);
#ifndef NDEBUG
	bool m_bShow_Debug = true;
	bool m_bShow_ImGuiDemo = false;
#endif
};