//created by Ziyad Barakat 2015

#ifndef TINY_SHADERS_H
#define TINY_SHADERS_H

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#include <gl/GL.h>
//disable annoying warnings about unsafe stdio functions
#pragma  warning(disable: 4474)
#pragma  warning(disable: 4996)
//this automatically loads the OpenGL library if you are using Visual studio 
//comment this out if you have your own method 
//#pragma comment (lib, "opengl32.lib")
#endif

#if defined(__linux__) 
#include <GL/gl.h>
#endif

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <functional>
#include <memory>
#include <system_error>
#include <bitset>
#include <ctype.h>
#include <math.h>

namespace TinyShaders
{
	using parseUniformBlockEvent_t = std::function<void(GLuint errorNumber, std::string errorMessage)>;

	const int maxNumShaderComponents = 5;/**< The Maximum number of components a shader program can have. It's always 5*/
	std::string defaultProgramBinaryExtension = ".glbin";
	std::string defaultBinaryPath = "./Shaders/";
	std::string defaultBinaryconfigPath = "Binaries.txt";
	std::string defaultShaderProgramPath = "Shaders.txt";

	enum class error_t
	{
		success,
		invalidString,
		invalidShaderProgramName,
		invalidShaderProgramIndex,
		invalidShaderName,
		invalidShaderIndex,
		invalidFilePath,
		shaderProgramNotFound,
		shaderNotFound,
		invalidShaderType,
		shaderLoadFailed,
		shaderProgramLoadFailed,
		shaderProgramLinkFailed,
		shaderAlreadyLoaded,
		shaderProgramAlreadyExists,
		invalidSourceFile,
		shaderCompileFailed,
		shaderProgramCompileFailed
	};

	enum class shaderType_t
	{
		vertex = gl_vertex_shader,
		fragment = gl_fragment_shader,
		geometry = gl_geometry_shader,
		tessControl, gl_tess_control_shader,
		tessEval = gl_tess_evaluation_shader,
		compute = gl_compute_shader
	};

	class errorCategory_t : public std::error_category
	{
		public:
			const char* name() const throw() override
			{
				return "tinyShaders";
			}

			virtual std::string message(int errorValue) const override
			{
				auto err = (error_t)errorValue;
				switch (err)
				{
				case error_t::success:
				{
					return "function call was successful \n";
				}
				case error_t::invalidString:
				{
					return "Error: string was invalid \n";
				}					
				case error_t::invalidShaderProgramName:
				{
					return "Error: invalid shader program name \n";
				}					
				case error_t::invalidShaderProgramIndex:
				{
					return "Error: invalid shader program index \n";
				}
				case error_t::invalidShaderName:
				{
					return "Error: invalid shader name \n";
				}
				case error_t::invalidShaderIndex:
				{
					return "Error: invalid shader index \n";
				}
				case error_t::invalidFilePath:
				{
					return "Error: invalid file path \n";
				}
				case error_t::shaderProgramNotFound:
				{
					return "Error: shader program not found \n";
				}
				case error_t::shaderNotFound:
				{
					return "Error: shader not found \n";
				}
				case error_t::invalidShaderType:
				{
					return "Error: invalid shader type \n";
				}
				case error_t::shaderLoadFailed:
				{
					return "Error: shader has failed to load \n";
				}
				case error_t::shaderProgramLoadFailed:
				{
					return "Error: shader program has failed to load \n";
				}
				case error_t::shaderProgramLinkFailed:
				{
					return "Error: shader program linking has failed \n";
				}
				case error_t::shaderAlreadyLoaded:
				{
					return "Error: shader has already been loaded. skipping \n";
				}
				case error_t::shaderProgramAlreadyExists:
				{
					return "Error: shader program has already been loaded. skipping \n";
				}
				case error_t::invalidSourceFile:
				{
					return "Error: source file is invalid \n";
				}

				case error_t::shaderCompileFailed:
				{
					return "Error: the shader has failed to compile \n";
				}

				case error_t::shaderProgramCompileFailed:
				{
					return "Error: the shader program has failed to compile \n";
				}

				default:
				{
					return "Unspecified error \n";
				}
				}
			}

