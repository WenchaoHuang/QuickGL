/*************************************************************************
***********************    QuickGL_Texture2DMS    ************************
*************************************************************************/
#include "Texture2DMS.h"
#include "Internal.h"

/*************************************************************************
**************************    glTexture2DMS    ***************************
*************************************************************************/
glTexture2DMS::glTexture2DMS() : glTexture(glTextureType::e2DMultiSample), m_eSamples(glSampleCount::x1)
{
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_ResID);

	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
}


glTexture2DMS::glTexture2DMS(glFormat eFromat, glExtent2D extent, glSampleCount eSamples) : glTexture2DMS()
{
	this->Storage(eFromat, extent, eSamples);
}


bool glTexture2DMS::Storage(glFormat eFromat, glExtent2D extent, glSampleCount eSamples)
{
	QGL_CHECK_ERROR;

	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_ResID);

	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, static_cast<GLsizei>(eSamples), static_cast<GLenum>(eFromat), extent.width, extent.height, GL_TRUE);

	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

	if (QGL_CHECK_ERROR == true)
	{
		m_eSamples = eSamples;

		m_eFormat = eFromat;

		m_Extent = extent;

		return true;
	}

	return false;
}


glTexture2DMS::~glTexture2DMS() noexcept
{

}