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



class ShaderManager
{
	struct TShader;
	struct TShaderComponent;

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

					TShaderComponent* NewComponent = new TShaderComponent(Name, Type, Path);

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

		static TShader* GetShaderByName(const char* ShaderName)
		{
			if (ShaderName != nullptr)
			{
#if defined(_WIN32)
				for each(auto Iter in GetInstance()->Shaders)
#elif defined(__linux)
				for (auto Iter : GetInstance()->Shaders)
#endif
				{
					if (!strcmp(Iter->Name, ShaderName))
					{
						return Iter;
					}
				}

				return nullptr;
			}
			return nullptr;
		}

		static TShader* GetShaderByIndex(GLuint ShaderIndex)
		{
			if (ShaderIndex <= GetInstance()->Shaders.size() - 1)
			{
#if defined(_WIN32)
				for each(auto Iter in GetInstance()->Shaders)
#elif defined(__linux)
				for (auto Iter : GetInstance()->Shaders)
#endif
				{
					if (Iter->ID == ShaderIndex)
					{
						return Iter;
					}
				}
				return nullptr;
			}
			return nullptr;
		}

		static void LoadShaderComponent(const GLchar* Name, 
			const GLchar* ShaderFile, 
			GLuint ShaderType)
		{
			TShaderComponent* NewComponent = new TShaderComponent(Name, ShaderType, ShaderFile);
		}

		static void LoadShadersFromConfigFile(const GLchar* ConfigFile)
		{
			FILE* pConfigFile = fopen(ConfigFile, "r+");
			const GLuint MaxNumComponents = 5;
			GLint NumInputs, NumOutputs, NumShaders, Iterator;

			std::vector<const GLchar*> Inputs, Outputs, Paths, Names;

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

					std::vector<TShaderComponent*> Components;

					Components.push_back(new TShaderComponent(Names[0], GL_VERTEX_SHADER, Paths[0]));
					Components.push_back(new TShaderComponent(Names[1], GL_FRAGMENT_SHADER, Paths[1]));
					Components.push_back(new TShaderComponent(Names[2], GL_GEOMETRY_SHADER, Paths[2]));
					Components.push_back(new TShaderComponent(Names[3], GL_TESS_CONTROL_SHADER, Paths[3]));
					Components.push_back(new TShaderComponent(Names[4], GL_TESS_EVALUATION_SHADER, Paths[4]));

					TShader* NewShader = new TShader(ShaderName, Inputs, Outputs, Components);
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
			GLint Successful = GL_FALSE;
			GLchar ErrorLog[512];

			std::vector<TShaderComponent*> Components;
			Components.push_back(GetComponentByName(VertexComponentName));
			Components.push_back(GetComponentByName(FragmentComponentName));
			Components.push_back(GetComponentByName(GeometryComponentName));
			Components.push_back(GetComponentByName(TessContComponentName));
			Components.push_back(GetComponentByName(TessEvalComponentName));

			TShader* NewShader = new TShader(ShaderName, Inputs, Outputs, Components);
		}

		private:

			struct TShaderComponent
			{
				TShaderComponent(const GLchar* ShaderName, GLuint ShaderType, const GLchar* ShaderFilePath) :
					Name(ShaderName), Type(ShaderType)
				{
					IsCompiled = GL_FALSE;
					FilePath = ShaderFilePath;
					Compile();
				}
				TShaderComponent(){}
				~TShaderComponent(){}

				GLvoid Compile()
				{
					if (!IsCompiled)
					{
						GLchar ErrorLog[512];
						GLint Success;

						GLchar* Source = GetInstance()->FileToBuffer(FilePath);

						Handle = glCreateShader(Type);
						glShaderSource(Handle, 1, (const GLchar**)&Source, 0);
						glCompileShader(Handle);

						glGetShaderiv(Handle, GL_COMPILE_STATUS, &Success);
						glGetShaderInfoLog(Handle, sizeof(ErrorLog), 0, ErrorLog);

						if (Success != GL_TRUE)
						{
							printf("Error: failed to compile %s shader component:\n", GetInstance()->ShaderTypeToString(Type));
							printf("%s\n", ErrorLog);
							return;
						}
						IsCompiled = GL_TRUE;
						GetInstance()->ShaderComponents.push_back(this);
						ID = GetInstance()->ShaderComponents.size() - 1;
					}

					else
					{
						printf("Error: Shader Component Already compiled \n");
					}

				}

				const GLchar* Name;
				const GLchar* FilePath;
				GLuint Handle, Type, ID;
				GLboolean IsCompiled;
			};

			struct TShader
			{
				TShader()
				{
					NumInputs = 0;
					NumOutputs = 0;
					MaxNumComponents = 5;
					ID = 0;
				};
				TShader(const GLchar* ShaderName,
					std::vector<const GLchar*> ShaderInputs,
					std::vector<const GLchar*> ShaderOutputs,
					std::vector<TShaderComponent*> ShaderComponents) :
					Name(ShaderName), Inputs(ShaderInputs),
					Outputs(ShaderOutputs), Components(ShaderComponents)
				{
					MaxNumComponents = 5;
					Compiled = GL_FALSE;

					Compile();
				};

				TShader(const GLchar* ShaderName) : Name(ShaderName)
				{
					NumInputs = 0;
					NumOutputs = 0;
					MaxNumComponents = 5;
					Compiled = GL_FALSE;
				};
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

						Compiled = GL_TRUE;
						GetInstance()->Shaders.push_back(this);
						ID = GetInstance()->Shaders.size() - 1;
						return GL_TRUE;
					}

					return GL_FALSE;
				}

				const GLchar* Name;
				GLuint Handle, ID;
				GLuint MaxNumComponents;
				GLboolean Compiled;
				GLuint NumInputs, NumOutputs;
				std::vector<const GLchar*> Inputs, Outputs;
				std::vector<TShaderComponent*> Components;
			};

		static TShaderComponent* GetComponentByName(const GLchar* ComponentName)
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

		static TShaderComponent* GetComponentByIndex(GLuint ComponentIndex)
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
		
		void Shutdown(){}		

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
		std::vector<TShaderComponent*> ShaderComponents;	

		static GLboolean IsInitialized;
		static ShaderManager* Instance;
};

GLboolean ShaderManager::IsInitialized = GL_FALSE;
ShaderManager* ShaderManager::Instance = nullptr;
#endif
