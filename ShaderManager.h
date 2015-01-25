#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_

#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)
#include <gl/GL.h>
#endif

#if defined(__linux__) || defined(__GNUG__) || defined(__GNUC__) || defined(__clang__)
#include <GL/gl.h>
#endif

#include <list>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHADER_VERTEX 0
#define SHADER_FRAGMENT 1
#define SHADER_GEOMETRY 2
#define SHADER_TESS_CONT 3
#define SHADER_TESS_EVAL 4
#define SHADER_COMPUTE 5

struct ShaderComponent
{
	ShaderComponent(GLchar* ShaderName, GLuint ShaderType, GLchar* FilePath, 
			std::vector<GLchar*> ShaderInputs, std::vector<GLchar*> ShaderOutputs) :
		Name(ShaderName), Type(ShaderType), Inputs(ShaderInputs), Outputs(ShaderOutputs)
	{
	GLchar* ErrorLog = new GLchar[512];

	switch(Type)
	{
		case SHADER_VERTEX:
			{
				Source = FileToBuffer(FilePath);
				Handle = glCreateShader(GL_VERTEX_SHADER);
				glShaderSource(Handle, 1, Source, 0);
				glCompileShader(Handle);

				GLboolean Success;
				glGetShaderiv(Handle, GL_COMPILE_STATUS, &Success);
				glGetShaderInfoLog(Handle, sizeof(ErrorLog), 0, ErrorLog);

				if(Success)
				{
					printf("Failed to compile vertex shader\n%s\n", ErrorLog);
					return;
				}	
				break;
			}

		case SHADER_FRAGMENT:
			{
				Source = FileToBuffer(FilePath);
				Handle = glCreateShader(GL_FRAGMENT_SHADER);
				glShaderSource(Handle, 1, Source, 0);
				glCompileShader(Handle);

				GLboolean Success;
				glGetShaderiv(Handle, GL_COMPILE_STATUS, &Success);
				glGetShaderInfoLog(Handle, sizeof(ErrorLog), 0, ErrorLog);

				if(Success)
				{
					printf("Failed to compile fragment shader\n%s\n", ErrorLog);
					return;
				}	
				break;
			}

		case SHADER_GEOMETRY:
			{	
				Source = FileToBuffer(FilePath);
				Handle = glCreateShader(GL_GEOMETRY_SHADER);
				glShaderSource(Handle, 1, Source, 0);
				glCompileShader(Handle);

				GLboolean Success;
				glGetShaderiv(Handle, GL_COMPILE_STATUS, &Success);
				glGetShaderInfoLog(Handle, sizeof(ErrorLog), 0, ErrorLog);

				if(Success)
				{
					printf("Failed to compile geometry shader\n%s\n", ErrorLog);
					return;
				}	
				break;

	
			}

		case SHADER_TESS_CONT:
			{	
				Source = FileToBuffer(FilePath);
				Handle = glCreateShader(GL_TESS_CONTROL_SHADER);
				glShaderSource(Handle, 1, Source, 0);
				glCompileShader(Handle);

				GLboolean Success;
				glGetShaderiv(Handle, GL_COMPILE_STATUS, &Success);
				glGetShaderInfoLog(Handle, sizeof(ErrorLog), 0, ErrorLog);

				if(Success)
				{
					printf("Failed to compile tesselation control shader\n%s\n", ErrorLog);
					return;
				}	
				break;
			}

		case SHADER_TESS_EVAL:
			{	
				Source = FileToBuffer(FilePath);
				Handle = glCreateShader(GL_TESS_EVALUATION_SHADER);
				glShaderSource(Handle, 1, Source, 0);
				glCompileShader(Handle);

				GLboolean Success;
				glGetShaderiv(Handle, GL_COMPILE_STATUS, &Success);
				glGetShaderInfoLog(Handle, sizeof(ErrorLog), 0, ErrorLog);

				if(Success)
				{
					printf("Failed to compile tesselation evaluation shader\n%s\n", ErrorLog);
					return;
				}	
				break;

				
			}

		case SHADER_COMPUTE:
			{
				Source = FileToBuffer(FilePath);
				Handle = glCreateShader(GL_VERTEX_SHADER);
				glShaderSource(Handle, 1, Source, 0);
				glCompileShader(Handle);

				GLboolean Success;
				glGetShaderiv(Handle, GL_COMPILE_STATUS, &Success);
				glGetShaderInfoLog(Handle, sizeof(ErrorLog), 0, ErrorLog);

				if(Success)
				{
					printf("Failed to compile compute shader\n%s\n", ErrorLog);
					return;
				}	
				break;
			}

		default:
			{
				printf("Error: invalid parameter \n");
				break;
			}

	}
	}
	~ShaderComponent();
	GLchar* Name;
    GLchar** Source;
	std::vector<GLchar*> Inputs, Outputs;
	GLuint Handle, Type;
};

struct TShader
{
		TShader(GLchar* Name);

		GLchar* Name;
		GLuint GLID;
		std::vector<ShaderComponent*> ShaderComponents;
};

class ShaderManager
{
	public:


		ShaderManager();
		ShaderManager(const GLchar* TextFilePath);

		~ShaderManager();

		TShader* GetShaderByName(const char* ShaderName);
		TShader* GetShaderByIndex(GLuint ShaderIndex);

		std::list<TShader*> GetShaders();

		private:
		
		void Shutdown();

		void LoadShaderComponent(const GLchar* ShaderFile, GLuint ShaderType);

		GLchar* FileToBuffer(const GLchar* Path);

		GLuint TranslateType(GLchar* TypeString);

		std::list<TShader*> Shaders;
		std::list<ShaderComponent*> ShaderComponents;
	
};
#endif
