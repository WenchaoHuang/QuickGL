/*************************************************************************
***********************    QuickGL_Renderbuffer    ***********************
*************************************************************************/
#pragma once

#include "Resource.h"

namespace QuickGL
{
	/*********************************************************************
	************************    glRenderbuffer    ************************
	*********************************************************************/

	/**
	 *	@brief	OpenGL renderbuffer object.
	 */
	class QGLAPI glRenderbuffer : public glResource
	{

	public:

		//!	@brief	Create renderbuffer object.
		glRenderbuffer();

		//!	@brief	Destroy renderbuffer object.
		~glRenderbuffer();

	public:

		//!	@brief	Establish data storage, format and dimensions of a renderbuffer object's image.
		bool Storage(glFormat eFormat, glExtent2D extent, glSampleCount eSamples = glSampleCount::x1);

		//!	@brief	Check if renderbuffer storage is empty.
		bool IsEmpty() const { return m_Extent2D.width * m_Extent2D.height == 0; }

		//!	@brief	Return samples of the renderbuffer.
		glSampleCount Samples() const { return m_eSamples; }

		//!	@brief	Return extent of the renderbuffer.
		glExtent2D Extent() const { return m_Extent2D; }

		//!	@brief	Return format of the renderbuffer.
		glFormat Format() const { return m_eFormat; }

		//!	@brief	Free renderbuffer storage.
		void Free();

	private:

		glFormat			m_eFormat;
		glExtent2D			m_Extent2D;
		glSampleCount		m_eSamples;
	};
}