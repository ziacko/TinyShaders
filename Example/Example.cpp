#include <TinyExtender.h>
#include <TinyShaders.h>
#include <WindowManager.h>

int main()
{
	WindowManager::Initialize();
	
	WindowManager::AddWindow(new FWindow("Example"));
	TinyExtender::InitializeExtensions();

	ShaderManager::LoadShadersFromConfigFile("Shaders/Shaders.txt");
	glUseProgram(ShaderManager::GetShaderByIndex(0)->Handle);
	
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glPointSize(20.0f);
	while (!WindowManager::GetWindowShouldClose("Example"))
	{
		WindowManager::PollForEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_POINTS, 0, 1);
		WindowManager::WindowSwapBuffers("Example");
	}
	ShaderManager::Shutdown();
	WindowManager::ShutDown();
	
	return 0;
}
