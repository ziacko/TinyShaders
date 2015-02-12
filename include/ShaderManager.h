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

GLchar* FileToBuffer(const GLchar* Path)
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

struct ShaderComponent 
{
	ShaderComponent(const GLchar* ShaderName, GLuint ShaderType, const GLchar* ShaderFilePath) :
		Name(ShaderName), Type(ShaderType)
	{
		IsCompiled = GL_FALSE;
		FilePath = ShaderFilePath;
		Compile();
	}
	ShaderComponent(){}
	~ShaderComponent(){}

	GLvoid Compile()
	{
		if (!IsCompiled)
		{
			GLchar ErrorLog[512];
			GLint Success;

			GLchar* Source = FileToBuffer(FilePath);

			Handle = glCreateShader(Type);
			glShaderSource(Handle, 1, (const GLchar**)&Source, 0);
			glCompileShader(Handle);

			glGetShaderiv(Handle, GL_COMPILE_STATUS, &Success);
			glGetShaderInfoLog(Handle, sizeof(ErrorLog), 0, ErrorLog);

			if (Success != GL_TRUE)
			{
				printf("Error: failed to compile shader:\n");
				printf("%s\n", ErrorLog);
				return;
			}
			IsCompiled = GL_TRUE;
		}

		else
		{
			printf("Error: Shader Component Already compiled \n");
		}

	}

	const GLchar* Name;
	const GLchar* FilePath;
	GLuint Handle, Type;
	GLboolean IsCompiled;
};

struct TShader
{
		TShader()
		{
			NumInputs = 0;
			NumOutputs = 0;
			MaxNumComponents = 5;
		};
		TShader(const GLchar* ShaderName, 
			GLuint NumShaderInputs,
			GLchar** ShaderInputs, 
			GLuint NumShaderOutputs,
			GLchar** ShaderOutputs, 
			ShaderComponent** Components) : 
			Name(ShaderName), NumInputs(NumShaderInputs),
			NumOutputs(NumShaderOutputs)
		{
			Inputs.assign(ShaderInputs, ShaderInputs + NumInputs);
			Outputs.assign(ShaderOutputs, ShaderOutputs + NumOutputs);
			Compiled = GL_FALSE;

			Compile();
		};

		TShader(const GLchar* ShaderName){};
		GLboolean Compile()
		{
			Handle = glCreateProgram();
			GLchar ErrorLog[512];
			GLint Successful = GL_FALSE;
			if (!Compiled)
			{

				for (GLuint Iterator = 0; Iterator < MaxNumComponents; Iterator++)
				{
					if (Components[Iterator] != nullptr)
					{
						glAttachShader(Handle, Components[Iterator]->Handle);
					}
				}

				// specify vertex input attributes
				for (GLuint i = 0; i < Inputs.size(); ++i)
				{
					glBindAttribLocation(Handle, i, Inputs[i]);
				}

				// specify pixel shader outputs
				for (GLuint i = 0; i < Outputs.size(); ++i)
				{
					glBindFragDataLocation(Handle, i, Outputs[i]);
				}

				glLinkProgram(Handle);
				glGetProgramiv(Handle, GL_LINK_STATUS, &Successful);
				glGetProgramInfoLog(Handle, sizeof(ErrorLog), 0, ErrorLog);

				if (!Successful)
				{
					printf("Error: failed to link program %s:\n", Name);
					printf("%s\n", ErrorLog);
					return GL_FALSE;
				}

				return GL_TRUE;
			}

			return GL_FALSE;
		}


		const GLchar* Name;
		GLuint Handle;
		GLuint MaxNumComponents;
		GLboolean Compiled;
		GLuint NumInputs, NumOutputs;
		std::vector<const GLchar*> Inputs, Outputs;
		std::vector<ShaderComponent*> Components;
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
			ShaderComponent* NewComponent = new ShaderComponent(Name, ShaderType, ShaderFile);

