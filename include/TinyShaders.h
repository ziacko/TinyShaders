#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_
#if defined(_WIN32) || defined(_WIN64)
//created by ziyad barakat 2015
#include <Windows.h>
#include <gl/GL.h>
#define _CRT_SECURE_NO_WARNINGS 1
//this automatically loads the OpenGL library if you are using Visual studio 
#pragma comment (lib, "opengl32.lib")
#endif

#if defined(__linux__) 
#include <GL/gl.h>
#endif

#include <list>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TSHADERS_ERROR_NOTINITIALIZED 1
#define TSHADERS_ERROR_INVALIDSTRING 2
#define TSHADERS_ERROR_INVALIDSHADERNAME 3
#define TSHADERS_ERROR_INVALIDSHADERINDEX 4
#define TSHADERS_ERROR_INVALIDCOMPONENTNAME 5
#define TSHADERS_ERROR_INVALIDCOMPONENTINDEX 6
#define TSHADERS_ERROR_INVALIDFILEPATH 7
#define TSHADERS_ERROR_SHADERNOTFOUND 8
#define TSHADERS_ERROR_COMPONENTNOTFOUND 9
#define TSHADERS_ERROR_INVALIDSHADERTYPE 10
#define TSHADERS_ERROR_FAILEDCOMPONENTLOAD 11
#define TSHADERS_ERROR_FAILEDSHADERLINK 12
#define TSHADERS_ERROR_COMPONENTEXISTS 13
#define TSHADERS_ERROR_SHADEREXISTS 14
#define TSHADERS_ERROR_INVALIDSOURCEFILE 15


#define TSHADERS_WARNING_COMPONENTALREADYEXISTS 1
#define TSHADERS_WARNING_SHADERALREADYEXISTS 2

class ShaderManager
{
	struct TShader;
	struct TShaderComponent;

	public:

		ShaderManager(){}
		~ShaderManager(){}

		static void Shutdown()
		{
			if (ShaderManager::IsInitialized)
			{
				for (GLuint Iterator = 0; Iterator < GetInstance()->ShaderComponents.size(); Iterator++)
				{
					GetInstance()->ShaderComponents[Iterator]->Shutdown();
					 delete GetInstance()->ShaderComponents[Iterator];
				}

				for (GLuint Iterator = 0; Iterator < GetInstance()->Shaders.size(); Iterator++)
				{
					GetInstance()->Shaders[Iterator]->Shutdown();
					delete GetInstance()->Shaders[Iterator];
				}

				GetInstance()->Shaders.clear();
				GetInstance()->ShaderComponents.clear();

				delete Instance;
			}
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
			if (ShaderManager::IsInitialized)
			{
				if (ShaderName != nullptr)
				{
					for (GLuint Iterator = 0; Iterator < GetInstance()->Shaders.size(); Iterator++)
					{
						if (!strcmp(GetInstance()->Shaders[Iterator]->Name, ShaderName))
						{
							return GetInstance()->Shaders[Iterator];
						}
					}
					return nullptr;
				}
				PrintErrorMessage(TSHADERS_ERROR_SHADERNOTFOUND);
				return nullptr;
			}
			PrintErrorMessage(TSHADERS_ERROR_NOTINITIALIZED);
			return nullptr;
		}

		static TShader* GetShaderByIndex(GLuint ShaderIndex)
		{
			if (ShaderManager::IsInitialized)
			{
				if (ShaderIndex <= GetInstance()->Shaders.size() - 1)
				{
					return GetInstance()->Shaders[ShaderIndex];
				}
				PrintErrorMessage(TSHADERS_ERROR_INVALIDSHADERINDEX);
				return nullptr;
			}
			PrintErrorMessage(TSHADERS_ERROR_NOTINITIALIZED);
			return nullptr;
		}

		static TShaderComponent* GetComponentByName(const GLchar* ComponentName)
		{
			if (ShaderManager::IsInitialized)
			{
				if (ComponentName != nullptr)
				{
					for (GLuint Iterator = 0; Iterator < GetInstance()->ShaderComponents.size(); Iterator++)
					{
						if (!strcmp(GetInstance()->ShaderComponents[Iterator]->Name, ComponentName))
						{
							return GetInstance()->ShaderComponents[Iterator];
						}
					}
					PrintErrorMessage(TSHADERS_ERROR_COMPONENTNOTFOUND);
					return nullptr;
				}
				PrintErrorMessage(TSHADERS_ERROR_INVALIDCOMPONENTNAME);
				return nullptr;
			}
			PrintErrorMessage(TSHADERS_ERROR_NOTINITIALIZED);
			return nullptr;
		}

