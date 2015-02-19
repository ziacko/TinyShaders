#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_
#if defined(_WIN32) || defined(_WIN64)
//created by ziyad barakat-2015
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
#define TSHADERS_ERROR_INVALIDSHADERPROGRAMNAME 3
#define TSHADERS_ERROR_INVALIDSHADERPROGRAMINDEX 4
#define TSHADERS_ERROR_INVALIDSHADERNAME 5
#define TSHADERS_ERROR_INVALIDSHADERINDEX 6
#define TSHADERS_ERROR_INVALIDFILEPATH 7
#define TSHADERS_ERROR_SHADERPROGRAMNOTFOUND 8
#define TSHADERS_ERROR_SHADERNOTFOUND 9
#define TSHADERS_ERROR_INVALIDSHADERTYPE 10
#define TSHADERS_ERROR_FAILEDSHADERLOAD 11
#define TSHADERS_ERROR_FAILEDSHADERPROGRAMLINK 12
#define TSHADERS_ERROR_SHADEREXISTS 13
#define TSHADERS_ERROR_SHADERPROGRAMEXISTS 14
#define TSHADERS_ERROR_INVALIDSOURCEFILE 15

class TinyShaders
{
	struct TShaderProgram;
	struct TShader;

	public:

		TinyShaders(){}
		~TinyShaders(){}

		/*
		* shuts down TinyShaders. deletes all OpenGL shaders and shader programs 
		* as well as calling shutdown on all shader and programs and clears all vectors.
		*/
		static void Shutdown()
		{
			if (TinyShaders::IsInitialized)
			{
				for (GLuint Iterator = 0; Iterator < GetInstance()->Shaders.size(); Iterator++)
				{
					GetInstance()->Shaders[Iterator]->Shutdown();
					 delete GetInstance()->Shaders[Iterator];
				}

				for (GLuint Iterator = 0; Iterator < GetInstance()->ShaderPrograms.size(); Iterator++)
				{
					GetInstance()->ShaderPrograms[Iterator]->Shutdown();
					delete GetInstance()->ShaderPrograms[Iterator];
				}

				GetInstance()->ShaderPrograms.clear();
				GetInstance()->Shaders.clear();

				delete Instance;
			}
		}

		/*
		* returns a pointer to a TShaderProgram corresponding to the given name. returns nullptr if the TShaderProgram is not found
		*/
		static TShaderProgram* GetShaderProgramByName(const char* ProgramName)
		{
			if (TinyShaders::IsInitialized)
			{
				if (ProgramName != nullptr)
				{
					for (GLuint Iterator = 0; Iterator < GetInstance()->ShaderPrograms.size(); Iterator++)
					{
						if (!strcmp(GetInstance()->ShaderPrograms[Iterator]->Name, ProgramName))
						{
							return GetInstance()->ShaderPrograms[Iterator];
						}
					}
					return nullptr;
				}
				PrintErrorMessage(TSHADERS_ERROR_SHADERPROGRAMNOTFOUND);
				return nullptr;
			}
			PrintErrorMessage(TSHADERS_ERROR_NOTINITIALIZED);
			return nullptr;
		}

		/*
		* returns a pointer to a TShaderProgram corresponding to the given index. returns nullptr if the TShaderProgram is not found
		*/
		static TShaderProgram* GetShaderProgramByIndex(GLuint ProgramIndex)
		{
			if (TinyShaders::IsInitialized)
			{
				if (ProgramIndex <= GetInstance()->ShaderPrograms.size() - 1)
				{
					return GetInstance()->ShaderPrograms[ProgramIndex];
				}
				PrintErrorMessage(TSHADERS_ERROR_INVALIDSHADERPROGRAMINDEX);
				return nullptr;
			}
			PrintErrorMessage(TSHADERS_ERROR_NOTINITIALIZED);
			return nullptr;
		}

