#include <TinyExtender.h>
#include <TinyShaders.h>
#include <TinyWindow.h>

int main()
{
	WindowManager::Initialize();
	
	WindowManager::AddWindow("Example");
	TinyExtender::InitializeExtensions();

	//the shader manager doesnt actually need to be initialized
	TinyShaders::LoadShaderProgramsFromConfigFile("Shaders/Shaders.txt");

	glUseProgram(TinyShaders::GetShaderProgramByIndex(0)->Handle);	
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glPointSize(20.0f);
	while (!WindowManager::GetWindowShouldClose("Example"))
	{
		WindowManager::PollForEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_POINTS, 0, 1);
		WindowManager::MakeWindowCurrentContext("Example");
		WindowManager::WindowSwapBuffers("Example");
	}
	TinyShaders::Shutdown();
	WindowManager::ShutDown();
	
	return 0;
}
