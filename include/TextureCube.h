/*************************************************************************
***********************    QuickGL_TextureCube    ************************
*************************************************************************/
#pragma once

#include "Image2D.h"
#include "Texture.h"

namespace QuickGL
{
	/*********************************************************************
	**************************    glCubeFace    **************************
	*********************************************************************/

	/**
	 *	@brief	Tag of Cube face.
	 */
	enum class glCubeFace : uint32_t
	{
		ePositiveX		= 0x8515,		//!	@brief	Right side.
		eNegativeX		= 0x8516,		//!	@brief	Left side.
		ePositiveY		= 0x8517,		//!	@brief	Top side.
		eNegativeY		= 0x8518,		//!	@brief	Bottom side.
		ePositiveZ		= 0x8519,		//!	@brief	Front side.
		eNegativeZ		= 0x851A		//!	@brief	Back side.
	};

	//!	@brief	Operator: plus with integer.
	constexpr glCubeFace operator+(glCubeFace eFace, uint32_t i)
	{
		return static_cast<glCubeFace>(static_cast<uint32_t>(eFace) + i);
	}

	/*********************************************************************
	************************    glTextureCube    *************************
	*********************************************************************/

	/**
	 *	@brief	OpenGL cube-map object.
	 */
	class QGLAPI glTextureCube : public glTexture
	{

	public:

		//!	@brief	Create cube-map object.
		glTextureCube();

		//!	@brief	Create cube-map object and initializes data store.
		explicit glTextureCube(glFormat eFormat, uint32_t size);

		//!	@brief	Destroy cube-map object.
		~glTextureCube() noexcept;

	public:

		//!	@brief	Enable seamless sampling.
		static void EnableSeamless();

		//!	@brief	Disable seamless sampling.
		static void DisableSeamless();

	public:

		//!	@brief	Return extent of the cube-map.
		glExtent2D Extent() const { return m_Extent; }

		//!	@brief	Specify length of the side of the cube-map.
		bool Storage(glFormat eFormat, uint32_t size);

		//!	@brief	Specify cube-map image.
		bool SetImage2D(glCubeFace eFace, const glImage2D && Image, glFormat eFormat);

		//!	@brief	Specify cube-map image.
		bool SetImage2D(glCubeFace eFace, const glImage2D & Image, glFormat eFormat);

		//!	@brief	Specify minify filtering type.
		void SetMinFilter(glFilter eFilter);

		//!	@brief	Specify magnify filtering type.
		void SetMagFilter(glFilter eFilter);

		//!	@brief	Generate mipmap.
		void GenerateMipmap();

	private:

		glExtent2D		m_Extent;
	};
}