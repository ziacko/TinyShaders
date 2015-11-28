#include <TinyExtender.h>
#include "TinyShaders.h"
#include <TinyWindow.h>

int main()
{
	windowManager* manager = new windowManager();
	//windowManager::Initialize();
	
	manager->AddWindow("Example");
	TinyExtender::InitializeExtensions();

	//the shader manager doesn't actually need to be initialized
	tinyShaders::LoadShaderProgramsFromConfigFile("Shaders/Shaders.txt", true);

	glUseProgram(tinyShaders::GetShaderProgramByIndex(0)->handle);
	
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glPointSize(20.0f);
	while (!manager->GetWindowShouldCloseByName("Example"))
	{
		manager->PollForEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_POINTS, 0, 1);
		manager->WindowSwapBuffersByName("Example");
	}
	tinyShaders::Shutdown();
	manager->ShutDown();
	
	return 0;
}
