/*************************************************************************
*************************    QuickGL_Program    **************************
*************************************************************************/

#include <fstream>
#include <sstream>
#include <filesystem>
#include "Internal.h"
#include "Texture.h"
#include "Program.h"

/*************************************************************************
****************************    glProgram    *****************************
*************************************************************************/
glProgram::glProgram() : m_HasGeo(false), m_HasTess(false), m_HasComp(false)
{
	m_ResID = glCreateProgram();
}

glProgram::glProgram(const char * ShadersPath) : glProgram()
{
	this->Setup(ShadersPath);
}

glProgram::glProgram(const glShader<glShaderStage::eCS> & ComputeShader) : glProgram()
{
	this->Link(ComputeShader);
}

glProgram::glProgram(const glShader<glShaderStage::eVS> & VertexShader,
					 const glShader<glShaderStage::eFS> & FragmentShader) : glProgram()
{
	this->Link(VertexShader, FragmentShader);
}

glProgram::glProgram(const glShader<glShaderStage::eVS> & VertexShader,
					 const glShader<glShaderStage::eGS> & GeometryShader,
					 const glShader<glShaderStage::eFS> & FragmentShader) : glProgram()
{
	this->Link(VertexShader, GeometryShader, FragmentShader);
}

glProgram::glProgram(const glShader<glShaderStage::eVS>  & VertexShader,
					 const glShader<glShaderStage::eTCS> & TessControlShader,
					 const glShader<glShaderStage::eTES> & TessEvaluationShader,
					 const glShader<glShaderStage::eFS>  & FragmentShader) : glProgram()
{
	this->Link(VertexShader, TessControlShader, TessEvaluationShader, FragmentShader);
}

glProgram::glProgram(const glShader<glShaderStage::eVS>  & VertexShader,
					 const glShader<glShaderStage::eTCS> & TessControlShader,
					 const glShader<glShaderStage::eTES> & TessEvaluationShader,
					 const glShader<glShaderStage::eGS>  & GeometryShader,
					 const glShader<glShaderStage::eFS>  & FragmentShader) : glProgram()
{
	this->Link(VertexShader, TessControlShader, TessEvaluationShader, GeometryShader, FragmentShader);
}


bool glProgram::Link(const glShader<glShaderStage::eCS> & ComputeShader)
{
	m_HasTess = m_HasGeo = false;	m_HasComp = true;

	glAttachShader(m_ResID, ComputeShader);

	glLinkProgram(m_ResID);

	glDetachShader(m_ResID, ComputeShader);

	return this->CheckLinkStatus();
}


bool glProgram::Link(const glShader<glShaderStage::eVS> & VertexShader,
					 const glShader<glShaderStage::eFS> & FragmentShader)
{
	m_HasTess = m_HasGeo = m_HasComp = false;

	glAttachShader(m_ResID, VertexShader);
	glAttachShader(m_ResID, FragmentShader);

	glLinkProgram(m_ResID);

	glDetachShader(m_ResID, FragmentShader);
	glDetachShader(m_ResID, VertexShader);

	return this->CheckLinkStatus();
}


bool glProgram::Link(const glShader<glShaderStage::eVS> & VertexShader,
					 const glShader<glShaderStage::eGS> & GeometryShader,
					 const glShader<glShaderStage::eFS> & FragmentShader)
{
	m_HasTess = m_HasComp = false;	m_HasGeo = true;

	glAttachShader(m_ResID, VertexShader);
	glAttachShader(m_ResID, GeometryShader);
	glAttachShader(m_ResID, FragmentShader);

	glLinkProgram(m_ResID);

	glDetachShader(m_ResID, FragmentShader);
	glDetachShader(m_ResID, GeometryShader);
	glDetachShader(m_ResID, VertexShader);

	return this->CheckLinkStatus();
}


bool glProgram::Link(const glShader<glShaderStage::eVS>  & VertexShader,
					 const glShader<glShaderStage::eTCS> & TessControlShader,
					 const glShader<glShaderStage::eTES> & TessEvaluationShader,
					 const glShader<glShaderStage::eFS>  & FragmentShader)
{
	m_HasGeo = m_HasComp = false;	m_HasTess = true;

	glAttachShader(m_ResID, VertexShader);
	glAttachShader(m_ResID, FragmentShader);
	glAttachShader(m_ResID, TessControlShader);
	glAttachShader(m_ResID, TessEvaluationShader);

	glLinkProgram(m_ResID);

	glDetachShader(m_ResID, TessEvaluationShader);
	glDetachShader(m_ResID, TessControlShader);
	glDetachShader(m_ResID, FragmentShader);
	glDetachShader(m_ResID, VertexShader);

	return this->CheckLinkStatus();
}


