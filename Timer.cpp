#include "Timer.h"

TimerControl::TimerControl(void) 
{
	QueryPerformanceFrequency(&_countsPerSecond);
	_curtime = 0;

	run();
} 
TimerControl::~TimerControl(void) {} 

double TimerControl::getElapcedSeconds() 
{
	return ((double)_currentCounts.QuadPart /(double)_countsPerSecond.QuadPart);
}

void TimerControl::run()
{
	while (true)
	{
		QueryPerformanceCounter(&_currentCounts);
		_curtime = getElapcedSeconds();

		for (int i = 0; i < _timers.size(); i++)
		{
			Timer *tTimer = _timers[i];
			if (tTimer->_startTime != -1 && _curtime >= (tTimer->_startTime + tTimer->_interval))
			{
				if (tTimer->_iterations == 0 || tTimer->_curIterations <= tTimer->_iterations)
				{
					tTimer->_curIterations++;
					tTimer->_startTime = _curtime;

					tTimer->_function();
				}else 
				{
					tTimer->_function();
					delete tTimer;
				}
			}
		}
	}
}

bool TimerControl::add(std::string name, float interval, int iterations, void (*func) (void))
{
	if (!getTimer(name))
	{
		Timer *newTimer = new Timer(name, interval, -1, iterations, func);
		_timers.push_back(newTimer);
	}
}

bool TimerControl::start(std::string name)
{
	Timer *tempTimer = getTimer(name);
	if (!tempTimer)
		return false;
	else
		tempTimer->_startTime = _curtime;

	return true;
}

bool TimerControl::pause(std::string name)
{
	Timer *tempTimer = getTimer(name);
	if (!tempTimer)
		return false;
	else
		tempTimer->_startTime = -1;

	return true;
}

bool TimerControl::stop(std::string name)
{
	Timer *tempTimer = getTimer(name);
	if (!tempTimer)
		return false;
	else
	{
		tempTimer->_startTime = -1;
		tempTimer->_curIterations = 0;
	}

	return true;
}

bool TimerControl::remove(std::string name)
{
	Timer *tempTimer = getTimer(name);
	if (!tempTimer)
		return false;
	else
		delete tempTimer;

	return true;
}

Timer* TimerControl::getTimer(std::string name)
{
	for (int i = 0; i < _timers.size(); i++)
		if (_timers[i]->_name == name)
			return _timers[i];
}