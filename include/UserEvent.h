/*************************************************************************
************************    QuickGL_UserEvent    *************************
*************************************************************************/
#pragma once

#include "Common.h"

namespace QuickGL
{
	/*********************************************************************
	***************************    Modifier    ***************************
	*********************************************************************/

	/**
	 *	@brief	Modifier tags.
	 */
	enum Modifier : int
	{
		QGL_MOD_ALT			= 0x0004,
		QGL_MOD_SHIFT		= 0x0001,
		QGL_MOD_SUPER		= 0x0008,
		QGL_MOD_CONTROL		= 0x0002,
	};

	/*********************************************************************
	**************************    ActionType    **************************
	*********************************************************************/

	/**
	 *	@brief	Action types.
	 */
	enum Action : int
	{
		QGL_ACTION_PRESS		= 0x0001,
		QGL_ACTION_REPEAT		= 0x0002,
		QGL_ACTION_RELEASE		= 0x0000
	};

	/*********************************************************************
	*************************    MouseButton    **************************
	*********************************************************************/

	/**
	 *	@brief	Mouse buttons.
	 */
	enum MouseButton : int
	{
		QGL_MOUSE_BUTTON_LEFT		= 0x0000,
		QGL_MOUSE_BUTTON_RIGHT		= 0x0001,
		QGL_MOUSE_BUTTON_MIDDLE		= 0x0002,
	};

	/*********************************************************************
	*****************************    Key    ******************************
	*********************************************************************/

	/**
	 *	@brief	Tags of key.
	 */
	enum Key : int
	{
		QGL_KEY_UNKNOWN			= -1,

		/* Printable keys */
		QGL_KEY_SPACE			= 32,
		QGL_KEY_APOSTROPHE		= 39,	/* ' */
		QGL_KEY_COMMA			= 44,	/* , */
		QGL_KEY_MINUS			= 45,	/* - */
		QGL_KEY_PERIOD			= 46,	/* . */
		QGL_KEY_SLASH			= 47,	/* / */
		QGL_KEY_0				= 48,
		QGL_KEY_1				= 49,
		QGL_KEY_2				= 50,
		QGL_KEY_3				= 51,
		QGL_KEY_4				= 52,
		QGL_KEY_5				= 53,
		QGL_KEY_6				= 54,
		QGL_KEY_7				= 55,
		QGL_KEY_8				= 56,
		QGL_KEY_9				= 57,
		QGL_KEY_SEMICOLON		= 59,	/* ; */
		QGL_KEY_EQUAL			= 61,	/* = */
		QGL_KEY_A				= 65,
		QGL_KEY_B				= 66,
		QGL_KEY_C				= 67,
		QGL_KEY_D				= 68,
		QGL_KEY_E				= 69,
		QGL_KEY_F				= 70,
		QGL_KEY_G				= 71,
		QGL_KEY_H				= 72,
		QGL_KEY_I				= 73,
		QGL_KEY_J				= 74,
		QGL_KEY_K				= 75,
		QGL_KEY_L				= 76,
		QGL_KEY_M				= 77,
		QGL_KEY_N				= 78,
		QGL_KEY_O				= 79,
		QGL_KEY_P				= 80,
		QGL_KEY_Q				= 81,
		QGL_KEY_R				= 82,
		QGL_KEY_S				= 83,
		QGL_KEY_T				= 84,
		QGL_KEY_U				= 85,
		QGL_KEY_V				= 86,
		QGL_KEY_W				= 87,
		QGL_KEY_X				= 88,
		QGL_KEY_Y				= 89,
		QGL_KEY_Z				= 90,
		QGL_KEY_LEFT_BRACKET	= 91,	/* [ */
		QGL_KEY_BACKSLASH		= 92,	/* \ */
		QGL_KEY_RIGHT_BRACKET	= 93,	/* ] */
		QGL_KEY_GRAVE_ACCENT	= 96,	/* ` */
		QGL_KEY_WORLD_1			= 161,	/* non-US #1 */
		QGL_KEY_WORLD_2			= 162,	/* non-US #2 */

