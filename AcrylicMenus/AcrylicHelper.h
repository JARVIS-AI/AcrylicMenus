#pragma once
#include "pch.h"
#include "SystemHelper.h"
#include "AppearanceConfiguration.h"

namespace AcrylicMenus
{
namespace AcrylicHelper
{
	typedef enum _WINDOWCOMPOSITIONATTRIBUTE
	{
		WCA_UNDEFINED,
		WCA_NCRENDERING_ENABLED,
		WCA_NCRENDERING_POLICY,
		WCA_TRANSITIONS_FORCEDISABLED,
		WCA_ALLOW_NCPAINT,
		WCA_CAPTION_BUTTON_BOUNDS,
		WCA_NONCLIENT_RTL_LAYOUT,
		WCA_FORCE_ICONIC_REPRESENTATION,
		WCA_EXTENDED_FRAME_BOUNDS,
		WCA_HAS_ICONIC_BITMAP,
		WCA_THEME_ATTRIBUTES,
		WCA_NCRENDERING_EXILED,
		WCA_NCADORNMENTINFO,
		WCA_EXCLUDED_FROM_LIVEPREVIEW,
		WCA_VIDEO_OVERLAY_ACTIVE,
		WCA_FORCE_ACTIVEWINDOW_APPEARANCE,
		WCA_DISALLOW_PEEK,
		WCA_CLOAK,
		WCA_CLOAKED,
		WCA_ACCENT_POLICY,
		WCA_FREEZE_REPRESENTATION,
		WCA_EVER_UNCLOAKED,
		WCA_VISUAL_OWNER,
		WCA_HOLOGRAPHIC,
		WCA_EXCLUDED_FROM_DDA,
		WCA_PASSIVEUPDATEMODE,
		WCA_USEDARKMODECOLORS,
		WCA_CORNER_STYLE,
		WCA_PART_COLOR,
		WCA_DISABLE_MOVESIZE_FEEDBACK,
		WCA_LAST
	} WINDOWCOMPOSITIONATTRIBUTE;

	typedef struct _WINDOWCOMPOSITIONATTRIBUTEDATA
	{
		WINDOWCOMPOSITIONATTRIBUTE Attribute;
		PVOID pvData;
		SIZE_T cbData;
	} WINDOWCOMPOSITIONATTRIBUTEDATA;

	typedef enum _ACCENT_STATE
	{
		ACCENT_DISABLED,
		ACCENT_ENABLE_GRADIENT,
		ACCENT_ENABLE_TRANSPARENTGRADIENT,
		ACCENT_ENABLE_BLURBEHIND,
		ACCENT_ENABLE_ACRYLICBLURBEHIND,
		ACCENT_ENABLE_HOSTBACKDROP,
		ACCENT_INVALID_STATE
	} ACCENT_STATE;

	typedef enum _ACCENT_FLAG
	{
		ACCENT_NONE,
		ACCENT_WINDOWS11_LUMINOSITY = 0x2,
		ACCENT_BORDER_LEFT = 0x20,
		ACCENT_BORDER_TOP = 0x40,
		ACCENT_BORDER_RIGHT = 0x80,
		ACCENT_BORDER_BOTTOM = 0x100,
		ACCENT_BORDER_ALL = (ACCENT_BORDER_LEFT | ACCENT_BORDER_TOP | ACCENT_BORDER_RIGHT | ACCENT_BORDER_BOTTOM)
	} ACCENT_FLAG;

	typedef struct _ACCENT_POLICY
	{
		ACCENT_STATE AccentState;
		DWORD AccentFlags;
		DWORD dwGradientColor;
		DWORD dwAnimationId;
	} ACCENT_POLICY;

	typedef BOOL(WINAPI* pfnSetWindowCompositionAttribute)(HWND, WINDOWCOMPOSITIONATTRIBUTEDATA*);
	static pfnSetWindowCompositionAttribute SetWindowCompositionAttribute
		= (pfnSetWindowCompositionAttribute)GetProcAddress(GetModuleHandle(L"User32"), "SetWindowCompositionAttribute");

	static BOOL SetAcrylicEffect(HWND hWnd, DWORD dwTintColor)
	{
		ACCENT_POLICY policy = {
			ACCENT_ENABLE_ACRYLICBLURBEHIND,
			ACCENT_WINDOWS11_LUMINOSITY | ACCENT_BORDER_ALL,
			dwTintColor,
			0
		};
		WINDOWCOMPOSITIONATTRIBUTEDATA data = {
			WCA_ACCENT_POLICY,
			&policy,
			sizeof(ACCENT_POLICY)
		};

		return SetWindowCompositionAttribute(hWnd, &data);
	}

	static BOOL SetAcrylicEffect(HWND hWnd, DWORD dwTintColor, DWORD dwOpacity)
	{
		return SetAcrylicEffect(hWnd, (dwOpacity << 24) | (dwTintColor & 0xFFFFFF));
	}
}
}