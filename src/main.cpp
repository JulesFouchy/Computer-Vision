#include <Cool/Log/Log.h>
#include <Cool/App/AppManager.h>
#include <Cool/App/OpenGLWindowingSystem.h>

#include "App.h"

int main() {
	// Init Logging
	Cool::Log::Initialize();
	// Init Glfw and set OpenGL version to 4.3
	Cool::OpenGLWindowingSystem windowingSystem(4, 3);
	// Create the main window and its OpenGL context
	Cool::OpenGLWindow mainWindow = windowingSystem.createWindow("Computer Vision", 1280, 720);
#ifdef NDEBUG
	glfwMaximizeWindow(mainWindow.get());
#endif
	// App
	App app;
	Cool::AppManager appManager(mainWindow, app);
	appManager.run();
}