#include <TinyExtender.h>
#include <TinyShaders.h>
#include <TinyWindow.h>

float QuadVerts[] = 
{
	-1.0f, -1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, 0.0f, 1.0f,
	-1.0f, 1.0f, 0.0f, 1.0f,

	-1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f
};




GLuint VertexArrayObj = 0;
GLuint VertexBufferObj = 0;
float OrthoMatrix[16];

//create a 4*4 matrix for on orthographic projection matrix
void CreateOrthoProjection(float Right, float Left, float Top, float Bottom, float Far, float Near)
{
	OrthoMatrix[0] = (2 / (Right - Left));
	OrthoMatrix[1] = 0;
 	OrthoMatrix[2] = 0;
	OrthoMatrix[3] = -((Right + Left) / (Right - Left));
	OrthoMatrix[4] = 0; 
	OrthoMatrix[5] = (2 / (Top - Bottom));
   	OrthoMatrix[6] = 0;
 	OrthoMatrix[7] = -((Top + Bottom) / (Top - Bottom));
	OrthoMatrix[8] = 0;
    OrthoMatrix[9] = 0;
    OrthoMatrix[10] = (-2 / (Far - Near));
    OrthoMatrix[11] = -((Far + Near) / (Far - Near));
	OrthoMatrix[12] = 0;
	OrthoMatrix[13] = 0;
	OrthoMatrix[14] = 0;
	OrthoMatrix[15] = 1;	
}

int main()
{
	WindowManager::Initialize();
	
	WindowManager::AddWindow("Example");
	TinyExtender::InitializeExtensions();

	//the shader manager doesn't actually need to be initialized
	TinyShaders::LoadShaderProgramsFromConfigFile("Shaders/Shaders.txt");

	glViewport(0, 0, 1280, 720);
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glPointSize(20.0f);

	CreateOrthoProjection(0.0f, 1280.0f, 0.0f, 720.0f, 100.0f, 0.0f);
	
	for(int i = 0; i < 16; i++)
	{
		printf("%f\n", OrthoMatrix[i]);
	}
	/*
	//create a rendering quad
	//generate an empty vertex array object
	glGenVertexArrays(1, &VertexArrayObj);
	glBindVertexArray(VertexArrayObj);
	//generate an empty vertex buffer object
	glGenBuffers(1, &VertexBufferObj);
	//bind the Vertex buffer object to the current render pass
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObj);
	//fill the buffer that has just been bound with our rendering quad
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 6, QuadVerts, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(false);
	//
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	//bind the vertex array to the current render pass
	glBindVertexArray(VertexArrayObj);
	*/

	while (!WindowManager::GetWindowShouldClose("Example"))
	{		
		WindowManager::PollForEvents();
	
		//tell OpenGL to use your shader program for this render pass	
		glUseProgram(TinyShaders::GetShaderProgramByIndex(0)->Handle);
		//bind the vertex array object to the current render pass (tell OpenGL to draw the Vertices that we created earlier)
		//glBindVertexArray(VertexArrayObj);

	//	GLuint MatrixID = glGetUniformLocation(TinyShaders::GetShaderProgramByIndex(0)->Handle, "Projection");
		//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, OrthoMatrix);

		glDrawArrays(GL_POINTS, 0, 1);
		
		WindowManager::WindowSwapBuffers("Example");
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	TinyShaders::Shutdown();
	WindowManager::ShutDown();
	
	return 0;
}
