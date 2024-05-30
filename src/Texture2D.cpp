/*************************************************************************
************************    QuickGL_Texture2D    *************************
*************************************************************************/
#include "Texture2D.h"
#include "Internal.h"

/*************************************************************************
***************************    glTexutre2D    ****************************
*************************************************************************/
glTexture2D::glTexture2D() : glTexture(glTextureType::e2D)
{
	glBindTexture(GL_TEXTURE_2D, m_ResID);

	glBindTexture(GL_TEXTURE_2D, 0);
}


glTexture2D::glTexture2D(const glImage2D & Image, glFormat eFormat) : glTexture2D()
{
	this->SetImage2D(Image, eFormat);
}


glTexture2D::glTexture2D(const glImage2D && Image, glFormat eFormat) : glTexture2D()
{
	this->SetImage2D(Image, eFormat);
}


glTexture2D::glTexture2D(uint32_t width, uint32_t height, glFormat eFormat) : glTexture2D()
{
	this->Storage(eFormat, glExtent2D(width, height));
}


bool glTexture2D::SetImage2D(const glImage2D && Image, glFormat eFormat)
{
	return this->SetImage2D(Image, eFormat);
}


bool glTexture2D::SetImage2D(const glImage2D & Image, glFormat eFormat)
{
	if (!Image.IsEmpty())
	{
		QGL_CHECK_ERROR;

		glExtent2D extent = Image.Extent();

		glBindTexture(GL_TEXTURE_2D, m_ResID);

		glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(eFormat), extent.width, extent.height, 0, static_cast<GLenum>(Image.Format()), static_cast<GLenum>(Image.DataType()), Image.Data());

		glBindTexture(GL_TEXTURE_2D, 0);

		if (QGL_CHECK_ERROR == true)
		{
			m_eFormat = eFormat;

			m_Extent = extent;

			return true;
		}
	}

	return false;
}


bool glTexture2D::Storage(glFormat eFormat, glExtent2D extent)
{
	QGL_CHECK_ERROR;

	glBindTexture(GL_TEXTURE_2D, m_ResID);

	glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(eFormat), extent.width, extent.height, 0, GL_RGB, GL_FLOAT, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);

	if (QGL_CHECK_ERROR == true)
	{
		m_eFormat = eFormat;

		m_Extent = extent;

		return true;
	}

	return false;
}


void glTexture2D::SetWrapS(glWrapMode eWrap)
{
	glBindTexture(GL_TEXTURE_2D, m_ResID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(eWrap));

	glBindTexture(GL_TEXTURE_2D, 0);
}


void glTexture2D::SetWrapT(glWrapMode eWrap)
{
	glBindTexture(GL_TEXTURE_2D, m_ResID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(eWrap));

	glBindTexture(GL_TEXTURE_2D, 0);
}


void glTexture2D::SetMinFilter(glFilter eMinFilter)
{
	glBindTexture(GL_TEXTURE_2D, m_ResID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(eMinFilter));

	glBindTexture(GL_TEXTURE_2D, 0);
}


void glTexture2D::SetMagFilter(glFilter eMagFilter)
{
	glBindTexture(GL_TEXTURE_2D, m_ResID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(eMagFilter));

	glBindTexture(GL_TEXTURE_2D, 0);
}


void glTexture2D::SetMipmapMode(glMipmapMode eMipmapMode)
{

}


void glTexture2D::GenerateMipmap()
{
	glBindTexture(GL_TEXTURE_2D, m_ResID);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}


glTexture2D::~glTexture2D()
{

}