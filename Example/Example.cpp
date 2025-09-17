#define TW_NO_CONSOLE

#include <TinyExtender.h>
#include <TinyWindow.h>

using namespace TinyExtender;
using namespace TinyWindow;

#define NO_STDIO_REDIRECT

#include "TinyShaders.h"
using namespace TinyShaders;

void LoadShaderProgramsFromConfigFile(const std::string& path, bool useBinary, std::vector<shaderProgram_t*>* programs)
{
	FILE* pConfigFile = fopen( path.c_str(), "r" );
	GLuint numInputs = 0;
	GLuint numOutputs = 0;
	GLuint numPrograms = 0;
	GLuint numShaders = 0;
	GLuint iterator = 0;

	std::vector< std::string > inputs, outputs, paths, names;
	std::vector<shader_t> localShaders;
	if ( pConfigFile )
	{
		//get the total number of shader programs
		fscanf( pConfigFile, "%u\n", &numPrograms );

		for ( GLuint programIter = 0;
			programIter <numPrograms;
			programIter++, paths.clear(), inputs.clear(), outputs.clear(), names.clear(), localShaders.clear() )
		{
			//get the name of the shader program
			auto* programName = new char[255];
			fscanf( pConfigFile, "%s\n", programName );
			printf( "%s\n", programName );

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

				for( GLuint it = 0; it <numShaders; it++ )
				{
					auto* shaderName = new char[255];
					auto* shaderPath = new char[255];
					auto* shaderType = new char[255];

					//get shader name
					fscanf( pConfigFile, "%s\n", shaderName );
					printf( "%s\n", shaderName );

					//if the shader hasn't been loaded already then make a new one
					{
						//remove printf calls?
						//get type
						fscanf( pConfigFile, "%s\n", shaderType );
						printf( "%s\n", shaderType );
						//get file path
						fscanf( pConfigFile, "%s\n", shaderPath );
						printf( "%s\n", shaderPath );

						shaderType_e newType = StringToShaderType((std::string)shaderType);

						shader_t newShader = shader_t(shaderName, newType, shaderPath);
						LoadShader(newShader, shaderName, shaderPath, newType );
						if(newShader.isCompiled)
						{
							localShaders.push_back(newShader);
						}
						else
						{
							return;
						}
					}
				}
				//tell fscanf to skip a couple lines. very unsafe!
				fscanf( pConfigFile, "%*[^\n]\n %*[^\n]\n", nullptr );

				shaderProgram_t newShaderProgram = shaderProgram_t( programName, inputs, outputs, localShaders, useBinary);
				CompileShaderProgram(newShaderProgram, useBinary);

				if (newShaderProgram.isCompiled)
				{
					if (programs != nullptr)
					{
						programs->push_back(&newShaderProgram);
					}
					continue;
				}
				fclose(pConfigFile);
			}
		}
		fclose( pConfigFile );
	}
}


int main()
{
	std::unique_ptr<windowManager> manager(new windowManager());

	windowSetting_t defaultSetting;
	defaultSetting.name = "example window";
	defaultSetting.resolution = vec2_t<unsigned short>(1280, 720);
	defaultSetting.SetProfile(profile_e::compatibility);

	tWindow* window = manager->AddWindow(defaultSetting);

	TinyExtender::InitializeExtensions();

	std::vector<shaderProgram_t*> programs;
	LoadShaderProgramsFromConfigFile("Shaders/Shaders.txt", true, &programs);

	//tinyShaders::LoadProgramBinariesFromConfigFile("./Shaders/Binaries.txt");

	glUseProgram(programs[0]->handle);
	
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glPointSize(20.0f);
	while (window->GetShouldClose() == false)
	{
		manager->PollForEvents();
		glDrawArrays(GL_POINTS, 0, 1);//I just need one point for this

		manager->SwapDrawBuffers(window);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	manager->ShutDown();
	return 0;
}