bool glProgram::Link(const glShader<glShaderStage::eVS>  & VertexShader,
					 const glShader<glShaderStage::eTCS> & TessControlShader,
					 const glShader<glShaderStage::eTES> & TessEvaluationShader,
					 const glShader<glShaderStage::eGS>  & GeometryShader,
					 const glShader<glShaderStage::eFS>  & FragmentShader)
{
	m_HasTess = m_HasGeo = true;	m_HasComp = false;

	glAttachShader(m_ResID, VertexShader);
	glAttachShader(m_ResID, GeometryShader);
	glAttachShader(m_ResID, FragmentShader);
	glAttachShader(m_ResID, TessControlShader);
	glAttachShader(m_ResID, TessEvaluationShader);

	glLinkProgram(m_ResID);

	glDetachShader(m_ResID, TessEvaluationShader);
	glDetachShader(m_ResID, TessControlShader);
	glDetachShader(m_ResID, FragmentShader);
	glDetachShader(m_ResID, GeometryShader);
	glDetachShader(m_ResID, VertexShader);

	return this->CheckLinkStatus();
}


bool glProgram::Setup(const std::string ShadersPath)
{
	//!	Test if vertex-shader and fragment-shader files existed.
	if (std::filesystem::exists(ShadersPath + ".vert") && std::filesystem::exists(ShadersPath + ".frag"))
	{
		//!	Create vertex-shader.
		glShader<glShaderStage::eVS>	VertexShader(glProgram::ReadToString(ShadersPath + ".vert"));

		//!	Create fragment-shader.
		glShader<glShaderStage::eFS>	FragmentShader(glProgram::ReadToString(ShadersPath + ".frag"));

		//!	Test if tessellation shader files existed.
		if (std::filesystem::exists(ShadersPath + ".tesc") && std::filesystem::exists(ShadersPath + ".tese"))
		{
			//!	Create tess-control shader.
			glShader<glShaderStage::eTCS>	TessControlShader(glProgram::ReadToString(ShadersPath + ".tesc"));

			//!	Create tess-evaluation shader.
			glShader<glShaderStage::eTES>	TessEvaluationShader(glProgram::ReadToString(ShadersPath + ".tese"));

			//!	Test if geometry-shader file existed.
			if (std::filesystem::exists(ShadersPath + ".geom"))
			{
				//!	Create geometry-shader.
				glShader<glShaderStage::eGS>	GeometryShader(glProgram::ReadToString(ShadersPath + ".geom"));

				//!	Link shader program.
				this->Link(VertexShader, TessControlShader, TessEvaluationShader, GeometryShader, FragmentShader);
			}
			else
			{
				//!	Link shader program.
				this->Link(VertexShader, TessControlShader, TessEvaluationShader, FragmentShader);
			}
		}
		else if (std::filesystem::exists(ShadersPath + ".geom"))
		{
			//!	Create geometry-shader.
			glShader<glShaderStage::eGS>	GeometryShader(glProgram::ReadToString(ShadersPath + ".geom"));

			//!	Link shader program.
			this->Link(VertexShader, GeometryShader, FragmentShader);
		}
		else
		{
			//!	Link shader program.
			this->Link(VertexShader, FragmentShader);
		}
	}
	else if (std::filesystem::exists(ShadersPath + ".comp"))
	{
		//!	Create Compute-shader.
		glShader<glShaderStage::eCS>	ComputeShader(glProgram::ReadToString(ShadersPath + ".comp"));

		//!	Link shader program.
		this->Link(ComputeShader);
	}
	else
	{
		m_LinkLog = "Invalid path.\n";
	}

	return this->IsGood();
}


bool glProgram::CheckLinkStatus()
{
	int linkStatus = GL_FALSE, logSize = 0;

	glGetProgramiv(m_ResID, GL_LINK_STATUS, &linkStatus);

	glGetProgramiv(m_ResID, GL_INFO_LOG_LENGTH, &logSize);

	m_LinkLog.resize(logSize);

	glGetProgramInfoLog(m_ResID, logSize, NULL, (char*)m_LinkLog.data());

	if (linkStatus == GL_FALSE)
	{
		m_LinkLog.resize(m_LinkLog.size() - 1);

		m_LinkLog = "\n" + m_LinkLog + "\n";

		return false;
	}
	else
	{
		m_LinkLog = "Link success.\n";

		return true;
	}
}


void glProgram::SetUniformSampler(const char * name, const glTexture * pTexture)
{
	GLuint samplerID = *pTexture;

	glActiveTexture(GL_TEXTURE0 + samplerID);

	glBindTexture(static_cast<GLenum>(pTexture->GetType()), samplerID);

	glUniform1i(glGetUniformLocation(m_ResID, name), samplerID);

	glActiveTexture(GL_TEXTURE0);
}


