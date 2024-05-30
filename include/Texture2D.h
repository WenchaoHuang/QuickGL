/*************************************************************************
************************    QuickGL_Texture2D    *************************
*************************************************************************/
#pragma once

#include "Image2D.h"
#include "Texture.h"

namespace QuickGL
{
	/*********************************************************************
	*************************    glTexutre2D    **************************
	*********************************************************************/

	/**
	 *	@brief	OpenGL 2D texture object.
	 */
	class QGLAPI glTexture2D : public glTexture
	{

	public:

		//!	@brief	Create 2D texture object.
		glTexture2D();

		//!	@brief	Create 2D texture object by image.
		explicit glTexture2D(const glImage2D & Image, glFormat eFormat);

		//!	@brief	Create 2D texture object by image.
		explicit glTexture2D(const glImage2D && Image, glFormat eFormat);

		//!	@brief	Create 2D texture object and initializes data store.
		explicit glTexture2D(uint32_t width, uint32_t height, glFormat eFormat);

		//!	@brief	Destroy 2D texture object.
		~glTexture2D() noexcept;

	public:

		//!	@brief	Return texture extent.
		glExtent2D Extent() const { return m_Extent; }

		//!	@brief	Specify two-dimensional texture image.
		bool Storage(glFormat eFormat, glExtent2D extent);

		//!	@brief	Specify two-dimensional texture image.
		bool SetImage2D(const glImage2D & Image, glFormat eFormat);

		//!	@brief	Specify two-dimensional texture image.
		bool SetImage2D(const glImage2D && Image, glFormat eFormat);

		//!	@brief	Check if image is empty.
		bool IsEmpty() const { return m_Extent.width * m_Extent.height == 0; }

		//!	@brief	Specify mipmap mode.
		void SetMipmapMode(glMipmapMode eMipmapMode);

		//!	@brief	Specify minify filtering type.
		void SetMinFilter(glFilter eMinFilter);

		//!	@brief	Specify magnify filtering type.
		void SetMagFilter(glFilter eMagFilter);

		//!	@brief	Specify S-Wrapping type.
		void SetWrapS(glWrapMode eWrapS);

		//!	@brief	Specify T-Wrapping type.
		void SetWrapT(glWrapMode eWrapT);

		//!	@brief	Generate mipmap.
		void GenerateMipmap();

	private:

		glExtent2D		m_Extent;
	};
}