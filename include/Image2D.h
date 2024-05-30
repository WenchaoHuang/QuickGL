/*************************************************************************
*************************    QuickGL_Image2D    **************************
*************************************************************************/
#pragma once

#include <vector>
#include "Resource.h"

namespace QuickGL
{
	/*********************************************************************
	***********************    glExternalFormat    ***********************
	*********************************************************************/

	/**
	 *	@brief	Formats of image.
	 */
	enum class glExternalFormat : uint32_t
	{
		eR			= 0x1903,		//!	@brief	{ Red }
		eRG			= 0x8227,		//!	@brief	{ Red, Green }
		eRGB		= 0x1907,		//!	@brief	{ Red, Green, Blue }
		eRGBA		= 0x1908		//!	@brief	{ Red, Green, Blue, Alpha }
	};

	/*********************************************************************
	***********************    glPixelDataType    ************************
	*********************************************************************/

	/**
	 *	@brief	Types of pixel data.
	 */
	enum class glPixelDataType : uint32_t
	{
		eFloat				= 0x1406,		//!	@brief	GL_FLOAT
		eUnsignedByte		= 0x1401		//!	@brief	GL_UNSIGNED_BYTE
	};

	/*********************************************************************
	**************************    glImage2D    ***************************
	*********************************************************************/

	/**
	 *	@brief	OpenGL image 2D object.
	 */
	class QGLAPI glImage2D
	{

	public:

		//!	@brief	Create image(empty) object.
		glImage2D();

		//!	@brief	Exchange context.
		glImage2D(glImage2D && Other);

		//!	@brief	Copy from others.
		glImage2D(const glImage2D & Other);

		//!	@brief	Exchange context.
		glImage2D & operator=(glImage2D && Other);

		//!	@brief	Copy from others.
		glImage2D & operator=(const glImage2D & Other);

		//!	@brief	Create image object and load from file.
		explicit glImage2D(const char * pImagePath, bool flipImage = false);

		//!	@brief	Delete image object.
		~glImage2D() noexcept;

	public:

		//!	@brief	Load image from file.
		bool Load(const char * pImagePath, bool flipImage = false);

		//!	@brief	Save png-image to file.
		bool SavePNG(const char * pImagePath, bool flipImage = false) const;

		//!	@brief	Save bmp-image to file.
		bool SaveBMP(const char * pImagePath, bool flipImage = false) const;

		//!	@brief	Save tga-image to file.
		bool SaveTGA(const char * pImagePath, bool flipImage = false) const;

		//!	@brief	Save jpg-image to file.
		bool SaveJPGE(const char * pImagePath, bool flipImage = false) const;

		//!	@brief	Resize image store.
		void Resize(glExtent2D extent, glExternalFormat eFormat, glPixelDataType eDataType);

		//!	@brief	Returns address of image data.
		const char * Data() const { return m_ImageData.data(); }

		//!	@brief	Returns image format.
		glExternalFormat Format() const { return m_eExtFormat; }

		//!	@brief	Returns image data-type.
		glPixelDataType DataType() const { return m_eDataType; }

		//!	@brief	If image is empty.
		bool IsEmpty() const { return m_ImageData.empty(); }

		//!	@brief	Return image extent.
		glExtent2D Extent() const { return m_Extent; }

		//!	@brief	Returns address of image data.
		char * Data() { return m_ImageData.data(); }

		//!	@brief	Exchange context.
		void Swap(glImage2D && Other);

		//!	@brief	Exchange context.
		void Swap(glImage2D & Other);

		//!	@brief	Erase image data.
		void Clear();

	private:

		glExtent2D				m_Extent;

		glPixelDataType			m_eDataType;

		glExternalFormat		m_eExtFormat;

		std::vector<char>		m_ImageData;
	};
}