// csfml-wrapper.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <SFML/Graphics.h>

extern "C" __declspec(dllexport) inline bool __cdecl sf_render_window_poll_event(sfRenderWindow* window, sfEvent *event)
{
	return sfRenderWindow_pollEvent(window, event);
}

extern "C" __declspec(dllexport) inline sfRenderWindow* __cdecl sf_render_window_create(int height, int width, char* title)
{
	sfVideoMode mode = { height, width, 32 };
	return sfRenderWindow_create(mode, title, sfResize | sfClose, nullptr);
}

extern "C" __declspec(dllexport) inline void __cdecl sf_render_window_set_title(sfRenderWindow* window, char* title)
{
	sfRenderWindow_setTitle(window, title);
}
extern "C" __declspec(dllexport) inline void __cdecl sf_render_window_close(sfRenderWindow* window)
{
	sfRenderWindow_close(window);
}

extern "C" __declspec(dllexport) inline bool __cdecl sf_render_window_is_open(sfRenderWindow* window)
{
	return sfRenderWindow_isOpen(window);
}



