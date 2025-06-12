#pragma once

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
  static void addTimer(uint8_t id, bool isCyclic = false) {
    if (id >= MAX_TIMERS) return;
    timers[id].isCyclic = isCyclic;
    timers[id].isActive = false;
    timers[id].isDone = false;
    timers[id].startTime = 0;
    timers[id].interval = 0;
    initialized[id] = true;
  }
  
  static void addTimerAndStart(uint8_t id, uint32_t interval, bool isCyclic = false) {
    addTimer(id, isCyclic);
    start(id, interval);
  }

  static void update() {
    uint32_t current = millis();
    for (uint8_t i = 0; i < MAX_TIMERS; i++) {
      if (!initialized[i]) continue;

      if (timers[i].isActive) {

        if (timers[i].isCyclic && timers[i].isDone)  timers[i].isDone = false;

        if (current - timers[i].startTime >= timers[i].interval) {
          timers[i].isDone = true;
          if (timers[i].isCyclic){
            timers[i].startTime = current;
          }
        }
      }
    }
  }

  static void start(uint8_t id, uint32_t interval) {
    if (id >= MAX_TIMERS || !initialized[id]) return;
    timers[id].startTime = millis();
    timers[id].interval = interval;
    timers[id].isActive = true;
    timers[id].isDone = false;
  }

  static void resetAndStop(uint8_t id) {
    if (id >= MAX_TIMERS || !initialized[id]) return;
    timers[id].isActive = false;
    timers[id].isDone = false;
    timers[id].startTime = 0;
    timers[id].interval = 0;
  }

  static void restart(uint8_t id, uint32_t interval) {
    if (id >= MAX_TIMERS || !initialized[id]) return;
    resetAndStop(id);
    start(id, interval);
  }

  static bool isActive(uint8_t id) {
    if (id >= MAX_TIMERS || !initialized[id]) return false;
    return timers[id].isActive;
  }

  static bool isDone(uint8_t id) {
    if (id >= MAX_TIMERS || !initialized[id]) return false;
    return timers[id].isDone;
  }

  static uint32_t getTimeFromStart(uint8_t id) {
    if (id >= MAX_TIMERS || !initialized[id] || !timers[id].isActive) return 0;
    return millis() - timers[id].startTime;
  }

  static uint32_t getTimeToFinish(uint8_t id) {
    if (id >= MAX_TIMERS || !initialized[id] || !timers[id].isActive) return 0;
    uint32_t elapsed = millis() - timers[id].startTime;
    return (elapsed < timers[id].interval) ? (timers[id].interval - elapsed) : 0;
  }

private:
  static TimerEntry timers[MAX_TIMERS];
  static bool initialized[MAX_TIMERS];
};

TimerEntry Timers::timers[MAX_TIMERS];
bool Timers::initialized[MAX_TIMERS] = {false};
