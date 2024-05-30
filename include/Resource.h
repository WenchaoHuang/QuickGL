/*************************************************************************
*************************    QuickGL_Resource    *************************
*************************************************************************/
#pragma once

#include "Common.h"

namespace QuickGL
{
	/*********************************************************************
	**************************    glResource    **************************
	*********************************************************************/

	/**
	 *	@brief	Generic OpenGL object.
	 */
	class QGLAPI glResource
	{

	public:

		//!	@brief	Default constructor.
		glResource() : m_ResID(0) {}

		//!	@brief	OpenGL resource object is non-copyable.
		glResource(const glResource&) = delete;

		//!	@brief	OpenGL resource object is non-assignable.
		void operator=(const glResource&) = delete;

		//!	@brief	Convert to OpenGL resource ID.
		operator unsigned int() const { return m_ResID; }

		//!	@brief	Check if resource is valid.
		bool IsValid() const { return m_ResID != 0; }

	protected:

		unsigned int		m_ResID;
	};
}