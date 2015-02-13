#include <TinyExtender.h>
#include <TinyShaders.h>
#include <TinyWindow.h>

int main()
{
	WindowManager::Initialize();
	
	WindowManager::AddWindow("Example");
	TinyExtender::InitializeExtensions();

	ShaderManager::LoadShaderComponent("Vertex Test",
		"Shaders/vertex.glsl",
		GL_VERTEX_SHADER);
	ShaderManager::LoadShaderComponent("Fragment Test",
		"Shaders/pixel.glsl",
		GL_FRAGMENT_SHADER);

	std::vector<const GLchar*> Inputs, Outputs;
	Inputs.push_back("Position");
	Inputs.push_back("UV");
	Outputs.push_back("outColour");

	ShaderManager::BuildShaderFromComponents("Shader Test",
		Inputs,
		Outputs,
		"Vertex Test", 
		"Fragment Test",
		nullptr,
		nullptr,
		nullptr);

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
	WindowManager::ShutDown();

	return 0;
}