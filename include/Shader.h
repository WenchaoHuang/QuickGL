/*************************************************************************
**************************    QuickGL_Shader    **************************
*************************************************************************/
#pragma once

#include <string>
#include "Resource.h"

namespace QuickGL
{
	/*********************************************************************
	************************    glShaderStage    *************************
	*********************************************************************/

	/**
	 *	@brief	Types of OpenGL shader.
	 */
	enum class glShaderStage : uint32_t
	{
		eVS		= 0x8B31,		//!	@brief	GL_VERTEX_SHADER
		eCS		= 0x91B9,		//!	@brief	GL_COMPUTE_SHADER
		eGS		= 0x8DD9,		//!	@brief	GL_GEOMETRY_SHADER
		eFS		= 0x8B30,		//!	@brief	GL_FRAGMENT_SHADER
		eTCS	= 0x8E88,		//!	@brief	GL_TESS_CONTROL_SHADER
		eTES	= 0x8E87		//!	@brief	GL_TESS_EVALUATION_SHADER
	};

	/*********************************************************************
	***************************    glShader    ***************************
	*********************************************************************/

	/**
	 *	@brief	Template for OpenGL shader objects.
	 */
	template<glShaderStage eStage> class QGLAPI glShader : public glResource
	{

	public:

		//!	@brief	Create shader object.
		glShader();

		//!	@brief	Create shader object and compiles it.
		explicit glShader(const std::string & ShaderCode);

		//!	@brief	Destroy shader object.
		~glShader() noexcept;

	public:

		//!	@brief	Returns compile log.
		const char * GetCompileLog() const;

		//!	@brief	Compiles shader, and returns compile status.
		bool Compile(const std::string & ShaderCode);

		//!	@brief	If shader was compiled successfully.
		bool IsGood() const;

	private:

		std::string		m_CompileLog;
	};
}