		static TShaderComponent* GetComponentByIndex(GLuint ComponentIndex)
		{
			if (ShaderManager::IsInitialized)
			{
				if (ComponentIndex <= GetInstance()->ShaderComponents.size() - 1)
				{
					return GetInstance()->ShaderComponents[ComponentIndex];
				}
				PrintErrorMessage(TSHADERS_ERROR_INVALIDCOMPONENTINDEX);
				return nullptr;
			}
			PrintErrorMessage(TSHADERS_ERROR_NOTINITIALIZED);
			return nullptr;
		}

		static void LoadShaderComponent(const GLchar* Name, 
			const GLchar* ShaderFile, 
			GLuint ShaderType)
		{
			if (ShaderManager::IsInitialized)
			{
				if (Name != nullptr)
				{
					if (ShaderType >= 0 && ShaderType <= 5)
					{
						TShaderComponent* NewComponent = new TShaderComponent(Name, ShaderType, ShaderFile);
					}
					PrintErrorMessage(TSHADERS_ERROR_INVALIDSHADERTYPE, GetInstance()->ShaderTypeToString(ShaderType));
				}
				PrintErrorMessage(TSHADERS_ERROR_INVALIDSTRING);
			}
			PrintErrorMessage(TSHADERS_ERROR_NOTINITIALIZED);
		}