			errorCategory_t() {};

			const static errorCategory_t& get()
			{
				const static errorCategory_t category;
				return category;
			}
	};

	inline std::error_code make_error_code(error_t errorCode)
	{
		return std::error_code(static_cast<int>(errorCode), errorCategory_t::get());
	}
}

namespace std
{
	template<> struct is_error_code_enum<TinyShaders::error_t> : std::true_type {};
};

namespace TinyShaders
{
	class tShader
	{
		friend class shaderManager;

	public:

		std::string		name;			/**<The name of the shader component */
		std::string		filePath;		/**<The FilePath of the component*/
		GLuint				handle;			/**<The handle to the shader in OpenGL*/
		shaderType_t		type;			/**<The type of shader ( Vertex, Fragment, etc.)*/
		GLboolean			isCompiled;		/**<Whether the shader has been compiled*/

		tShader(std::string shaderName, shaderType_t shaderType, std::string shaderFilePath) :
			name(shaderName), type(shaderType), isCompiled(false), filePath(shaderFilePath)
		{
			std::string buffer;
			FileToBuffer(shaderFilePath, buffer);
			Compile(buffer);
		}

		tShader(std::string shaderName, std::string buffer, shaderType_t shaderType)
			: name(shaderName), type(shaderType)
		{
			type = shaderType;
			isCompiled = GL_FALSE;
			Compile(buffer);
			filePath = nullptr;

		}
		tShader() :
		handle(0), type(shaderType_t::vertex), isCompiled(false) {}
		~tShader() {}

		/*
		* compile the shader from a given text file
		*/
		std::error_code Compile(std::string source)
		{
			//if the component hasn't been compiled yet
			if (!isCompiled)
			{
				char errorLog[512];
				GLint successful;

				if (!source.empty())
				{
					handle = glCreateShader(static_cast<unsigned int>(type));
					glShaderSource(handle, 1, (const char**)&source, 0);
					glCompileShader(handle);

					glGetShaderiv(handle, gl_compile_status, &successful);
					glGetShaderInfoLog(handle, sizeof(errorLog), 0, errorLog);

					if (successful != GL_TRUE)
					{
						return error_t::shaderLoadFailed;
					}

					else
					{
						isCompiled = GL_TRUE;
					}
				}
				else
				{
					return error_t::invalidSourceFile;
				}
			}
			else
			{
				//either the file name doesn't exist or the component has already been loaded
				return error_t::invalidFilePath;
			}
			return error_t::success;
		}

		/*
		* remove the shader from OpenGL
		*/
		void Shutdown()
		{
			glDeleteShader(handle);
			isCompiled = GL_FALSE;
		}

		/*
* convert the given file to a single dimension c-string buffer
*/
		std::error_code FileToBuffer(const std::string& path, std::string& bufferToFill)
		{
			FILE* file = fopen(path.c_str(), "rt");

			if (file == nullptr)
			{
				return error_t::invalidFilePath;
			}

			//get total byte in given file
			fseek(file, 0, SEEK_END);
			GLuint FileLength = ftell(file);
			fseek(file, 0, SEEK_SET);

			//allocate a file buffer and read the contents of the file
			std::string buffer(FileLength, '\0');
			fread(&buffer[0], sizeof(char), FileLength, file);

			fclose(file);
			bufferToFill = buffer;
			return error_t::success;
		}
	};

	/*
	* a TShaderProgram is is essentially an OpenGL shader program
	*/
	class tShaderProgram
	{
		friend class shaderManager;

	public:

		std::string						name;				/**< The name of the shader program */
		GLuint								handle;				/**< The OpenGL handle to the shader program */
		GLboolean							isCompiled;			/**< Whether the shader program has been linked successfully */
		std::vector< std::string >		inputs;				/**< The inputs of the shader program as a vector of strings */
		std::vector< std::string >		outputs;			/**< The outputs of the shader program as a vector of strings */
		std::vector< tShader* >			shaders;			/**< The components that the shader program is comprised of as a vector */

		/*
		* basic constructor
		*/
		tShaderProgram() : 
		handle(0), isCompiled(false) {};

