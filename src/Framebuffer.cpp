/*************************************************************************
***********************    QuickGL_Framebuffer    ************************
*************************************************************************/
#include "Renderbuffer.h"
#include "Framebuffer.h"
#include "Texture2DMS.h"
#include "Texture2D.h"
#include "Internal.h"

/*************************************************************************
**************************    glFramebuffer    ***************************
*************************************************************************/
glFramebuffer::glFramebuffer() : m_ClearMask(0), m_ClearDepth(1.0), m_ClearStencil(0)
{
	glGenFramebuffers(1, &m_ResID);

	m_ClearColor[0] = 0.0f;
	m_ClearColor[1] = 0.0f;
	m_ClearColor[2] = 0.0f;
	m_ClearColor[3] = 0.0f;
}


void glFramebuffer::Viewport(glOffset2D offset, glExtent2D extent)
{
	glViewport(offset.x, offset.y, extent.width, extent.height);
}


void glFramebuffer::ColorWriteMask(bool red, bool green, bool blue, bool alpha)
{
	glColorMask(static_cast<GLboolean>(red), static_cast<GLboolean>(green), static_cast<GLboolean>(blue), static_cast<GLboolean>(alpha));
}


void glFramebuffer::ClearColor(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);

	glClear(GL_COLOR_BUFFER_BIT);
}


void glFramebuffer::ClearDepth(float depth)
{
	glClearDepth(static_cast<GLdouble>(depth));

	glClear(GL_DEPTH_BUFFER_BIT);
}


void glFramebuffer::ClearStencil(int value)
{
	glClearStencil(value);

	glClear(GL_STENCIL_BUFFER_BIT);
}


bool glFramebuffer::Attach(glAttachmentSlot eSlot, const glRenderbuffer * pRenderbuffer)
{
	QGL_CHECK_ERROR;

	glBindFramebuffer(GL_FRAMEBUFFER, m_ResID);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<GLenum>(eSlot), GL_RENDERBUFFER, *pRenderbuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return QGL_CHECK_ERROR;
}


bool glFramebuffer::Attach(glAttachmentSlot eSlot, const glTexture2D * pTexture2D, int level)
{
	QGL_CHECK_ERROR;

	glBindFramebuffer(GL_FRAMEBUFFER, m_ResID);

	glFramebufferTexture2D(GL_FRAMEBUFFER, static_cast<GLenum>(eSlot), GL_TEXTURE_2D, *pTexture2D, level);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return QGL_CHECK_ERROR;
}


bool glFramebuffer::Attach(glAttachmentSlot eSlot, const glTexture2DMS * pTexture2DMS, int level)
{
	QGL_CHECK_ERROR;

	glBindFramebuffer(GL_FRAMEBUFFER, m_ResID);

	glFramebufferTexture2D(GL_FRAMEBUFFER, static_cast<GLenum>(eSlot), GL_TEXTURE_2D_MULTISAMPLE, *pTexture2DMS, level);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return QGL_CHECK_ERROR;
}


bool glFramebuffer::Attach(glAttachmentSlot eSlot, const glTextureCube * pCubeMap, glCubeFace eFace, int level)
{
	QGL_CHECK_ERROR;

	glBindFramebuffer(GL_FRAMEBUFFER, m_ResID);

	glFramebufferTexture2D(GL_FRAMEBUFFER, static_cast<GLenum>(eSlot), static_cast<GLenum>(eFace), *pCubeMap, level);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return QGL_CHECK_ERROR;
}


bool glFramebuffer::BlitColorFrom(const glFramebuffer * pSrcFBO, glOffset2D srcOffset, glOffset2D dstOffset, glExtent2D extent)
{
	QGL_CHECK_ERROR;

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_ResID);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, pSrcFBO->m_ResID);

	glBlitFramebuffer(srcOffset.x, srcOffset.y, srcOffset.x + extent.width, srcOffset.y + extent.height,
					  dstOffset.x, dstOffset.y, dstOffset.x + extent.width, dstOffset.y + extent.height,
					  GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

	return QGL_CHECK_ERROR;
}


