/*************************************************************************
************************    QuickGL_Capability    ************************
*************************************************************************/
#include "PipelineState.h"
#include "Internal.h"

/*************************************************************************
*************************    glRasterization    **************************
*************************************************************************/
void glRasterization::PointSize(float size)
{
	glPointSize(size);
}


void glRasterization::LineWidth(float width)
{
	glLineWidth(width);
}


void glRasterization::CullMode(glCullMode eCullMode)
{
	glad_glCullFace(static_cast<GLenum>(eCullMode));
}


void glRasterization::FrontFace(glFrontFace eFrontFace)
{
	glad_glFrontFace(static_cast<GLenum>(eFrontFace));
}


void glRasterization::PolygonMode(glPolygonMode ePolygonMode)
{
	glad_glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(ePolygonMode));
}


void glRasterization::PolygonOffset(float factor, float units)
{
	glPolygonOffset(factor, units);
}


/*************************************************************************
***************************    glColorBlend    ***************************
*************************************************************************/
void glColorBlend::Enable()
{
	glEnable(GL_BLEND);
}


void glColorBlend::Disable()
{
	glDisable(GL_BLEND);
}


void glColorBlend::Equation(glBlendOp eOp)
{
	glBlendEquation(static_cast<GLenum>(eOp));
}


void glColorBlend::Color(float red, float green, float blue, float alpha)
{
	glBlendColor(red, green, blue, alpha);
}


void glColorBlend::Func(glBlendFactor eSrcFactor, glBlendFactor eDstFactor)
{
	glBlendFunc(static_cast<GLenum>(eSrcFactor), static_cast<GLenum>(eDstFactor));
}


void glColorBlend::FuncSeparate(glBlendFactor eSrcRGB, glBlendFactor eDstRGB, glBlendFactor eSrcA, glBlendFactor eDstA)
{
	glBlendFuncSeparate(static_cast<GLenum>(eSrcRGB), static_cast<GLenum>(eDstRGB), static_cast<GLenum>(eSrcA), static_cast<GLenum>(eDstA));
}


/*************************************************************************
**************************    glScissorTest    ***************************
*************************************************************************/
void glScissorTest::Enable()
{
	glEnable(GL_SCISSOR_TEST);
}


void glScissorTest::Disable()
{
	glDisable(GL_SCISSOR_TEST);
}


void glScissorTest::Rectangle(glOffset2D offset, glExtent2D extent)
{
	glScissor(offset.x, offset.y, extent.width, extent.height);
}


/*************************************************************************
***************************    glDepthTest    ****************************
*************************************************************************/
void glDepthTest::Enable()
{
	glEnable(GL_DEPTH_TEST);
}


void glDepthTest::Disable()
{
	glDisable(GL_DEPTH_TEST);
}


void glDepthTest::Writable(bool enableWriting)
{
	glDepthMask(static_cast<GLboolean>(enableWriting));
}


void glDepthTest::CompareFunc(glCompareOp eOp)
{
	glDepthFunc(static_cast<GLenum>(eOp));
}


/*************************************************************************
**************************    glStencilTest    ***************************
*************************************************************************/
void glStencilTest::Enable()
{
	glEnable(GL_STENCIL_TEST);
}


void glStencilTest::Disable()
{
	glDisable(GL_STENCIL_TEST);
}


void glStencilTest::CompareFunc(glCompareOp eOp, int refVaule, uint32_t mask)
{
	glStencilFunc(static_cast<GLenum>(eOp), refVaule, mask);
}


void glStencilTest::Op(glStencilOp eStencilFail, glStencilOp eDepthFail, glStencilOp eDepthPass)
{
	glad_glStencilOp(static_cast<GLenum>(eStencilFail), static_cast<GLenum>(eDepthFail), static_cast<GLenum>(eDepthPass));
}