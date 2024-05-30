/*************************************************************************
*************************    QuickGL_Image2D    **************************
*************************************************************************/
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <stb/stb_image_write.h>
#include <stb/stb_image.h>
#include "Internal.h"
#include "Image2D.h"

static GLint ToChannels(glExternalFormat eExtFormat);

/*************************************************************************
****************************    glImage2D    *****************************
*************************************************************************/
glImage2D::glImage2D() : m_eExtFormat(glExternalFormat::eRGB), m_eDataType(glPixelDataType::eUnsignedByte)
{

}


glImage2D::glImage2D(const char * pImagePath, bool flipImage) : glImage2D()
{
	this->Load(pImagePath, flipImage);
}


glImage2D::glImage2D(const glImage2D & Other) : glImage2D()
{
	m_eExtFormat = Other.m_eExtFormat;

	m_eDataType = Other.m_eDataType;

	m_ImageData = Other.m_ImageData;

	m_Extent = Other.m_Extent;
}


glImage2D::glImage2D(glImage2D && Other) : glImage2D()
{
	this->Swap(Other);
}


bool glImage2D::Load(const char * pImagePath, bool flipImage)
{
	stbi_set_flip_vertically_on_load(flipImage);

	int Width = 0, Height = 0, Channels = 0;

	bool IsHDR = stbi_is_hdr(pImagePath);

	void * pData = nullptr;

	if (!IsHDR)		pData = stbi_load(pImagePath, &Width, &Height, &Channels, 0);
	else			pData = stbi_loadf(pImagePath, &Width, &Height, &Channels, 0);

	if (pData == nullptr)
	{
		printf(" QuickGL_Error: glImage2D() => Failed to open image: \"%s\"\n", pImagePath);
	}
	else
	{
		if (Channels == 1)			m_eExtFormat = glExternalFormat::eR;
		else if (Channels == 2)		m_eExtFormat = glExternalFormat::eRG;
		else if (Channels == 3)		m_eExtFormat = glExternalFormat::eRGB;
		else if (Channels == 4)		m_eExtFormat = glExternalFormat::eRGBA;
		else
		{
			stbi_image_free(pData);		return false;
		}

		if (IsHDR)		m_ImageData.resize(Width * Height * Channels * 4);
		else			m_ImageData.resize(Width * Height * Channels);

		if (!IsHDR)		m_eDataType = glPixelDataType::eUnsignedByte;
		else			m_eDataType = glPixelDataType::eFloat;

		memcpy(m_ImageData.data(), pData, m_ImageData.size());

		m_Extent = glExtent2D(Width, Height);

		stbi_image_free(pData);

		return true;
	}

	return false;
}


bool glImage2D::SavePNG(const char * pImagePath, bool flipImage) const
{
	stbi_flip_vertically_on_write(flipImage);

	if (m_eDataType != glPixelDataType::eUnsignedByte)	return false;

	return stbi_write_png(pImagePath, m_Extent.width, m_Extent.height, ToChannels(m_eExtFormat), m_ImageData.data(), 0) != 0;
}


bool glImage2D::SaveBMP(const char * pImagePath, bool flipImage) const
{
	stbi_flip_vertically_on_write(flipImage);

	if (m_eDataType != glPixelDataType::eUnsignedByte)	return false;

	return stbi_write_bmp(pImagePath, m_Extent.width, m_Extent.height, ToChannels(m_eExtFormat), m_ImageData.data()) != 0;
}


bool glImage2D::SaveTGA(const char * pImagePath, bool flipImage) const
{
	stbi_flip_vertically_on_write(flipImage);

	if (m_eDataType != glPixelDataType::eUnsignedByte)	return false;

	return stbi_write_tga(pImagePath, m_Extent.width, m_Extent.height, ToChannels(m_eExtFormat), m_ImageData.data()) != 0;
}


bool glImage2D::SaveJPGE(const char * pImagePath, bool flipImage) const
{
	stbi_flip_vertically_on_write(flipImage);

	if (m_eDataType != glPixelDataType::eUnsignedByte)	return false;

	return stbi_write_jpg(pImagePath, m_Extent.width, m_Extent.height, ToChannels(m_eExtFormat), m_ImageData.data(), 0) != 0;
}


void glImage2D::Resize(glExtent2D extent, glExternalFormat eFormat, glPixelDataType eDataType)
{
	if (eDataType == glPixelDataType::eFloat)
	{
		m_ImageData.resize(extent.width * extent.height * ToChannels(eFormat) * sizeof(float));
	}
	else if (eDataType == glPixelDataType::eUnsignedByte)
	{
		m_ImageData.resize(extent.width * extent.height * ToChannels(eFormat) * sizeof(unsigned char));
	}

	m_eDataType = eDataType;

	m_eExtFormat = eFormat;

	m_Extent = extent;
}


int ToChannels(glExternalFormat eExtFormat)
{
	if (eExtFormat == glExternalFormat::eR)				return 1;
	else if (eExtFormat == glExternalFormat::eRG)		return 2;
	else if (eExtFormat == glExternalFormat::eRGB)		return 3;
	else if (eExtFormat == glExternalFormat::eRGBA)		return 4;
	else												return 0;
}


glImage2D & glImage2D::operator=(glImage2D && Other)
{
	this->Swap(Other);		return (*this);
}


glImage2D & glImage2D::operator=(const glImage2D & Other)
{
	m_eExtFormat = Other.m_eExtFormat;

	m_eDataType = Other.m_eDataType;

	m_ImageData = Other.m_ImageData;

	m_Extent = Other.m_Extent;

	return (*this);
}


void glImage2D::Swap(glImage2D & Other)
{
	m_ImageData.swap(Other.m_ImageData);

	QGL_SWAP(m_eDataType, Other.m_eDataType);

	QGL_SWAP(m_eExtFormat, Other.m_eExtFormat);

	QGL_SWAP(m_Extent, Other.m_Extent);
}


void glImage2D::Clear()
{
	m_ImageData.clear();

	m_ImageData.shrink_to_fit();

	m_Extent = { 0, 0 };
}


void glImage2D::Swap(glImage2D && Other)
{
	this->Swap(Other);
}


glImage2D::~glImage2D() noexcept
{

}