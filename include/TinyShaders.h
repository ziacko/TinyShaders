#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_
#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)
//created by ziyad barakat 2015
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

#define VERTEX_SHADER 0
#define FRAGMENT_SHADER 1
#define GEOMETRY_SHADER 2
#define TESSCONT_SHADER 3
#define TESSEVAL_SHADER 4
#define COMPUTE_SHADER 5

class ShaderManager
{
	struct TShader;
	struct TShaderComponent;

	public:

		ShaderManager(){}
		~ShaderManager(){}

		static void Shutdown()
		{
#if defined(_WIN32)
			for each(auto Iter in GetInstance()->ShaderComponents)
#elif defined(__linux__)
			for (auto Iter : GetInstance()->ShaderComponents)
#endif
			{
				Iter->Shutdown();
				delete Iter;
			}

#if defined(_WIN32)
			for each(auto Iter in GetInstance()->Shaders)
#elif defined(__linux__)
			for (auto Iter : GetInstance()->Shaders)
#endif
			{
				Iter->Shutdown();
				//delete Iter;
			}

			GetInstance()->Shaders.clear();
			GetInstance()->ShaderComponents.clear();

			delete Instance;
		}

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
			FILE* pConfigFile = fopen(ConfigFile, "r");
			const GLuint MaxNumComponents = 5;
			GLuint NumInputs = 0;
			GLuint NumOutputs = 0;
			GLuint NumShaders = 0;
			GLuint Iterator = 0;

			std::vector<const GLchar*> Inputs, Outputs, Paths, Names;

			if (pConfigFile)
			{
				fscanf(pConfigFile, "%i\n\n", &NumShaders);

				for (GLuint ShaderIter = 0;
					ShaderIter < NumShaders;
					ShaderIter++, fscanf(pConfigFile, "\n\n"), Paths.clear(), Inputs.clear(), Outputs.clear(), Names.clear())
				{
					//get the name of the shader
					GLchar* ShaderName = new GLchar[255];
					fscanf(pConfigFile, "%s\n", ShaderName);

					//this is an anti-trolling measure. If a shader with the same name already exists the don't bother making a new one.
					if (!GetInstance()->ShaderExists(ShaderName))
					{

						//get the number of shader inputs
						fscanf(pConfigFile, "%i\n", &NumInputs);

						//get all inputs
						for (Iterator = 0; Iterator < NumInputs; Iterator++)
						{
							GLchar* Input = new GLchar[255];
							fscanf(pConfigFile, "%s\n", Input);
							Inputs.push_back(Input);
						}

						//get the number of shader outputs
						fscanf(pConfigFile, "%i\n", &NumOutputs);

						//get all outputs
						for (Iterator = 0; Iterator < NumOutputs; Iterator++)
						{
							GLchar* Output = new GLchar[255];
							fscanf(pConfigFile, "%s\n", Output);
							Outputs.push_back(Output);
						}

						//get all component Names
						for (Iterator = 0; Iterator < MaxNumComponents; Iterator++)
						{
							GLchar* Name = new GLchar[255];
							fscanf(pConfigFile, "%s\n", Name);
							Names.push_back(Name);
						}

						//get all Shader Paths
						for (Iterator = 0; Iterator < MaxNumComponents; Iterator++)
						{
							GLchar* Path = new GLchar[255];
							fscanf(pConfigFile, "%s\n", Path);
							Paths.push_back(Path);
						}

						std::vector<TShaderComponent*> Components;

						for (GLuint ComponentIterator = 0; ComponentIterator < MaxNumComponents; ComponentIterator++)
						{
							if (strcmp(Names[ComponentIterator], "None") != 0)
							{
								if (!GetInstance()->ShaderComponentExists(Names[ComponentIterator]))
								{
									//If a shader component of the same name doesn't exist then compile it and add it to storage
									Components.push_back(new TShaderComponent(Names[ComponentIterator], ComponentIterator, Paths[ComponentIterator]));
								}

								else
								{
									//If one already exists then dig that one out from storage and attach it to the shader. It should already be compiled!
									Components.push_back(GetComponentByName(Names[ComponentIterator]));
								}
							}
						}
						TShader* NewShader = new TShader(ShaderName, Inputs, Outputs, Components);
					}
				}
			}
			fclose(pConfigFile);
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
			std::vector<TShaderComponent*> Components;
			Components.push_back(GetComponentByName(VertexComponentName));
			Components.push_back(GetComponentByName(FragmentComponentName));
			Components.push_back(GetComponentByName(GeometryComponentName));
			Components.push_back(GetComponentByName(TessContComponentName));
			Components.push_back(GetComponentByName(TessEvalComponentName));