		static void LoadShadersFromConfigFile(const GLchar* ConfigFile)
		{
			if (!ShaderManager::IsInitialized)
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

<<<<<<< HEAD
						//this is an anti-trolling measure. If a shader with the same name already exists the don't bother making a new one.
						if (!GetInstance()->ShaderExists(ShaderName))
=======
						//get the number of shader inputs
						fscanf(pConfigFile, "%i\n", &NumInputs);

						//get all inputs
						for (Iterator = 0; Iterator < NumInputs; Iterator++)
>>>>>>> 9153425ecab36713dd3b7238276b718f850894d6
						{

							//get he number of shader inputs
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
										switch (ComponentIterator)
										{
										case 0:
										{
											Components.push_back(new TShaderComponent(Names[ComponentIterator], GL_VERTEX_SHADER, Paths[ComponentIterator]));
											break;
										}

										case 1:
										{
											Components.push_back(new TShaderComponent(Names[ComponentIterator], GL_FRAGMENT_SHADER, Paths[ComponentIterator]));
											break;
										}

										case 2:
										{
											Components.push_back(new TShaderComponent(Names[ComponentIterator], GL_GEOMETRY_SHADER, Paths[ComponentIterator]));
											break;

										}

										case 3:
										{
											Components.push_back(new TShaderComponent(Names[ComponentIterator], GL_TESS_CONTROL_SHADER, Paths[ComponentIterator]));
											break;
										}

										case 4:
										{
											Components.push_back(new TShaderComponent(Names[ComponentIterator], GL_TESS_EVALUATION_SHADER, Paths[ComponentIterator]));
											break;
										}
										}
										
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
					fclose(pConfigFile);
				}

				else
				{
					PrintErrorMessage(TSHADERS_ERROR_INVALIDFILEPATH, ConfigFile);
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
			if (ShaderManager::IsInitialized)
			{
				std::vector<TShaderComponent*> Components;
				Components.push_back(GetComponentByName(VertexComponentName));
				Components.push_back(GetComponentByName(FragmentComponentName));
				Components.push_back(GetComponentByName(GeometryComponentName));
				Components.push_back(GetComponentByName(TessContComponentName));
				Components.push_back(GetComponentByName(TessEvalComponentName));

				TShader* NewShader = new TShader(ShaderName, Inputs, Outputs, Components);
			}
			PrintErrorMessage(TSHADERS_ERROR_NOTINITIALIZED);
		}

		static GLboolean ShaderExists(const GLchar* ShaderName)
		{
			if (ShaderName != nullptr)
			{
				if (!GetInstance()->Shaders.empty())
				{
					for (GLuint Iterator = 0; Iterator < GetInstance()->Shaders.size(); Iterator++)
					{
						if (GetInstance()->Shaders[Iterator] != nullptr &&
							!strcmp(ShaderName, GetInstance()->Shaders[Iterator]->Name))
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
					for (GLuint Iterator = 0; Iterator < GetInstance()->ShaderComponents.size(); Iterator++)
					{
						if (GetInstance()->ShaderComponents[Iterator] != nullptr && 
							!strcmp(ShaderComponentName, GetInstance()->ShaderComponents[Iterator]->Name))
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
					Type = ShaderType;
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
								PrintErrorMessage(TSHADERS_ERROR_FAILEDCOMPONENTLOAD, GetInstance()->ShaderTypeToString(Type));
								printf("%s\n", ErrorLog);
							}

							else
							{
								IsCompiled = GL_TRUE;
								GetInstance()->ShaderComponents.push_back(this);
								ID = GetInstance()->ShaderComponents.size() - 1;
							}	
						}
						else
						{
							PrintErrorMessage(TSHADERS_ERROR_INVALIDSOURCEFILE);
						}
					}
					else
					{
						//either the file name doesn't exist or the component has already been loaded
						PrintErrorMessage(TSHADERS_ERROR_INVALIDFILEPATH, FilePath);
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

					for (GLuint Iterator = 0; Iterator < GetInstance()->ShaderComponents.size(); Iterator++)
					{
						GetInstance()->ShaderComponents[Iterator]->Shutdown();
						delete GetInstance()->ShaderComponents[Iterator];
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
							PrintErrorMessage(TSHADERS_ERROR_FAILEDSHADERLINK, Name);
							printf("%s\n", ErrorLog);
							return GL_FALSE;
						}
						//if a shader successfully compiles then it will add itself to storage
						Compiled = GL_TRUE;
						GetInstance()->Shaders.push_back(this);
						ID = GetInstance()->Shaders.size() - 1;
						return GL_TRUE;
					}
					PrintErrorMessage(TSHADERS_ERROR_SHADEREXISTS, Name);
					return GL_FALSE;
				}

				const GLchar* Name;
				GLuint Handle, ID;
				GLuint MaxNumComponents;
				GLboolean Compiled;
				std::vector<const GLchar*> Inputs, Outputs;
				std::vector<TShaderComponent*> Components;
			};		

		static GLvoid PrintErrorMessage(GLuint ErrorNumber, const GLchar* String = nullptr)
		{
			switch (ErrorNumber)
			{
			case TSHADERS_ERROR_NOTINITIALIZED:
			{
				printf("Error: TinyShaders must first be initialized \n");
				break;
			}

			case TSHADERS_ERROR_INVALIDSTRING:
			{
				printf("Error: given string is invalid \n");
				break;
			}

			case TSHADERS_ERROR_INVALIDSHADERNAME:
			{
				printf("Error: given shader name is invalid \n");
				break;
			}

			case TSHADERS_ERROR_INVALIDSHADERINDEX:
			{
				printf("Error: given shader index is invalid \n");
				break;
			}

			case TSHADERS_ERROR_INVALIDCOMPONENTNAME:
			{
				printf("Error: given shader component name is invalid \n");
				break;
			}

			case TSHADERS_ERROR_INVALIDCOMPONENTINDEX:
			{
				printf("Error: given shader component index is invalid \n");
				break;
			}

			case TSHADERS_ERROR_INVALIDFILEPATH:
			{
				printf("Error: given file path is invalid %s \n", String);
				break;
			}

			case TSHADERS_ERROR_SHADERNOTFOUND:
			{
				printf("Error: shader with given name %s was not found \n", String);
				break;
			}

			case TSHADERS_ERROR_COMPONENTNOTFOUND:
			{
				printf("Error: shader component with given name %s was not found \n", String);
				break;
			}

			case TSHADERS_ERROR_INVALIDSHADERTYPE:
			{
				printf("Error: invalid shader type given \n");
				break;
			}

			case TSHADERS_ERROR_FAILEDCOMPONENTLOAD:
			{
				printf("Error: failed to compile %s shader component \n", String);
				break;
			}

			case TSHADERS_ERROR_FAILEDSHADERLINK:
			{
				if (String != nullptr)
				{
<<<<<<< HEAD
					printf("Error: failed to link program %s \n", String);
=======
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
>>>>>>> 9153425ecab36713dd3b7238276b718f850894d6
				}
				break;
			}

			case TSHADERS_ERROR_COMPONENTEXISTS:
			{
<<<<<<< HEAD
				printf("Error: shader component with this name %s already exists \n", String);
				break;
			}

			case TSHADERS_ERROR_SHADEREXISTS:
			{
				if (String != nullptr)
=======
#if defined(_WIN32)
				for each(auto Iter in GetInstance()->ShaderComponents)
#elif defined(__linux__)
				for (auto Iter : GetInstance()->ShaderComponents)
#endif
>>>>>>> 9153425ecab36713dd3b7238276b718f850894d6
				{
					printf("Error: shader with this name %s already exists \n", String);
					break;
				}
			}

			case TSHADERS_ERROR_INVALIDSOURCEFILE:
			{
				printf("Given Source file is invalid");
				break;
			}
			default:
			{
				break;
			}
			}
		}

		GLchar* FileToBuffer(const GLchar* Path)
		{
			FILE* File = fopen(Path, "rt");

			if (File == nullptr)
			{
				PrintErrorMessage(TSHADERS_ERROR_INVALIDFILEPATH, Path);
				//printf("Error: cannot open file %s for reading \n", Path);
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
