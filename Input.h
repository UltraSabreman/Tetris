#ifndef _INPUT_H_
#define _INPUT_H_
#include "Includes.h"

class Game;

class Input
{
	public:
		Input(Game *game);
		~Input();

		void mainHandler(ALLEGRO_EVENT_QUEUE *mainQueue, ALLEGRO_EVENT &event);
		void ioProcess();

		Game *_game;
		bool _madetimer;
		vector<bool> _keys;

		//shitty workaround to input delay
		ALLEGRO_TIMER *_leftTick;
		ALLEGRO_TIMER *_rightTick;
		ALLEGRO_TIMER *_downTick;

};

#endif