/*************************************************************************
***********************    QuickGL_TextureCube    ************************
*************************************************************************/
#include "TextureCube.h"
#include "Internal.h"

/*************************************************************************
**************************    glTextureCube    ***************************
*************************************************************************/
glTextureCube::glTextureCube() : glTexture(glTextureType::eCube)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_ResID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


glTextureCube::glTextureCube(glFormat eFormat, uint32_t size) : glTextureCube()
{
	this->Storage(eFormat, size);
}


bool glTextureCube::SetImage2D(glCubeFace eFace, const glImage2D && Image, glFormat eFormat)
{
	return this->SetImage2D(eFace, Image, eFormat);
}


bool glTextureCube::SetImage2D(glCubeFace eFace, const glImage2D & Image, glFormat eFormat)
{
	glExtent2D extent = Image.Extent();

	if (extent.width != extent.height)		return false;

	QGL_CHECK_ERROR;

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_ResID);

	glTexImage2D(static_cast<GLenum>(eFace), 0, static_cast<GLint>(eFormat), extent.width, extent.width, 0, static_cast<GLenum>(Image.Format()), static_cast<GLenum>(Image.DataType()), Image.Data());

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	if (QGL_CHECK_ERROR == true)
	{
		m_eFormat = eFormat;

		m_Extent = extent;

		return true;
	}

	return false;
}


bool glTextureCube::Storage(glFormat eFormat, uint32_t size)
{
	QGL_CHECK_ERROR;

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_ResID);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, static_cast<GLint>(eFormat), size, size, 0, GL_RGB, GL_FLOAT, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, static_cast<GLint>(eFormat), size, size, 0, GL_RGB, GL_FLOAT, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, static_cast<GLint>(eFormat), size, size, 0, GL_RGB, GL_FLOAT, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, static_cast<GLint>(eFormat), size, size, 0, GL_RGB, GL_FLOAT, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, static_cast<GLint>(eFormat), size, size, 0, GL_RGB, GL_FLOAT, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, static_cast<GLint>(eFormat), size, size, 0, GL_RGB, GL_FLOAT, NULL);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	if (QGL_CHECK_ERROR == true)
	{
		m_eFormat = eFormat;

		m_Extent = size;

		return true;
	}

	return false;
}


void glTextureCube::SetMagFilter(glFilter eFilter)
{
//	if (eFilter == glFilter::eLinearMipmapLinear)			eFilter = glFilter::eLinear;
//	if (eFilter == glFilter::eNearestMimapLinear)			eFilter = glFilter::eLinear;
//	if (eFilter == glFilter::eLinearMipmapNearest)			eFilter = glFilter::eNearest;
//	if (eFilter == glFilter::eNearestMipmapNearest)			eFilter = glFilter::eNearest;

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_ResID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(eFilter));

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


void glTextureCube::SetMinFilter(glFilter eFilter)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_ResID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(eFilter));

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


void glTextureCube::GenerateMipmap()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_ResID);

	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


void glTextureCube::DisableSeamless()
{
	glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}


void glTextureCube::EnableSeamless()
{
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}


glTextureCube::~glTextureCube() noexcept
{

}