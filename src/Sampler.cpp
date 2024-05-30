/*************************************************************************
*************************    QuickGL_Sampler    **************************
*************************************************************************/
#include "Internal.h"
#include "Sampler.h"

/*************************************************************************
****************************    glSampler    *****************************
*************************************************************************/
glSampler::glSampler()
{
	glGenSamplers(1, &m_ResID);
}


void glSampler::SetMinLod(float minLod)
{
	glSamplerParameterf(m_ResID, GL_TEXTURE_MIN_LOD, minLod);
}


void glSampler::SetMaxLod(float maxLod)
{
	glSamplerParameterf(m_ResID, GL_TEXTURE_MAX_LOD, maxLod);
}


void glSampler::SetMinLodBias(float minLodBias)
{
	glSamplerParameterf(m_ResID, GL_TEXTURE_LOD_BIAS, minLodBias);
}


void glSampler::SetWrapS(glWrapMode eWrapS)
{
	glSamplerParameteri(m_ResID, GL_TEXTURE_WRAP_S, static_cast<GLint>(eWrapS));
}


void glSampler::SetWrapT(glWrapMode eWrapT)
{
	glSamplerParameteri(m_ResID, GL_TEXTURE_WRAP_T, static_cast<GLint>(eWrapT));
}


void glSampler::SetWrapR(glWrapMode eWrapR)
{
	glSamplerParameteri(m_ResID, GL_TEXTURE_WRAP_R, static_cast<GLint>(eWrapR));
}


void glSampler::SetMagFilter(glFilter eMagFilter)
{
	glSamplerParameteri(m_ResID, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(eMagFilter));
}


void glSampler::SetMinFilter(glFilter eMinFilter)
{
	GLint minFilter = 0;

	glGetSamplerParameteriv(m_ResID, GL_TEXTURE_MIN_FILTER, &minFilter);

	if (eMinFilter == glFilter::eLinear)
	{
		if (minFilter == GL_NEAREST)
		{
			glSamplerParameteri(m_ResID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		else if (minFilter == GL_LINEAR_MIPMAP_NEAREST)
		{
			glSamplerParameteri(m_ResID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else if (minFilter == GL_NEAREST_MIPMAP_NEAREST)
		{
			glSamplerParameteri(m_ResID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		}
	}
	else if (eMinFilter == glFilter::eNearest)
	{
		if (minFilter == GL_LINEAR)
		{
			glSamplerParameteri(m_ResID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
		else if (minFilter == GL_LINEAR_MIPMAP_LINEAR)
		{
			glSamplerParameteri(m_ResID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		}
		else if (minFilter == GL_NEAREST_MIPMAP_LINEAR)
		{
			glSamplerParameteri(m_ResID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		}
	}
}


void glSampler::SetMipmapMode(glMipmapMode eMipmapMode)
{
	GLint minFilter = 0;

	glGetSamplerParameteriv(m_ResID, GL_TEXTURE_MIN_FILTER, &minFilter);

	if (eMipmapMode == glMipmapMode::eNone)
	{
		if ((minFilter == GL_LINEAR_MIPMAP_LINEAR) || (minFilter == GL_NEAREST_MIPMAP_LINEAR))
		{
			glSamplerParameteri(m_ResID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		else if ((minFilter == GL_LINEAR_MIPMAP_NEAREST) || (minFilter == GL_NEAREST_MIPMAP_NEAREST))
		{
			glSamplerParameteri(m_ResID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
	}
	else if (eMipmapMode == glMipmapMode::eLinear)
	{
		if ((minFilter == GL_LINEAR) || (minFilter == GL_NEAREST_MIPMAP_LINEAR))
		{
			glSamplerParameteri(m_ResID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else if ((minFilter == GL_NEAREST) || (minFilter == GL_NEAREST_MIPMAP_NEAREST))
		{
			glSamplerParameteri(m_ResID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		}
	}
	else if (eMipmapMode == glMipmapMode::eNearest)
	{
		if ((minFilter == GL_LINEAR) || (minFilter == GL_LINEAR_MIPMAP_LINEAR))
		{
			glSamplerParameteri(m_ResID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		}
		else if ((minFilter == GL_NEAREST) || (minFilter == GL_LINEAR_MIPMAP_NEAREST))
		{
			glSamplerParameteri(m_ResID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		}
	}
}


glFilter glSampler::GetMinFilter() const
{
	GLint minFilter = 0;

	glGetSamplerParameteriv(m_ResID, GL_TEXTURE_MIN_FILTER, &minFilter);
	
	if ((minFilter == GL_NEAREST) || (GL_LINEAR_MIPMAP_NEAREST) || (GL_NEAREST_MIPMAP_NEAREST))
	{
		return glFilter::eNearest;
	}

	return glFilter::eLinear;
}


glMipmapMode glSampler::GetMipmapMode() const
{
	GLint minFilter = 0;

	glGetSamplerParameteriv(m_ResID, GL_TEXTURE_MIN_FILTER, &minFilter);

	if ((minFilter == GL_LINEAR_MIPMAP_LINEAR) || (minFilter == GL_LINEAR_MIPMAP_NEAREST))
	{
		return glMipmapMode::eLinear;
	}
	else if ((minFilter == GL_NEAREST_MIPMAP_LINEAR) || (minFilter == GL_NEAREST_MIPMAP_NEAREST))
	{
		return glMipmapMode::eNearest;
	}
	
	return glMipmapMode::eNone;
}


glFilter glSampler::GetMagFilter() const
{
	glFilter eMagFilter = glFilter::eLinear;

	glGetSamplerParameteriv(m_ResID, GL_TEXTURE_MAG_FILTER, reinterpret_cast<GLint*>(&eMagFilter));

	return eMagFilter;
}


glWrapMode glSampler::GetWrapS() const
{
	glWrapMode eWrapS = glWrapMode::eRepeat;

	glGetSamplerParameteriv(m_ResID, GL_TEXTURE_WRAP_S, reinterpret_cast<GLint*>(&eWrapS));

	return eWrapS;
}


glWrapMode glSampler::GetWrapT() const
{
	glWrapMode eWrapT = glWrapMode::eRepeat;

	glGetSamplerParameteriv(m_ResID, GL_TEXTURE_WRAP_T, reinterpret_cast<GLint*>(&eWrapT));

	return eWrapT;
}


glWrapMode glSampler::GetWrapR() const
{
	glWrapMode eWrapR = glWrapMode::eRepeat;

	glGetSamplerParameteriv(m_ResID, GL_TEXTURE_WRAP_R, reinterpret_cast<GLint*>(&eWrapR));

	return eWrapR;
}


float glSampler::GetMinLodBias() const
{
	float minLodBias = 0.0f;

	glGetSamplerParameterfv(m_ResID, GL_TEXTURE_LOD_BIAS, &minLodBias);

	return minLodBias;
}


float glSampler::GetMinLod() const
{
	float minLod = 0.0f;

	glGetSamplerParameterfv(m_ResID, GL_TEXTURE_MIN_LOD, &minLod);

	return minLod;
}


float glSampler::GetMaxLod() const
{
	float maxLod = 0.0f;
	
	glGetSamplerParameterfv(m_ResID, GL_TEXTURE_MAX_LOD, &maxLod);
	
	return maxLod;
}


glSampler::~glSampler()
{
	glDeleteSamplers(1, &m_ResID);
}