			TShader* NewShader = new TShader(ShaderName, Inputs, Outputs, Components);
		}

		static GLboolean ShaderExists(const GLchar* ShaderName)
		{
			if (ShaderName != nullptr)
			{
				if (!GetInstance()->Shaders.empty())
				{
#if defined(_WIN32)
					for each(auto Iter in GetInstance()->Shaders)
#elif defined(__linux__)
					for (auto Iter : GetInstance()->Shaders)
#endif
					{
						if (Iter != nullptr && !strcmp(ShaderName, Iter->Name))
						{
							return GL_TRUE;
						}
					}
					return GL_FALSE;
				}
				return GL_FALSE;
			}
			return GL_FALSE;
		}

		static GLboolean ShaderComponentExists(const GLchar* ShaderComponentName)
		{
			if (ShaderComponentName != nullptr)
			{
				if (!GetInstance()->ShaderComponents.empty())
				{
#if defined(_WIN32)
					for each(auto Iter in GetInstance()->ShaderComponents)
#elif defined(__linux__)
					for (auto Iter : GetInstance()->ShaderComponents)
#endif
					{
						if (Iter != nullptr && !strcmp(ShaderComponentName, Iter->Name))
						{
							return GL_TRUE;
						}
					}
					return GL_FALSE;
				}
				return GL_FALSE;
			}
			return GL_FALSE;
		}

	private:

		struct TShaderComponent
			{
				TShaderComponent(const GLchar* ShaderName, GLuint ShaderType, const GLchar* ShaderFilePath) :
					Name(ShaderName)
				{
					Type = GetInstance()->TranslateShaderType(ShaderType);
					IsCompiled = GL_FALSE;
					FilePath = ShaderFilePath;
					Compile();
				}
				TShaderComponent(){}
				~TShaderComponent(){}

				GLvoid Compile()
				{
					//if the component hasn't been compiled yet
					if (!IsCompiled)
					{
						GLchar ErrorLog[512];
						GLint Successful = GL_FALSE;
						GLchar* Source = GetInstance()->FileToBuffer(FilePath);

						if (Source != nullptr)
						{
							Handle = glCreateShader(Type);
							glShaderSource(Handle, 1, (const GLchar**)&Source, 0);
							glCompileShader(Handle);

							glGetShaderiv(Handle, GL_COMPILE_STATUS, &Successful);
							glGetShaderInfoLog(Handle, sizeof(ErrorLog), 0, ErrorLog);

							if (Successful != GL_TRUE)
							{
								printf("Error: failed to compile %s shader component:\n", GetInstance()->ShaderTypeToString(Type));
								printf("%s\n", ErrorLog);
								return;
							}
							IsCompiled = GL_TRUE;
							GetInstance()->ShaderComponents.push_back(this);
							ID = GetInstance()->ShaderComponents.size() - 1;
						}
					}
					else
					{
						//either the file name doesn't exist or the shader/component has already been loaded
						printf("Error: failed to load %s file\n", FilePath);
					}
				}

				GLvoid Shutdown()
				{
					glDeleteShader(Handle);
					IsCompiled = GL_FALSE;
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
					Compiled = GL_FALSE;
					Compile();
				};

				TShader(const GLchar* ShaderName) : Name(ShaderName)
				{
					MaxNumComponents = 5;
					Compiled = GL_FALSE;
				};

				~TShader(){}

				GLvoid Shutdown()
				{
					glDeleteProgram(Handle);
#if defined(_WIN32)
					for each(auto Iter in Components)
#elif defined(__linux__)
					for (auto Iter : Components)
#endif
					{
						Iter->Shutdown();
						//delete Iter;
					}

					Components.clear();
					Inputs.clear();
					Outputs.clear();
				}
				GLboolean Compile()
				{
					Handle = glCreateProgram();
					GLchar ErrorLog[512];
					GLint Successful = GL_FALSE;
					if (!Compiled)
					{

						for (GLuint Iterator = 0; Iterator < Components.size(); Iterator++)
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
						//if a shader successfully compiles then it will add itself to storage
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
				std::vector<const GLchar*> Inputs, Outputs;
				std::vector<TShaderComponent*> Components;
			};

		static TShaderComponent* GetComponentByName(const GLchar* ComponentName)
			{
				if (ComponentName != nullptr)
				{
#if defined(_WIN32)
					for each(auto Iter in GetInstance()->ShaderComponents)
#elif defined(__linux__)
					for (auto Iter : GetInstance()->ShaderComponents)
#endif
					{
						if (!strcmp(ComponentName, Iter->Name))
						{
							return Iter;
						}
					}
					return nullptr;
				}
				return nullptr;
			}

		static TShaderComponent* GetComponentByIndex(GLuint ComponentIndex)
			{
#if defined(_WIN32)
				for each(auto Iter in GetInstance()->ShaderComponents)
#elif defined(__linux__)
				for (auto Iter : GetInstance()->ShaderComponents)
#endif
				{
					if (Iter->Handle == ComponentIndex)
					{
						return Iter;
					}
				}
				return nullptr;
			}		

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

		const GLint TranslateShaderType(GLuint ShaderType)
		{
			switch (ShaderType)
			{
			case VERTEX_SHADER:
			{
				return GL_VERTEX_SHADER;
			}

			case FRAGMENT_SHADER:
			{
				return GL_FRAGMENT_SHADER;
			}

			case GEOMETRY_SHADER:
			{
				return GL_GEOMETRY_SHADER;
			}

			case TESSCONT_SHADER:
			{
				return GL_TESS_CONTROL_SHADER;
			}

			case TESSEVAL_SHADER:
			{
				return GL_TESS_EVALUATION_SHADER;
			}

			case COMPUTE_SHADER:
			{
				return GL_COMPUTE_SHADER;
			}

			default:
			{
				return -1;
			}

			}
		}

		std::vector<TShader*> Shaders;
		std::vector<TShaderComponent*> ShaderComponents;	

		static GLboolean IsInitialized;
		static ShaderManager* Instance;
};

GLboolean ShaderManager::IsInitialized = GL_FALSE;
ShaderManager* ShaderManager::Instance = nullptr;
#endif