std::string glProgram::ReadToString(const std::string Path)
{
	std::stringstream	StringStream;

	std::ifstream	FileStream(Path);

	if (!FileStream.is_open() || !FileStream.good())
	{
		printf(" QuickGL_Error: glProgram >> Unable to open file: \"%s\"\n", Path.c_str());
	}
	else if (FileStream.good())
	{
		StringStream << FileStream.rdbuf();
	}

	FileStream.close();

	return StringStream.str();
}


const char * glProgram::GetLinkLog() const
{
	return m_LinkLog.c_str();
}


bool glProgram::IsGood() const
{
	return m_LinkLog == "Link success.\n";
}


void glProgram::Unuse() const
{
	glUseProgram(0);
}


void glProgram::Use() const
{
	glUseProgram(m_ResID);
}


glProgram::~glProgram() noexcept
{
	glDeleteProgram(m_ResID);
}

/*************************************************************************
***************************    SetUniforms    ****************************
*************************************************************************/

//!	@brief	SetUniformi
void glProgram::SetUniform1i(const char * name, int v0) const { glUniform1i(glGetUniformLocation(m_ResID, name), v0); }
void glProgram::SetUniform2i(const char * name, int v0, int v1) const { glUniform2i(glGetUniformLocation(m_ResID, name), v0, v1); }
void glProgram::SetUniform3i(const char * name, int v0, int v1, int v2) const { glUniform3i(glGetUniformLocation(m_ResID, name), v0, v1, v2); }
void glProgram::SetUniform4i(const char * name, int v0, int v1, int v2, int v3) const { glUniform4i(glGetUniformLocation(m_ResID, name), v0, v1, v2, v3); }

//!	@brief	SetUniformf
void glProgram::SetUniform1f(const char * name, float v0) const { glUniform1f(glGetUniformLocation(m_ResID, name), v0); }
void glProgram::SetUniform2f(const char * name, float v0, float v1) const { glUniform2f(glGetUniformLocation(m_ResID, name), v0, v1); }
void glProgram::SetUniform3f(const char * name, float v0, float v1, float v2) const { glUniform3f(glGetUniformLocation(m_ResID, name), v0, v1, v2); }
void glProgram::SetUniform4f(const char * name, float v0, float v1, float v2, float v3) const { glUniform4f(glGetUniformLocation(m_ResID, name), v0, v1, v2, v3); }

//!	@brief	SetUniformiv
void glProgram::SetUniform1iv(const char * name, int count, const int * value) const { glUniform1iv(glGetUniformLocation(m_ResID, name), count, value); }
void glProgram::SetUniform2iv(const char * name, int count, const int * value) const { glUniform2iv(glGetUniformLocation(m_ResID, name), count, value); }
void glProgram::SetUniform3iv(const char * name, int count, const int * value) const { glUniform3iv(glGetUniformLocation(m_ResID, name), count, value); }
void glProgram::SetUniform4iv(const char * name, int count, const int * value) const { glUniform4iv(glGetUniformLocation(m_ResID, name), count, value); }

//!	@brief	SetUniformfv
void glProgram::SetUniform1fv(const char * name, int count, const float * value) const { glUniform1fv(glGetUniformLocation(m_ResID, name), count, value); }
void glProgram::SetUniform2fv(const char * name, int count, const float * value) const { glUniform2fv(glGetUniformLocation(m_ResID, name), count, value); }
void glProgram::SetUniform3fv(const char * name, int count, const float * value) const { glUniform3fv(glGetUniformLocation(m_ResID, name), count, value); }
void glProgram::SetUniform4fv(const char * name, int count, const float * value) const { glUniform4fv(glGetUniformLocation(m_ResID, name), count, value); }

//!	@brief	SetUniformMatrixf
void glProgram::SetUniformMatrix2f(const char * name, const float * value) const { glUniformMatrix2fv(glGetUniformLocation(m_ResID, name), 1, GL_FALSE, value); }
void glProgram::SetUniformMatrix3f(const char * name, const float * value) const { glUniformMatrix3fv(glGetUniformLocation(m_ResID, name), 1, GL_FALSE, value); }
void glProgram::SetUniformMatrix4f(const char * name, const float * value) const { glUniformMatrix4fv(glGetUniformLocation(m_ResID, name), 1, GL_FALSE, value); }

//!	@brief	SetUniformMatrixfv
void glProgram::SetUniformMatrix2fv(const char * name, int count, const float * value) const { glUniformMatrix2fv(glGetUniformLocation(m_ResID, name), count, GL_FALSE, value); }
void glProgram::SetUniformMatrix3fv(const char * name, int count, const float * value) const { glUniformMatrix3fv(glGetUniformLocation(m_ResID, name), count, GL_FALSE, value); }
void glProgram::SetUniformMatrix4fv(const char * name, int count, const float * value) const { glUniformMatrix4fv(glGetUniformLocation(m_ResID, name), count, GL_FALSE, value); }