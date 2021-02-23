#include "App.h"

#include <Cool/App/RenderState.h>
#include <Cool/App/Input.h>
#include <Cool/LoadImage/LoadImage.h>

static constexpr unsigned int GAUSS_KERNEL_BINDING = 0;

App::App()
	: m_gaussKernel(GAUSS_KERNEL_BINDING, 8.f)
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
	RenderState::setExportSize(w, h);
	m_texFB.setSize({ w, h });
}

void App::update() {
	render();
}

void App::render() {
	// X blur pass
	m_renderer.begin();
	m_gaussKernel.apply(m_imageTex, m_renderer, true);
	m_renderer.renderBuffer().blitTo(m_texFB);
	// Y blur pass
	m_renderer.begin();
	m_gaussKernel.apply(m_texFB, m_renderer, false);
	m_renderer.end();
}

void App::exportImage() {
	m_exporter.beginImageExport();
	render();
	m_exporter.endImageExport(m_renderer.renderBuffer());
}

void App::ImGuiWindows() {
	ImGui::Begin("Canny");
	m_gaussKernel.ImGui();
	if (ImGui::Button("Save Image")) {
		m_exporter.setIsExportImageWindowOpen(true);
	}
	ImGui::End();
	if (m_exporter.ImGuiExportImageWindow())
		exportImage();
#ifndef NDEBUG
	if (m_bShow_Debug) {
		ImGui::Begin("Debug", &m_bShow_Debug);
		ImGui::Text("Application average %.1f FPS", ImGui::GetIO().Framerate);
		ImGui::Text("Rendering Size : %d %d", RenderState::Size().width(), RenderState::Size().height());
		ImGui::Text("Mouse Position in Render Area : %d %d screen coordinates", Input::MouseInScreenCoordinates().x, Input::MouseInScreenCoordinates().y);
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

void App::onKeyboardEvent(int key, int scancode, int action, int mods) {
	if (!RenderState::IsExporting()) {
		if (Input::MatchesChar("s", key)) {
			m_exporter.setIsExportImageWindowOpen(true);
		}
	}
}