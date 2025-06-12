## Пример
```cpp
#include  "Timers.h"

void setup() {
	Serial.begin(115200);
	Serial.println("Старт программы");
	
	Timers::addTimer(0, false); // однократный таймер
	Timers::addTimer(1, true); // циклический таймер
	Timers::addTimer(2, false); // циклический таймер

	Timers::start(0, 5000); // запуск однократного таймера на 5 секунд
	Timers::start(1, 2000); // запуск циклического таймера на 2 секунды
	Timers::start(2, 10000); // запуск циклического таймера на 10 секунды
}

void loop() {
	Timers::update();
	
	if(Timers::isDone(0)) {
		Serial.print("Однократный таймер №0 сработал! Время: ");
		Serial.print(millis());
		Serial.println(" мс");
		Timers::resetAndStop(0);
	}
	
	if(Timers::isDone(1)) {
		static  int count = 0;
		count++;
		Serial.print("Циклический таймер №1 сработал! Счетчик: ");
		Serial.println(count);
	}
	
	if(Timers::isDone(2)) {
		Timers::resetAndStop(2);
		Timers::resetAndStop(1);
		Serial.print("Однократный таймер №2 сработал! Время: ");
		Serial.print(millis());
		Serial.println(" мс");
		Serial.print("Циклический таймер №1 остановлен!");
	}
}
``` 