		/*
		* uses the given values to create an OpenGL shader program
		*/
		tShaderProgram(std::string programName,
			std::vector< std::string > programInputs,
			std::vector< std::string > programOutputs,
			std::vector< tShader* > programShaders,
			bool saveBinary = false) :
			name(programName), inputs(programInputs),
			outputs(programOutputs), shaders(programShaders)
		{
			isCompiled = GL_FALSE;
			if (Compile(saveBinary) != error_t::success)
			{
				exit(0);
			};
			//get number of uniform blocks
			/*if (parseUniformBlockEvent != nullptr)
			{
				shaderBlocksEvent(handle);
			}*/
		};

		/*
		* another bare bones constructor
		*/
		tShaderProgram(std::string programName) : 
			name(programName), isCompiled(false), handle(0) {};

		tShaderProgram(std::string programName, GLuint programHandle) :
			name(programName), handle(programHandle), isCompiled(false) {}

		~tShaderProgram() {}

		/*
		* shut down the shader program. delete it from OpenGL
		*/
		void Shutdown()
		{
			glDeleteProgram(handle);

			for (auto & shader : shaders)
			{
				shader->Shutdown();
			}
			shaders.clear();
			inputs.clear();
			outputs.clear();
		}

		/*
		* compile the OpenGL shader program with the given information
		*/
		std::error_code Compile(bool saveBinary)
		{
			handle = glCreateProgram();
			char errorLog[512];
			GLint successful = GL_FALSE;
			if (!isCompiled)
			{
				for (auto & shader : shaders)
				{
					if (shader != nullptr)
					{
						glAttachShader(handle, shader->handle);
					}
				}

				// specify vertex input attributes
				for (size_t i = 0; i < inputs.size(); ++i)
				{
					glBindAttribLocation(handle, (GLuint)i, inputs[i].c_str());
				}

				// specify pixel shader outputs
				for (size_t i = 0; i < outputs.size(); ++i)
				{
					glBindFragDataLocation(handle, (GLuint)i, outputs[i].c_str());
				}

				if (saveBinary)
				{
					glProgramParameteri(handle, gl_program_binary_retrievable_hint, GL_TRUE);
				}

				glLinkProgram(handle);
				glGetProgramiv(handle, gl_link_status, &successful);

				if (!successful)
				{
					glGetProgramInfoLog(handle, sizeof(errorLog), 0, errorLog);
					printf("%s \n", errorLog);
					return error_t::shaderProgramLinkFailed;
				}
				//if a shader successfully compiles then it will add itself to storage

				if (saveBinary)
				{
					GLint binarySize = 0;
					glGetProgramiv(handle, gl_program_binary_length, &binarySize);

					auto* buffer = (void*)malloc(binarySize);
					GLenum binaryFormat = GL_NONE;

					glGetProgramBinary(handle, binarySize, NULL, &binaryFormat, buffer);

					std::string path;

					path += defaultBinaryPath;
					path += name;
					path += defaultProgramBinaryExtension;

					FILE* file = fopen(path.c_str(), "wb");
					fprintf(file, "%s\n", name.c_str());
					fprintf(file, "%i\n", binarySize);
					fprintf(file, "%i\n", binaryFormat);
					fwrite(buffer, binarySize, 1, file);
					fclose(file);
					path.clear();
				}
				isCompiled = GL_TRUE;
				return error_t::success;
			}
			return error_t::shaderProgramAlreadyExists;
		}

	};

	class shaderManager
	{
		public:
			parseUniformBlockEvent_t parseUniformBlockEvent;

			std::vector< std::unique_ptr<tShaderProgram>>		shaderPrograms;    	/**< All loaded shader programs */
			std::vector< std::unique_ptr<tShader>>			shaders;			/**< All loaded shaders*/

			shaderManager(){}
			~shaderManager(){}

			/*
			* shuts down TinyShaders. deletes all OpenGL shaders and shader programs 
			* as well as calling shutdown on all shader and programs and clears all vectors.
			*/
			void Shutdown()
			{
				for (auto & shader : shaders)
				{
					shader->Shutdown();
					// delete shaders[iterator];
				}

				for (auto & shaderProgram : shaderPrograms)
				{
					shaderProgram->Shutdown();
					//delete shaderPrograms[iterator];
				}

				shaderPrograms.clear();
				//delete instance;
			}

