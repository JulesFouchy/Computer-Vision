#include "App.h"

#include <Cool/App/RenderState.h>
#include <Cool/App/Input.h>
#include <Cool/LoadImage/LoadImage.h>

#include <iostream>

App::App()
	: m_shaderApplyGaussKernel1D("Cool/Renderer_Fullscreen/fullscreen.vert", "shaders/Apply1DGaussKernel.frag"),
	  m_gaussKernel(8.f)
{
	// Load Image
	m_imageTex.genTexture();
	int w, h;
	unsigned char* data = LoadImage::Load("img/einstein.jpg", &w, &h);
	m_imageTex.uploadRGBA(w, h, data);
	LoadImage::Free(data);
	//
	RenderState::setPreviewAspectRatio(w / (float)h);
	RenderState::setPreviewAspectRatioControl(true);
	m_texFB.setSize({ w, h });
}

void App::update() {
	// X blur pass
	m_renderer.begin();
	{
		glClearColor(m_bgColor.r, m_bgColor.g, m_bgColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		m_shaderApplyGaussKernel1D.bind();
		m_imageTex.bindToSlot(0);
		m_shaderApplyGaussKernel1D.setUniform1i("u_TextureSlot", 0);
		m_shaderApplyGaussKernel1D.setUniform1i("u_bHorizontal", 1);
		m_shaderApplyGaussKernel1D.setUniform1i("u_kernelSize", m_gaussKernel.getSize());
		m_renderer.render();
	}
	m_renderer.renderBuffer().blitTo(m_texFB);
	// Y blur pass
	m_renderer.begin();
	{
		glClearColor(m_bgColor.r, m_bgColor.g, m_bgColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		m_shaderApplyGaussKernel1D.bind();
		m_shaderApplyGaussKernel1D.setUniform1f("sigma", 8);
		m_texFB.attachTextureToSlot(0);
		m_shaderApplyGaussKernel1D.setUniform1i("u_TextureSlot", 0);
		m_shaderApplyGaussKernel1D.setUniform1i("u_bHorizontal", 0);
		m_shaderApplyGaussKernel1D.setUniform1i("u_kernelSize", m_gaussKernel.getSize());
		m_renderer.render();
	}
	m_renderer.end();
}

void App::ImGuiWindows() {
	ImGui::Begin("Canny");
	m_gaussKernel.ImGui();
	ImGui::End();
#ifndef NDEBUG
	if (m_bShow_Debug) {
		ImGui::Begin("Debug", &m_bShow_Debug);
		ImGui::Text("Application average %.1f FPS", ImGui::GetIO().Framerate);
		ImGui::Text("Rendering Size : %d %d", RenderState::Size().width(), RenderState::Size().height());
		ImGui::Text("Mouse Position in Render Area : %d %d pixels", Input::MouseInPixels().x, Input::MouseInPixels().y);
		ImGui::Text("Mouse Position in Render Area : %.1f %.1f centimeters", Input::MouseInCentimeters().x, Input::MouseInCentimeters().y);
		ImGui::Text("Mouse Position Normalized : %.2f %.2f", Input::MouseInNormalizedRatioSpace().x, Input::MouseInNormalizedRatioSpace().y);
		ImGui::ColorEdit3("Background Color", glm::value_ptr(m_bgColor));
		ImGui::Checkbox("Show Demo Window", &m_bShow_ImGuiDemo);
		ImGui::End();
	}
	if (m_bShow_ImGuiDemo) // Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		ImGui::ShowDemoWindow(&m_bShow_ImGuiDemo);
#endif
}

void App::ImGuiMenus() {
	if (ImGui::BeginMenu("Windows")) {
#ifndef NDEBUG
		ImGui::Separator();
		ImGui::Checkbox("Debug", &m_bShow_Debug);
#endif
		ImGui::EndMenu();
	}
}

void App::onEvent(const SDL_Event& e) {
	if (!RenderState::IsExporting()) {
		switch (e.type) {

		case SDL_MOUSEMOTION:
			if (!ImGui::GetIO().WantCaptureMouse) {

			}
			break;

		case SDL_MOUSEWHEEL:
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (!ImGui::GetIO().WantCaptureMouse) {
				switch (e.button.button) {
				case SDL_BUTTON_LEFT:
					break;
				case SDL_BUTTON_RIGHT:
					break;
				case SDL_BUTTON_MIDDLE:
					break;
				}
			}
			break;

		case SDL_MOUSEBUTTONUP:
			if (!ImGui::GetIO().WantCaptureMouse) {
				switch (e.button.button) {
				case SDL_BUTTON_LEFT:
					break;
				case SDL_BUTTON_RIGHT:
					break;
				case SDL_BUTTON_MIDDLE:
					break;
				}
			}
			break;

		case SDL_KEYDOWN:
			if (!ImGui::GetIO().WantTextInput) {

			}
			break;

		case SDL_KEYUP:
			if (!ImGui::GetIO().WantTextInput) {

			}
			break;

		default:
			break;
		}
	}
}