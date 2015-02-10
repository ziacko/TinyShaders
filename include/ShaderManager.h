#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_
#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#include <gl/GL.h>
#define _CRT_SECURE_NO_WARNINGS 1
//this automatically loads the OpenGL library if you are using Visual studio 
#pragma comment (lib, "opengl32.lib")
#endif

#if defined(__linux__) || defined(__GNUG__) || defined(__GNUC__) || defined(__clang__)
#include <GL/gl.h>
#endif

#include <list>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ShaderComponent
{
	ShaderComponent(const GLchar* ShaderName, GLuint ShaderType, const GLchar* FilePath) :
		Name(ShaderName), Type(ShaderType){}
	ShaderComponent(){}
	~ShaderComponent(){}
	const GLchar* Name;
    const GLchar** Source;
	GLuint Handle, Type;
};

struct TShader
{
		TShader(){};
		TShader(const GLchar* ShaderName)
		{
			Name = ShaderName;
		};

		const GLchar* Name;
		GLuint GLID;
		std::vector<const GLchar*> Inputs, Outputs;
		std::vector<ShaderComponent*> ShaderComponents;
};

class ShaderManager
{
	public:

		ShaderManager(){}
		ShaderManager(const char* TextFilePath)
		{
			FILE* File = fopen(TextFilePath, "r+");

			GLint Iterator = 0;
			GLuint InputIterator, OutputIterator = 0;
			GLuint TotalShaders = 0;

			if (File)
			{
				fscanf(File, "%i\n\n", &TotalShaders);

				for (GLuint TotalShadersIter = 0; Iterator != EOF && TotalShadersIter < TotalShaders; TotalShadersIter++,
					fscanf(File, "\n"), Iterator = 0)
				{
					GLuint NumInputs, NumOutputs;
					std::vector<const char*> Inputs, Outputs;

					//get name
					char* Name = new char[255];
					fscanf(File, "%s\n", Name);

					//get type
					char* TypeName = new char[255];
					fscanf(File, "%s\n", TypeName);
					GLuint Type = StringToShaderType(TypeName);

					//get number of inputs
					fscanf(File, "%i\n", &NumInputs);

					for (Iterator = 0, InputIterator = 0; InputIterator < NumInputs; InputIterator++)
					{
						char* InputName = new char[255];
						Iterator = fscanf(File, "%s\n", InputName);
						Inputs.push_back(InputName);
					}

					//get number of outputs
					fscanf(File, "%i\n", &NumOutputs);

					//get outputs
					for (Iterator = 0, OutputIterator = 0; OutputIterator < NumOutputs; OutputIterator++)
					{
						char* OutputName = new char[255];
						Iterator = fscanf(File, "%s\n", OutputName);
						Outputs.push_back(OutputName);
					}

					char* Path = new char[255];
					Iterator = fscanf(File, "%s\n", Path);

					ShaderComponent* NewComponent = new ShaderComponent(Name, Type, Path);

					ShaderComponents.push_back(NewComponent);
				}
			}
			fclose(File);
		}

		~ShaderManager(){}

		static ShaderManager* GetInstance()
		{
			if (ShaderManager::IsInitialized)
			{
				return ShaderManager::Instance;
			}

			ShaderManager::IsInitialized = GL_TRUE;
			ShaderManager::Instance = new ShaderManager();
			return ShaderManager::Instance;

		}

		TShader* GetShaderByName(const char* ShaderName);
		TShader* GetShaderByIndex(GLuint ShaderIndex);

		static ShaderComponent* GetComponentByName(const GLchar* ComponentName)
		{
			if (ComponentName != nullptr)
			{
#if defined(_MSC_VER)
				for each(auto Iter in GetInstance()->ShaderComponents)
				{
					if (!strcmp(ComponentName, Iter->Name))
					{
						return Iter;
					}
				}
#elif defined(__linux__)
				for (auto Iter : GetInstance()->ShaderComponents)
				{
					if (!strcmp(ComponentName, Iter->Name))
					{
						return Iter;
					}
				}
#endif
				return nullptr;
			}
			return nullptr;
		}

		static ShaderComponent* GetComponentByIndex(GLuint ComponentIndex)
		{
			for each(auto Iter in GetInstance()->ShaderComponents)
			{
				if (Iter->Handle == ComponentIndex)
				{
					return Iter;
				}
			}
			return nullptr;
		}

		static std::vector<TShader*> GetShaders()
		{
			return GetInstance()->Shaders;
		}

		static void LoadShaderComponent(const GLchar* Name, 
			const GLchar* ShaderFile, 
			GLuint ShaderType)
		{
			ShaderComponent* NewComponent = new ShaderComponent();
			GLint Success;
			GLchar ErrorLog[512];
			NewComponent->Name = Name;
			NewComponent->Type = ShaderType;
			NewComponent->Source = (const GLchar**)FileToBuffer(ShaderFile);
			printf("%s \n", NewComponent->Source);
			NewComponent->Handle = glCreateShader(NewComponent->Type);
			glShaderSource(NewComponent->Handle, 1, (const GLchar**)&NewComponent->Source, 0);
			glCompileShader(NewComponent->Handle);

			glGetShaderiv(NewComponent->Handle, GL_COMPILE_STATUS, &Success);
			glGetShaderInfoLog(NewComponent->Handle, sizeof(ErrorLog), 0, ErrorLog);

			if (Success == GL_TRUE)
			{
				GetInstance()->ShaderComponents.push_back(NewComponent);
			}

			else
			{
				printf("Error: failed to compile shader:\n");
				printf("%s\n", ErrorLog);
			}
		}

