#include <TinyExtender.h>
#include <TinyShaders.h>
#include <TinyWindow.h>
#include <math.h>

#define PI 3.14159265358979323846

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
float Projection[16];
float View[16];
float Model[16];

//create a 4*4 matrix for on orthographic projection matrix(doesn't currently work)
void CreateOrthoProjection(float Right, float Left, float Top, float Bottom, float Far, float Near)
{
	Projection[0] = (2 / (Right - Left));
	Projection[1] = 0;
 	Projection[2] = 0;
	Projection[3] = -((Right + Left) / (Right - Left));
	Projection[4] = 0; 
	Projection[5] = (2 / (Top - Bottom));
   	Projection[6] = 0;
 	Projection[7] = -((Top + Bottom) / (Top - Bottom));
	Projection[8] = 0;
    Projection[9] = 0;
    Projection[10] = (-2 / (Far - Near));
    Projection[11] = -((Far + Near) / (Far - Near));
	Projection[12] = 0;
	Projection[13] = 0;
	Projection[14] = 0;
	Projection[15] = 1;	
}

//create a 4*4 matrix for a perspective projection matrix
void CreatePerspectiveMatrix(float FOV, float AspectRatio, float Near, float Far)
{
	float XYmax = Near * tanf(FOV * (PI/ 360.0f));
	float XMin = -XYmax;
	float YMin = -XYmax;

	float Width = XYmax - XMin;
	float Height = XYmax - YMin;

	float Depth = Far - Near;
	float Q = -((Far * Near) / Depth);
	float QN = -2 * ((Far * Near) / Depth);

	float W = 2 * (Near / Width);
	W = W / AspectRatio;
	float H = 2 * (Near / Height);

	Projection[0] = W;
	Projection[1] = 0;
	Projection[2] = 0;
	Projection[3] = 0;

	Projection[4] = 0;
	Projection[5] = H;
	Projection[6] = 0;
	Projection[7] = 0;

	Projection[8] = 0;
	Projection[9] = 0;
	Projection[10] = Q;
	Projection[11] = -1;

	Projection[12] = 0;
	Projection[13] = 0;
	Projection[14] = QN;
	Projection[15] = 0;
}

// take in an array and normalize the members
void Normalize(float Vector[3])
{
	for (int Iter = 0; Iter < 3; Iter++)
	{
		Vector[Iter] = (Vector[Iter] / Vector[Iter]);
	}
}

