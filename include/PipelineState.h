/*************************************************************************
**********************    QuickGL_PipelineState    ***********************
*************************************************************************/
#pragma once

#include "Common.h"

namespace QuickGL
{
	/*********************************************************************
	*************************    glCompareOp    **************************
	*********************************************************************/

	/**
	 *	@brief	Compare functions for depth-test and stencil-test.
	 */
	enum class glCompareOp : uint32_t
	{
		eLess				= 0x0201,		//!	@brief	Passes if the incoming depth value is less than the stored depth value (default).
		eEqual				= 0x0202,		//!	@brief	Passes if the incoming depth value is equal to the stored depth value.
		eNever				= 0x0200,		//!	@brief	Never passes.
		eAlways				= 0x0207,		//!	@brief	Always passes.
		eGreater			= 0x0204,		//!	@brief	Passes if the incoming depth value is greater than the stored depth value.
		eNotEqual			= 0x0205,		//!	@brief	Passes if the incoming depth value is not equal to the stored depth value.
		eLessOrEqual		= 0x0203,		//!	@brief	Passes if the incoming depth value is less than or equal to the stored depth value.
		eGreaterOrEqual		= 0x0206		//!	@brief	Passes if the incoming depth value is greater than or equal to the stored depth value.
	};

	/*********************************************************************
	*************************    glStencilOp    **************************
	*********************************************************************/

	/**
	 *	@brief	Stencil comparison function.
	 */
	enum class glStencilOp : uint32_t
	{
		eKeep					= 0x1E00,		//!	@brief	Keeps the current value.
		eZero					= 0x0000,		//!	@brief	Sets the stencil buffer value to 0.
		eInvert					= 0x150A,		//!	@brief	Bitwise inverts the current stencil buffer value.
		eReplace				= 0x1E01,		//!	@brief	Sets the stencil buffer value to ref, as specified by glStencilFunc.
		eIncrementAndWrap		= 0x8507,		//!	@brief	Increments the current stencil buffer value. Wraps stencil buffer value to zero when incrementing the maximum representable unsigned value.
		eDecrementAndWrap		= 0x8508,		//!	@brief	Decrements the current stencil buffer value. Wraps stencil buffer value to the maximum representable unsigned value when decrementing a stencil buffer value of zero.
		eIncrementAndClamp		= 0x1E02,		//!	@brief	Increments the current stencil buffer value. Clamps to the maximum representable unsigned value.
		eDecrementAndClamp		= 0x1E03		//!	@brief	Decrements the current stencil buffer value. Clamps to 0.
	};

	/*********************************************************************
	**************************    glBlendOp    ***************************
	*********************************************************************/

	/**
	 *	@brief	Framebuffer blending operations.
	 */
	enum class glBlendOp : uint32_t
	{
		eMin					= 0x8007,
		eMax					= 0x8008,
		eAdd					= 0x8006,
		eSubtract				= 0x800A,
		eReverseSubtract		= 0x800B
	};

	/*********************************************************************
	************************    glBlendFactor    *************************
	*********************************************************************/

	/**
	 *	@brief	Framebuffer blending factors.
	 */
	enum class glBlendFactor : uint32_t
	{
		eOne						= 0x0001,
		eZero						= 0x0000,
		eSrcColor					= 0x0300,
		eDstColor					= 0x0306,
		eSrcAlpha					= 0x0302,
		eDstAlpha					= 0x0304,
		eSrc1Color					= 0x88F9,
		eSrc1Alpha					= 0x8589,
		eConstantColor				= 0x8001,
		eConstantAlpha				= 0x8003,
		eSrcAlphaSaturate			= 0x0308,
		eOneMinusSrcColor			= 0x0301,
		eOneMinusDstColor			= 0x0307,
		eOneMinusSrcAlpha			= 0x0303,
		eOneMinusDstAlpha			= 0x0305,
		eOneMinusSrc1Color			= 0x88FA,
		eOneMinusSrc1Alpha			= 0x88FB,
		eOneMinusConstantColor		= 0x8002,
		eOneMinusConstantAlpha		= 0x8004
	};

	/*********************************************************************
	*************************    glFrontFace    **************************
	*********************************************************************/

	/**
	 *	@brief	Control polygon rasterization mode.
	 */
	enum class glPolygonMode : uint32_t
	{
		eFill		= 0x1B02,		//!	@brief	The interior of the polygon is filled.
		eLine		= 0x1B01,		//!	@brief	Boundary edges of the polygon are drawn as line segments.
		ePoint		= 0x1B00		//!	@brief	Polygon vertices that are marked as the start of a boundary edge are drawn as points. 
	};

