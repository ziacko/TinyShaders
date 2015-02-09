#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_

#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)
//#include <Windows.h>
//#include <gl/GL.h>
//this automatically loads the OpenGL library if you are using Visual studio 
//#pragma comment (lib, "opengl32.lib")
#endif

#if defined(__linux__) || defined(__GNUG__) || defined(__GNUC__) || defined(__clang__)
#include <GL/gl.h>
#endif

#include <list>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TinyExtender.h>

#define SHADER_VERTEX 0
#define SHADER_FRAGMENT 1
#define SHADER_GEOMETRY 2
#define SHADER_TESS_CONT 3
#define SHADER_TESS_EVAL 4
#define SHADER_COMPUTE 5

struct ShaderComponent
{
	ShaderComponent(const char* ShaderName, GLuint ShaderType, const char* FilePath, 
			std::vector<const char*> ShaderInputs, std::vector<const char*> ShaderOutputs) :
		Name(ShaderName), Type(ShaderType), Inputs(ShaderInputs), Outputs(ShaderOutputs)
	{}
	~ShaderComponent();
	const char* Name;
    const char** Source;
	std::vector<const char*> Inputs, Outputs;
	GLuint Handle, Type;
};

struct TShader
{
		TShader(const char* Name);

		const char* Name;
		GLuint GLID;
		std::vector<ShaderComponent*> ShaderComponents;
};

class ShaderManager
{
	public:


		ShaderManager();
		ShaderManager(const char* TextFilePath);

		~ShaderManager();

		TShader* GetShaderByName(const char* ShaderName);
		TShader* GetShaderByIndex(GLuint ShaderIndex);

		std::list<TShader*> GetShaders();

		private:
		
		void Shutdown();

		void LoadShaderComponent(const char* ShaderFile, GLuint ShaderType)
		{
			GLuint ShaderComponent;
			switch (ShaderType)
			{
			case SHADER_VERTEX:
			{
				glCreateShader(ShaderComponent);
				//glShaderSource(ShaderComponent, 1, FileToBuffer(ShaderFile), 0);
				//glCompileShader(ShaderComponent);
				break;
			}

			case SHADER_FRAGMENT:
			{
				break;
			}

			case SHADER_GEOMETRY:
			{
				break;
			}

			case SHADER_TESS_CONT:
			{
				break;
			}

			case SHADER_TESS_EVAL:
			{

			}
			default:
			{
				break;
			}
			}

		}

		char* FileToBuffer(const char* Path);

		GLint TranslateType(const char* TypeString);

		std::list<TShader*> Shaders;
		std::list<ShaderComponent*> ShaderComponents;	
	
};
#endif