		/* Function keys */
		QGL_KEY_ESCAPE			= 256,
		QGL_KEY_ENTER			= 257,
		QGL_KEY_TAB				= 258,
		QGL_KEY_BACKSPACE		= 259,
		QGL_KEY_INSERT			= 260,
		QGL_KEY_DELETE			= 261,
		QGL_KEY_RIGHT			= 262,
		QGL_KEY_LEFT			= 263,
		QGL_KEY_DOWN			= 264,
		QGL_KEY_UP				= 265,
		QGL_KEY_PAGE_UP			= 266,
		QGL_KEY_PAGE_DOWN		= 267,
		QGL_KEY_HOME			= 268,
		QGL_KEY_END				= 269,
		QGL_KEY_CAPS_LOCK		= 280,
		QGL_KEY_SCROLL_LOCK		= 281,
		QGL_KEY_NUM_LOCK		= 282,
		QGL_KEY_PRINT_SCREEN	= 283,
		QGL_KEY_PAUSE			= 284,
		QGL_KEY_F1				= 290,
		QGL_KEY_F2				= 291,
		QGL_KEY_F3				= 292,
		QGL_KEY_F4				= 293,
		QGL_KEY_F5				= 294,
		QGL_KEY_F6				= 295,
		QGL_KEY_F7				= 296,
		QGL_KEY_F8				= 297,
		QGL_KEY_F9				= 298,
		QGL_KEY_F10				= 299,
		QGL_KEY_F11				= 300,
		QGL_KEY_F12				= 301,
		QGL_KEY_F13				= 302,
		QGL_KEY_F14				= 303,
		QGL_KEY_F15				= 304,
		QGL_KEY_F16				= 305,
		QGL_KEY_F17				= 306,
		QGL_KEY_F18				= 307,
		QGL_KEY_F19				= 308,
		QGL_KEY_F20				= 309,
		QGL_KEY_F21				= 310,
		QGL_KEY_F22				= 311,
		QGL_KEY_F23				= 312,
		QGL_KEY_F24				= 313,
		QGL_KEY_F25				= 314,
		QGL_KEY_KP_0			= 320,
		QGL_KEY_KP_1			= 321,
		QGL_KEY_KP_2			= 322,
		QGL_KEY_KP_3			= 323,
		QGL_KEY_KP_4			= 324,
		QGL_KEY_KP_5			= 325,
		QGL_KEY_KP_6			= 326,
		QGL_KEY_KP_7			= 327,
		QGL_KEY_KP_8			= 328,
		QGL_KEY_KP_9			= 329,
		QGL_KEY_KP_DECIMAL		= 330,
		QGL_KEY_KP_DIVIDE		= 331,
		QGL_KEY_KP_MULTIPLY		= 332,
		QGL_KEY_KP_SUBTRACT		= 333,
		QGL_KEY_KP_ADD			= 334,
		QGL_KEY_KP_ENTER		= 335,
		QGL_KEY_KP_EQUAL		= 336,
		QGL_KEY_LEFT_SHIFT		= 340,
		QGL_KEY_LEFT_CONTROL	= 341,
		QGL_KEY_LEFT_ALT		= 342,
		QGL_KEY_LEFT_SUPER		= 343,
		QGL_KEY_RIGHT_SHIFT		= 344,
		QGL_KEY_RIGHT_CONTROL	= 345,
		QGL_KEY_RIGHT_ALT		= 346,
		QGL_KEY_RIGHT_SUPER		= 347,
		QGL_KEY_MENU			= 348
	};

	/*********************************************************************
	**************************    UserEvent    ***************************
	*********************************************************************/

	/**
	 *	@brief	Description of user events.
	 */
	class QGLAPI UserEvent
	{

	public:

		//!	@brief	Called when the cursor enters the client area of the window.
		virtual void CursorEnter() {}

		//!	@brief	Called when the cursor leaves the client area of the window.
		virtual void CursorLeave() {}

		//!	@brief	Called when the user attempts to close the window.
		virtual void WindowClose() {}

		//!	@brief	Called when the client area of the window needs to be redrawn.
		virtual void WindowRefresh() {}

		//!	@brief	Called when the window is moved.
		virtual void WindowMove([[maybe_unused]] int posX, [[maybe_unused]] int posY) {}

		//!	@brief	Called when the cursor is moved.
		virtual void CursorMove([[maybe_unused]] int posX, [[maybe_unused]] int posY) {}

		//!	@brief	Called when the window is resized.
		virtual void WindowResize([[maybe_unused]] int width, [[maybe_unused]] int height) {}

		//!	@brief	Called when a scrolling device is used, such as mouse wheel or scrolling area of touchpad.
		virtual void WheelScroll([[maybe_unused]] int offsetX, [[maybe_unused]] int offsetY) {}

		//!	@brief	Called when the framebuffer is resized.
		virtual void FramebufferResize([[maybe_unused]] int width, [[maybe_unused]] int height) {}

		//!	@brief	Called when one or more dragged files are dropped on the window.
		virtual void FilesDrop([[maybe_unused]] int count, [[maybe_unused]] const char ** pPaths) {}

		//!	@brief	Called when a key is pressed, repeated or released.
		virtual void KeyboardPress([[maybe_unused]] Key eKey, [[maybe_unused]] Action eAction, [[maybe_unused]] Modifier eModifier) {}

		//!	@brief	Called when a mouse button is pressed or released.
		virtual void MouseClick([[maybe_unused]] MouseButton eButton, [[maybe_unused]] Action eAction, [[maybe_unused]] Modifier eModifier) {}
	};
}