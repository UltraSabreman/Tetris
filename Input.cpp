#include "Input.h"
#include "Game.h"

Input::Input(Game *game)
{
	_game = game;
	_keys.resize(300);
	_madetimer= false;
}

void Input::mainHandler(ALLEGRO_EVENT_QUEUE *mainQueue, ALLEGRO_EVENT &event)
{
	if (!_madetimer)
	{
		_leftTick = al_create_timer(0.5);
		al_register_event_source(mainQueue, al_get_timer_event_source(_leftTick));

		_rightTick = al_create_timer(0.5);
		al_register_event_source(mainQueue, al_get_timer_event_source(_rightTick));

		_downTick = al_create_timer(0.01);
		al_register_event_source(mainQueue, al_get_timer_event_source(_downTick));
		_madetimer = true;
	}


	if (event.type == ALLEGRO_EVENT_TIMER)
	{
		if (event.timer.source == _leftTick)
		{
			_keys[ALLEGRO_KEY_LEFT] = true;
			al_stop_timer(_leftTick);
		}
		if (event.timer.source == _rightTick)
		{
			_keys[ALLEGRO_KEY_RIGHT] = true;
			al_stop_timer(_rightTick);
		}	
		if (event.timer.source == _downTick)
		{
			_keys[ALLEGRO_KEY_DOWN] = true;
			al_stop_timer(_downTick);
		}
	}

	if (event.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		int curPress = event.keyboard.keycode;
		switch (curPress)
		{
			case ALLEGRO_KEY_A:
			case ALLEGRO_KEY_UP:
				_game->_currentTet->tryTurn(TETRIS_DIR_LEFT);
			break;

			case ALLEGRO_KEY_Z:
				_game->_currentTet->tryTurn(TETRIS_DIR_RIGHT);
			break;

			case ALLEGRO_KEY_LEFT:
				_game->_currentTet->tryMove(TETRIS_DIR_LEFT);

				al_start_timer(_leftTick);
			break;

			case ALLEGRO_KEY_RIGHT:
				_game->_currentTet->tryMove(TETRIS_DIR_RIGHT);

				al_start_timer(_rightTick);
			break;

			case ALLEGRO_KEY_DOWN:
				_game->_currentTet->tryMove(TETRIS_DIR_DOWN);

				al_start_timer(_downTick);
			break;

			default:
				_keys[curPress] = true;
			break;
		}
	}

	if (event.type == ALLEGRO_EVENT_KEY_UP)
	{
		int curPress = event.keyboard.keycode;
		switch (curPress)
		{
			case ALLEGRO_KEY_LEFT:
				_keys[curPress] = false;

				al_stop_timer(_leftTick);
			break;

			case ALLEGRO_KEY_RIGHT:
				_keys[curPress] = false;

				al_stop_timer(_rightTick);
			break;

			case ALLEGRO_KEY_DOWN:
				_keys[curPress] = false;

				al_stop_timer(_downTick);
			break;

			default:
				_keys[curPress] = false;
			break;
		}
			
	}

}

void Input::ioProcess()
{
	if (_keys[ALLEGRO_KEY_LEFT])
		_game->_currentTet->tryMove(TETRIS_DIR_LEFT);

	if (_keys[ALLEGRO_KEY_RIGHT])
		_game->_currentTet->tryMove(TETRIS_DIR_RIGHT);
			
	if (_keys[ALLEGRO_KEY_DOWN])
		_game->_speedMod = 1;
	else
		_game->_speedMod = _game->_oldMod;
}