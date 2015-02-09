#include <TinyWindow.h>
#include <ShaderManager.h>

int main()
{
	GLchar* WindowName = "Shader Manager Test";
	WindowManager::Initialize();

	WindowManager::AddWindow(WindowName);

	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

	while (!WindowManager::GetWindowShouldClose(WindowName))
	{
		WindowManager::PollForEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		WindowManager::WindowSwapBuffers(WindowName);
	}

	WindowManager::ShutDown();
	return 0;

}