			/*
			* returns a pointer to a TShaderProgram corresponding to the given name. returns nullptr if the TShaderProgram is not found
			*/
			std::error_code GetShaderProgramByName( std::string programName, tShaderProgram* outProgram )
			{
				if (!programName.empty())
				{
					for (auto & shaderProgram : shaderPrograms)
					{
						if (shaderProgram->name.compare(programName) == 0)
						{
							outProgram = shaderProgram.get();
							return error_t::success;
						}
					}
					return error_t::shaderProgramNotFound;
				}
				return error_t::invalidShaderProgramName;
			}

			/*
			* returns a pointer to a TShader corresponding to the given name. returns nullptr if the TShader is not found
			*/
			std::error_code GetShaderByName( std::string shaderName, tShader* outShader )
			{
				if (!shaderName.empty())
				{
					for (auto & shaderIter : shaders)
					{
						if (shaderIter->name.compare(shaderName) == 0)
						{
							outShader = shaderIter.get();
							return error_t::success;
						}
					}
					return error_t::shaderNotFound;
				}
				return error_t::invalidShaderName;
			}

			/*
			* load an OpenGL shader
			*/
			std::error_code LoadShader( std::string name, std::string shaderFile, shaderType_t shaderType, tShader* outShader = nullptr )
			{
				if (!name.empty())
				{
					std::unique_ptr<tShader> newShader(new tShader(name, shaderType, shaderFile));
					if (newShader->isCompiled)
					{
						shaders.push_back(std::move(newShader));
						outShader = shaders.back().get();
						return error_t::success;
					}
					return error_t::shaderCompileFailed;
				}
				return error_t::invalidString;
			}

			/*
			* loads all shaders and shader programs specified in a custom configuration file
			*/
			std::error_code LoadShaderProgramsFromConfigFile(const std::string& configPath, bool saveBinary = false, std::vector<tShaderProgram*>* outPrograms = nullptr)
			{
					FILE* pConfigFile = fopen( configPath.c_str(), "r" );
					GLuint numInputs = 0;
					GLuint numOutputs = 0;
					GLuint numPrograms = 0;
					GLuint numShaders = 0;
					GLuint iterator = 0;

					std::vector< std::string > inputs, outputs, paths, names;
					std::vector< tShader* > shaders;
					if ( pConfigFile )
					{
						//get the total number of shader programs
						fscanf( pConfigFile, "%u\n", &numPrograms );

						for ( GLuint programIter = 0;
							programIter <numPrograms;
							programIter++, paths.clear(), inputs.clear(), outputs.clear(), names.clear(), shaders.clear() )
						{
							//get the name of the shader program 
							auto* programName = new char[255];
							fscanf( pConfigFile, "%s\n", programName );
							printf( "%s\n", programName );

							//this is an anti-trolling measure. If a shader with the same name already exists the don't bother making a new one.
							if ( !ShaderProgramExists( programName ) )
							{
								//get the number of shader inputs
								fscanf( pConfigFile, "%u\n", &numInputs );

								//get all inputs
								for ( iterator = 0; iterator <numInputs; iterator++ )
								{
									auto* input = new char[255];
									fscanf( pConfigFile, "%s\n", input );
									inputs.emplace_back( input );
								}

								//get the number of shader outputs
								fscanf( pConfigFile, "%u\n", &numOutputs );

								//get all outputs
								for ( iterator = 0; iterator <numOutputs; iterator++ )
								{
									auto* output = new char[255];
									fscanf( pConfigFile, "%s\n", output );
									outputs.emplace_back( output );
								}

								//get number of shaders
								fscanf( pConfigFile, "%u\n", &numShaders );
								printf( "%u\n", numShaders );

								for( GLuint iterator = 0; iterator <numShaders; iterator++ )
								{
									auto* shaderName = new char[255];
									auto* shaderPath = new char[255];
									auto* shaderType = new char[255];
								
									//get shader name
									fscanf( pConfigFile, "%s\n", shaderName );
									printf( "%s\n", shaderName );

									//if the shader hasn't been loaded already then make a new one
									if( !ShaderExists( shaderName ) )
									{
										//remove printf calls?
										//get type
										fscanf( pConfigFile, "%s\n", shaderType );
										printf( "%s\n", shaderType );
										//get file path
										fscanf( pConfigFile, "%s\n", shaderPath );
										printf( "%s\n", shaderPath );

										shaderType_t newType;
										StringToShaderType((std::string)shaderType, newType);

										tShader* newShader = new tShader(shaderName, newType, shaderPath);
										if(newShader->isCompiled)
										{
											shaders.push_back(std::move(newShader));
										}
										else
										{
											return error_t::shaderCompileFailed;
										}
									}

									else
									{
										//tell scanf to skip a couple lines. very unsafe!
										fscanf( pConfigFile, "%*[^\n]\n %*[^\n]\n", nullptr );
										//if shader already exists then add an existing one from storage, it should already be compiled
										tShader* newShader = nullptr;
										GetShaderByName(shaderName, newShader);
										shaders.push_back( newShader );
									}
								}

								std::unique_ptr<tShaderProgram> newShaderProgram(new tShaderProgram( programName, inputs, outputs, shaders, saveBinary));
							
								if (newShaderProgram->isCompiled)
								{
									if (outPrograms != nullptr)
									{
										outPrograms->push_back(newShaderProgram.get());
									}
									shaderPrograms.push_back(std::move(newShaderProgram));
								}
								fclose(pConfigFile); 
								return error_t::shaderProgramCompileFailed;
							}
						}
						fclose( pConfigFile );
						return error_t::success;
					}
				return error_t::invalidFilePath;
			}

