/*************************************************************************
*************************    QuickGL_Texture    **************************
*************************************************************************/
#include "Internal.h"
#include "Texture.h"

/*************************************************************************
****************************    glTexture    *****************************
*************************************************************************/
glTexture::glTexture(glTextureType eType) : m_eTexType(eType), m_eFormat(glFormat::eUndefined)
{
	glGenTextures(1, &m_ResID);
}


glTexture::~glTexture()
{
	glDeleteTextures(1, &m_ResID);
}