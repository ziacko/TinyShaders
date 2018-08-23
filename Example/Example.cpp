#include <TinyExtender.h>

#include <TinyWindow.h>

using namespace TinyWindow;
using namespace TinyExtender;

#include "TinyShaders.h"
using namespace TinyShaders;

int main()
{
	std::unique_ptr<windowManager> manager(new windowManager());
	std::unique_ptr<tWindow> window(manager->AddWindow("Example"));

	TinyExtender::InitializeExtentions();

	//the shader manager doesn't actually need to be initialized
	shaderManager* shaders = new shaderManager();
	std::vector<tShaderProgram*> programs;
	shaders->LoadShaderProgramsFromConfigFile("Shaders/Shaders.txt", true, &programs);

	//tinyShaders::LoadProgramBinariesFromConfigFile("./Shaders/Binaries.txt");

	glUseProgram(programs[0]->handle);
	
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glPointSize(20.0f);
	while (!window->shouldClose)
	{
		manager->PollForEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_POINTS, 0, 1);
		window->SwapDrawBuffers();
	}
	manager->ShutDown();
	tWindow* tempWindow = window.release();
	delete tempWindow;
	
	return 0;
}
