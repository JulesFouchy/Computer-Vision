#pragma once

#include <Cool/App/IApp.h>
#include <Cool/OpenGL/Shader.h>
#include <Cool/OpenGL/Texture.h>
#include <Cool/Renderer_Fullscreen/Renderer_Fullscreen.h>

using namespace Cool;

class App : public Cool::IApp {
public:
	App();
	~App() = default;

	void update() override;
	void ImGuiWindows() override;
	void ImGuiMenus() override;
	void onEvent(const SDL_Event & e) override;

private:
	Renderer_Fullscreen m_renderer;
	Texture m_imageTex;
	Shader m_shaderCanny;
	float m_sigma = 1.;
	glm::vec3 m_bgColor = glm::vec3(0.478f, 0.674f, 0.792f);
#ifndef NDEBUG
	bool m_bShow_Debug = true;
	bool m_bShow_ImGuiDemo = false;
#endif
};