			std::error_code LoadProgramBinariesFromConfigFile( const std::string& configPath, std::vector<tShaderProgram*>* outPrograms = nullptr )
			{
				//open a file stream to binaries.txt
				GLuint numBinaries;
				FILE* configFile = fopen(configPath.c_str(), "r");
				if ( configFile )
				{
					fscanf(configFile, "%u", &numBinaries);
					fscanf(configFile, "%*[^\n]\n %*[^\n]\n", nullptr);
					for (unsigned int iter = 0; iter < numBinaries; iter++)
					{
						char binaryPath[255];
						fscanf(configFile, "%s \n", binaryPath);

						FILE* binaryFile = fopen(binaryPath, "rb");
						//std::ifstream file;
						char binaryName[255];
						GLuint binarySize = 0;
						GLuint size = 0;
						GLuint binaryFormat = 0;

						fscanf(binaryFile, "%s \n", binaryName);
						fscanf(binaryFile, "%u \n", &binarySize);
						fscanf(binaryFile, "%u \n", &binaryFormat);

						auto* binaryBuffer = (void*)malloc(binarySize);
						fread(binaryBuffer, binarySize, 1, binaryFile);
						fclose(binaryFile);

						//load the buffer into OpenGL
						GLuint programHandle = glCreateProgram();
						glProgramBinary(programHandle, binaryFormat, binaryBuffer, binarySize);
						free(binaryBuffer);
						GLint isSuccessful = false;

						glGetProgramiv(programHandle, gl_link_status, &isSuccessful);

						if (isSuccessful)
						{
							//create a program object and load into the list
							std::unique_ptr<tShaderProgram> newProgram(new tShaderProgram(binaryName, programHandle));
							{
								if (newProgram->isCompiled)
								{
									shaderPrograms.push_back(std::move(newProgram));
									if (outPrograms != nullptr)
									{
										outPrograms->push_back(newProgram.get());
									}
								}
							}
						}
						else
						{
							fclose(configFile);
							return error_t::shaderProgramLinkFailed;
						}
					}
					fclose(configFile);
					return error_t::success;
				}
				return error_t::invalidFilePath;
			}