bool glFramebuffer::BlitColorFromFramebuffer0(glOffset2D srcOffset, glOffset2D dstOffset, glExtent2D extent)
{
	QGL_CHECK_ERROR;

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_ResID);

	glBlitFramebuffer(srcOffset.x, srcOffset.y, srcOffset.x + extent.width, srcOffset.y + extent.height,
					  dstOffset.x, dstOffset.y, dstOffset.x + extent.width, dstOffset.y + extent.height,
					  GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	return QGL_CHECK_ERROR;
}


bool glFramebuffer::BlitColorToFramebuffer0(glOffset2D srcOffset, glOffset2D dstOffset, glExtent2D extent)
{
	QGL_CHECK_ERROR;

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_ResID);

	glBlitFramebuffer(srcOffset.x, srcOffset.y, srcOffset.x + extent.width, srcOffset.y + extent.height,
					  dstOffset.x, dstOffset.y, dstOffset.x + extent.width, dstOffset.y + extent.height,
					  GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

	return QGL_CHECK_ERROR;
}


void glFramebuffer::Reset()
{
	if (!this->IsCompleted())		return;

	glBindFramebuffer(GL_FRAMEBUFFER, m_ResID);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<GLenum>(glAttachmentSlot::eDepth), GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<GLenum>(glAttachmentSlot::eColor0), GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<GLenum>(glAttachmentSlot::eColor1), GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<GLenum>(glAttachmentSlot::eColor2), GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<GLenum>(glAttachmentSlot::eColor3), GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<GLenum>(glAttachmentSlot::eColor4), GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<GLenum>(glAttachmentSlot::eColor5), GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<GLenum>(glAttachmentSlot::eColor6), GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<GLenum>(glAttachmentSlot::eColor7), GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<GLenum>(glAttachmentSlot::eStencil), GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<GLenum>(glAttachmentSlot::eDepthStencil), GL_RENDERBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void glFramebuffer::Detach(glAttachmentSlot eSlot)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_ResID);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<GLenum>(eSlot), GL_RENDERBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


bool glFramebuffer::IsCompleted() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_ResID);

	bool result = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return result;
}


void glFramebuffer::SetClearMask(bool color, bool depth, bool stencil)
{
	m_ClearMask = 0;
	m_ClearMask |= GL_COLOR_BUFFER_BIT * static_cast<uint32_t>(color);
	m_ClearMask |= GL_DEPTH_BUFFER_BIT * static_cast<uint32_t>(depth);
	m_ClearMask |= GL_STENCIL_BUFFER_BIT * static_cast<uint32_t>(stencil);
}


void glFramebuffer::SetClearColor(float red, float green, float blue, float alpha)
{
	m_ClearColor[0] = red;
	m_ClearColor[1] = green;
	m_ClearColor[2] = blue;
	m_ClearColor[3] = alpha;
}


void glFramebuffer::SetClearDepth(double depth)
{
	m_ClearDepth = depth;
}


void glFramebuffer::SetClearStencil(int stencil)
{
	m_ClearStencil = stencil;
}


void glFramebuffer::BeginRenderPass()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_ResID);

	if (m_ClearMask & GL_COLOR_BUFFER_BIT)
	{
		glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
	}
	
	if (m_ClearMask & GL_DEPTH_BUFFER_BIT)
	{
		glClearDepth(m_ClearDepth);
	}

	if (m_ClearMask & GL_STENCIL_BUFFER_BIT)
	{
		glClearStencil(m_ClearStencil);
	}

	if (m_ClearMask != 0)
	{
		glClear(static_cast<GLbitfield>(m_ClearMask));
	}
}


void glFramebuffer::EndRenderPass()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


glFramebuffer::~glFramebuffer()
{
	glDeleteFramebuffers(1, &m_ResID);
}