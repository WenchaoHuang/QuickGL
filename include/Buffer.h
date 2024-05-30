/*************************************************************************
**************************    QuickGL_Buffer    **************************
*************************************************************************/
#pragma once

#include <vector>
#include "Resource.h"

namespace QuickGL
{
	/*********************************************************************
	************************    glBufferUsage    *************************
	*********************************************************************/

	/**
	 *	@brief	Usage types of OpenGL buffer.
	 *
	 *	@note	STREAM	- The data store contents will be modified once and used at most a few times.
	 *	@note	STATIC	- The data store contents will be modified once and used many times.
	 *	@note	DYNAMIC - The data store contents will be modified repeatedly and used many times.
	 *
	 *	@note	DRAW	- The data store contents will be modified repeatedly and used many times.
	 *	@note	READ	- The data store contents are modified by reading data from the GL, and used to return that data when queried by the application.
	 *	@note	COPY	- The data store contents are modified by reading data from the GL, and used as the source for GL drawing and image specification commands.
	 */
	enum class glBufferUsage : uint32_t
	{
		eStreamDraw		= 0x88E0,		//!	@brief	GL_STREAM_DRAW
		eStreamRead		= 0x88E1,		//!	@brief	GL_STREAM_READ
		eStreamCopy		= 0x88E2,		//!	@brief	GL_STREAM_COPY

		eStaticDraw		= 0x88E4,		//!	@brief	GL_STATIC_DRAW
		eStaticRead		= 0x88E5,		//!	@brief	GL_STATIC_READ
		eStaticCopy		= 0x88E6,		//!	@brief	GL_STATIC_COPY

		eDynamicDraw	= 0x88E8,		//!	@brief	GL_DYNAMIC_DRAW
		eDynamicRead	= 0x88E9,		//!	@brief	GL_DYNAMIC_READ
		eDynamicCopy	= 0x88EA		//!	@brief	GL_DYNAMIC_COPY
	};

	/*********************************************************************
	***************************    glBuffer    ***************************
	*********************************************************************/

	/**
	 *	@brief	OpenGL buffer object.
	 */
	class QGLAPI glBuffer : public glResource
	{

	public:

		//!	@brief	Create buffer object.
		glBuffer();

		//!	@brief	Destroy buffer object.
		~glBuffer();

	public:

		//!	@brief	Create and initialize buffer object's data store.
		bool Allocate(size_t bytes, const void * pData = nullptr, glBufferUsage eUsage = glBufferUsage::eStaticDraw);

		//!	@brief	Copy all or part of the data store of a buffer object to the data store of another buffer object.
		bool CopyFrom(const glBuffer * pSrcBuffer, size_t srcOffset, size_t dstOffset, size_t bytes);

		//!	@brief	Update a subset of a buffer object's data store.
		bool Write(const void * pSrc, size_t offset, size_t bytes);

		//!	@brief	Return a subset of a buffer object's data store.
		bool Read(void * pDst, size_t offset, size_t bytes);

		//!	@brief	If buffer store is empty.
		bool IsEmpty() const { return m_Bytes == 0; }

		//!	@brief	Return size of buffer in bytes.
		size_t Bytes() const { return m_Bytes; }

		//!	@brief	Free data store.
		void Free();

	private:

		size_t		m_Bytes;
	};

	/*********************************************************************
	***************************    glArray    ****************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for OpenGL buffer object.
	 */
	template<typename Type> class glArray : public glBuffer
	{

	public:

		//!	@brief	Size type.
		using size_type = unsigned int;

		//!	@brief	Create and initialize buffer object's data store.
		void Upload(const std::vector<Type> & HostData, glBufferUsage eUsage = glBufferUsage::eStaticDraw)
		{
			glBuffer::Allocate(sizeof(Type) * HostData.size(), HostData.data(), eUsage);
		}

		//!	@brief	Create and initialize buffer object's data store.
		void Resize(size_t count, const Type * pData = nullptr, glBufferUsage eUsage = glBufferUsage::eStaticDraw)
		{
			glBuffer::Allocate(sizeof(Type) * count, pData, eUsage);
		}

		//!	@brief	Copy all or part of the data store of a buffer object to the data store of another buffer object.
		bool CopyFrom(const glArray * pSrcArray, size_type srcOffset, size_type dstOffset, size_type bytes)
		{
			return glBuffer::CopyFrom(pSrcArray, sizeof(Type) * srcOffset, sizeof(Type) * dstOffset, sizeof(Type) * bytes);
		}

		//!	@brief	Updates a subset of a buffer object's data store.
		bool Write(const Type * pSrc, size_type offset, size_type count)
		{
			return glBuffer::Write(pSrc, sizeof(Type) * offset, sizeof(Type) * count);
		}

		//!	@brief	Returns a subset of a buffer object's data store.
		bool Read(Type * pDst, size_type offset, size_type count)
		{
			return glBuffer::Read(pDst, sizeof(Type) * offset, sizeof(Type) * count);
		}

		//!	@brief	Return element count of array.
		size_type Size() const { return glBuffer::Bytes() / sizeof(Type); }

		//!	@brief	Free data store.
		void Clear() { glBuffer::Free(); }

	private:

		using glBuffer::Allocate;
		using glBuffer::CopyFrom;
		using glBuffer::Write;
		using glBuffer::Read;
		using glBuffer::Free;
	};
}