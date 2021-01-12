#include <Cool/Log/Log.h>
#include <Cool/App/AppManager.h>

#include "App.h"

int main() {
	Cool::Log::Initialize();
	Cool::AppManager appManager("Computer Vision");
	App app;
	return appManager.run(app);
}