//create a 4*4 view matrix. (i.e the camera's Position(Eye), Target and Orientation(Up)
void SetViewMatrix(float PosX, float PosY, float PosZ,
	float TargX, float TargY, float TargZ,
	float OrientX, float OrientY, float OrientZ)
{
	float Position[3] = { PosX, PosY, PosZ };
	/*float Target[3] = { TargX, TargY, TargZ };
	float Orientation[3] = { OrientX, OrientY, OrientZ };
	
	float Forward[3] = { 0 };

	for (int Iter = 0; Iter < 3; Iter++)
	{
		float Value = 0;
		if (Position[Iter] == 0 && Target[Iter] == 0)
		{
			Value = 0;
			Forward[Iter] = 0;
		}

		else
		{
			Value = Position[Iter] - Target[Iter];
			Forward[Iter] = Value / Value;
		}
		
	}

	float Right[3] = { 0 };
	Right[0] = (Orientation[1] * Forward[2]) - (Orientation[2] * Forward[1]);
	Right[1] = (Orientation[2] * Forward[0]) - (Orientation[0] * Forward[2]);
	Right[2] = (Orientation[0] * Forward[1]) - (Orientation[1] * Forward[0]);
	for (int Iter = 0; Iter < 3; Iter++)
	{
		if (Right[Iter] == 0)
		{
			Right[Iter] = 0;
		}
		else
		{
			Right[Iter] = (Right[Iter] / Right[Iter]);
		}
	}

	float Up[3] = { 0 };
	Up[0] = (Forward[1] * Right[2]) - (Forward[2] * Right[1]);
	Up[1] = (Forward[2] * Right[0]) - (Forward[0] * Right[2]);
	Up[2] = (Forward[0] * Right[1]) - (Forward[1] * Right[0]);

/*
	float OrientationMatrix[16] = {
		Forward[0], Right[0], Up[0], 0,
		Forward[1], Right[1], Up[1], 0,
		Forward[2], Right[2], Up[2], 0,
		0, 0, 0, 1};*/

	//apparently this is all i needed to make a LookAt(View) matrix... 2 hours of hard labor wasted
	float TranslationMatrix[16] = {
		1,	0,	0,	0,
		0,	1,	0,	0,
		0,	0,	1,	0,
		-Position[0], -Position[1], -Position[2], 1
	};

	/*float ResultMatrix[16] = {
		(OrientationMatrix[0] * TranslationMatrix[0]) +
		(OrientationMatrix[1] * TranslationMatrix[4]) + 
		(OrientationMatrix[2] * TranslationMatrix[8]) +
		(OrientationMatrix[3] * TranslationMatrix[12]),

		(OrientationMatrix[0] * TranslationMatrix[1]) +
		(OrientationMatrix[1] * TranslationMatrix[5]) +
		(OrientationMatrix[2] * TranslationMatrix[9]) +
		(OrientationMatrix[3] * TranslationMatrix[13]),

		(OrientationMatrix[0] * TranslationMatrix[2]) +
		(OrientationMatrix[1] * TranslationMatrix[6]) +
		(OrientationMatrix[2] * TranslationMatrix[10]) +
		(OrientationMatrix[3] * TranslationMatrix[14]),

		(OrientationMatrix[0] * TranslationMatrix[3]) +
		(OrientationMatrix[1] * TranslationMatrix[7]) +
		(OrientationMatrix[2] * TranslationMatrix[11]) +
		(OrientationMatrix[3] * TranslationMatrix[15]),

		//----------------------------------------------

		(OrientationMatrix[4] * TranslationMatrix[0]) +
		(OrientationMatrix[5] * TranslationMatrix[4]) +
		(OrientationMatrix[6] * TranslationMatrix[8]) +
		(OrientationMatrix[7] * TranslationMatrix[12]),

		(OrientationMatrix[4] * TranslationMatrix[1]) +
		(OrientationMatrix[5] * TranslationMatrix[5]) +
		(OrientationMatrix[6] * TranslationMatrix[9]) +
		(OrientationMatrix[7] * TranslationMatrix[13]),

		(OrientationMatrix[4] * TranslationMatrix[2]) +
		(OrientationMatrix[5] * TranslationMatrix[6]) +
		(OrientationMatrix[6] * TranslationMatrix[10]) +
		(OrientationMatrix[7] * TranslationMatrix[14]),

		(OrientationMatrix[4] * TranslationMatrix[3]) +
		(OrientationMatrix[5] * TranslationMatrix[7]) +
		(OrientationMatrix[6] * TranslationMatrix[11]) +
		(OrientationMatrix[7] * TranslationMatrix[15]),
	
		//---------------------------------------------

		(OrientationMatrix[8] * TranslationMatrix[0]) +
		(OrientationMatrix[9] * TranslationMatrix[4]) +
		(OrientationMatrix[10] * TranslationMatrix[8]) +
		(OrientationMatrix[11] * TranslationMatrix[12]),

		(OrientationMatrix[8] * TranslationMatrix[1]) +
		(OrientationMatrix[9] * TranslationMatrix[5]) +
		(OrientationMatrix[10] * TranslationMatrix[9]) +
		(OrientationMatrix[11] * TranslationMatrix[13]),

		(OrientationMatrix[8] * TranslationMatrix[2]) +
		(OrientationMatrix[9] * TranslationMatrix[6]) +
		(OrientationMatrix[10] * TranslationMatrix[10]) +
		(OrientationMatrix[11] * TranslationMatrix[14]),

		(OrientationMatrix[8] * TranslationMatrix[3]) +
		(OrientationMatrix[9] * TranslationMatrix[7]) +
		(OrientationMatrix[10] * TranslationMatrix[11]) +
		(OrientationMatrix[11] * TranslationMatrix[15]),

		//-------------------------------------------------
		(OrientationMatrix[12] * TranslationMatrix[0]) +
		(OrientationMatrix[13] * TranslationMatrix[4]) +
		(OrientationMatrix[14] * TranslationMatrix[8]) +
		(OrientationMatrix[15] * TranslationMatrix[12]),

		(OrientationMatrix[12] * TranslationMatrix[1]) +
		(OrientationMatrix[13] * TranslationMatrix[5]) +
		(OrientationMatrix[14] * TranslationMatrix[9]) +
		(OrientationMatrix[15] * TranslationMatrix[13]),

		(OrientationMatrix[12] * TranslationMatrix[2]) +
		(OrientationMatrix[13] * TranslationMatrix[6]) +
		(OrientationMatrix[14] * TranslationMatrix[10]) +
		(OrientationMatrix[15] * TranslationMatrix[14]),

		(OrientationMatrix[12] * TranslationMatrix[3]) +
		(OrientationMatrix[13] * TranslationMatrix[7]) +
		(OrientationMatrix[14] * TranslationMatrix[11]) +
		(OrientationMatrix[15] * TranslationMatrix[15]),	
	};*/

	for (int ViewIter = 0; ViewIter < 16; ViewIter++)
	{
		View[ViewIter] = TranslationMatrix[ViewIter];
	}

}

