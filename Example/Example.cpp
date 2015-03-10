#include <TinyExtender.h>
#include <TinyShaders.h>
#include <TinyWindow.h>

int main()
{
	WindowManager::Initialize();
	
	WindowManager::AddWindow("Example");
	TinyExtender::InitializeExtensions();

	//the shader manager doesn't actually need to be initialized
	TinyShaders::LoadShaderProgramsFromConfigFile("Shaders/Shaders.txt");


	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glPointSize(20.0f);
	GLuint X, Y;
	while (!WindowManager::GetWindowShouldClose("Example"))
	{		
		WindowManager::PollForEvents();
		
		glUseProgram(TinyShaders::GetShaderProgramByIndex(0)->Handle);
		GLuint Location = glGetUniformLocation(TinyShaders::GetShaderProgramByIndex(0)->Handle, "Test");
		WindowManager::GetMousePositionInWindow("Example", X, Y);
		glUniform2f(Location, 1280.0f / X, 720.0f / Y);

		glDrawArrays(GL_POINTS, 0, 1);
		
		WindowManager::WindowSwapBuffers("Example");
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	TinyShaders::Shutdown();
	WindowManager::ShutDown();
	
	return 0;
}
