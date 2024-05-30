/*************************************************************************
************************    QuickGL_UserEvent    *************************
*************************************************************************/
#include "UserEvent.h"
#include "Window.h"

using namespace QuickGL;

/*************************************************************************
*****************************    glWindow    *****************************
*************************************************************************/

void glWindow::KeyboardPressCallback(GLFWwindow * pWindow, int eKey, int scancode, int eAction, int eMods)
{
	if (sm_MapWindows[pWindow]->m_pUserEvent != nullptr)
	{
		sm_MapWindows[pWindow]->m_pUserEvent->KeyboardPress(static_cast<Key>(eKey), static_cast<Action>(eAction), static_cast<Modifier>(eMods));
	}
}


void glWindow::WheelScrollCallback(GLFWwindow * pWindow, double offsetX, double offsetY)
{
	if (sm_MapWindows[pWindow]->m_pUserEvent != nullptr)
	{
		sm_MapWindows[pWindow]->m_pUserEvent->WheelScroll(static_cast<int>(offsetX), static_cast<int>(offsetY));
	}
}


void glWindow::MouseClickCallback(GLFWwindow * pWindow, int eButton, int eAction, int eMods)
{
	if (sm_MapWindows[pWindow]->m_pUserEvent != nullptr)
	{
		sm_MapWindows[pWindow]->m_pUserEvent->MouseClick(static_cast<MouseButton>(eButton), static_cast<Action>(eAction), static_cast<Modifier>(eMods));
	}
}


void glWindow::FilesDropCallback(GLFWwindow * pWindow, int count, const char ** pPaths)
{
	if (sm_MapWindows[pWindow]->m_pUserEvent != nullptr)
	{
		sm_MapWindows[pWindow]->m_pUserEvent->FilesDrop(count, pPaths);
	}
}


void glWindow::CursorMoveCallback(GLFWwindow * pWindow, double posX, double posY)
{
	if (sm_MapWindows[pWindow]->m_pUserEvent != nullptr)
	{
		sm_MapWindows[pWindow]->m_pUserEvent->CursorMove(static_cast<int>(posX), static_cast<int>(posY));
	}
}


void glWindow::FramebufferResizeCallback(GLFWwindow * pWindow, int width, int height)
{
	if (sm_MapWindows[pWindow]->m_pUserEvent != nullptr)
	{
		sm_MapWindows[pWindow]->m_pUserEvent->FramebufferResize(width, height);
	}
}


void glWindow::WindowResizeCallback(GLFWwindow * pWindow, int width, int height)
{
	if (sm_MapWindows[pWindow]->m_pUserEvent != nullptr)
	{
		sm_MapWindows[pWindow]->m_pUserEvent->WindowResize(width, height);
	}
}


void glWindow::WindowMoveCallback(GLFWwindow * pWindow, int posX, int posY)
{
	if (sm_MapWindows[pWindow]->m_pUserEvent != nullptr)
	{
		sm_MapWindows[pWindow]->m_pUserEvent->WindowMove(posX, posY);
	}
}


void glWindow::CursorEnterCallback(GLFWwindow * pWindow, int isTrue)
{
	if (sm_MapWindows[pWindow]->m_pUserEvent != nullptr)
	{
		if (isTrue == 0)
		{
			sm_MapWindows[pWindow]->m_pUserEvent->CursorLeave();
		}
		else
		{
			sm_MapWindows[pWindow]->m_pUserEvent->CursorEnter();
		}
	}
}


void glWindow::WindowRefreshCallback(GLFWwindow * pWindow)
{
	if (sm_MapWindows[pWindow]->m_pUserEvent != nullptr)
	{
		sm_MapWindows[pWindow]->m_pUserEvent->WindowRefresh();
	}
}


void glWindow::WindowCloseCallback(GLFWwindow * pWindow)
{
	if (sm_MapWindows[pWindow]->m_pUserEvent != nullptr)
	{
		sm_MapWindows[pWindow]->m_pUserEvent->WindowClose();
	}
}