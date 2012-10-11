#include "Includes.h"
#include "Game.h"

//TODO: Make a dedicatd grid space and grid first thing! 
// That way you know exactly where all the menu elemets will go
// and how the game will look.

void DrawingHandler(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT *event, Game *game)
{
	int ScrH = al_get_display_height(display);
	int ScrW = al_get_display_width(display);

	al_clear_to_color(al_map_rgb(0,0,0));
	game->draw();
}

void LogicHandler(ALLEGRO_EVENT *event)
{

}

void MainRunLoop(ALLEGRO_DISPLAY *display)
{
	Game *game = new Game(display);

	ALLEGRO_EVENT_QUEUE *mainEventQueue = al_create_event_queue();
	ALLEGRO_TIMER *drawTimer = al_create_timer(1.0 / FPS);
	ALLEGRO_TIMER *logicTimer = al_create_timer(0.5); //need to make this dynamic later on.
	
	al_register_event_source(mainEventQueue, al_get_display_event_source(display));
	al_register_event_source(mainEventQueue, al_get_keyboard_event_source());
	al_register_event_source(mainEventQueue, al_get_mouse_event_source());
	al_register_event_source(mainEventQueue, al_get_timer_event_source(drawTimer));
	al_register_event_source(mainEventQueue, al_get_timer_event_source(logicTimer));

	bool Run = true;
	bool draw = true;

	al_start_timer(drawTimer);
	al_start_timer(logicTimer);

	while(Run)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(mainEventQueue, &event);
		
		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			if(event.timer.source == drawTimer) 
			{
				draw = true;
			}
			else if(event.timer.source == logicTimer)
			{
				LogicHandler(&event);
			}
		}

		/*if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			curPress = event.keyboard.keycode;
		}*/

		if (draw == true && al_event_queue_is_empty(mainEventQueue)) 
		{
			DrawingHandler(display, &event, game);
			al_flip_display();
			draw = false;
		}
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			Run = false;
	}

	al_destroy_timer(drawTimer);
	al_destroy_timer(logicTimer);
	al_destroy_event_queue(mainEventQueue);
}

int main(int argc, char *args[])
{
	if(!al_init()) { cout << "failed to initialize allegro!\n"; return -1; }

	ALLEGRO_DISPLAY* display = NULL;
		display = al_create_display(640, 480);

	if(!display) { cout << "failed to create display!\n"; return -1; }
	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();

	//Init Addons
	al_init_font_addon();
	if(!al_init_ttf_addon()) { cout << "Failed to initilize ttf addon!\n"; return -1; }
	if(!al_init_image_addon()) { cout << "Failed to initilize image addon!\n"; return -1; }
	if(!al_init_primitives_addon()) { cout << "Failed to initilize primatives addon!\n"; return -1; }

	//input Devices
	if(!al_install_mouse()) { cout << "Failed to initilize mouse!\n"; return -1; }
	if(!al_install_keyboard()) { cout << "Failed to initilize keyboard!\n"; return -1; }

	MainRunLoop(display);

	return EXIT_SUCCESS;
}