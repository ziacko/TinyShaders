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

#include <list>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

#define TINYSHADERS_ERROR_NOT_INITIALIZED 1
#define TINYSHADERS_ERROR_INVALID_STRING 2
#define TINYSHADERS_ERROR_INVALID_SHADER_PROGRAM_NAME 3
#define TINYSHADERS_ERROR_INVALID_SHADER_PROGRAM_INDEX 4
#define TINYSHADERS_ERROR_INVALID_SHADER_NAME 5
#define TINYSHADERS_ERROR_INVALID_SHADER_INDEX 6
#define TINYSHADERS_ERROR_INVALID_FILE_PATH 7
#define TINYSHADERS_ERROR_SHADER_PROGRAM_NOT_FOUND 8
#define TINYSHADERS_ERROR_SHADER_NOT_FOUND 9
#define TINYSHADERS_ERROR_INVALID_SHADER_TYPE 10
#define TINYSHADERS_ERROR_FAILED_SHADER_LOAD 11
#define TINYSHADERS_ERROR_FAILED_SHADER_PROGRAM_LINK 12
#define TINYSHADERS_ERROR_SHADER_ALREADY_EXISTS 13
#define TINYSHADERS_ERROR_SHADER_PROGRAM_ALREADY_EXISTS 14
#define TINYSHADERS_ERROR_INVALID_SOURCE_FILE 15
//the macros below are safe for editing
#define TINYSHADERS_DEFAULT_PROGRAM_BINARY_EXTENSION ".glbin"
#define TINYSHADERS_DEFAULT_BINARY_PATH "./Shaders/"
#define TINYSHADERS_DEFAULT_BINARY_CONFIG "Binaries.txt"
#define TINYSHADERS_DEFAULT_PROGRAM_PATH "Shaders.txt"

#define TINYSHADERS_MAX_NUM_SHADER_COMPONENTS 5						/**< The Maximum number of components a shader program can have. It's always 5*/

typedef void( *parseBlocks_t )( GLuint programHandle ); /**< a callback that can gather all the info about the uniform blocks that are in a shader program*/

