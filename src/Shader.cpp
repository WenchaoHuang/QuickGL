/*************************************************************************
**************************    QuickGL_Shader    **************************
*************************************************************************/
#include "Internal.h"
#include "Shader.h"

template class glShader<glShaderStage::eVS>;
template class glShader<glShaderStage::eCS>;
template class glShader<glShaderStage::eGS>;
template class glShader<glShaderStage::eFS>;
template class glShader<glShaderStage::eTCS>;
template class glShader<glShaderStage::eTES>;

/*************************************************************************
*****************************    glShader    *****************************
*************************************************************************/
template<glShaderStage eStage> glShader<eStage>::glShader()
{
	m_ResID = glCreateShader(static_cast<GLenum>(eStage));
}


template<glShaderStage eStage> glShader<eStage>::glShader(const std::string & ShaderCode) : glShader()
{
	this->Compile(ShaderCode);
}


template<glShaderStage eStage> bool glShader<eStage>::Compile(const std::string & ShaderCode)
{
	if (m_ResID == 0)				return false;

	const char * pShaderCodes = ShaderCode.c_str();

	glShaderSource(m_ResID, 1, &pShaderCodes, NULL);

	glCompileShader(m_ResID);

	int compileStatus = GL_FALSE, infoLogSize = 0;

	glGetShaderiv(m_ResID, GL_INFO_LOG_LENGTH, &infoLogSize);

	glGetShaderiv(m_ResID, GL_COMPILE_STATUS, &compileStatus);

	m_CompileLog.resize(infoLogSize);

	glGetShaderInfoLog(m_ResID, infoLogSize, NULL, (char*)m_CompileLog.c_str());

	if (compileStatus != GL_FALSE)		m_CompileLog = "Compile success.\n";

	return compileStatus != GL_FALSE;
}


template<glShaderStage eStage> const char * glShader<eStage>::GetCompileLog() const
{
	return m_CompileLog.c_str();
}


template<glShaderStage eStage> bool glShader<eStage>::IsGood() const
{
	return m_CompileLog == "Compile success.\n";
}


template<glShaderStage eStage> glShader<eStage>::~glShader() noexcept
{
	glDeleteShader(m_ResID);
}