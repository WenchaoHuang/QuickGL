/*************************************************************************
**************************    QuickGL_Window    **************************
*************************************************************************/
#include <GLFW/glfw3.h>
#include "Window.h"

using namespace QuickGL;

std::map<GLFWwindow*, glWindow*>			glWindow::sm_MapWindows;

std::map<std::thread::id, glWindow*>		glWindow::sm_MapContexts;

/*************************************************************************
*****************************    glWindow    *****************************
*************************************************************************/

static void ErrorReport(int errorCode, const char * pMessage)
{
	printf(" QuickGL_Error(%d): %s", errorCode, pMessage);
}

/*************************************************************************
*****************************    glWindow    *****************************
*************************************************************************/
glWindow::glWindow() : m_pUserEvent(nullptr), m_pGLFWwindow(nullptr), m_eSampleCount(glSampleCount::x1)
{

}


bool glWindow::Open(const char * pTitle, glOffset2D offset, glExtent2D extent, glSampleCount eSamples)
{
	if (m_pGLFWwindow != nullptr)		return false;

	glfwInit();
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, static_cast<int>(eSamples));
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_pGLFWwindow = glfwCreateWindow(extent.width, extent.height, pTitle, NULL, NULL);

	if (m_pGLFWwindow != nullptr)
	{
		m_eSampleCount = eSamples;

		sm_MapWindows[m_pGLFWwindow] = this;

		glfwSetErrorCallback(ErrorReport);
		glfwSetDropCallback(m_pGLFWwindow, FilesDropCallback);
		glfwSetKeyCallback(m_pGLFWwindow, KeyboardPressCallback);
		glfwSetScrollCallback(m_pGLFWwindow, WheelScrollCallback);
		glfwSetWindowPosCallback(m_pGLFWwindow, WindowMoveCallback);
		glfwSetCursorPosCallback(m_pGLFWwindow, CursorMoveCallback);
		glfwSetMouseButtonCallback(m_pGLFWwindow, MouseClickCallback);
		glfwSetWindowSizeCallback(m_pGLFWwindow, WindowResizeCallback);
		glfwSetWindowCloseCallback(m_pGLFWwindow, WindowCloseCallback);
		glfwSetCursorEnterCallback(m_pGLFWwindow, CursorEnterCallback);
		glfwSetWindowRefreshCallback(m_pGLFWwindow, WindowRefreshCallback);
		glfwSetFramebufferSizeCallback(m_pGLFWwindow, FramebufferResizeCallback);
		glfwSetWindowPos(m_pGLFWwindow, offset.x, offset.y);
	}

	return m_pGLFWwindow != nullptr;
}


void glWindow::RegisterUserEventCallback(UserEvent * pUserEvent)
{
	m_pUserEvent = pUserEvent;
}


bool glWindow::ShouldClose() const
{
	return glfwWindowShouldClose(m_pGLFWwindow) != 0;
}


void glWindow::SetTitle(const char * pTitle)
{
	glfwSetWindowTitle(m_pGLFWwindow, pTitle);
}


void glWindow::SetCursorPos(glOffset2D pos)
{
	glfwSetCursorPos(m_pGLFWwindow, static_cast<double>(pos.x), static_cast<double>(pos.y));
}


void glWindow::Resize(glExtent2D extent)
{
	glfwSetWindowSize(m_pGLFWwindow, extent.width, extent.height);
}


void glWindow::SetPos(glOffset2D pos)
{
	glfwSetWindowPos(m_pGLFWwindow, pos.x, pos.y);
}


void glWindow::MakeContextCurrent()
{
	if (m_pGLFWwindow != nullptr)
	{
		glfwMakeContextCurrent(m_pGLFWwindow);

		for (auto iter : sm_MapContexts)
		{
			if (iter.second == this)
			{
				sm_MapContexts.erase(iter.first);

				break;
			}
		}

		sm_MapContexts[std::this_thread::get_id()] = this;
	}
}


bool glWindow::HasContext() const
{
	if (sm_MapContexts.find(std::this_thread::get_id()) != sm_MapContexts.end())
	{
		return sm_MapContexts[std::this_thread::get_id()] == this;
	}

	return false;
}


void glWindow::SwapBuffers()
{
	glfwSwapBuffers(m_pGLFWwindow);
}


void glWindow::Maximize()
{
	glfwMaximizeWindow(m_pGLFWwindow);
}


void glWindow::Show()
{
	glfwShowWindow(m_pGLFWwindow);
}


void glWindow::Hide()
{
	glfwHideWindow(m_pGLFWwindow);
}


glExtent2D glWindow::Extent() const
{
	glExtent2D extent;

	glfwGetWindowSize(m_pGLFWwindow, reinterpret_cast<int*>(&extent.width), reinterpret_cast<int*>(&extent.height));

	return extent;
}


glExtent2D glWindow::FramebufferExtent() const
{
	glExtent2D extent;

	glfwGetFramebufferSize(m_pGLFWwindow, reinterpret_cast<int*>(&extent.width), reinterpret_cast<int*>(&extent.height));

	return extent;
}


void glWindow::SetVsync(bool isVsync)
{
	glfwSwapInterval(static_cast<int>(isVsync));
}


void glWindow::PollEvents()
{
	glfwPollEvents();
}


void glWindow::Close()
{
	if (m_pGLFWwindow != nullptr)
	{
		glfwDestroyWindow(m_pGLFWwindow);

		sm_MapWindows.erase(m_pGLFWwindow);

		m_eSampleCount = glSampleCount::x1;

		m_pGLFWwindow = nullptr;
	}
}


glWindow::~glWindow()
{
	this->Close();
}