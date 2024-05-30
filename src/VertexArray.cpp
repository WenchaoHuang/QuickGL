/*************************************************************************
***********************    QuickGL_VertexArray    ************************
*************************************************************************/
#include "VertexArray.h"
#include "Internal.h"
#include "Buffer.h"

/*************************************************************************
**************************    glVertexArray    ***************************
*************************************************************************/
glVertexArray::glVertexArray()
{
	glGenVertexArrays(1, &m_ResID);
}


void glVertexArray::DrawArrays(glPrimitiveTopology eTopology, uint32_t count, uint32_t first) const
{
	glBindVertexArray(m_ResID);

	glDrawArrays(static_cast<GLenum>(eTopology), first, count);

	glBindVertexArray(0);
}


void glVertexArray::DrawElements(glPrimitiveTopology eTopology, uint32_t count, size_t offset) const
{
	glBindVertexArray(m_ResID);

	glDrawElements(static_cast<GLenum>(eTopology), count, GL_UNSIGNED_INT, (const void*)offset);

	glBindVertexArray(0);
}


void glVertexArray::SetAttrib1fp(uint32_t binding, const glBuffer * pBuffer, uint32_t stride, size_t offset)
{
	glBindVertexArray(m_ResID);

	glBindBuffer(GL_ARRAY_BUFFER, *pBuffer);

	glVertexAttribPointer(binding, 1, GL_FLOAT, GL_FALSE, stride, (const void*)offset);

	glEnableVertexAttribArray(binding);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}


void glVertexArray::SetAttrib2fp(uint32_t binding, const glBuffer * pBuffer, uint32_t stride, size_t offset)
{
	glBindVertexArray(m_ResID);

	glBindBuffer(GL_ARRAY_BUFFER, *pBuffer);

	glVertexAttribPointer(binding, 2, GL_FLOAT, GL_FALSE, stride, (const void*)offset);

	glEnableVertexAttribArray(binding);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}


void glVertexArray::SetAttrib3fp(uint32_t binding, const glBuffer * pBuffer, uint32_t stride, size_t offset)
{
	glBindVertexArray(m_ResID);

	glBindBuffer(GL_ARRAY_BUFFER, *pBuffer);

	glVertexAttribPointer(binding, 3, GL_FLOAT, GL_FALSE, stride, (const void*)offset);

	glEnableVertexAttribArray(binding);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}


void glVertexArray::SetAttrib4fp(uint32_t binding, const glBuffer * pBuffer, uint32_t stride, size_t offset)
{
	glBindVertexArray(m_ResID);

	glBindBuffer(GL_ARRAY_BUFFER, *pBuffer);

	glVertexAttribPointer(binding, 4, GL_FLOAT, GL_FALSE, stride, (const void*)offset);

	glEnableVertexAttribArray(binding);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}


void glVertexArray::SetAttrib4f(uint32_t binding, float v0, float v1, float v2, float v3)
{
	glBindVertexArray(m_ResID);

	glVertexAttrib4f(binding, v0, v1, v2, v3);

	glBindVertexArray(0);
}


void glVertexArray::SetAttrib3f(uint32_t binding, float v0, float v1, float v2)
{
	glBindVertexArray(m_ResID);

	glVertexAttrib3f(binding, v0, v1, v2);

	glBindVertexArray(0);
}


void glVertexArray::SetAttrib2f(uint32_t binding, float v0, float v1)
{
	glBindVertexArray(m_ResID);

	glVertexAttrib2f(binding, v0, v1);

	glBindVertexArray(0);
}


void glVertexArray::SetAttrib1f(uint32_t binding, float v0)
{
	glBindVertexArray(m_ResID);

	glVertexAttrib1f(binding, v0);
	
	glBindVertexArray(0);
}


void glVertexArray::SetIndexAttrib(const glBuffer * pBuffer)
{
	glBindVertexArray(m_ResID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *pBuffer);

	glBindVertexArray(0);
}


void glVertexArray::DisableAttrib(uint32_t binding)
{
	glBindVertexArray(m_ResID);

	glDisableVertexAttribArray(binding);

	glBindVertexArray(0);
}


void glVertexArray::EnableAttrib(uint32_t binding)
{
	glBindVertexArray(m_ResID);

	glEnableVertexAttribArray(binding);

	glBindVertexArray(0);
}


glVertexArray::~glVertexArray()
{
	glDeleteVertexArrays(1, &m_ResID);
}