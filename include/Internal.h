/*************************************************************************
*************************    QuickGL_Internal    *************************
*************************************************************************/
#pragma once

#include <stdio.h>
#include <GLAD/glad.h>

#define QGL_SWAP(a, b)				{ auto c = a; a = b; b = c; }

#define QGL_CHECK_ERROR				glCheckError(__FILE__, __LINE__)

namespace QuickGL
{
	/*********************************************************************
	*************************    glCheckError    *************************
	*********************************************************************/

	inline bool glCheckError(const char * file, int line)
	{
		if (glGetError() != GL_NO_ERROR)
		{
			printf(" VisualGL_Error: %s => line: %d.\n", file, line);

			return false;
		}

		return true;
	}
}

using namespace QuickGL;

#undef glPolygonMode
#undef glStencilOp
#undef glFrontFace