//created my Ziyad Barakat 2015

#ifndef TINY_SHADERS_H
#define TINY_SHADERS_H
#if defined(_WIN32) || defined(_WIN64)
//created by ziyad barakat-2015
#include <Windows.h>
#include < Gl/GL.h>
//disable annoying warnings about unsafe stdio functions
#pragma warning(disable: 4474)
#pragma warning(disable: 4996)
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

typedef GLvoid( *parseBlocks_t )( GLuint programHandle );	/**< callback that can gather all the info about the uniform blocks that are in a shader program */

/*
* print the error message and additional information corresponding to the Error handle
*/
inline static GLvoid TinyShaders_PrintErrorMessage( GLuint errorNumber, const GLchar* errorMessage = nullptr )
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

/*
* convert the given file to a single dimension c-string buffer
*/
inline GLchar* FileToBuffer( const GLchar* path )
{
	FILE* file = fopen(path, "rt");

	if (file == nullptr)
	{
		TinyShaders_PrintErrorMessage(TINYSHADERS_ERROR_INVALID_FILE_PATH, path);
		//printf( "Error: cannot open file %s for reading \n", Path );
		return nullptr;
	}

	//get total byte in given file
	fseek(file, 0, SEEK_END);
	GLuint FileLength = ftell(file);
	fseek(file, 0, SEEK_SET);

	//allocate a file buffer and read the contents of the file
	GLchar* buffer = new GLchar[FileLength + 1];
	memset(buffer, 0, FileLength + 1);
	fread(buffer, sizeof(GLchar), FileLength, file);

	fclose(file);
	return buffer;
}

class tinyShaders
{
	struct shaderProgram_t;
	struct shader_t;

	public:

		tinyShaders( GLvoid )
		{
			shaderBlocksEvent = nullptr;
		}
		~tinyShaders( GLvoid ){}

		/*
		* shuts down TinyShaders. deletes all OpenGL shaders and shader programs 
		* as well as calling shutdown on all shader and programs and clears all vectors.
		*/
		inline GLvoid Shutdown( GLvoid )
		{
			if ( tinyShaders::isInitialized )
			{
				for ( GLuint iterator = 0; iterator < shaders.size(); iterator++ )
				{
					shaders[iterator]->Shutdown();
					 delete shaders[iterator];
				}

				for ( GLuint iterator = 0; iterator < shaderPrograms.size(); iterator++ )
				{
					shaderPrograms[iterator]->Shutdown();
					delete shaderPrograms[iterator];
				}

				shaderPrograms.clear();
				shaders.clear();
			}
		}

