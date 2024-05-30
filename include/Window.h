/*************************************************************************
**************************    QuickGL_Window    **************************
*************************************************************************/
#pragma once

#include <map>
#include <thread>
#include "Common.h"

struct GLFWwindow;

namespace QuickGL
{
	class UserEvent;

	/*********************************************************************
	***************************    glWindow    ***************************
	*********************************************************************/

	/**
	 *	@brief		Win32 window object contains OpenGL context.
	 */
	class QGLAPI glWindow
	{

	public:

		//!	@brief	Create win32 window object.
		glWindow();

		//!	@brief	Win32 window is noncopyable.
		glWindow(const glWindow&) = delete;

		//!	@brief	Win32 window is nonassignable.
		void operator=(const glWindow&) = delete;

		//!	@brief	Destroy win32 window object.
		~glWindow();

	public:

		//!	@brief	Process all pending events.
		static void PollEvents();

		//!	@brief	Set synchronization for the current context.
		static void SetVsync(bool isVsync);

	public:

		//!	@brief	Return window extent.
		glExtent2D Extent() const;

		//!	@brief	Return framebuffer extent.
		glExtent2D FramebufferExtent() const;

		//!	@brief	Open a Win32 window.
		bool Open(const char * pTitle, glOffset2D offset, glExtent2D extent, glSampleCount eSamples = glSampleCount::x1);

		//!	@brief	Register user event callback.
		void RegisterUserEventCallback(UserEvent * pUserEvent);

		//!	@brief	Set the title of this window.
		void SetTitle(const char * pTitle);

		//!	@brief	Set the position of the cursor, relative to the client area of the window.
		void SetCursorPos(glOffset2D pos);

		//!	@brief	Set the size of the client area of this window.
		void Resize(glExtent2D extent);

		//!	@brief	Set the position of the client area of this window.
		void SetPos(glOffset2D pos);

		//!	@brief	Make the context of this window current for the calling thread.
		void MakeContextCurrent();

		//!	@brief	If the calling thread has the OpenGL context.
		bool HasContext() const;

		//!	@brief	Check the close flag of this window.
		bool ShouldClose() const;

		//!	@brief	Swap the front and back buffers of this window.
		void SwapBuffers();

		//!	@brief	Maximizes this window.
		void Maximize();

		//!	@brief	Make this window visible.
		void Show();

		//!	@brief	Hide this window.
		void Hide();

		//!	@brief	Close this window.
		void Close();

	private:

		//!	@brief	Default user event callbacks.
		static void WindowCloseCallback(GLFWwindow * pWindow);
		static void WindowRefreshCallback(GLFWwindow * pWindow);
		static void CursorEnterCallback(GLFWwindow * pWindow, int isTrue);
		static void WindowMoveCallback(GLFWwindow * pWindow, int posX, int posY);
		static void WindowResizeCallback(GLFWwindow * pWindow, int width, int height);
		static void CursorMoveCallback(GLFWwindow * pWindow, double posX, double posY);
		static void FramebufferResizeCallback(GLFWwindow * pWindow, int width, int height);
		static void FilesDropCallback(GLFWwindow * pWindow, int count, const char ** pPaths);
		static void WheelScrollCallback(GLFWwindow * pWindow, double offsetX, double offsetY);
		static void MouseClickCallback(GLFWwindow * pWindow, int eButton, int eAction, int eMods);
		static void KeyboardPressCallback(GLFWwindow * pWindow, int eKey, int Scancode, int eAction, int eMods);

	private:

		UserEvent *										m_pUserEvent;

		GLFWwindow *									m_pGLFWwindow;

		glSampleCount									m_eSampleCount;

		static std::map<GLFWwindow*, glWindow*>			sm_MapWindows;

		static std::map<std::thread::id, glWindow*>		sm_MapContexts;
	};
}