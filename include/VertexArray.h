/*************************************************************************
***********************    QuickGL_VertexArray    ************************
*************************************************************************/
#pragma once

#include "Resource.h"

namespace QuickGL
{
	/*********************************************************************
	*********************    glPrimitiveTopology    **********************
	*********************************************************************/

	/**
	 *	@brief	Topologies of OpenGL primitive.
	 */
	enum class glPrimitiveTopology : uint32_t
	{
		eLines				= 0x0001,		//!	@brief	GL_LINES
		eQuads				= 0x0007,		//!	@brief	GL_QUADS
		ePoints				= 0x0000,		//!	@brief	GL_POINTS
		ePatches			= 0x000E,		//!	@brief	GL_PATCHES
		ePolygon			= 0x0009,		//!	@brief	GL_POLYGON
		eLineLoop			= 0x0002,		//!	@brief	GL_LINE_LOOP
		eQuadStrip			= 0x0008,		//!	@brief	GL_QUAD_STRIP
		eLineStrip			= 0x0003,		//!	@brief	GL_LINE_STRIP
		eTriangles			= 0x0004,		//!	@brief	GL_TRIANGLES
		eTriangleFan		= 0x0006,		//!	@brief	GL_TRIANGLE_FAN
		eTriangleStrip		= 0x0005		//!	@brief	GL_TRIANGLE_STRIP
	};

	/*********************************************************************
	************************    glVertexArray    *************************
	*********************************************************************/
	
	/**
	 *	@brief	OpenGL vertex array object.
	 */
	class QGLAPI glVertexArray : public glResource
	{

	public:

		//!	@brief	Create vertex array object.
		glVertexArray();

		//!	@brief	Destroy vertex array object.
		~glVertexArray();

	public:

		//!	@brief	Specify the value of a generic vertex attribute (float).
		void SetAttrib1f(uint32_t binding, float v0);

		//!	@brief	Specify the value of a generic vertex attribute (vec2).
		void SetAttrib2f(uint32_t binding, float v0, float v1);

		//!	@brief	Specify the value of a generic vertex attribute (vec3).
		void SetAttrib3f(uint32_t binding, float v0, float v1, float v2);

		//!	@brief	Specify the value of a generic vertex attribute (vec4).
		void SetAttrib4f(uint32_t binding, float v0, float v1, float v2, float v3);

		//!	@brief	Define an array of generic vertex attribute data (float).
		void SetAttrib1fp(uint32_t binding, const glBuffer * pBuffer, uint32_t stride, size_t offset = 0);

		//!	@brief	Define an array of generic vertex attribute data (vec2).
		void SetAttrib2fp(uint32_t binding, const glBuffer * pBuffer, uint32_t stride, size_t offset = 0);

		//!	@brief	Define an array of generic vertex attribute data (vec3).
		void SetAttrib3fp(uint32_t binding, const glBuffer * pBuffer, uint32_t stride, size_t offset = 0);

		//!	@brief	Define an array of generic vertex attribute data (vec4).
		void SetAttrib4fp(uint32_t binding, const glBuffer * pBuffer, uint32_t stride, size_t offset = 0);

		//!	@brief	Render primitives from array data.
		void DrawElements(glPrimitiveTopology eTopology, uint32_t count, size_t offset = 0) const;

		//!	@brief	Render primitives from array data.
		void DrawArrays(glPrimitiveTopology eTopology, uint32_t count, uint32_t first = 0) const;

		//!	@brief	Specify binding attribute (must be 32-bit integer-type per binding).
		void SetIndexAttrib(const glBuffer * pBuffer);

		//!	@brief	Disable a generic vertex attribute array.
		void DisableAttrib(uint32_t binding);

		//!	@brief	Enable a generic vertex attribute array.
		void EnableAttrib(uint32_t binding);
	};
}