		/*
		* returns a pointer to a TShaderProgram corresponding to the given name. returns nullptr if the TShaderProgram is not found
		*/
		inline shaderProgram_t* GetShaderProgramByName( const GLchar* programName ) const 
		{
			if ( tinyShaders::isInitialized )
			{
				if ( programName != nullptr )
				{
					for ( GLuint iterator = 0; iterator < shaderPrograms.size(); iterator++ )
					{
						if ( !strcmp( shaderPrograms[iterator]->name, programName ) )
						{
							return shaderPrograms[iterator];
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
		inline shaderProgram_t* GetShaderProgramByIndex( GLuint programIndex ) const 
		{
			if ( tinyShaders::isInitialized )
			{
				if ( programIndex <= shaderPrograms.size() - 1 )
				{
					return shaderPrograms[programIndex];
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
		inline shader_t* GetShaderByName( const GLchar* shaderName ) const 
		{
			if ( tinyShaders::isInitialized )
			{
				if ( shaderName != nullptr )
				{
					for ( GLuint iterator = 0; iterator < shaders.size(); iterator++ )
					{
						if ( !strcmp( shaders[iterator]->name, shaderName ) )
						{
							return shaders[iterator];
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
		inline shader_t* GetShaderByIndex( GLuint shaderIndex ) const 
		{
			if ( tinyShaders::isInitialized )
			{
				if ( shaderIndex <= shaders.size() - 1 )
				{
					return shaders[shaderIndex];
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
		inline void LoadShader( const GLchar* name, const GLchar* shaderFile, GLuint shaderType )
		{
			if ( tinyShaders::isInitialized )
			{
				if ( name != nullptr )
				{
					if ( shaderType <= 5 )
					{
						shader_t* newShader = new shader_t( name, shaderType, shaderFile, this );
					}
					TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_INVALID_SHADER_TYPE, ShaderTypeToString( shaderType ) );
				}
				TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_INVALID_STRING );
			}
			TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_NOT_INITIALIZED );
		}

		/*
		* loads all shaders and shader programs specified in a custom configuration file
		*/
		inline void LoadShaderProgramsFromConfigFile( const GLchar* configFile )
		{
			if ( isInitialized )
			{
				FILE* pConfigFile = fopen( configFile, "r" );
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
						if ( !ShaderProgramExists( programName ) )
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

									shaders.push_back( new shader_t( shaderName, StringToShaderType( ( const char* )shaderType ), shaderPath, this ) );
								}

								else
								{
									//tell scanf to skip a couple lines
									fscanf( pConfigFile, "%*[^\n]\n %*[^\n]\n", NULL );
									//if shader already exists then add an existing one from storage, it should already be compiled
									shaders.push_back( GetShaderByName( shaderName ) );
								}
							}

							shaderProgram_t* newShaderProgram = new shaderProgram_t( programName, inputs, outputs, shaders, this );
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

		inline void LoadShadersFromConfigFile( const GLchar* configFile )
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

						if( !ShaderExists( shaderName ) )
						{
							shaderType = empty;
							fscanf( pConfigFile, "%s\n", shaderType );

							shaderPath = empty;
							fscanf( pConfigFile, "%s\n", shaderPath );

							shader_t* newShader = new shader_t( shaderName, StringToShaderType( shaderType ), shaderPath, this );
							delete newShader;		
						}
					}
				}
			}
		}

		inline void SaveShaderProgramsToConfigFile( const GLchar* fileName )
		{
			//write total amount of shaders
			FILE* pConfigFile = fopen( fileName, "w+" );

			fprintf( pConfigFile, "%i\n\n", ( GLint )shaderPrograms.size() );

			for( GLuint programIter = 0; programIter < shaderPrograms.size(); programIter++ )
			{
				//write program name
				fprintf( pConfigFile, "%s\n", shaderPrograms[programIter]->name );

				//write number of inputs
				fprintf( pConfigFile, "%i\n", ( GLint )shaderPrograms[programIter]->inputs.size() );

				//write inputs
				for( GLuint inputIter = 0; inputIter < shaderPrograms[programIter]->inputs.size(); inputIter++ )
				{
					fprintf( pConfigFile, "%s\n", shaderPrograms[programIter]->inputs[inputIter] );	
				}

				fprintf( pConfigFile, "%i\n", ( GLint )shaderPrograms[programIter]->outputs.size() );

				//write outputs
				for( GLuint outputIter = 0; outputIter < shaderPrograms[programIter]->outputs.size(); outputIter++ )
				{
					fprintf( pConfigFile, "%s\n", shaderPrograms[programIter]->outputs[outputIter] );
				}

				//write number of shaders
				fprintf( pConfigFile, "%i\n", ( GLint )shaderPrograms[programIter]->shaders.size() );

				for( GLuint shaderIter = 0; shaderIter < shaderPrograms[programIter]->shaders.size(); shaderIter++ )
				{
					//write shader name
					fprintf( pConfigFile, "%s\n", shaderPrograms[programIter]->shaders[shaderIter]->name );

					//write shader type
					fprintf( pConfigFile, "%s\n", ShaderTypeToString( shaderPrograms[programIter]->shaders[shaderIter]->type ) );
					
					//write shader file path
					fprintf( pConfigFile, "%s\n", shaderPrograms[programIter]->shaders[shaderIter]->filePath );
				}
			}	
			fclose( pConfigFile );
		}	
		
		/*
		* builds a new OpenGL shader program from already loaded shaders
		*/
		inline void BuildProgramFromShaders( const GLchar* shaderName,
			std::vector< const GLchar* > inputs,
			std::vector< const GLchar* > outputs,
			const GLchar* vertexShaderName,
			const GLchar* fragmentShaderName,
			const GLchar* geometryShaderName,
			const GLchar* tessContShaderName,
			const GLchar* tessEvalShaderName )
		{
			if ( tinyShaders::isInitialized )
			{
				std::vector< shader_t* > shaders;
				shaders.push_back( GetShaderByName( vertexShaderName ) );
				shaders.push_back( GetShaderByName( fragmentShaderName ) );
				shaders.push_back( GetShaderByName( geometryShaderName ) );
				shaders.push_back( GetShaderByName( tessContShaderName ) );
				shaders.push_back( GetShaderByName( tessEvalShaderName ) );

				shaderProgram_t* newShaderProgram = new shaderProgram_t( shaderName, inputs, outputs, shaders, this );
				delete newShaderProgram;
			}
			TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_NOT_INITIALIZED );
		}

		/*
		* check if the shader program exists in TinyShaders.( has it been loaded and initialized? )
		*/
		inline GLboolean ShaderProgramExists( const GLchar* shaderName ) const 
		{
			if ( shaderName != nullptr )
			{
				if ( !shaderPrograms.empty() )
				{
					for ( GLuint iterator = 0; iterator < shaderPrograms.size(); iterator++ )
					{
						if ( shaderPrograms[iterator] != nullptr &&
							!strcmp( shaderName, shaderPrograms[iterator]->name ) )
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
		inline GLboolean ShaderExists( const GLchar* shaderName ) const 
		{
			if ( shaderName != nullptr )
			{
				if ( !shaders.empty() )
				{
					for ( GLuint iterator = 0; iterator < shaders.size(); iterator++ )
					{
						if ( shaders[iterator] != nullptr && 
							!strcmp( shaderName, shaders[iterator]->name ) )
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

		inline GLvoid LoadShaderFromBuffer( const char* name, const GLchar* buffer, GLuint shaderType )
		{
			if( tinyShaders::isInitialized )
			{
				if( buffer != nullptr )
				{
					if( name != nullptr )
					{
						if( !ShaderExists( name ) )
						{
							shader_t* newShader = new shader_t( name, buffer, shaderType, this );	
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

		inline GLboolean SetShaderBlockParseEvent( parseBlocks_t shaderBlockParse )
		{
			if ( isInitialized )
			{
				shaderBlocksEvent = shaderBlockParse;
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
				const GLchar*		name;			/**< The name of the shader component */
				const GLchar*		filePath;		/**< The FilePath of the component */
				GLuint				handle;			/**< The handle to the shader in OpenGL */
				GLuint				type;			/**< The type of shader ( Vertex, Fragment, etc.) */
				GLuint				iD;				/**< The ID of the shader */
				GLboolean			isCompiled;		/**< Whether the shader has been compiled */

				shader_t( const GLchar* saderName, GLuint shaderType, const GLchar* shaderFilePath, tinyShaders* shaderManager) :
					name( saderName )
				{
					type = shaderType;
					isCompiled = GL_FALSE;
					filePath = shaderFilePath;
					Compile( FileToBuffer( shaderFilePath ), shaderManager );
				}

				shader_t( const GLchar* shaderName, const GLchar* buffer, GLuint shaderType, tinyShaders* shaderManager ) 
					: name( shaderName ), type( shaderType )
				{
					type = shaderType;
					isCompiled = GL_FALSE;
					Compile( buffer, shaderManager );

				}
				shader_t( GLvoid ){}
				~shader_t( GLvoid ){}

				/*
				* compile the shader from a given text file
				*/
				inline GLvoid Compile( const GLchar* source, tinyShaders* shaderManager )
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

							glGetShaderiv( handle, GL_COMPILE_STATUS, &successful );
							glGetShaderInfoLog( handle, sizeof( errorLog ), 0, errorLog );

							if ( successful != GL_TRUE )
							{
								TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_FAILED_SHADER_LOAD, shaderManager->ShaderTypeToString( type ) );
								printf( "%s\n", errorLog );
							}

							else
							{
								isCompiled = GL_TRUE;
								shaderManager->shaders.push_back( this );
								iD = shaderManager->shaders.size() - 1;
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
				inline GLvoid Shutdown( GLvoid )
				{
					glDeleteShader( handle );
					isCompiled = GL_FALSE;
				}
			};

		/*
		* a TShaderProgram is is essentially an OpengL shader program 
		*/
		struct shaderProgram_t
		{
			/*
			* basic constructor
			*/

			const GLchar*						name;				/**< The name of the shader program */
			GLuint								handle;				/**< The OpenGL handle to the shader program */
			GLuint								iD;					/**< The ID of the shader program */
			static const GLuint					maxNumShaders;		/**< The Maximum number of components a shader program can have. It's always 5*/
			GLboolean							compiled;			/**< Whether the shader program has been linked successfully */
			std::vector< const GLchar* >		inputs;				/**< The inputs of the shader program as a vector of strings */
			std::vector< const GLchar* >		outputs;			/**< The outputs of the shader program as a vector of strings */
			std::vector< shader_t* >			shaders;			/**< The components that the shader program is comprised of as a vector */

			shaderProgram_t( GLvoid )
			{
				iD = 0;
			};

			/*
			* uses the given values to create an OpenGL shader program
			*/
			shaderProgram_t( const GLchar* shaderName,
				std::vector< const GLchar* > programInputs,
				std::vector< const GLchar* > programOutputs,
				std::vector< shader_t* > programShaders,
				tinyShaders* shaderManager ) :
				name( shaderName ), inputs( programInputs ),
				outputs( programOutputs ), shaders( programShaders )
			{
				compiled = GL_FALSE;
				Compile( shaderManager );
				//get number of uniform blocks
				if ( shaderManager->shaderBlocksEvent != nullptr )
				{
					shaderManager->shaderBlocksEvent( handle );
				}
			};

			/*
			* another bare bones constructor
			*/
			shaderProgram_t( const GLchar* shaderName ) : name( shaderName )
			{
				compiled = GL_FALSE;
			};

			~shaderProgram_t( GLvoid ){}

			/*
			* shut down the shader program. delete it from OpenGL
			*/
			inline GLvoid Shutdown( GLvoid )
			{
				glDeleteProgram( handle );

				for ( GLuint iterator = 0; iterator < shaders.size(); iterator++ )
				{
					shaders[iterator]->Shutdown();
				}
				shaders.clear();
				inputs.clear();
				outputs.clear();
			}
				
			/*
			* compile the OpenGL shader program with the given information
			*/
			inline GLboolean Compile( tinyShaders* shaderManager )
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

					glLinkProgram( handle );
					glGetProgramiv( handle, GL_LINK_STATUS, &successful );
					glGetProgramInfoLog( handle, sizeof( errorLog ), 0, errorLog );

					if ( !successful )
					{
						TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_FAILED_SHADER_PROGRAM_LINK, name );
						printf( "%s\n", errorLog );
						return GL_FALSE;
					}
					//if a shader successfully compiles then it will add itself to storage
					compiled = GL_TRUE;
					shaderManager->shaderPrograms.push_back( this );
					iD = shaderManager->shaderPrograms.size() - 1;
					return GL_TRUE;
				}
				TinyShaders_PrintErrorMessage( TINYSHADERS_ERROR_SHADER_PROGRAM_ALREADY_EXISTS, name );
				return GL_FALSE;
			}

		};

		std::vector< shaderProgram_t* >		shaderPrograms;		/**< All loaded shader programs */
		std::vector< shader_t* >			shaders;			/**< All loaded shaders */

		GLboolean							isInitialized;		/**< Whether TinyShadershas ban initialized */
		parseBlocks_t						shaderBlocksEvent;

		/*
		* convert the given string to a shader type
		*/
		inline GLuint StringToShaderType( const GLchar* typeString ) const 
		{
			if( typeString != nullptr )
			{
				if ( !strcmp( typeString, "Vertex" ) )
				{
					return GL_VERTEX_SHADER;
				}

				if ( !strcmp( typeString, "Fragment" ) )
				{
					return GL_FRAGMENT_SHADER;
				}

				if ( !strcmp( typeString, "Geometry" ) )
				{
					return GL_GEOMETRY_SHADER;
				}

				if ( !strcmp( typeString, "Tessellation Control" ) )
				{
					return GL_TESS_CONTROL_SHADER;
				}

				if ( !strcmp( typeString, "Tessellation Evaluation" ) )
				{
					return GL_TESS_EVALUATION_SHADER;
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
};

const GLuint tinyShaders::shaderProgram_t::maxNumShaders = 5;
#endif