			std::error_code LoadShadersFromConfigFile( const std::string& configFile, std::vector<tShader*>* outShaders = nullptr)
			{
				FILE* pConfigFile = fopen( configFile.c_str(), "r+" );
				GLuint numShaders = 0;

				if( pConfigFile )
				{
					//get the number of shaders to load
					fscanf(pConfigFile, "%u\n", &numShaders);
					char* shaderName;
					char*	shaderType;
					char*	shaderPath;

					char empty[255];	

					for( GLuint iterator = 0; iterator <numShaders; 
							iterator++, fscanf( pConfigFile, "\n\n" ) )
					{
						shaderName = empty;
						fscanf( pConfigFile, "%s\n", shaderName );

						if( !ShaderExists( shaderName ) )
						{
							shaderType = empty;
							fscanf( pConfigFile, "%s\n", shaderType );

							shaderPath = empty;
							fscanf( pConfigFile, "%s\n", shaderPath );

							shaderType_t typeVal;
							StringToShaderType(shaderType, typeVal);
							std::unique_ptr<tShader> newShader (new tShader(shaderName, typeVal, shaderPath ));
							if (newShader->isCompiled)
							{
								shaders.push_back(std::move(newShader));
								if (outShaders != nullptr)
								{
									outShaders->push_back(shaders.back().get());
								}
							}
							fclose(pConfigFile);
							return error_t::shaderCompileFailed;
						}
					}
					fclose(pConfigFile);
					return error_t::success;
				}
				return error_t::invalidFilePath;
			}

			std::error_code SaveShaderProgramsToConfigFile( const std::string& fileName )
			{
				//write total amount of shaders
				FILE* pConfigFile = fopen( fileName.c_str(), "w+" );

				if (pConfigFile)
				{

					fprintf(pConfigFile, "%i\n\n", (GLint)shaderPrograms.size());

					for (auto & shaderProgram : shaderPrograms)
					{
						//write program name
						fprintf(pConfigFile, "%s\n", shaderProgram->name.c_str());

						//write number of inputs
						fprintf(pConfigFile, "%i\n", (GLint)shaderProgram->inputs.size());

						//write inputs
						for (auto & input : shaderProgram->inputs)
						{
							fprintf(pConfigFile, "%s\n", input.c_str());
						}

						fprintf(pConfigFile, "%i\n", (GLint)shaderProgram->outputs.size());

						//write outputs
						for (auto & output : shaderProgram->outputs)
						{
							fprintf(pConfigFile, "%s\n", output.c_str());
						}

						//write number of shaders
						fprintf(pConfigFile, "%i\n", (GLint)shaderProgram->shaders.size());

						for (auto & shader : shaderProgram->shaders)
						{
							//write shader name
							fprintf(pConfigFile, "%s\n", shader->name.c_str());

							//write shader type
							fprintf(pConfigFile, "%s\n", ShaderTypeToString(shader->type).c_str());

							//write shader file path
							fprintf(pConfigFile, "%s\n", shader->filePath.c_str());
						}
					}
					fclose(pConfigFile);
					return error_t::success;
				}
				return error_t::invalidFilePath;
			}	
		
			/*
			* builds a new OpenGL shader program from already loaded shaders
			*/
			std::error_code BuildProgramFromShaders( const std::string& shaderName,
				const std::vector< std::string >& inputs,
				const std::vector< std::string >& outputs,
				const std::string& vertexShaderName,
				const std::string& fragmentShaderName,
				const std::string& geometryShaderName,
				const std::string& tessContShaderName,
				const std::string& tessEvalShaderName,
				tShaderProgram* outProgram = nullptr,
				bool saveBinary = false )
			{
					std::vector< tShader* > shaderList;
					tShader* vertexShader = nullptr;
					GetShaderByName(vertexShaderName, vertexShader);
					tShader* fragmentShader = nullptr;
					GetShaderByName(fragmentShaderName, fragmentShader);
					tShader* geometryShader = nullptr;
					GetShaderByName(geometryShaderName, geometryShader);
					tShader* tessControlShader = nullptr;
					GetShaderByName(tessContShaderName, tessControlShader);
					tShader* tessEvalShader = nullptr;
					GetShaderByName(tessEvalShaderName, tessEvalShader);

					shaderList.push_back( vertexShader );
					shaderList.push_back( fragmentShader );
					shaderList.push_back( geometryShader );
					shaderList.push_back( tessControlShader );
					shaderList.push_back( tessEvalShader );

					std::unique_ptr<tShaderProgram> newShaderProgram(new tShaderProgram( shaderName, inputs, outputs, shaderList, saveBinary ));
					if (newShaderProgram->isCompiled)
					{
						shaderPrograms.push_back(std::move(newShaderProgram));
						if (outProgram != nullptr)
						{
							outProgram = shaderPrograms.back().get();
						}
						return error_t::success;
					}
					return error_t::shaderProgramLoadFailed;
			}