		/*
		* returns a pointer to a TShader corresponding to the given name. returns nullptr if the TShader is not found
		*/
		static TShader* GetShaderByName(const GLchar* ShaderName)
		{
			if (TinyShaders::IsInitialized)
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
					PrintErrorMessage(TSHADERS_ERROR_SHADERNOTFOUND);
					return nullptr;
				}
				PrintErrorMessage(TSHADERS_ERROR_INVALIDSHADERNAME);
				return nullptr;
			}
			PrintErrorMessage(TSHADERS_ERROR_NOTINITIALIZED);
			return nullptr;
		}

		/*
		* return a pointer to a TShader corresponding to the given index. returns nullptr if the TShader is not found
		*/
		static TShader* GetShaderByIndex(GLuint ShaderIndex)
		{
			if (TinyShaders::IsInitialized)
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

		/*
		* load an OpenGL shader
		*/
		static void LoadShader(const GLchar* Name, 
			const GLchar* ShaderFile, 
			GLuint ShaderType)
		{
			if (TinyShaders::IsInitialized)
			{
				if (Name != nullptr)
				{
					if (ShaderType >= 0 && ShaderType <= 5)
					{
						TShader* NewShader = new TShader(Name, ShaderType, ShaderFile);
					}
					PrintErrorMessage(TSHADERS_ERROR_INVALIDSHADERTYPE, GetInstance()->ShaderTypeToString(ShaderType));
				}
				PrintErrorMessage(TSHADERS_ERROR_INVALIDSTRING);
			}
			PrintErrorMessage(TSHADERS_ERROR_NOTINITIALIZED);
		}

		/*
		* loads all shaders and shader programs specified in a custom configuration file
		*/
		static void LoadShaderProgramsFromConfigFile(const GLchar* ConfigFile)
		{
			if (!TinyShaders::IsInitialized)
			{
				FILE* pConfigFile = fopen(ConfigFile, "r");
				GLuint NumInputs = 0;
				GLuint NumOutputs = 0;
				GLuint NumPrograms = 0;
				GLuint Iterator = 0;

				std::vector<const GLchar*> Inputs, Outputs, Paths, Names;

				if (pConfigFile)
				{
					//get the total number of shader programs
					fscanf(pConfigFile, "%i\n\n", &NumPrograms);

					for (GLuint ProgramIter = 0;
						ProgramIter < NumPrograms;
						ProgramIter++, fscanf(pConfigFile, "\n\n"), Paths.clear(), Inputs.clear(), Outputs.clear(), Names.clear())
					{
						//get the name of the shader program 
						GLchar* ProgramName = new GLchar[255];
						fscanf(pConfigFile, "%s\n", ProgramName);

						//this is an anti-trolling measure. If a shader with the same name already exists the don't bother making a new one.
						if (!GetInstance()->ShaderProgramExists(ProgramName))
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
							for (Iterator = 0; Iterator < TShaderProgram::MaxNumShaders; Iterator++)
							{
								GLchar* Name = new GLchar[255];
								fscanf(pConfigFile, "%s\n", Name);
								Names.push_back(Name);
							}

							//get all Shader Paths
							for (Iterator = 0; Iterator < TShaderProgram::MaxNumShaders; Iterator++)
							{
								GLchar* Path = new GLchar[255];
								fscanf(pConfigFile, "%s\n", Path);
								Paths.push_back(Path);
							}

							std::vector<TShader*> Shaders;

							for (GLuint ShaderIterator = 0; ShaderIterator < TShaderProgram::MaxNumShaders; ShaderIterator++)
							{
								if (strcmp(Names[ShaderIterator], "None") != 0)
								{
									if (!GetInstance()->ShaderExists(Names[ShaderIterator]))
									{
										//If a shader component of the same name doesn't exist then compile it and add it to storage
										switch (ShaderIterator)
										{
										case 0:
										{
											Shaders.push_back(new TShader(Names[ShaderIterator], GL_VERTEX_SHADER, Paths[ShaderIterator]));
											break;
										}

										case 1:
										{
											Shaders.push_back(new TShader(Names[ShaderIterator], GL_FRAGMENT_SHADER, Paths[ShaderIterator]));
											break;
										}

										case 2:
										{
											Shaders.push_back(new TShader(Names[ShaderIterator], GL_GEOMETRY_SHADER, Paths[ShaderIterator]));
											break;

										}

										case 3:
										{
											Shaders.push_back(new TShader(Names[ShaderIterator], GL_TESS_CONTROL_SHADER, Paths[ShaderIterator]));
											break;
										}

										case 4:
										{
											Shaders.push_back(new TShader(Names[ShaderIterator], GL_TESS_EVALUATION_SHADER, Paths[ShaderIterator]));
											break;
										}

										default:
										{
											break;
										}
										}										
									}

									else
									{
										//If one already exists then dig that one out from storage and attach it to the shader. It should already be compiled!
										Shaders.push_back(GetShaderByName(Names[ShaderIterator]));
									}
								}
							}
							TShaderProgram* NewShader = new TShaderProgram(ProgramName, Inputs, Outputs, Shaders);
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

		/*
		* builds a new OpenGL shader program from already loaded shaders
		*/
		static void BuildProgramFromShaders(const GLchar* ShaderName,
			std::vector<const GLchar*> Inputs,
			std::vector<const GLchar*> Outputs,
			const GLchar* VertexShaderName,
			const GLchar* FragmentShaderName,
			const GLchar* GeometryShaderName,
			const GLchar* TessContShaderName,
			const GLchar* TessEvalShaderName)
		{
			if (TinyShaders::IsInitialized)
			{
				std::vector<TShader*> Shaders;
				Shaders.push_back(GetShaderByName(VertexShaderName));
				Shaders.push_back(GetShaderByName(FragmentShaderName));
				Shaders.push_back(GetShaderByName(GeometryShaderName));
				Shaders.push_back(GetShaderByName(TessContShaderName));
				Shaders.push_back(GetShaderByName(TessEvalShaderName));

				TShaderProgram* NewShaderProgram = new TShaderProgram(ShaderName, Inputs, Outputs, Shaders);
			}
			PrintErrorMessage(TSHADERS_ERROR_NOTINITIALIZED);
		}

		/*
		* check if the shader program exists in TinyShaders.(has it been loaded and initialized?)
		*/
		static GLboolean ShaderProgramExists(const GLchar* ShaderName)
		{
			if (ShaderName != nullptr)
			{
				if (!GetInstance()->ShaderPrograms.empty())
				{
					for (GLuint Iterator = 0; Iterator < GetInstance()->ShaderPrograms.size(); Iterator++)
					{
						if (GetInstance()->ShaderPrograms[Iterator] != nullptr &&
							!strcmp(ShaderName, GetInstance()->ShaderPrograms[Iterator]->Name))
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

		/*
		* check if the shader exists in TinyShaders. (has it been loaded and initialized?)
		*/
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

	private:

		/*
		* a TShader is essentially an OpenGL shader
		*/
		struct TShader
			{
				TShader(const GLchar* ShaderName, GLuint ShaderType, const GLchar* ShaderFilePath) :
					Name(ShaderName)
				{
					Type = ShaderType;
					IsCompiled = GL_FALSE;
					FilePath = ShaderFilePath;
					Compile();
				}
				TShader(){}
				~TShader(){}

				/*
				* compile the shader with the given information
				*/
				GLvoid Compile()
				{
					//if the component hasn't been compiled yet
					if (!IsCompiled)
					{
						GLchar ErrorLog[512];
						GLint Success;
						GLchar* Source = GetInstance()->FileToBuffer(FilePath);

						if (Source != nullptr)
						{
							Handle = glCreateShader(Type);
							glShaderSource(Handle, 1, (const GLchar**)&Source, 0);
							glCompileShader(Handle);

							glGetShaderiv(Handle, GL_COMPILE_STATUS, &Success);
							glGetShaderInfoLog(Handle, sizeof(ErrorLog), 0, ErrorLog);

							if (Success != GL_TRUE)
							{
								PrintErrorMessage(TSHADERS_ERROR_FAILEDSHADERLOAD, GetInstance()->ShaderTypeToString(Type));
								printf("%s\n", ErrorLog);
							}

							else
							{
								IsCompiled = GL_TRUE;
								GetInstance()->Shaders.push_back(this);
								ID = GetInstance()->Shaders.size() - 1;
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

				/*
				* remove the shader from OpenGL
				*/
				GLvoid Shutdown()
				{
					glDeleteShader(Handle);
					IsCompiled = GL_FALSE;
				}

				const GLchar* Name; /**<the name of the shader component */
				const GLchar* FilePath; /**<the FilePath of the component*/
				GLuint Handle; /**<The handle to the shader in OpenGL*/
				GLuint Type; /**<the type of shader (Vertex, Fragment, etc.)*/
				GLuint ID; /**<the ID of the shader*/
				GLboolean IsCompiled; /**<Whether the shader has been compiled*/
			};

		/*
		* a TShaderProgram is is essentially an OpengL shader program 
		*/
		struct TShaderProgram
			{
				/*
				* basic constructor
				*/
				TShaderProgram()
				{
					MaxNumShaders = 5;
					ID = 0;
				};

				/*
				* uses the given values to create an OpenGL shader program
				*/
				TShaderProgram(const GLchar* ShaderName,
					std::vector<const GLchar*> ProgramInputs,
					std::vector<const GLchar*> ProgramOutputs,
					std::vector<TShader*> ProgramShaders) :
					Name(ShaderName), Inputs(ProgramInputs),
					Outputs(ProgramOutputs), Shaders(ProgramShaders)
				{
					Compiled = GL_FALSE;
					Compile();
				};

				/*
				* another bare bones constructor
				*/
				TShaderProgram(const GLchar* ShaderName) : Name(ShaderName)
				{
					MaxNumShaders = 5;
					Compiled = GL_FALSE;
				};

				~TShaderProgram(){}

				/*
				* shut down the shader program. delete it from OpenGL
				*/
				GLvoid Shutdown()
				{
					glDeleteProgram(Handle);

					for (GLuint Iterator = 0; Iterator < GetInstance()->Shaders.size(); Iterator++)
					{
						GetInstance()->Shaders[Iterator]->Shutdown();
						delete GetInstance()->Shaders[Iterator];
					}
					Shaders.clear();
					Inputs.clear();
					Outputs.clear();
				}
				
				/*
				* compile the OpenGL shader program with the given information
				*/
				GLboolean Compile()
				{
					Handle = glCreateProgram();
					GLchar ErrorLog[512];
					GLint Successful = GL_FALSE;
					if (!Compiled)
					{
						for (GLuint Iterator = 0; Iterator < Shaders.size(); Iterator++)
						{
							if (Shaders[Iterator] != nullptr)
							{
								glAttachShader(Handle, Shaders[Iterator]->Handle);
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
							PrintErrorMessage(TSHADERS_ERROR_FAILEDSHADERPROGRAMLINK, Name);
							printf("%s\n", ErrorLog);
							return GL_FALSE;
						}
						//if a shader successfully compiles then it will add itself to storage
						Compiled = GL_TRUE;
						GetInstance()->ShaderPrograms.push_back(this);
						ID = GetInstance()->ShaderPrograms.size() - 1;
						return GL_TRUE;
					}
					PrintErrorMessage(TSHADERS_ERROR_SHADERPROGRAMEXISTS, Name);
					return GL_FALSE;
				}

				const GLchar* Name; /**<The name of the shader program*/
				GLuint Handle; /**<The OpenGL handle to the shader program*/
				GLuint ID;/**< the ID of the shader program*/
				static GLuint MaxNumShaders; /**<The Maximum number of components a shader program can have. It's always 5*/
				GLboolean Compiled; /**<Whether the shader program has been linked successfully*/
				std::vector<const GLchar*> Inputs; /**<the inputs of the shader program as a vector of strings*/
				std::vector<const GLchar*> Outputs; /**< the outputs of the shader program as a vector of strings*/
				std::vector<TShader*> Shaders; /**< the components that the shader program is comprised of as a vector*/
			};		

		/*
		* returns a static reference to an instance of TinyShaders
		*/
		static TinyShaders* GetInstance()
		{
			if (TinyShaders::IsInitialized)
			{
				return TinyShaders::Instance;
			}

			TinyShaders::IsInitialized = GL_TRUE;
			TinyShaders::Instance = new TinyShaders();
			return TinyShaders::Instance;
		}

		/*
		* print the error message and additional information corresponding to the Error handle
		*/
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

			case TSHADERS_ERROR_INVALIDSHADERPROGRAMNAME:
			{
				printf("Error: given shader name is invalid \n");
				break;
			}

			case TSHADERS_ERROR_INVALIDSHADERPROGRAMINDEX:
			{
				printf("Error: given shader index is invalid \n");
				break;
			}

			case TSHADERS_ERROR_INVALIDSHADERNAME:
			{
				printf("Error: given shader component name is invalid \n");
				break;
			}

			case TSHADERS_ERROR_INVALIDSHADERINDEX:
			{
				printf("Error: given shader component index is invalid \n");
				break;
			}

			case TSHADERS_ERROR_INVALIDFILEPATH:
			{
				printf("Error: given file path is invalid %s \n", String);
				break;
			}

			case TSHADERS_ERROR_SHADERPROGRAMNOTFOUND:
			{
				printf("Error: shader with given name %s was not found \n", String);
				break;
			}

			case TSHADERS_ERROR_SHADERNOTFOUND:
			{
				printf("Error: shader component with given name %s was not found \n", String);
				break;
			}

			case TSHADERS_ERROR_INVALIDSHADERTYPE:
			{
				printf("Error: invalid shader type given \n");
				break;
			}

			case TSHADERS_ERROR_FAILEDSHADERLOAD:
			{
				printf("Error: failed to compile %s shader component \n", String);
				break;
			}

			case TSHADERS_ERROR_FAILEDSHADERPROGRAMLINK:
			{
				if (String != nullptr)
				{
					printf("Error: failed to link program %s \n", String);
				}
				break;
			}

			case TSHADERS_ERROR_SHADEREXISTS:
			{
				printf("Error: shader component with this name %s already exists \n", String);
				break;
			}

			case TSHADERS_ERROR_SHADERPROGRAMEXISTS:
			{
				if (String != nullptr)
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

		/*
		* convert the given file to a single dimension c-string buffer
		*/
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

		/*
		* convert the given string to a shader type
		*/
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
		
		/*
		* convert the given shader type to a string
		*/
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

		std::vector<TShaderProgram*> ShaderPrograms; /**< all loaded shader programs */
		std::vector<TShader*> Shaders; /**< all loaded shaders*/

		static GLboolean IsInitialized; /**<Whether TinyShaders has ban initialized */
		static TinyShaders* Instance; /**<a static instance of the TinyShaders API*/
};

GLboolean TinyShaders::IsInitialized = GL_FALSE;
TinyShaders* TinyShaders::Instance = nullptr;
GLuint TinyShaders::TShaderProgram::MaxNumShaders = 5;
#endif
