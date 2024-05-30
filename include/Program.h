/*************************************************************************
*************************    QuickGL_Program    **************************
*************************************************************************/
#pragma once

#include "Shader.h"

namespace QuickGL
{
	class glTexture;

	/*********************************************************************
	**************************    glProgram    ***************************
	*********************************************************************/

	/**
	 *	@brief	OpenGL shader program object.
	 */
	class QGLAPI glProgram : public glResource
	{

	public:

		//!	@brief	Create program object.
		glProgram();

		//!	@brief	Setup program automatically.
		explicit glProgram(const char * ShadersPath);

		//!	@brief	Create program and link by CS.
		explicit glProgram(const glShader<glShaderStage::eCS> & ComputeShader);

		//!	@brief	Create program and link by VS and FS.
		explicit glProgram(const glShader<glShaderStage::eVS> & VertexShader,
						   const glShader<glShaderStage::eFS> & FragmentShader);

		//!	@brief	Create program and link by VS, GS and FS.
		explicit glProgram(const glShader<glShaderStage::eVS> & VertexShader,
						   const glShader<glShaderStage::eGS> & GeometryShader,
						   const glShader<glShaderStage::eFS> & FragmentShader);

		//!	@brief	Create program and link by VS, TCS, TES, and FS.
		explicit glProgram(const glShader<glShaderStage::eVS>  & VertexShader,
						   const glShader<glShaderStage::eTCS> & TessControlShader,
						   const glShader<glShaderStage::eTES> & TessEvaluationShader,
						   const glShader<glShaderStage::eFS>  & FragmentShader);

		//!	@brief	Create program and link by VS, TCS, TES, GS, and FS.
		explicit glProgram(const glShader<glShaderStage::eVS>  & VertexShader,
						   const glShader<glShaderStage::eTCS> & TessControlShader,
						   const glShader<glShaderStage::eTES> & TessEvaluationShader,
						   const glShader<glShaderStage::eGS>  & GeometryShader,
						   const glShader<glShaderStage::eFS>  & FragmentShader);

		//!	@brief	Destroy program object.
		~glProgram() noexcept;

	public:

		//!	@brief	Use program.
		void Use() const;

		//!	@brief	Unuse program.
		void Unuse() const;

		//!	@brief	Setup program.
		bool Setup(const std::string ShadersPath);

		//!	@brief	Link shader program.
		bool Link(const glShader<glShaderStage::eCS> & ComputeShader);

		//!	@brief	Link shader program.
		bool Link(const glShader<glShaderStage::eVS> & VertexShader,
				  const glShader<glShaderStage::eFS> & FragmentShader);

		//!	@brief	Link shader program.
		bool Link(const glShader<glShaderStage::eVS> & VertexShader,
				  const glShader<glShaderStage::eGS> & GeometryShader,
				  const glShader<glShaderStage::eFS> & FragmentShader);

		//!	@brief	Link shader program.
		bool Link(const glShader<glShaderStage::eVS>  & VertexShader,
				  const glShader<glShaderStage::eTCS> & TessControlShader,
				  const glShader<glShaderStage::eTES> & TessEvaluationShader,
				  const glShader<glShaderStage::eFS>  & FragmentShader);

		//!	@brief	Link shader program.
		bool Link(const glShader<glShaderStage::eVS>  & VertexShader,
				  const glShader<glShaderStage::eTCS> & TessControlShader,
				  const glShader<glShaderStage::eTES> & TessEvaluationShader,
				  const glShader<glShaderStage::eGS>  & GeometryShader,
				  const glShader<glShaderStage::eFS>  & FragmentShader);

		//!	@brief	If has tessellation shading stage.
		bool HasTessellationShadingStage() const { return m_HasTess; }

		//!	@brief	If has geometry shading stage.
		bool HasGeometryShadingStage() const { return m_HasGeo; }

		//!	@brief	If has compute shading shader.
		bool HasComputeShadingStage() const { return m_HasComp; }

		//!	@brief	Return link log.
		const char * GetLinkLog() const;

		//!	@brief	If program was linked successfully.
		bool IsGood() const;

	public:

		//!	@brief	SetUniformi
		void SetUniform1i(const char * name, int v0) const;
		void SetUniform2i(const char * name, int v0, int v1) const;
		void SetUniform3i(const char * name, int v0, int v1, int v2) const;
		void SetUniform4i(const char * name, int v0, int v1, int v2, int v3) const;

		//!	@brief	SetUniformf
		void SetUniform1f(const char * name, float v0) const;
		void SetUniform2f(const char * name, float v0, float v1) const;
		void SetUniform3f(const char * name, float v0, float v1, float v2) const;
		void SetUniform4f(const char * name, float v0, float v1, float v2, float v3) const;

		//!	@brief	SetUniformiv
		void SetUniform1iv(const char * name, int count, const int * value) const;
		void SetUniform2iv(const char * name, int count, const int * value) const;
		void SetUniform3iv(const char * name, int count, const int * value) const;
		void SetUniform4iv(const char * name, int count, const int * value) const;

		//!	@brief	SetUniformfv
		void SetUniform1fv(const char * name, int count, const float * value) const;
		void SetUniform2fv(const char * name, int count, const float * value) const;
		void SetUniform3fv(const char * name, int count, const float * value) const;
		void SetUniform4fv(const char * name, int count, const float * value) const;

		//!	@brief	SetUniformMatrixfv
		void SetUniformMatrix2fv(const char * name, int count, const float * value) const;
		void SetUniformMatrix3fv(const char * name, int count, const float * value) const;
		void SetUniformMatrix4fv(const char * name, int count, const float * value) const;

		//!	@brief	SetUniformMatrixf
		void SetUniformMatrix2f(const char * name, const float * value) const;
		void SetUniformMatrix3f(const char * name, const float * value) const;
		void SetUniformMatrix4f(const char * name, const float * value) const;

		//!	@brief	SetUniformSampler
		void SetUniformSampler(const char * name, const glTexture * pTexture);

	private:

		//!	@brief	Read file to string.
		static std::string ReadToString(const std::string Path);

		//!	@brief	Checks link status.
		bool CheckLinkStatus();

	private:

		bool			m_HasGeo;
		bool			m_HasTess;
		bool			m_HasComp;
		std::string		m_LinkLog;
	};
}