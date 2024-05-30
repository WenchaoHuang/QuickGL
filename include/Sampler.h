/*************************************************************************
*************************    QuickGL_Sampler    **************************
*************************************************************************/
#pragma once

#include "Resource.h"

namespace QuickGL
{
	/*********************************************************************
	***************************    glFilter    ***************************
	*********************************************************************/

	/**
	 *	@brief	Filter Types of OpenGL texture object.
	 */
	enum class glFilter : int
	{
		eLinear			= 0x2601,		//!	@brief	Takes an interpolated value from the texture coordinate's neighboring texels, approximating a color between the texels.
		eNearest		= 0x2600		//!	@brief	Selects the pixel which center is closest to the texture coordinate.
	};

	/*********************************************************************
	*************************    glMipmapMode    *************************
	*********************************************************************/

	/**
	 *	@brief	Specify mipmap mode used for texture lookups.
	 */
	enum class glMipmapMode : int
	{
		eNone			= 0x0000,		//!	@brief	Disable mipmaps (use level-0 image).
		eLinear			= 0x0001,		//!	@brief	Linearly interpolates between the two closest mipmaps.
		eNearest		= 0x0002		//!	@brief	Linearly interpolates between the two mipmaps that most closely match the size of a pixel.
	};

	/*********************************************************************
	**************************    glWrapMode    **************************
	*********************************************************************/

	/**
	 *	@brief	Specify behavior of sampling with texture coordinates outside an image.
	 */
	enum class glWrapMode : int
	{
		eRepeat				= 0x2901,	//!	@brief	Repeats the texture image.
		eClampToEdge		= 0x812F,	//!	@brief	Clamps the coordinates between 0 and 1.
		eMirroredRepeat		= 0x8370	//!	@brief	Mirrors the image with each repeat.
	};

	/*********************************************************************
	**************************    glSampler    ***************************
	*********************************************************************/

	/**
	 *	@brief	OpenGL sampler object.
	 */
	class QGLAPI glSampler : public glResource
	{

	public:

		//!	@brief	Create sampler object.
		glSampler();

		//!	@brief	Destroy sampler object.
		~glSampler();

	public:

		/**
		 *	@brief		Set the minimum level-of-detail parameter.
		 *	@note		This floating-point value limits the selection of highest resolution mipmap (lowest mipmap level).
		 *	@note		The initial value is -1000.
		 */
		void SetMinLod(float minLod);

		/**
		 *	@brief		Set the maximum level - of - detail parameter.
		 *	@note		This floating - point value limits the selection of the lowest resolution mipmap(highest mipmap level).
		 *	@note		The initial value is 1000.
		 */
		void SetMaxLod(float maxLod);

		/**
		 *	@brief		Set the bias of minimum level-of-detail parameter.
		 *	@note		The initial value is 0.
		 */
		void SetMinLodBias(float minLodBias);

		/**
		 *	@brief		Set the wrap parameter for texture coordinate s.
		 */
		void SetWrapS(glWrapMode eWrapS);

		/**
		 *	@brief		Set the wrap parameter for texture coordinate t.
		 */
		void SetWrapT(glWrapMode eWrapT);

		/**
		 *	@brief		Set the wrap parameter for texture coordinate r.
		 */
		void SetWrapR(glWrapMode eWrapR);

		/**
		 *	@brief		Set the texture minification function.
		 */
		void SetMinFilter(glFilter eMinFilter);

		/**
		 *	@brief		Set the texture magnification function.
		 */
		void SetMagFilter(glFilter eMagFilter);

		/**
		 *	@brief		Set the texture mipmap mode.
		 */
		void SetMipmapMode(glMipmapMode eMipmapMode);

	public:

		/**
		 *	@brief		Return the texture minification filter.
		 *	@note		The initial value is glFilter::eLinear.
		 */
		glFilter GetMinFilter() const;

		/**
		 *	@brief		Return the texture magnification filter.
		 *	@note		The initial value is glFilter::eLinear.
		 */
		glFilter GetMagFilter() const;

		/**
		 *	@brief		Return the texture minification filter for mipmaps.
		 *	@note		The initial value is glMipmapMode::eNearest.
		 */
		glMipmapMode GetMipmapMode() const;

		/**
		 *	@brief		Return the wrapping function for texture coordinate s.
		 *	@note		The initial value is glWrapMode::eRepeat.
		 */
		glWrapMode GetWrapS() const;

		/**
		 *	@brief		Return the wrapping function for texture coordinate t.
		 *	@note		The initial value is glWrapMode::eRepeat.
		 */
		glWrapMode GetWrapT() const;

		/**
		 *	@brief		Return the wrapping function for texture coordinate r.
		 *	@note		The initial value is glWrapMode::eRepeat.
		 */
		glWrapMode GetWrapR() const;

		/**
		 *	@brief		Return the bias of texture minimum level-of-detail value.
		 *	@note		The initial value is 0.
		 */
		float GetMinLodBias() const;

		/**
		 *	@brief		Return the texture minimum level-of-detail value.
		 *	@note		The initial value is −1000.
		 */
		float GetMinLod() const;

		/**
		 *	@brief		Return the texture maximum level-of-detail value.
		 *	@note		The initial value is 1000.
		 */
		float GetMaxLod() const;
	};
}