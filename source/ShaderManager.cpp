#include "ShaderManager.h"

ShaderManager::ShaderManager()
{

}

ShaderManager::ShaderManager(const char* TextFilePath)
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
				std::vector<const char*> Inputs, Outputs;

				//get name
				char* Name = new char[255];
				fscanf(File, "%s\n", Name);

				//get type
				char* TypeName = new char[255];
				fscanf(File, "%s\n", TypeName);
				GLuint Type = TranslateType(TypeName);

				//get number of inputs
				fscanf(File, "%i\n", &NumInputs);

				for(Iterator = 0, InputIterator = 0; InputIterator < NumInputs; InputIterator++)
				{
					char* InputName = new char[255];
					Iterator = fscanf(File, "%s\n", InputName);
					Inputs.push_back(InputName);
				}

				//get number of outputs
				fscanf(File, "%i\n", &NumOutputs);

				//get outputs
				for(Iterator = 0, OutputIterator = 0; OutputIterator < NumOutputs; OutputIterator++)
				{
					char* OutputName = new char[255];
					Iterator = fscanf(File, "%s\n", OutputName);
					Outputs.push_back(OutputName);						
				}

				char* Path = new char[255];
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

char* ShaderManager::FileToBuffer(const char* Path)
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
	char* Buffer = new char[FileLength + 1];
	memset(Buffer, 0, FileLength + 1);
	fread(Buffer, sizeof(char), FileLength, File);

	fclose(File);
	return Buffer;
}

GLint ShaderManager::TranslateType(const char* TypeString)
{
	if (!strcmp(TypeString, "Vertex"))
	{
		return SHADER_VERTEX;
	}

	if (!strcmp(TypeString, "Fragment"))
	{
		return SHADER_FRAGMENT;
	}

	if (!strcmp(TypeString, "Geometry"))
	{
		return SHADER_GEOMETRY;
	}

	if (!strcmp(TypeString, "TessCont"))
	{
		return SHADER_TESS_CONT;
	}

	if (!strcmp(TypeString, "TessEval"))
	{
		return SHADER_TESS_EVAL;
	}

	return -1;
}

/*char* ErrorLog = new char[512];

switch (Type)
{
case SHADER_VERTEX:
{
	Source = FileToBuffer(FilePath);
	Handle = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(Handle, 1, Source, 0);
	glCompileShader(Handle);

	GLboolean Success;
	glGetShaderiv(Handle, GL_COMPILE_STATUS, &Success);
	glGetShaderInfoLog(Handle, sizeof(ErrorLog), 0, ErrorLog);

	if (Success)
	{
		printf("Failed to compile vertex shader\n%s\n", ErrorLog);
		return;
	}
	break;
}

case SHADER_FRAGMENT:
{
	Source = FileToBuffer(FilePath);
	Handle = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(Handle, 1, Source, 0);
	glCompileShader(Handle);

	GLboolean Success;
	glGetShaderiv(Handle, GL_COMPILE_STATUS, &Success);
	glGetShaderInfoLog(Handle, sizeof(ErrorLog), 0, ErrorLog);

	if (Success)
	{
		printf("Failed to compile fragment shader\n%s\n", ErrorLog);
		return;
	}
	break;
}

case SHADER_GEOMETRY:
{
	Source = FileToBuffer(FilePath);
	Handle = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(Handle, 1, Source, 0);
	glCompileShader(Handle);

	GLboolean Success;
	glGetShaderiv(Handle, GL_COMPILE_STATUS, &Success);
	glGetShaderInfoLog(Handle, sizeof(ErrorLog), 0, ErrorLog);

	if (Success)
	{
		printf("Failed to compile geometry shader\n%s\n", ErrorLog);
		return;
	}
	break;


}

case SHADER_TESS_CONT:
{
	Source = FileToBuffer(FilePath);
	Handle = glCreateShader(GL_TESS_CONTROL_SHADER);
	glShaderSource(Handle, 1, Source, 0);
	glCompileShader(Handle);

	GLboolean Success;
	glGetShaderiv(Handle, GL_COMPILE_STATUS, &Success);
	glGetShaderInfoLog(Handle, sizeof(ErrorLog), 0, ErrorLog);

	if (Success)
	{
		printf("Failed to compile tessellation control shader\n%s\n", ErrorLog);
		return;
	}
	break;
}

case SHADER_TESS_EVAL:
{
	Source = FileToBuffer(FilePath);
	Handle = glCreateShader(GL_TESS_EVALUATION_SHADER);
	glShaderSource(Handle, 1, Source, 0);
	glCompileShader(Handle);

	GLboolean Success;
	glGetShaderiv(Handle, GL_COMPILE_STATUS, &Success);
	glGetShaderInfoLog(Handle, sizeof(ErrorLog), 0, ErrorLog);

	if (Success)
	{
		printf("Failed to compile tesselation evaluation shader\n%s\n", ErrorLog);
		return;
	}
	break;


}

case SHADER_COMPUTE:
{
	Source = FileToBuffer(FilePath);
	Handle = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(Handle, 1, Source, 0);
	glCompileShader(Handle);

	GLboolean Success;
	glGetShaderiv(Handle, GL_COMPILE_STATUS, &Success);
	glGetShaderInfoLog(Handle, sizeof(ErrorLog), 0, ErrorLog);

	if (Success)
	{
		printf("Failed to compile compute shader\n%s\n", ErrorLog);
		return;
	}
	break;
}

default:
{
	printf("Error: invalid parameter \n");
	break;
}

}*/