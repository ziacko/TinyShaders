#include "ShaderManager.h"

ShaderManager::ShaderManager()
{

}

ShaderManager::ShaderManager(const GLchar* TextFilePath)
{

	FILE* File = fopen(TextFilePath, "r+");

	GLint Iterator = 0;
    GLuint InputIterator, OutputIterator = 0;
	GLuint TotalShaders = 0;

	if(File)
	{
		fscanf(File, "%i\n\n", &TotalShaders);
		
		for(GLuint TotalShadersIter = 0; Iterator != EOF && TotalShadersIter < TotalShaders; TotalShadersIter++,
					fscanf(File, "\n"), Iterator = 0)
			{
				GLuint NumInputs, NumOutputs;
				std::vector<GLchar*> Inputs, Outputs;

				//get name
				GLchar* Name = new GLchar[255];
				fscanf(File, "%s\n", Name);

				//get type
				GLchar* TypeName = new GLchar[255];
				fscanf(File, "%s\n", TypeName);
				GLuint Type = TranslateType(TypeName);

				//get number of inputs
				fscanf(File, "%i\n", &NumInputs);

				for(Iterator = 0, InputIterator = 0; InputIterator < NumInputs; InputIterator++)
				{
					GLchar* InputName = new GLchar[255];
					Iterator = fscanf(File, "%s\n", InputName);
					Inputs.push_back(InputName);
				}

				//get number of outputs
				fscanf(File, "%i\n", &NumOutputs);

				//get outputs
				for(Iterator = 0, OutputIterator = 0; OutputIterator < NumOutputs; OutputIterator++)
				{
					GLchar* OutputName = new GLchar[255];
					Iterator = fscanf(File, "%s\n", OutputName);
					Outputs.push_back(OutputName);						
				}

				GLchar* Path = new GLchar[255];
				Iterator = fscanf(File, "%s\n", Path);
				
				ShaderComponent* NewComponent = new ShaderComponent(Name, Type, Path,
					Inputs, Outputs);

				ShaderComponents.push_back(NewComponent);

			}
		}
		fclose(File);
}

ShaderManager::~ShaderManager()
{

}

std::list<TShader*> ShaderManager::GetShaders()
{
	return Shaders;
}

void ShaderManager::LoadShaderComponent(const GLchar* ShaderFile, GLuint ShaderType)
{

}

GLchar* ShaderManager::FileToBuffer(const GLchar* Path)
{
	FILE* File = fopen(Path, "rt");

	if(File == nullptr)
	{
		printf("Error: cannot open file %s for reading \n", Path);
		return nullptr;					
	}

	//get total byte in given file
	fseek(File, 0, SEEK_END);
	GLuint FileLength = ftell(File);
	fseek(File, 0, SEEK_SET);

	//allocate a file buffer and read the contents of the file
	GLchar* Buffer = new GLchar[FileLength + 1];
	memset(Buffer, 0, FileLength + 1);
	fread(Buffer, sizeof(GLchar), FileLength, File);

	fclose(File);
	return Buffer;
}

GLuint ShaderManager::TranslateType(GLchar* TypeString)
{
	if(!strcmp(TypeString, "Vertex"))
	{
		return SHADER_VERTEX;
	}

	if(!strcmp(TypeString, "Fragment"))
	{
		return SHADER_FRAGMENT;
	}

	if(!strcmp(TypeString, "Geometry"))
	{
		return SHADER_GEOMETRY;
	}

	if(!strcmp(TypeString, "TessCont"))
	{
		return SHADER_TESS_CONT;
	}

	if(!strcmp(TypeString, "TessEval"))
	{
		return SHADER_TESS_EVAL;
	}

	default:
	{
		Printf("Error: invalid shader type string \n");
		break;
	}
}
