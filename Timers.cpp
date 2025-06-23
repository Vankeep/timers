#include "Timers.h"

TimerEntry Timers::_timers[MAX_TIMERS];
bool Timers::_initialized[MAX_TIMERS] = {false};

void Timers::addTimer(uint8_t id, bool isCyclic) {
     if (id >= MAX_TIMERS) return;
     _timers[id] = {
          .startTime = 0,
          .interval = 0,
          .isActive = false,
          .isDone = false,
          .isCyclic = isCyclic
     };
     _initialized[id] = true;
}

void Timers::addTimerAndStart(uint8_t id, uint32_t interval, bool isCyclic) {
     addTimer(id, isCyclic);
     start(id, interval);
}

void Timers::update() {
     uint32_t current = millis();
     for (uint8_t i = 0; i < MAX_TIMERS; i++) {
          if (!_initialized[i] || !_timers[i].isActive) continue;

          if (_timers[i].isDone) {
               if (_timers[i].isCyclic) {
                    _timers[i].isDone = false;
                    _timers[i].startTime = current;
               }
               continue;
          }

          if (current - _timers[i].startTime >= _timers[i].interval) {
               _timers[i].isDone = true;
          }
     }
}

void Timers::start(uint8_t id, uint32_t interval) {
     if (id >= MAX_TIMERS || !_initialized[id]) return;
     _timers[id].startTime = millis();
     _timers[id].interval = interval;
     _timers[id].isActive = true;
     _timers[id].isDone = false;
}

void Timers::resetAndStop(uint8_t id) {
     if (id >= MAX_TIMERS || !_initialized[id]) return;
     _timers[id].isActive = false;
     _timers[id].isDone = false;
     _timers[id].startTime = 0;
     _timers[id].interval = 0;
}

void Timers::restart(uint8_t id, uint32_t interval) {
     if (id >= MAX_TIMERS || !_initialized[id]) return;
     resetAndStop(id);
     start(id, interval);
}

bool Timers::isActive(uint8_t id) {
     if (id >= MAX_TIMERS || !_initialized[id]) return false;
     return _timers[id].isActive;
}

bool Timers::isDone(uint8_t id) {
     if (id >= MAX_TIMERS || !_initialized[id]) return false;
     return _timers[id].isDone;
}

uint32_t Timers::getTimeFromStart(uint8_t id) {
     if (id >= MAX_TIMERS || !_initialized[id] || !_timers[id].isActive) return 0;
     return millis() - _timers[id].startTime;
}

uint32_t Timers::getTimeToFinish(uint8_t id) {
     if (id >= MAX_TIMERS || !_initialized[id] || !_timers[id].isActive) return 0;
     uint32_t elapsed = millis() - _timers[id].startTime;
     return (elapsed < _timers[id].interval) ? (_timers[id].interval - elapsed) : 0;
}