/*
* print the error message and additional information corresponding to the Error handle
*/
inline static void TinyShaders_PrintErrorMessage(GLuint errorNumber, const GLchar* errorMessage = nullptr)
{
	switch (errorNumber)
	{
		case TINYSHADERS_ERROR_NOT_INITIALIZED:
		{
			printf("Error: TinyShaders must first be initialized \n");
			break;
		}

		case TINYSHADERS_ERROR_INVALID_STRING:
		{
			printf("Error: given string is invalid \n");
			break;
		}

		case TINYSHADERS_ERROR_INVALID_SHADER_PROGRAM_NAME:
		{
			printf("Error: given shader name is invalid \n");
			break;
		}

		case TINYSHADERS_ERROR_INVALID_SHADER_PROGRAM_INDEX:
		{
			printf("Error: given shader index is invalid \n");
			break;
		}

		case TINYSHADERS_ERROR_INVALID_SHADER_NAME:
		{
			printf("Error: given shader component name is invalid \n");
			break;
		}

		case TINYSHADERS_ERROR_INVALID_SHADER_INDEX:
		{
			printf("Error: given shader component index is invalid \n");
			break;
		}

		case TINYSHADERS_ERROR_INVALID_FILE_PATH:
		{
			printf("Error: given file path is invalid %s \n", errorMessage);
			break;
		}

		case TINYSHADERS_ERROR_SHADER_PROGRAM_NOT_FOUND:
		{
			printf("Error: shader with given name %s was not found \n", errorMessage);
			break;
		}

		case TINYSHADERS_ERROR_SHADER_NOT_FOUND:
		{
			printf("Error: shader component with given name %s was not found \n", errorMessage);
			break;
		}

		case TINYSHADERS_ERROR_INVALID_SHADER_TYPE:
		{
			printf("Error: invalid shader type given \n");
			break;
		}

		case TINYSHADERS_ERROR_FAILED_SHADER_LOAD:
		{
			printf("Error: failed to compile %s shader component \n", errorMessage);
			break;
		}

		case TINYSHADERS_ERROR_FAILED_SHADER_PROGRAM_LINK:
		{
			if (errorMessage != nullptr)
			{
				printf("Error: failed to link program %s \n", errorMessage);
			}
			break;
		}

		case TINYSHADERS_ERROR_SHADER_ALREADY_EXISTS:
		{
			printf("Error: shader component with this name %s already exists \n", errorMessage);
			break;
		}

		case TINYSHADERS_ERROR_SHADER_PROGRAM_ALREADY_EXISTS:
		{
			if (errorMessage != nullptr)
			{
				printf("Error: shader with this name %s already exists \n", errorMessage);
				break;
			}
		}

		case TINYSHADERS_ERROR_INVALID_SOURCE_FILE:
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

class tinyShaders
{
	struct shaderProgram_t;
	struct shader_t;

	public:

		tinyShaders( void ){}
		~tinyShaders( void ){}

		/*
		* shuts down TinyShaders. deletes all OpenGL shaders and shader programs 
		* as well as calling shutdown on all shader and programs and clears all vectors.
		*/
		static inline void Shutdown( void )
		{
			if ( tinyShaders::isInitialized )
			{
				for ( GLuint iterator = 0; iterator < GetInstance()->shaders.size(); iterator++ )
				{
					GetInstance()->shaders[iterator]->Shutdown();
					 delete GetInstance()->shaders[iterator];
				}

				for ( GLuint iterator = 0; iterator < GetInstance()->shaderPrograms.size(); iterator++ )
				{
					GetInstance()->shaderPrograms[iterator]->Shutdown();
					delete GetInstance()->shaderPrograms[iterator];
				}

				GetInstance()->shaderPrograms.clear();
				GetInstance()->shaders.clear();

				delete instance;
			}
		}

		/*
		* returns a pointer to a TShaderProgram corresponding to the given name. returns nullptr if the TShaderProgram is not found
		*/
		static inline shaderProgram_t* GetShaderProgramByName( const GLchar* programName )
		{
			if ( tinyShaders::isInitialized )
			{
				if ( programName != nullptr )
				{
					for ( GLuint iterator = 0; iterator < GetInstance()->shaderPrograms.size(); iterator++ )
					{
						if ( !strcmp( GetInstance()->shaderPrograms[iterator]->name, programName ) )
						{
							return GetInstance()->shaderPrograms[iterator];
						}
					}
					return nullptr;
				}
				TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_SHADER_PROGRAM_NOT_FOUND );
				return nullptr;
			}
			TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_NOT_INITIALIZED );
			return nullptr;
		}

		/*
		* returns a pointer to a TShaderProgram corresponding to the given index. returns nullptr if the TShaderProgram is not found
		*/
		static inline shaderProgram_t* GetShaderProgramByIndex( GLuint programIndex )
		{
			if ( tinyShaders::isInitialized )
			{
				if ( programIndex <= GetInstance()->shaderPrograms.size() - 1 )
				{
					return GetInstance()->shaderPrograms[programIndex];
				}
				TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_INVALID_SHADER_PROGRAM_INDEX );
				return nullptr;
			}
			TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_NOT_INITIALIZED );
			return nullptr;
		}

		/*
		* returns a pointer to a TShader corresponding to the given name. returns nullptr if the TShader is not found
		*/
		static inline shader_t* GetShaderByName( const GLchar* shaderName )
		{
			if ( tinyShaders::isInitialized )
			{
				if ( shaderName != nullptr )
				{
					for ( GLuint iterator = 0; iterator < GetInstance()->shaders.size(); iterator++ )
					{
						if ( !strcmp( GetInstance()->shaders[iterator]->name, shaderName ) )
						{
							return GetInstance()->shaders[iterator];
						}
					}
					TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_SHADER_NOT_FOUND );
					return nullptr;
				}
				TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_INVALID_SHADER_NAME );
				return nullptr;
			}
			TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_NOT_INITIALIZED );
			return nullptr;
		}

		/*
		* return a pointer to a TShader corresponding to the given index. returns nullptr if the TShader is not found
		*/
		static inline  shader_t* GetShaderByIndex( GLuint shaderIndex )
		{
			if ( tinyShaders::isInitialized )
			{
				if ( shaderIndex <= GetInstance()->shaders.size() - 1 )
				{
					return GetInstance()->shaders[shaderIndex];
				}
				TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_INVALID_SHADER_INDEX );
				return nullptr;
			}
			TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_NOT_INITIALIZED );
			return nullptr;
		}

		/*
		* load an OpenGL shader
		*/
		static inline void LoadShader( const GLchar* name, const GLchar* shaderFile, GLuint shaderType )
		{
			if ( tinyShaders::isInitialized )
			{
				if ( name != nullptr )
				{
					if ( shaderType <= 5 )
					{
						shader_t* newShader = new shader_t( name, shaderType, shaderFile );
					}
					TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_INVALID_SHADER_TYPE, GetInstance()->ShaderTypeToString( shaderType ) );
				}
				TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_INVALID_STRING );
			}
			TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_NOT_INITIALIZED );
		}

		/*
		* loads all shaders and shader programs specified in a custom configuration file
		*/
		static inline void LoadShaderProgramsFromConfigFile( const GLchar* configPath, bool saveBinary = false )
		{
			if ( GetInstance()->isInitialized )
			{
				FILE* pConfigFile = fopen( configPath, "r" );
				GLuint numInputs = 0;
				GLuint numOutputs = 0;
				GLuint numPrograms = 0;
				GLuint numShaders = 0;
				GLuint iterator = 0;

				std::vector< const GLchar* > inputs, outputs, paths, names;
				std::vector< shader_t* > shaders;
				if ( pConfigFile )
				{
					//get the total number of shader programs
					fscanf( pConfigFile, "%i\n", &numPrograms );

					for ( GLuint programIter = 0;
						programIter <numPrograms;
						programIter++, paths.clear(), inputs.clear(), outputs.clear(), names.clear(), shaders.clear() )
					{
						//get the name of the shader program 
						GLchar* programName = new GLchar[255];
						fscanf( pConfigFile, "%s\n", programName );
						printf( "%s\n", programName );

						//this is an anti-trolling measure. If a shader with the same name already exists the don't bother making a new one.
						if ( !GetInstance()->ShaderProgramExists( programName ) )
						{
							//get the number of shader inputs
							fscanf( pConfigFile, "%i\n", &numInputs );

							//get all inputs
							for ( iterator = 0; iterator <numInputs; iterator++ )
							{
								GLchar* input = new GLchar[255];
								fscanf( pConfigFile, "%s\n", input );
								inputs.push_back( input );
							}

							//get the number of shader outputs
							fscanf( pConfigFile, "%i\n", &numOutputs );

							//get all outputs
							for ( iterator = 0; iterator <numOutputs; iterator++ )
							{
								GLchar* output = new GLchar[255];
								fscanf( pConfigFile, "%s\n", output );
								outputs.push_back( output );
							}

							//get number of shaders
							fscanf( pConfigFile, "%i\n", &numShaders );
							printf( "%i\n", numShaders );

							for( GLuint iterator = 0; iterator <numShaders; iterator++ )
							{
								GLchar* shaderName = new GLchar[255];
								GLchar* shaderPath = new GLchar[255];
								GLchar* shaderType = new GLchar[255];
								
								//get shader name
								fscanf( pConfigFile, "%s\n", shaderName );
								printf( "%s\n", shaderName );

								//if the shader hasn't been loaded already then make a new one
								if( !ShaderExists( shaderName ) )
								{
									//get type
									fscanf( pConfigFile, "%s\n", shaderType );
									printf( "%s\n", shaderType );
									//get file path
									fscanf( pConfigFile, "%s\n", shaderPath );
									printf( "%s\n", shaderPath );

									shaders.push_back( new shader_t( shaderName, GetInstance()->StringToShaderType( ( const char* )shaderType ), shaderPath ) );
								}

								else
								{
									//tell scanf to skip a couple lines
									fscanf( pConfigFile, "%*[^\n]\n %*[^\n]\n", NULL );
									//if shader already exists then add an existing one from storage, it should already be compiled
									shaders.push_back( GetShaderByName( shaderName ) );
								}
							}

							shaderProgram_t* newShaderProgram = new shaderProgram_t( programName, inputs, outputs, shaders, saveBinary);
							//get shader block names
						}
					}
					fclose( pConfigFile );
				}
				else
				{
					TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_INVALID_FILE_PATH );
				}
			}
			else
			{
				TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_NOT_INITIALIZED );
			}
		}

		static inline void LoadProgramBinariesFromConfigFile( const GLchar* configPath )
		{
			//open a file stream to binaries.txt
			GLuint numBinaries;
			FILE* configFile = NULL;
			configFile = fopen(configPath, "r");
			fscanf(configFile, "%i", &numBinaries);
			fscanf(configFile, "%*[^\n]\n %*[^\n]\n", NULL);
			for (unsigned int iter = 0; iter < numBinaries; iter++)
			{
				GLchar binaryPath[255];
				fscanf(configFile, "%s \n", binaryPath);

				FILE* binaryFile = fopen(binaryPath, "rb");
				//std::ifstream file;
				GLchar binaryName[255];
				GLuint binarySize = 0;
				GLuint size = 0;
				GLuint binaryFormat = 0;
				
				fscanf(binaryFile, "%s \n", binaryName);
				fscanf(binaryFile, "%i \n", &binarySize);
				fscanf(binaryFile, "%i \n", &binaryFormat);

				void* binaryBuffer = (void*)malloc(binarySize);
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
					shaderProgram_t* newProgram = new shaderProgram_t(binaryName, programHandle);
					newProgram->compiled = GL_TRUE;
					GetInstance()->shaderPrograms.push_back(newProgram);
					newProgram->iD = GetInstance()->shaderPrograms.size() - 1;
				}
			}
			fclose(configFile);
		}

		static inline void LoadShadersFromConfigFile( const GLchar* configFile )
		{
			if( tinyShaders::isInitialized )
			{
				FILE* pConfigFile = fopen( configFile, "r+" );
				GLuint numShaders = 0;

				if( pConfigFile )
				{
					//get the number of shaders to load
					fscanf( pConfigFile, "%i\n", &numShaders );
				GLchar* shaderName;
					GLchar*	shaderType;
				 	GLchar*	shaderPath;

					GLchar empty[255];	

					for( GLuint iterator = 0; iterator <numShaders; 
							iterator++, fscanf( pConfigFile, "\n\n" ) )
					{
						shaderName = empty;
						fscanf( pConfigFile, "%s\n", shaderName );

						if( !GetInstance()->ShaderExists( shaderName ) )
						{
							shaderType = empty;
							fscanf( pConfigFile, "%s\n", shaderType );

							shaderPath = empty;
							fscanf( pConfigFile, "%s\n", shaderPath );

							shader_t* newShader = new shader_t( shaderName, GetInstance()->StringToShaderType( shaderType ), shaderPath );
							delete newShader;		
						}
					}
				}
			}
		}

		static inline void SaveShaderProgramsToConfigFile( const GLchar* fileName )
		{
			//write total amount of shaders
			FILE* pConfigFile = fopen( fileName, "w+" );

			fprintf( pConfigFile, "%i\n\n", ( GLint )GetInstance()->shaderPrograms.size() );

			for( GLuint programIter = 0; programIter < GetInstance()->shaderPrograms.size(); programIter++ )
			{
				//write program name
				fprintf( pConfigFile, "%s\n", GetInstance()->shaderPrograms[programIter]->name );

				//write number of inputs
				fprintf( pConfigFile, "%i\n", ( GLint )GetInstance()->shaderPrograms[programIter]->inputs.size() );

				//write inputs
				for( GLuint inputIter = 0; inputIter < GetInstance()->shaderPrograms[programIter]->inputs.size(); inputIter++ )
				{
					fprintf( pConfigFile, "%s\n", GetInstance()->shaderPrograms[programIter]->inputs[inputIter] );	
				}

				fprintf( pConfigFile, "%i\n", ( GLint )GetInstance()->shaderPrograms[programIter]->outputs.size() );

				//write outputs
				for( GLuint outputIter = 0; outputIter < GetInstance()->shaderPrograms[programIter]->outputs.size(); outputIter++ )
				{
					fprintf( pConfigFile, "%s\n", GetInstance()->shaderPrograms[programIter]->outputs[outputIter] );
				}

				//write number of shaders
				fprintf( pConfigFile, "%i\n", ( GLint )GetInstance()->shaderPrograms[programIter]->shaders.size() );

				for( GLuint shaderIter = 0; shaderIter < GetInstance()->shaderPrograms[programIter]->shaders.size(); shaderIter++ )
				{
					//write shader name
					fprintf( pConfigFile, "%s\n", GetInstance()->shaderPrograms[programIter]->shaders[shaderIter]->name );

					//write shader type
					fprintf( pConfigFile, "%s\n", GetInstance()->ShaderTypeToString( GetInstance()->shaderPrograms[programIter]->shaders[shaderIter]->type ) );
					
					//write shader file path
					fprintf( pConfigFile, "%s\n", GetInstance()->shaderPrograms[programIter]->shaders[shaderIter]->filePath );
				}
			}	
			fclose( pConfigFile );
		}	
		
		/*
		* builds a new OpenGL shader program from already loaded shaders
		*/
		static inline void BuildProgramFromShaders( const GLchar* shaderName,
			std::vector< const GLchar* > inputs,
			std::vector< const GLchar* > outputs,
			const GLchar* vertexShaderName,
			const GLchar* fragmentShaderName,
			const GLchar* geometryShaderName,
			const GLchar* tessContShaderName,
			const GLchar* tessEvalShaderName,
			bool saveBinary = false )
		{
			if ( tinyShaders::isInitialized )
			{
				std::vector< shader_t* > shaders;
				shaders.push_back( GetShaderByName( vertexShaderName ) );
				shaders.push_back( GetShaderByName( fragmentShaderName ) );
				shaders.push_back( GetShaderByName( geometryShaderName ) );
				shaders.push_back( GetShaderByName( tessContShaderName ) );
				shaders.push_back( GetShaderByName( tessEvalShaderName ) );

				shaderProgram_t* newShaderProgram = new shaderProgram_t( shaderName, inputs, outputs, shaders, saveBinary );
				delete newShaderProgram;
			}
			TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_NOT_INITIALIZED );
		}

		/*
		* check if the shader program exists in TinyShaders.( has it been loaded and initialized? )
		*/
		static inline GLboolean ShaderProgramExists( const GLchar* shaderName )
		{
			if ( shaderName != nullptr )
			{
				if ( !GetInstance()->shaderPrograms.empty() )
				{
					for ( GLuint iterator = 0; iterator < GetInstance()->shaderPrograms.size(); iterator++ )
					{
						if ( GetInstance()->shaderPrograms[iterator] != nullptr &&
							!strcmp( shaderName, GetInstance()->shaderPrograms[iterator]->name ) )
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
		static inline GLboolean ShaderExists( const GLchar* shaderName )
		{
			if ( shaderName != nullptr )
			{
				if ( !GetInstance()->shaders.empty() )
				{
					for ( GLuint iterator = 0; iterator < GetInstance()->shaders.size(); iterator++ )
					{
						if ( GetInstance()->shaders[iterator] != nullptr && 
							!strcmp( shaderName, GetInstance()->shaders[iterator]->name ) )
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

		static inline void LoadShaderFromBuffer( const char* name, const GLchar* buffer, GLuint shaderType )
		{
			if( tinyShaders::isInitialized )
			{
				if( buffer != nullptr )
				{
					if( name != nullptr )
					{
						if( !ShaderExists( name ) )
						{
							shader_t* newShader = new shader_t( name, buffer, shaderType );	
							delete newShader;				
						}
						TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_SHADER_NOT_FOUND );
					}
					TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_INVALID_SHADER_NAME );
				}
				TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_INVALID_STRING );
			}
			TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_NOT_INITIALIZED );
		}

		static inline GLboolean SetShaderBlockParseEvent( parseBlocks_t shaderBlockParse )
		{
			if ( GetInstance()->isInitialized )
			{
				GetInstance()->shaderBlocksEvent = shaderBlockParse;
				return GL_TRUE;
			}
			return GL_FALSE;
		}

	private:

		/*
		* a TShader is essentially an OpenGL shader
		*/
		struct shader_t
		{
			shader_t( const GLchar* saderName, GLuint shaderType, const GLchar* shaderFilePath ) :
				name( saderName )
			{
				type = shaderType;
				isCompiled = GL_FALSE;
				filePath = shaderFilePath;
				Compile( GetInstance()->FileToBuffer( shaderFilePath ) );
			}

			shader_t( const GLchar* shaderName, const GLchar* buffer, GLuint shaderType ) 
				: name( shaderName ), type( shaderType )
			{
				type = shaderType;
				isCompiled = GL_FALSE;
				Compile( buffer );

			}
			shader_t( void ){}
			~shader_t( void ){}

			/*
			* compile the shader from a given text file
			*/
			inline void Compile( const GLchar* source )
			{
				//if the component hasn't been compiled yet
				if ( !isCompiled )
				{
					GLchar errorLog[512];
					GLint successful;

					if ( source != nullptr )
					{
						handle = glCreateShader( type );
						glShaderSource( handle, 1, ( const GLchar** )&source, 0 );
						glCompileShader( handle );

						glGetShaderiv( handle, gl_compile_status, &successful );
						glGetShaderInfoLog( handle, sizeof( errorLog ), 0, errorLog );

						if ( successful != GL_TRUE )
						{
							TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_FAILED_SHADER_LOAD, GetInstance()->ShaderTypeToString( type ) );
							printf( "%s\n", errorLog );
						}

						else
						{
							isCompiled = GL_TRUE;
							GetInstance()->shaders.push_back( this );
							iD = GetInstance()->shaders.size() - 1;
						}	
					}
					else
					{
						TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_INVALID_SOURCE_FILE );
					}
				}
				else
				{
					//either the file name doesn't exist or the component has already been loaded
					TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_INVALID_FILE_PATH, filePath );
				}
			}

			/*
			* remove the shader from OpenGL
			*/
			inline void Shutdown( void )
			{
				glDeleteShader( handle );
				isCompiled = GL_FALSE;
			}

			const GLchar*		name;			/**<The name of the shader component */
			const GLchar*		filePath;		/**<The FilePath of the component*/
			GLuint				handle;			/**<The handle to the shader in OpenGL*/
			GLuint				type;			/**<The type of shader ( Vertex, Fragment, etc.)*/
			GLuint				iD;				/**<The ID of the shader*/
			GLboolean			isCompiled;		/**<Whether the shader has been compiled*/
		};

		/*
		* a TShaderProgram is is essentially an OpengL shader program 
		*/
		struct shaderProgram_t
			{
				/*
				* basic constructor
				*/
				shaderProgram_t( void )
				{
					iD = 0;
				};

				/*
				* uses the given values to create an OpenGL shader program
				*/
				shaderProgram_t( const GLchar* programName,
					std::vector< const GLchar* > programInputs,
					std::vector< const GLchar* > programOutputs,
					std::vector< shader_t* > programShaders,
					bool saveBinary = false) :
					name( programName ), inputs( programInputs ),
					outputs( programOutputs ), shaders( programShaders )
				{
					compiled = GL_FALSE;
					Compile(saveBinary);
					//get number of uniform blocks
					if ( GetInstance()->shaderBlocksEvent != nullptr )
					{
						GetInstance()->shaderBlocksEvent( handle );
					}
				};

				/*
				* another bare bones constructor
				*/
				shaderProgram_t( const GLchar* programName ) : name( programName )
				{
					compiled = GL_FALSE;
				};

				shaderProgram_t(const GLchar* programName, GLuint programHandle) :
					name(programName), handle(programHandle)
				{

				}

				~shaderProgram_t( void ){}

				/*
				* shut down the shader program. delete it from OpenGL
				*/
				inline void Shutdown( void )
				{
					glDeleteProgram( handle );

					for ( GLuint iterator = 0; iterator < GetInstance()->shaders.size(); iterator++ )
					{
						GetInstance()->shaders[iterator]->Shutdown();
					}
					shaders.clear();
					inputs.clear();
					outputs.clear();
				}
				
				/*
				* compile the OpenGL shader program with the given information
				*/
				inline GLboolean Compile( bool saveBinary )
				{
					handle = glCreateProgram();
					GLchar errorLog[512];
					GLint successful = GL_FALSE;
					if ( !compiled )
					{
						for ( GLuint iterator = 0; iterator <shaders.size(); iterator++ )
						{
							if ( shaders[iterator] != nullptr )
							{
								glAttachShader( handle, shaders[iterator]->handle );
							}
						}

						// specify vertex input attributes
						for ( GLuint i = 0; i <inputs.size(); ++i )
						{
							glBindAttribLocation( handle, i, inputs[i] );
						}

						// specify pixel shader outputs
						for ( GLuint i = 0; i <outputs.size(); ++i )
						{
							glBindFragDataLocation( handle, i, outputs[i] );
						}

						if (saveBinary)
						{
							glProgramParameteri(handle, gl_program_binary_retrievable_hint, GL_TRUE);
						}

						glLinkProgram( handle );
						glGetProgramiv( handle, gl_link_status, &successful );
						

						if ( !successful )
						{
							glGetProgramInfoLog(handle, sizeof(errorLog), 0, errorLog);
							TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_FAILED_SHADER_PROGRAM_LINK, name );
							printf( "%s\n", errorLog );
							return GL_FALSE;
						}
						//if a shader successfully compiles then it will add itself to storage

						if (saveBinary)
						{
							GLint binarySize = 0;
							glGetProgramiv(handle, gl_program_binary_length, &binarySize);

							void* buffer = nullptr;
							buffer = (void*)malloc(binarySize);
							GLenum binaryFormat = GL_NONE;
							
							glGetProgramBinary(handle, binarySize, NULL, &binaryFormat, buffer);

							GLchar* path =  new GLchar[binarySize];
							memset(path, 1, binarySize);

							strcpy(path, TINYSHADERS_DEFAULT_BINARY_PATH);
							strcat(path, name);
							strcat(path, TINYSHADERS_DEFAULT_PROGRAM_BINARY_EXTENSION);

							FILE* file = fopen(path, "wb");
							fprintf(file, "%s\n", name);
							fprintf(file, "%i\n", binarySize);
							fprintf(file, "%i\n", binaryFormat);
							fwrite(buffer, binarySize, 1, file);
							fclose(file);
						}
						compiled = GL_TRUE;
						GetInstance()->shaderPrograms.push_back( this );
						iD = GetInstance()->shaderPrograms.size() - 1;
						return GL_TRUE;
					}
					TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_SHADER_PROGRAM_ALREADY_EXISTS, name );
					return GL_FALSE;
				}

				const GLchar*						name;				/**< The name of the shader program */
				GLuint								handle;				/**< The OpenGL handle to the shader program */
				GLuint								iD;					/**< The ID of the shader program */	
				GLboolean							compiled;			/**< Whether the shader program has been linked successfully */
				std::vector< const GLchar* >		inputs;				/**< The inputs of the shader program as a vector of strings */
				std::vector< const GLchar* >		outputs;			/**< The outputs of the shader program as a vector of strings */
				std::vector< shader_t* >			shaders;			/**< The components that the shader program is comprised of as a vector */
			};

		/*
		* returns a static reference to an instance of TinyShaders
		*/
		inline static tinyShaders* GetInstance( void )
		{
			if ( tinyShaders::isInitialized )
			{
				return tinyShaders::instance;
			}

			tinyShaders::isInitialized = GL_TRUE;
			tinyShaders::instance = new tinyShaders();
			return tinyShaders::instance;
		}

		/*
		* convert the given file to a single dimension c-string buffer
		*/
		inline GLchar* FileToBuffer( const GLchar* path ) const
		{
			FILE* file = fopen( path, "rt" );

			if ( file == nullptr )
			{
				TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_INVALID_FILE_PATH, path );
				//printf( "Error: cannot open file %s for reading \n", Path );
				return nullptr;
			}

			//get total byte in given file
			fseek( file, 0, SEEK_END );
			GLuint FileLength = ftell( file );
			fseek( file, 0, SEEK_SET );

			//allocate a file buffer and read the contents of the file
			GLchar* buffer = new GLchar[FileLength + 1];
			memset( buffer, 0, FileLength + 1 );
			fread( buffer, sizeof( GLchar ), FileLength, file );

			fclose( file );
			return buffer;
		}

		/*
		* convert the given string to a shader type
		*/
		inline GLuint StringToShaderType( const GLchar* typeString ) const
		{
			if( typeString != nullptr )
			{
				if ( !strcmp( typeString, "Vertex" ) )
				{
					return gl_vertex_shader;
				}

				if ( !strcmp( typeString, "Fragment" ) )
				{
					return gl_fragment_shader;
				}

				if ( !strcmp( typeString, "Geometry" ) )
				{
					return gl_geometry_shader;
				}

				if ( !strcmp( typeString, "Tessellation Control" ) )
				{
					return gl_tess_control_shader;
				}

				if ( !strcmp( typeString, "Tessellation Evaluation" ) )
				{
					return gl_tess_evaluation_shader;
				}

				return GL_FALSE;
			}
			TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_INVALID_STRING );
			return GL_FALSE;
		}
		
		/*
		* convert the given shader type to a string
		*/
		inline const GLchar* ShaderTypeToString( GLuint shaderType ) const 
		{
			switch ( shaderType )
			{
				case gl_vertex_shader:
				{
					return "Vertex";
				}

				case gl_fragment_shader:
				{
					return "Fragment";
				}
				
				case gl_geometry_shader:
				{
					return "Geometry";
				}

				case gl_tess_control_shader:
				{
					return "Tessellation Control";
				}

				case gl_tess_evaluation_shader:
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

		std::vector< shaderProgram_t* >		shaderPrograms;		/**< All loaded shader programs */
		std::vector< shader_t* >			shaders;			/**< All loaded shaders*/

		static GLboolean					isInitialized;		/**< Whether TinyShadershas ban initialized */
		static tinyShaders*					instance;			/**< A static instance of the TinyShaders API*/
		static parseBlocks_t				shaderBlocksEvent;
};

GLboolean tinyShaders::isInitialized = GL_FALSE;
tinyShaders* tinyShaders::instance = nullptr;
parseBlocks_t tinyShaders::shaderBlocksEvent = nullptr;
#endif
