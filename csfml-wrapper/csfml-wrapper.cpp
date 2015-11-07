// csfml-wrapper.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <SFML/Graphics.h>
#include <iostream>
#include <vector>

using namespace std;


extern "C" __declspec(dllexport) inline sfVector2f* __cdecl sf_vector_create(float x, float y);
extern "C" __declspec(dllexport) inline void __cdecl sf_vector_destroy(sfVector2f* vec);



extern "C" __declspec(dllexport) inline bool __cdecl sf_render_window_poll_event(sfRenderWindow* window, sfEvent event)
{
	return sfRenderWindow_pollEvent(window, &event);
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

extern "C" __declspec(dllexport) inline void __cdecl sf_render_window_clear(sfRenderWindow* window)  //TODO add color parameter later on maybe
{
	sfRenderWindow_clear(window, sfBlack);
}
extern "C" __declspec(dllexport) inline void __cdecl sf_render_window_draw_sprite(sfRenderWindow* window, sfSprite* sprite)
{
	sfRenderWindow_drawSprite(window, sprite, nullptr);
}
extern "C" __declspec(dllexport) inline void __cdecl sf_render_window_display(sfRenderWindow* window)
{
	sfRenderWindow_display(window);
}

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


extern "C" __declspec(dllexport) inline sfTime __cdecl sf_clock_restart(sfClock* clock)
{
	 return sfClock_restart(clock);
}



// start time operations

extern "C" __declspec(dllexport) inline sfTime __cdecl sf_time_zero(void)
{
	return sfTime_Zero;
}

extern "C" __declspec(dllexport) inline sfTime __cdecl sf_time_per_frame(void)
{
	return sfSeconds(1.f / 60.f);
}

extern "C" __declspec(dllexport) inline sfTime __cdecl sf_time_set_subtract(sfTime thisTime, sfTime otherTime)
{
	thisTime.microseconds -= otherTime.microseconds;
	return thisTime;
}

//TODO MAKE TIME HANDLING INTERNAL!!!!!!!!!!!!!!
//TODO create function pointers so that you can point straight into the c++ code without needing to write these lame loops in reds!

extern "C" __declspec(dllexport) inline sfTime __cdecl sf_time_set_add(sfTime thisTime, sfClock* clock)
{
	sfTime reset = sfClock_restart(clock);
	std::cout << reset.microseconds << std::endl; 
	//time.microseconds = thisTime.microseconds + otherTime.microseconds;
	
	return reset;
}

extern "C" __declspec(dllexport) inline bool __cdecl sf_time_greater_than(sfTime thisTime, sfTime otherTime)
{
	return thisTime.microseconds > otherTime.microseconds;
}

extern "C" __declspec(dllexport) inline void __cdecl sf_time_print(sfTime time)
{
	std::cout << time.microseconds << std::endl;
}


// end time operations


//utiliy functions

extern "C" __declspec(dllexport) inline void __cdecl print_integer(int integer)
{
	std::cout << integer << std::endl;
}

extern "C" __declspec(dllexport) inline float __cdecl sf_time_get_time(sfTime time)
{
	return time.microseconds;
}

void(*init)();
void(*process_events)(sfRenderWindow*, sfEvent*);
void(*update)(sfInt64);
void(*render)(sfRenderWindow*);
void(*shut_down)();

extern "C" __declspec(dllexport) inline void __cdecl set_callbacks(
	void(*init_setter)(),
	void(*process_events_setter)(sfRenderWindow*, sfEvent*),
	void(*update_setter)(sfInt64),
	void(*render_setter)(sfRenderWindow*),
	void(*shut_down_setter)())
{
	init = *init_setter;
	process_events = *process_events_setter;
	update = *update_setter;
	render = *render_setter;
	shut_down = *shut_down_setter;
}

extern "C" __declspec(dllexport) inline void __cdecl start(
	int width, 
	int height, 
	char* title)
{
	sfVideoMode mode = { height, width, 32 };
	auto *window = sfRenderWindow_create(mode, title, sfResize | sfClose, nullptr);
	sfEvent event;
	sfClock *clock = sfClock_create();
	auto timeSinceLastUpdate = sfTime_Zero;
	const auto TimePerFrame = sfSeconds(1.f / 60.f);
	init();
	while (sfRenderWindow_isOpen(window))
	{
		while (sfRenderWindow_pollEvent(window, &event))
		{
			process_events(window, &event);
		}
		
		timeSinceLastUpdate.microseconds += sfClock_restart(clock).microseconds;
		while (timeSinceLastUpdate.microseconds > TimePerFrame.microseconds)
		{
			timeSinceLastUpdate.microseconds -= TimePerFrame.microseconds;
			while (sfRenderWindow_pollEvent(window, &event))
			{
				process_events(window, &event);
			}
			update(TimePerFrame.microseconds);
		}
		render(window);
	}
	shut_down();
	sfRenderWindow_destroy(window);
}

//start sfFloatRect procedures
extern "C" __declspec(dllexport) inline float __cdecl sf_float_rect_height(sfFloatRect* rect)
{
	return rect->height;
}
extern "C" __declspec(dllexport) inline float __cdecl sf_float_rect_width(sfFloatRect* rect)
{
	return rect->width;
}
extern "C" __declspec(dllexport) inline float __cdecl sf_float_rect_top(sfFloatRect* rect)
{
	return rect->top;
}
extern "C" __declspec(dllexport) inline float __cdecl sf_float_rect_left(sfFloatRect* rect)
{
	return rect->left;
}
//end sfFloatRect procedures

// start sprite procedures
extern "C" __declspec(dllexport) inline sfSprite* __cdecl sf_sprite_create(void)
{
	return sfSprite_create();
}

extern "C" __declspec(dllexport) inline sfFloatRect __cdecl sf_sprite_get_local_bounds(sfSprite* sprite)
{
	return sfSprite_getLocalBounds(sprite);
}

extern "C" __declspec(dllexport) inline void __cdecl sf_sprite_set_origin_to_center(sfSprite* sprite)
{
	sfFloatRect bounds = sfSprite_getLocalBounds(sprite);
	sfVector2f temp = { bounds.width / 2.f, bounds.height / 2.f };
	sfSprite_setOrigin(sprite, temp);
}


extern "C" __declspec(dllexport) inline void __cdecl sf_sprite_set_texture(
	sfSprite* sprite, 
	const sfTexture* texture)
{
	return sfSprite_setTexture(sprite, texture, sfTrue);
}

extern "C" __declspec(dllexport) inline void __cdecl sf_sprite_set_position(sfSprite* sprite, float x, float y)
{
	sfVector2f temp = { x,y };
	sfSprite_setPosition(sprite, temp);
}

extern "C" __declspec(dllexport) inline void __cdecl sf_sprite_destroy(sfSprite* sprite)
{
	sfSprite_destroy(sprite);
}

// end sprite procedures

// start texture procedures

extern "C" __declspec(dllexport) inline sfTexture* __cdecl sf_texture_create(char* file_location)
{
	return sfTexture_createFromFile(file_location, nullptr);
}


extern "C" __declspec(dllexport) inline void __cdecl sf_texture_destroy(sfTexture* texture)
{
	sfTexture_destroy(texture);
}

// end texture procedures

// start Event procedures

extern "C" __declspec(dllexport) inline int __cdecl sf_event_get_key_code(sfEvent* event)
{
	return event->key.code;
}
extern "C" __declspec(dllexport) inline int __cdecl sf_event_get_type(sfEvent* event)
{
	return event->type;
}


// end Event procedures

// start vector procedures



// end vector procedures


//keep for reference... red passes by references only so hacks like this are needed

extern "C" __declspec(dllexport) inline sfVector2f* __cdecl sf_vector_create(float x, float y)
{
	sfVector2f* vec;
	vec = static_cast<sfVector2f*>(malloc(sizeof(sfVector2f)));
	vec->x = x;
	vec->y = y;
	return vec;
}
extern "C" __declspec(dllexport) inline void __cdecl sf_vector_destroy(sfVector2f* vec)
{
	free(vec);
}
