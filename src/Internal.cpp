/*************************************************************************
*************************    QuickGL_Internal    *************************
*************************************************************************/
#include <GLAD/glad.c>
#include "Internal.h"
#include "Common.h"

/*************************************************************************
**************************    QuickGL_LoadGL    **************************
*************************************************************************/
bool QuickGL::LoadGL()
{
	static bool s_isLoaded = false;

	if (s_isLoaded == false)
	{
		s_isLoaded = gladLoadGL() != 0;
	}

	return s_isLoaded;
}