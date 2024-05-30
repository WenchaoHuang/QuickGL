/*************************************************************************
***********************    QuickGL_Texture2DMS    ************************
*************************************************************************/
#pragma once

#include "Texture.h"

namespace QuickGL
{
	/*********************************************************************
	************************    glTexture2DMS    *************************
	*********************************************************************/

	/**
	 *	@brief	OpenGL 2D multisample texture object.
	 */
	class QGLAPI glTexture2DMS : public glTexture
	{

	public:

		//!	@brief	Create 2D multisample texture object.
		glTexture2DMS();

		//!	@brief	Create 2D multisample texture object and initializes data store.
		explicit glTexture2DMS(glFormat eFromat, glExtent2D extent, glSampleCount eSamples);

		//!	@brief	Destroy 2D multisample texture object.
		~glTexture2DMS() noexcept;

	public:

		//!	@brief	Specify storage for a two-dimensional multisample texture.
		bool Storage(glFormat eFromat, glExtent2D extent, glSampleCount eSamples);

		//!	@brief	Return count of samples.
		glSampleCount Samples() const { return m_eSamples; }

		//!	@brief	Return extent of image.
		glExtent2D Extent() const { return m_Extent; }

	private:

		glExtent2D			m_Extent;
		glSampleCount		m_eSamples;
	};
}