			if (NewComponent->IsCompiled)
			{
				GetInstance()->ShaderComponents.push_back(NewComponent);
			}
		}

		static void LoadShadersFromConfigFile(const GLchar* ConfigFile)
		{
			FILE* pConfigFile = fopen(ConfigFile, "r+");
			const GLuint MaxNumComponents = 5;
			GLint NumInputs, NumOutputs, NumShaders, Iterator;

			std::vector<GLchar*> Inputs, Outputs, Paths, Names;

			if (pConfigFile)
			{
				fscanf(pConfigFile, "%i\n\n", &NumShaders);

				for (GLint ShaderIter = 0;
					Iterator != EOF && ShaderIter < NumShaders;
					NumShaders++, fscanf(pConfigFile, "\n\n"), Paths.clear(), Inputs.clear(), Outputs.clear())
				{
					//get the name of the shader
					GLchar* ShaderName = new GLchar[255];
					fscanf(pConfigFile, "%s\n", ShaderName);

					//get he number of shader inputs
					fscanf(pConfigFile, "%i\n", &NumInputs);

					//get all inputs
					for (Iterator = 0; Iterator < NumInputs; Iterator++)
					{
						GLchar* Input = new GLchar[255];
						Iterator = fscanf(pConfigFile, "%s\n", Input);
						Inputs.push_back(Input);
					}

					//get the number of shader outputs
					fscanf(pConfigFile, "%i\n", &NumInputs);

					//get all outputs
					for (Iterator = 0; Iterator < NumOutputs; Iterator++)
					{
						GLchar* Output = new GLchar[255];
						Iterator = fscanf(pConfigFile, "%s\n", Output);
						Outputs.push_back(Output);
					}

					//get all component Names
					for (Iterator = 0; Iterator < MaxNumComponents; Iterator++)
					{
						GLchar* Name = new GLchar[255];
						Iterator = fscanf(pConfigFile, "%s\n", Name);
						Names.push_back(Name);
					}

					//get all Shader Paths
					for (Iterator = 0; Iterator < MaxNumComponents; Iterator++)
					{
						GLchar* Path = new GLchar[255];
						Iterator = fscanf(pConfigFile, "%s\n", Path);
						Paths.push_back(Path);
					}

					//TShader* NewShader = new TShader(Names[0], GL_VERTEX_SHADER, Paths[0]);
					ShaderComponent* VertexComponent = new ShaderComponent(Names[0], GL_VERTEX_SHADER, Paths[0]);
					ShaderComponent* FragmentComponent = new ShaderComponent(Names[1], GL_FRAGMENT_SHADER, Paths[1]);
					ShaderComponent* GeometryComponent = new ShaderComponent(Name[2], GL_GEOMETRY_SHADER, Paths[2]);
					ShaderComponent* TessContComponent = new ShaderComponent(Name[3], GL_TESS_CONTROL_SHADER, Paths[3]);
					ShaderComponent* TessEvalComponent = new ShaderComponent(Names[4], GL_TESS_EVALUATION_SHADER, Paths[4]);

					TShader* NewShader = new TShader()

				}
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

			NewShader->Handle = glCreateProgram();
			//these components should be compiled already
			if (VertexComponent != nullptr && VertexComponent->IsCompiled)
			{
				glAttachShader(NewShader->Handle, VertexComponent->Handle);
				NewShader->Components.push_back(VertexComponent);
			}

			if (FragmentComponent != nullptr && FragmentComponent->IsCompiled)
			{
				glAttachShader(NewShader->Handle, FragmentComponent->Handle);
				NewShader->Components.push_back(FragmentComponent);
			}

			if (GeometryComponent != nullptr && GeometryComponent->IsCompiled)
			{
				glAttachShader(NewShader->Handle, GeometryComponent->Handle);
				NewShader->Components.push_back(GeometryComponent);
			}

			if (TessContComponent != nullptr && TessContComponent->IsCompiled)
			{
				glAttachShader(NewShader->Handle, TessContComponent->Handle);
				NewShader->Components.push_back(TessContComponent);
			}

			if (TessEvalComponent != nullptr && TessEvalComponent->IsCompiled)
			{
				glAttachShader(NewShader->Handle, TessEvalComponent->Handle);
				NewShader->Components.push_back(TessEvalComponent);
			}

			// specify vertex input attributes
			for (GLuint i = 0; i < NewShader->Inputs.size(); ++i)
			{
				glBindAttribLocation(NewShader->Handle, i, NewShader->Inputs[i]);
			}

			// specify pixel shader outputs
			for (GLuint i = 0; i < NewShader->Outputs.size(); ++i)
			{
				glBindFragDataLocation(NewShader->Handle, i, NewShader->Outputs[i]);
			}

			glLinkProgram(NewShader->Handle);
			glGetProgramiv(NewShader->Handle, GL_LINK_STATUS, &Successful);
			glGetProgramInfoLog(NewShader->Handle, sizeof(ErrorLog), 0, ErrorLog);

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

		static void BuildShaderFromComponents(const GLchar* ShaderName,
			std::vector<const GLchar*> Inputs,
			std::vector<const GLchar*> Outputs,
			ShaderComponent* VertexComponent,
			ShaderComponent* FragmentComponent,
			ShaderComponent* GeometryComponent,
			ShaderComponent* TessContComponent,
			ShaderComponent* TessEvalComponent)
		{
			TShader* NewShader = new TShader(ShaderName);
			GLint Successful = GL_FALSE;
			GLchar ErrorLog[512];

			NewShader->Inputs = Inputs;
			NewShader->Outputs = Outputs;

			NewShader->Handle = glCreateProgram();
			//these components should be compiled already
			if (VertexComponent != nullptr && VertexComponent->IsCompiled)
			{
				glAttachShader(NewShader->Handle, VertexComponent->Handle);
				NewShader->Components.push_back(VertexComponent);
			}

			if (FragmentComponent != nullptr && FragmentComponent->IsCompiled)
			{
				glAttachShader(NewShader->Handle, FragmentComponent->Handle);
				NewShader->Components.push_back(FragmentComponent);
			}

			if (GeometryComponent != nullptr && GeometryComponent->IsCompiled)
			{
				glAttachShader(NewShader->Handle, GeometryComponent->Handle);
				NewShader->Components.push_back(GeometryComponent);
			}

			if (TessContComponent != nullptr && TessContComponent->IsCompiled)
			{
				glAttachShader(NewShader->Handle, TessContComponent->Handle);
				NewShader->Components.push_back(TessContComponent);
			}

			if (TessEvalComponent != nullptr && TessEvalComponent->IsCompiled)
			{
				glAttachShader(NewShader->Handle, TessEvalComponent->Handle);
				NewShader->Components.push_back(TessEvalComponent);
			}

			// specify vertex input attributes
			for (GLuint i = 0; i < NewShader->Inputs.size(); ++i)
			{
				glBindAttribLocation(NewShader->Handle, i, NewShader->Inputs[i]);
			}

			// specify pixel shader outputs
			for (GLuint i = 0; i < NewShader->Outputs.size(); ++i)
			{
				glBindFragDataLocation(NewShader->Handle, i, NewShader->Outputs[i]);
			}

			glLinkProgram(NewShader->Handle);
			glGetProgramiv(NewShader->Handle, GL_LINK_STATUS, &Successful);
			glGetProgramInfoLog(NewShader->Handle, sizeof(ErrorLog), 0, ErrorLog);

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

			return nullptr;
		}

		std::vector<TShader*> Shaders;
		std::vector<ShaderComponent*> ShaderComponents;	

		static GLboolean IsInitialized;
		static ShaderManager* Instance;
};

GLboolean ShaderManager::IsInitialized = GL_FALSE;
ShaderManager* ShaderManager::Instance = nullptr;
#endif
