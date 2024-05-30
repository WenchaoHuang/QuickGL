/*************************************************************************
**********************    QuickGL_Renderbuffer    ***********************
*************************************************************************/
#include "Renderbuffer.h"
#include "Internal.h"

/*************************************************************************
**************************    glRenderbuffer    **************************
*************************************************************************/
glRenderbuffer::glRenderbuffer() : m_eSamples(glSampleCount::x1), m_eFormat(glFormat::eUndefined)
{
	glGenRenderbuffers(1, &m_ResID);
}


bool glRenderbuffer::Storage(glFormat eFormat, glExtent2D extent, glSampleCount eSamples)
{
	QGL_CHECK_ERROR;

	glBindRenderbuffer(GL_RENDERBUFFER, m_ResID);

	if (eSamples == glSampleCount::x1)
	{
		glRenderbufferStorage(GL_RENDERBUFFER, static_cast<GLenum>(eFormat), extent.width, extent.height);
	}
	else
	{
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, static_cast<GLsizei>(eSamples), static_cast<GLenum>(eFormat), extent.width, extent.height);
	}

	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	if (QGL_CHECK_ERROR == true)
	{
		m_eSamples = eSamples;

		m_Extent2D = extent;

		m_eFormat = eFormat;

		return true;
	}

	return false;
}


void glRenderbuffer::Free()
{
	if (this->IsEmpty() == false)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_ResID);

		glRenderbufferStorage(GL_RENDERBUFFER, static_cast<GLenum>(glFormat::eRGB), 0, 0);

		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		m_eFormat = glFormat::eUndefined;

		m_eSamples = glSampleCount::x1;

		m_Extent2D = { 0, 0 };
	}
}


glRenderbuffer::~glRenderbuffer()
{
	glDeleteRenderbuffers(1, &m_ResID);
}