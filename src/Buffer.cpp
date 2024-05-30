/*************************************************************************
**************************    QuickGL_Buffer    **************************
*************************************************************************/
#include "Internal.h"
#include "Buffer.h"

/*************************************************************************
*****************************    glBuffer    *****************************
*************************************************************************/
glBuffer::glBuffer() : m_Bytes(0)
{
	glGenBuffers(1, &m_ResID);
}


bool glBuffer::Allocate(size_t bytes, const void * pData, glBufferUsage eUsage)
{
	QGL_CHECK_ERROR;

	glBindBuffer(GL_ARRAY_BUFFER, m_ResID);

	glBufferData(GL_ARRAY_BUFFER, bytes, pData, static_cast<GLenum>(eUsage));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (QGL_CHECK_ERROR == true)
	{
		m_Bytes = bytes;

		return true;
	}

	return false;
}


bool glBuffer::Write(const void * pSrc, size_t offset, size_t bytes)
{
	QGL_CHECK_ERROR;

	glBindBuffer(GL_ARRAY_BUFFER, m_ResID);

	glBufferSubData(GL_ARRAY_BUFFER, offset, bytes, pSrc);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return QGL_CHECK_ERROR;
}


bool glBuffer::Read(void * pDst, size_t offset, size_t bytes)
{
	QGL_CHECK_ERROR;

	glBindBuffer(GL_ARRAY_BUFFER, m_ResID);

	glGetBufferSubData(GL_ARRAY_BUFFER, offset, bytes, pDst);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return QGL_CHECK_ERROR;
}


bool glBuffer::CopyFrom(const glBuffer * pSrcBuffer, size_t srcOffset, size_t dstOffset, size_t bytes)
{
	QGL_CHECK_ERROR;

	glBindBuffer(GL_COPY_WRITE_BUFFER, m_ResID);

	glBindBuffer(GL_COPY_READ_BUFFER, pSrcBuffer->m_ResID);

	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, srcOffset, dstOffset, bytes);

	glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

	glBindBuffer(GL_COPY_READ_BUFFER, 0);

	return QGL_CHECK_ERROR;
}


void glBuffer::Free()
{
	if (m_Bytes != 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ResID);

		glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_Bytes = 0;
	}
}


glBuffer::~glBuffer()
{
	glDeleteBuffers(1, &m_ResID);
}