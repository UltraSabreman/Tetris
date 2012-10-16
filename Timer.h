#ifndef _TIMER_H_
#define _TIMER_H_

#include <vector>
#include <string>
#include <time.h>
#include <Windows.h>

/* A timer management system */

class Timer
{
	public:
		Timer(std::string inname, float interval, float startTime, int iterations, void (*func) (void))
		{
			_name = inname;
			_interval = interval;
			_startTime = startTime;
			_iterations = iterations;
			_function = func;

			_curIterations = 0;
			_elapsedTime = 0;
		}

		std::string _name;

		float _startTime;
		float _interval;
		int _iterations;

		int _curIterations;
		double _elapsedTime;

		void (*_function) (void);
};

static class TimerControl
{
	public:
		TimerControl(void);
		~TimerControl(void);

		void run();

		double getElapcedSeconds();

		bool add(std::string name, float interval, int iterations, void (*func) (void));
		bool start(std::string name);
		bool pause(std::string name);
		bool stop(std::string name);
		bool remove(std::string name);
	private:
		double _curtime;
		LARGE_INTEGER _currentCounts;
		LARGE_INTEGER _countsPerSecond;
		std::vector<Timer*> _timers;

		Timer* getTimer(std::string name);

};

#endif