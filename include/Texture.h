/*************************************************************************
*************************    QuickGL_Texture    **************************
*************************************************************************/
#pragma once

#include "Sampler.h"

namespace QuickGL
{
	/*********************************************************************
	************************    glTextureType    *************************
	*********************************************************************/

	/**
	 *	@brief	Types of OpenGL texture object.
	 */
	enum class glTextureType : uint32_t
	{
	//	e1D						= 0x0DE0,
		e2D						= 0x0DE1,
	//	e3D						= 0x806F,
		eCube					= 0x8513,
	//	eBuffer					= 0x8C2A,
	//	e1DArray				= 0x8C18,
	//	e2DArray				= 0x8C1A,
	//	eCubeArray				= 0x9009,
	//	eRectangle				= 0x84F5,
		e2DMultiSample			= 0x9100,
	//	e2DMultiSampleArray		= 0x9102
	};

	/*********************************************************************
	**************************    glTexture    ***************************
	*********************************************************************/

	/**
	 *	@brief	Base class for OpenGL texture object.
	 */
	class QGLAPI glTexture : public glResource
	{

	protected:

		//!	@brief	Create texture object.
		explicit glTexture(glTextureType eType);

		//!	@brief	Destroy texture object.
		~glTexture() noexcept;

	public:

		//!	@brief	Return image format.
		glFormat Format() const { return m_eFormat; }

		//!	@brief	Return texture type.
		glTextureType GetType() const { return m_eTexType; }

	protected:

		glFormat				m_eFormat;

		const glTextureType		m_eTexType;
	};
}