			/*
			* check if the shader program exists in TinyShaders.( has it been loaded and initialized? )
			*/
			GLboolean ShaderProgramExists( const std::string& shaderName )
			{
				if ( !shaderName.empty() )
				{
					if (!shaderPrograms.empty() )
					{
						for (auto & shaderProgram : shaderPrograms)
						{
							if ( shaderProgram != nullptr && shaderName.compare(shaderProgram->name) == 0)
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
			* check if the shader exists in TinyShaders. ( has it been loaded and initialized? )
			*/
			GLboolean ShaderExists( const std::string& shaderName )
			{
				if ( !shaderName.empty() )
				{
					if ( !shaders.empty() )
					{
						for (auto & shader : shaders)
						{
							if ( shader != nullptr && shaderName.compare(shader->name) )
							{
								return true;
							}
						}
						return false;
					}
					return false;
				}
				return false;
			}

			std::error_code LoadShaderFromBuffer( const std::string& name, const std::string& buffer, const shaderType_t& shaderType )
			{
				if ( !buffer.empty() )
				{
					if ( name.empty() )
					{
						if (!ShaderExists(name))
						{
							std::unique_ptr<tShader> newShader(new tShader(name, buffer, shaderType));
							if (newShader->isCompiled)
							{
								shaders.push_back(std::move(newShader));
								return error_t::success;
							}
							else
							{
								return error_t::shaderCompileFailed;
							}
						}
						return error_t::shaderNotFound;
					}
					return error_t::invalidShaderName;
				}
				return error_t::invalidString;
			}

		private:

			/*
			* convert the given string to a shader type
			*/
			std::error_code StringToShaderType( const std::string& typeString, shaderType_t& shaderTypeOut ) const
			{
				if( !typeString.empty() )
				{
					if ( typeString.compare("Vertex") == 0 )
					{
						shaderTypeOut = shaderType_t::vertex;
						return error_t::success;
					}

					if ( typeString.compare("Fragment") == 0 )
					{
						shaderTypeOut = shaderType_t::fragment;
						return error_t::success;
					}

					if ( typeString.compare("Geometry") == 0 )
					{
						shaderTypeOut = shaderType_t::geometry;
						return error_t::success;
					}

					if ( typeString.compare("Tessellation Control") == 0 )
					{
						shaderTypeOut = shaderType_t::tessEval;
						return error_t::success;
					}

					if ( typeString.compare("Tessellation Evaluation") == 0 )
					{
						shaderTypeOut = shaderType_t::tessEval;
						return error_t::success;
					}

					if (typeString.compare("Compute Shader") == 0)
					{
						shaderTypeOut = shaderType_t::compute;
						return error_t::success;
					}

					return error_t::invalidShaderType;
				}
				return error_t::invalidString;
			}
		
			/*
			* convert the given shader type to a string
			*/
			std::string ShaderTypeToString( const shaderType_t& shaderType ) const 
			{
				switch ( shaderType )
				{
					case shaderType_t::vertex:
					{
						return "Vertex";
					}
					case shaderType_t::fragment:
					{
						return "Fragment"; 
					}
					case shaderType_t::geometry:
					{
						return "Geometry";
					}
					case shaderType_t::tessControl:
					{
						return "Tessellation Control"; 
					}
					case shaderType_t::tessEval:
					{
						return "Tessellation Evaluation";
					}
					case shaderType_t::compute:
					{
						return "Compute";
					}
				}
				return nullptr;
			}
	};
}
#endif