		static void BuildShaderFromComponents(const GLchar* ShaderName,
			std::vector<const GLchar*> Inputs,
			std::vector<const GLchar*> Outputs,
			const GLchar* VertexComponentName,
			const GLchar* FragmentComponentName,
			const GLchar* GeometryComponentName,
			const GLchar* TessContComponentName,
			const GLchar* TessEvalComponentName)
		{
			TShader* NewShader  = new TShader(ShaderName);
			GLint Successful = GL_FALSE;
			GLchar ErrorLog[512];

			NewShader->Inputs =  Inputs;
			NewShader->Outputs = Outputs;
			ShaderComponent* VertexComponent = GetComponentByName(VertexComponentName);
			ShaderComponent* FragmentComponent = GetComponentByName(FragmentComponentName);
			ShaderComponent* GeometryComponent = GetComponentByName(GeometryComponentName);
			ShaderComponent* TessContComponent = GetComponentByName(TessContComponentName);
			ShaderComponent* TessEvalComponent = GetComponentByName(TessEvalComponentName);

			NewShader->GLID = glCreateProgram();
			if (VertexComponent != nullptr)
			{
				glAttachShader(NewShader->GLID, VertexComponent->Handle);
				NewShader->ShaderComponents.push_back(VertexComponent);
			}

			if (FragmentComponent)
			{
				glAttachShader(NewShader->GLID, FragmentComponent->Handle);
			}

			if (GeometryComponent)
			{
				glAttachShader(NewShader->GLID, GeometryComponent->Handle);
			}

			if (TessContComponent)
			{
				glAttachShader(NewShader->GLID, TessContComponent->Handle);
			}

			if (TessEvalComponent)
			{
				glAttachShader(NewShader->GLID, TessEvalComponent->Handle);
			}

			// specify vertex input attributes
			for (GLuint i = 0; i < NewShader->Inputs.size(); ++i)
			{
				glBindAttribLocation(NewShader->GLID, i, NewShader->Inputs[i]);
			}

			// specify pixel shader outputs
			for (GLuint i = 0; i < NewShader->Outputs.size(); ++i)
			{
				glBindFragDataLocation(NewShader->GLID, i, NewShader->Outputs[i]);
			}

			glLinkProgram(NewShader->GLID);
			glGetProgramiv(NewShader->GLID, GL_LINK_STATUS, &Successful);
			glGetProgramInfoLog(NewShader->GLID, sizeof(ErrorLog), 0, ErrorLog);

			if (Successful)
			{
				GetInstance()->Shaders.push_back(NewShader);
			}

			else
			{
				printf("Error: failed to link program %s:\n", NewShader->Name);
				printf("%s\n", ErrorLog);
			}
		}

		private:
		
		void Shutdown(){}		

		static GLchar* FileToBuffer(const GLchar* Path)
		{
			FILE* File = fopen(Path, "rt");

			if (File == nullptr)
			{
				printf("Error: cannot open file %s for reading \n", Path);
				return nullptr;
			}

			//get total byte in given file
			fseek(File, 0, SEEK_END);
			GLuint FileLength = ftell(File);
			fseek(File, 0, SEEK_SET);

			//allocate a file buffer and read the contents of the file
			char* Buffer = new char[FileLength + 1];
			memset(Buffer, 0, FileLength + 1);
			fread(Buffer, sizeof(char), FileLength, File);

			fclose(File);
			return Buffer;
		}

		GLuint StringToShaderType(const char* TypeString)
		{
			if (!strcmp(TypeString, "Vertex"))
			{
				return GL_VERTEX_SHADER;
			}

			if (!strcmp(TypeString, "Fragment"))
			{
				return GL_FRAGMENT_SHADER;
			}

			if (!strcmp(TypeString, "Geometry"))
			{
				return GL_GEOMETRY_SHADER;
			}

			if (!strcmp(TypeString, "Tessellation Control"))
			{
				return GL_TESS_CONTROL_SHADER;
			}

			if (!strcmp(TypeString, "Tessellation Evaluation"))
			{
				return GL_TESS_EVALUATION_SHADER;
			}

			return GL_FALSE;
		}
		const GLchar* ShaderTypeToString(GLuint ShaderType)
		{
			switch (ShaderType)
			{
				case GL_VERTEX_SHADER:
				{
					return "Vertex";
				}

				case GL_FRAGMENT_SHADER:
				{
					return "Fragment";
				}
				
				case GL_GEOMETRY_SHADER:
				{
					return "Geometry";
				}

				case GL_TESS_CONTROL_SHADER:
				{
					return "Tessellation Control";
				}

				case GL_TESS_EVALUATION_SHADER:
				{
					return "Tessellation Evaluation";
				}

				default:
				{
					return NULL;
				}
			}
		}

		std::vector<TShader*> Shaders;
		std::vector<ShaderComponent*> ShaderComponents;	

		static GLboolean IsInitialized;
		static ShaderManager* Instance;
};

GLboolean ShaderManager::IsInitialized = GL_FALSE;
ShaderManager* ShaderManager::Instance = nullptr;
#endif
