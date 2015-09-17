// csfml-wrapper.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <SFML/Graphics.h>
#include <iostream>

extern "C" __declspec(dllexport) inline sfEvent __cdecl sf_event_create(void)
{
	sfEvent event;
	return event;
}

extern "C" __declspec(dllexport) inline sfEventType __cdecl sf_event_get_type(sfEvent &event)
{
	return event.type;
}

extern "C" __declspec(dllexport) inline bool __cdecl sf_render_window_poll_event(sfRenderWindow* window, sfEvent *event)
{
	return sfRenderWindow_pollEvent(window, event);
}

extern "C" __declspec(dllexport) inline sfRenderWindow* __cdecl sf_render_window_create(int height, int width, char* title)
{
	sfVideoMode mode = { height, width, 32 };
	return sfRenderWindow_create(mode, title, sfResize | sfClose, nullptr);
}
// setters for render window

extern "C" __declspec(dllexport) inline void __cdecl sf_render_window_set_title(sfRenderWindow* window, char* title)
{
	sfRenderWindow_setTitle(window, title);
}

// end setters for render window


// start window operations

extern "C" __declspec(dllexport) inline void __cdecl sf_render_window_close(sfRenderWindow* window)
{
	sfRenderWindow_close(window);
}
extern "C" __declspec(dllexport) inline void __cdecl sf_render_window_destroy(sfRenderWindow* window)
{
	sfRenderWindow_destroy(window);
}

extern "C" __declspec(dllexport) inline bool __cdecl sf_render_window_is_open(sfRenderWindow* window)
{
	return sfRenderWindow_isOpen(window);
}


// end window operations

// start clock operations

extern "C" __declspec(dllexport) inline sfClock* __cdecl sf_clock_create(void)
{
	return sfClock_create();
}

extern "C" __declspec(dllexport) inline void __cdecl sf_clock_destroy(sfClock* clock)
{

	sfClock_destroy(clock);
}


extern "C" __declspec(dllexport) inline void __cdecl sf_clock_restart(sfClock* clock)
{
	 sfClock_restart(clock);
}



// start time operations

extern "C" __declspec(dllexport) inline sfTime* __cdecl sf_time_zero(void)
{
	return &sfTime_Zero;
}

extern "C" __declspec(dllexport) inline sfTime __cdecl sf_time_per_frame(void)
{
	return sfSeconds(1.f / 60.f);
}

extern "C" __declspec(dllexport) inline sfInt32 __cdecl sf_time_milliseconds(sfTime time)
{
	return sfTime_asMilliseconds(time);
}

extern "C" __declspec(dllexport) inline sfTime __cdecl sf_time_subtract(sfTime thisTime, sfTime otherTime)
{
	thisTime.microseconds -= otherTime.microseconds;
	return thisTime;
}

extern "C" __declspec(dllexport) inline sfTime __cdecl sf_time_add(sfTime thisTime, sfTime otherTime)
{
	
	thisTime.microseconds += otherTime.microseconds;
	return thisTime;
}

extern "C" __declspec(dllexport) inline bool __cdecl sf_time_greater_than(sfTime thisTime, sfTime otherTime)
{
	return thisTime.microseconds > otherTime.microseconds;
}



// end time operations




