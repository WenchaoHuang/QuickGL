/*************************************************************************
*****************************    QuickGL    ******************************
*************************************************************************/
#pragma once

#if defined(_WINDLL) && defined(QGLAPI_BUILD)
	#define QGL_DLL_EXPORT		__declspec(dllexport)
	#define QGL_DLL_IMPORT		__declspec(dllimport)
#else
	#define QGL_DLL_EXPORT
	#define QGL_DLL_IMPORT
#endif

#if defined(QGLAPI_BUILD)
	#define	QGLAPI				QGL_DLL_EXPORT
#else
	#define	QGLAPI				QGL_DLL_IMPORT
#endif

#include <stdint.h>

namespace QuickGL
{
	/*********************************************************************	
	*************************    Declaration    **************************
	*********************************************************************/

	class glBuffer;
	class glSampler;
	class glProgram;
	class glTexture2D;
	class glTexture2DMS;
	class glTextureCube;
	class glVertexArray;
	class glFramebuffer;
	class glRenderbuffer;

	/*********************************************************************
	****************************    LoadGL    ****************************
	*********************************************************************/

	/**
	 *	@brief		QuickGL load OpenGL library.
	 *	@return		If QuickGL failed to load OpenGL library, returns false.
	 *				Else if QuickGL had loaded or succeeded to load OpenGL library,
	 *				returns true.
	 */
	QGLAPI bool LoadGL();

	/*********************************************************************
	************************    glSampleCount    *************************
	*********************************************************************/

	/**
	 *	@brief	OpenGL sample counts.
	 */
	enum class glSampleCount
	{
		x1		= 0x0001,
		x2		= 0x0002,
		x4		= 0x0004,
		x8		= 0x0008,
		x16		= 0x0010
	};

	/*********************************************************************
	***************************    glFormat    ***************************
	*********************************************************************/

	/**
	 *	@brief	Common available image formats.
	 */
	enum class glFormat
	{
		eUndefined			= 0x0000,

		eR					= 0x1903,
		eRG					= 0x8227,
		eRGB				= 0x1907,
		eRGBA				= 0x1908,

		eR16				= 0x822A,
		eRG16				= 0x822C,
		eRGB16				= 0x8054,
		eRGBA16				= 0x805B,

		eR16F				= 0x822D,
		eRG16F				= 0x822F,
		eRGB16F				= 0x881B,
		eRGBA16F			= 0x881A,

		eR32F				= 0x822E,
		eRG32F				= 0x8230,
		eRGB32F				= 0x8815,
		eRGBA32F			= 0x8814,

		eD16				= 0x81A5,
		eD24				= 0x81A6,
		eD32				= 0x81A7,
		eD32F				= 0x8CAC,
		eD24S8				= 0x88F0,
		eD32S8				= 0x8CAD,

		eSRGB				= 0x8C40,
		eSRGBA				= 0x8C42
	};

	/*********************************************************************
	**************************    glOffset2D    **************************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying a two-dimensional offset.
	 */
	struct glOffset2D
	{
		int32_t		x;
		int32_t		y;

		constexpr glOffset2D() : x(0), y(0) {}
		constexpr glOffset2D(int32_t _i) : x(_i), y(_i) {}
		constexpr glOffset2D(int32_t _x, int32_t _y) : x(_x), y(_y) {}

		constexpr bool operator==(const glOffset2D & rhs) const { return (rhs.x == x) && (rhs.y == y); }
		constexpr bool operator!=(const glOffset2D & rhs) const { return (rhs.x != x) || (rhs.y != y); }
	};

	/*********************************************************************
	**************************    glExtent2D    **************************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying a two-dimensional extent.
	 */
	struct glExtent2D
	{
		uint32_t	width;
		uint32_t	height;

		constexpr glExtent2D() : width(0), height(0) {}
		constexpr glExtent2D(uint32_t i) : width(i), height(i) {}
		constexpr glExtent2D(uint32_t w, uint32_t h) : width(w), height(h) {}

		constexpr bool operator==(const glExtent2D & rhs) const { return (rhs.width == width) && (rhs.height == height); }
		constexpr bool operator!=(const glExtent2D & rhs) const { return (rhs.width != width) || (rhs.height != height); }

		constexpr glExtent2D operator*(float ratio) const { return glExtent2D(static_cast<uint32_t>(width * ratio), static_cast<uint32_t>(height * ratio)); }
		constexpr glExtent2D operator/(float ratio) const { return glExtent2D(static_cast<uint32_t>(width / ratio), static_cast<uint32_t>(height / ratio)); }
	};
}