	/*********************************************************************
	**************************    glCullMode    **************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask controlling triangle culling.
	 */
	enum class glCullMode : uint32_t
	{
		eBack				= 0x0405,		//!	@brief	Back-facing facets can be culled (default).
		eFront				= 0x0404,		//!	@brief	Front-facing facets can be culled.
		eFrontAndBack		= 0x0408		//!	@brief	Front- and back-facing facets can be culled.
	};

	/*********************************************************************
	*************************    glFrontFace    **************************
	*********************************************************************/

	/**
	 *	@brief	Specify the orientation of front-facing polygons.
	 */
	enum class glFrontFace : uint32_t
	{
		eClockwise			= 0x0900,		//!	@brief	Selects clockwise polygons as front-facing.
		eCounterClockwise	= 0x0901		//!	@brief	Selects counterclockwise polygons as front-facing (default).
	};

	/*********************************************************************
	***********************    glRasterization    ************************
	*********************************************************************/

	namespace glRasterization
	{
		//!	@brief	Specify the diameter of rasterized points.
		QGLAPI void PointSize(float size);

		//!	@brief	Specify the width of rasterized lines.
		QGLAPI void LineWidth(float width);

		//!	@brief	Specify whether front- or back-facing facets can be culled.
		QGLAPI void CullMode(glCullMode eCullMode);

		//!	@brief	Define front- and back-facing polygons.
		QGLAPI void FrontFace(glFrontFace eFrontFace);

		//!	@brief	Select a polygon rasterization mode.
		QGLAPI void PolygonMode(glPolygonMode ePolygonMode);

		//!	@brief	Set the scale and units used to calculate depth values.
		QGLAPI void PolygonOffset(float factor, float units);
	}

	/*********************************************************************
	*************************    glColorBlend    *************************
	*********************************************************************/

	namespace glColorBlend
	{
		//!	@brief	Enable color blending.
		QGLAPI void Enable();

		//!	@brief	Disable color blending.
		QGLAPI void Disable();

		//!	@brief	Specify the equation used for both the RGB blend equation and the Alpha blend equation.
		QGLAPI void Equation(glBlendOp eOp);

		//!	@brief	Set the blend color, initially the color is set to (0, 0, 0, 0).
		QGLAPI void Color(float red, float green, float blue, float alpha);

		//!	@brief	Specify pixel arithmetic.
		QGLAPI void Func(glBlendFactor eSrcFactor, glBlendFactor eDstFactor);

		//!	@brief	Specify pixel arithmetic for RGB and alpha components separately.
		QGLAPI void FuncSeparate(glBlendFactor eSrcRGB, glBlendFactor eDstRGB, glBlendFactor eSrcA, glBlendFactor eDstA);
	}

	/*********************************************************************
	************************    glScissorTest    *************************
	*********************************************************************/

	namespace glScissorTest
	{
		//!	@brief	Enable scissor test.
		QGLAPI void Enable();

		//!	@brief	Disable scissor test.
		QGLAPI void Disable();

		//!	@brief	Define the scissor box in window coordinates.
		QGLAPI void Rectangle(glOffset2D offset, glExtent2D extent);
	}

	/*********************************************************************
	*************************    glDepthTest    **************************
	*********************************************************************/

	namespace glDepthTest
	{
		//!	@brief	Enable depth test.
		QGLAPI void Enable();

		//!	@brief	Disable depth test.
		QGLAPI void Disable();

		//!	@brief	Enable or disable writing into the depth buffer.
		QGLAPI void Writable(bool enableWriting);

		//!	@brief	Specify the value used for depth buffer comparisons.
		QGLAPI void CompareFunc(glCompareOp eOp);
	};

	/*********************************************************************
	************************    glStencilTest    *************************
	*********************************************************************/

	namespace glStencilTest
	{
		//!	@brief	Enable stencil test.
		QGLAPI void Enable();

		//!	@brief	Disable stencil test.
		QGLAPI void Disable();

		//!	@brief	Specify front and back function and reference value for stencil testing.
		QGLAPI void CompareFunc(glCompareOp eOp, int refVaule, uint32_t mask);

		//!	@brief	Specify front and back stencil test actions.
		QGLAPI void Op(glStencilOp eStencilFail, glStencilOp eDepthFail, glStencilOp eDepthPass);
	}
}