void SetModelMatrix()
{
	Model[0] = 1;
	Model[1] = 0;
	Model[2] = 0;
	Model[3] = 0;
	
	Model[4] = 0;
	Model[5] = 1;
	Model[6] = 0;
	Model[7] = 0;

	Model[8] = 0;
	Model[9] = 0;
	Model[10] = 1;
	Model[11] = 0;

	Model[12] = 0;
	Model[13] = 0;
	Model[14] = 0;
	Model[15] = 1;
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

	CreatePerspectiveMatrix(90, 1280 / 720, 0.01f, 100.0f);
	SetModelMatrix();
	//SetModelMatrix();
	SetViewMatrix(0, 0, 5, 0, 0, 0, 0, 1, 0);

	//glm::mat4 Projection = glm::perspective(90.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
	//glm::mat4 Projection = glm::ortho(0, 1280, 720, 0);
	/*glm::mat4 View = glm::lookAt(
		glm::vec3(0, 0, 5), // camera position
		glm::vec3(0, 0, 0), // Object position
		glm::vec3(0, 1, 0));//camera orientation*/
	//glm::mat4 Model = glm::mat4(1.0f);
	
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
	

	while (!WindowManager::GetWindowShouldClose("Example"))
	{		
		WindowManager::PollForEvents();
	
		//tell OpenGL to use your shader program for this render pass	
		glUseProgram(TinyShaders::GetShaderProgramByIndex(0)->Handle);
		//bind the vertex array object to the current render pass (tell OpenGL to draw the Vertices that we created earlier)
		glBindVertexArray(VertexArrayObj);

		GLuint ProjectionID = glGetUniformLocation(TinyShaders::GetShaderProgramByIndex(0)->Handle, "Projection");
		glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, Projection);

		GLuint ViewID = glGetUniformLocation(TinyShaders::GetShaderProgramByIndex(0)->Handle, "View");
		glUniformMatrix4fv(ViewID, 1, GL_FALSE, View);

		GLuint ModelID = glGetUniformLocation(TinyShaders::GetShaderProgramByIndex(0)->Handle, "Model");
		glUniformMatrix4fv(ModelID, 1, GL_FALSE, Model);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		WindowManager::WindowSwapBuffers("Example");
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	TinyShaders::Shutdown();
	WindowManager::ShutDown();
	
	return 0;
}
