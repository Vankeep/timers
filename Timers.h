#pragma once
#include <Arduino.h>

#ifndef MAX_TIMERS
#define MAX_TIMERS 16 
#endif

struct TimerEntry {
     uint32_t startTime;
     uint32_t interval;
     bool isActive;
     bool isDone;
     bool isCyclic;
};

class Timers {
public:
     static void addTimer(uint8_t id, bool isCyclic = false);
     static void addTimerAndStart(uint8_t id, uint32_t interval, bool isCyclic = false);
     static void update();
     static void start(uint8_t id, uint32_t interval);
     static void resetAndStop(uint8_t id);
     static void restart(uint8_t id, uint32_t interval);
     static bool isActive(uint8_t id);
     static bool isDone(uint8_t id);
     static uint32_t getTimeFromStart(uint8_t id);
     static uint32_t getTimeToFinish(uint8_t id);

private:
     static TimerEntry _timers[MAX_TIMERS];
     static bool _initialized[MAX_TIMERS];
};
