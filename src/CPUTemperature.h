/*
	Библиотека для получения температуры процессора микроконтроллеров AVR
	GitHub: https://github.com/alexkor433/CPUTemperature
	
	Совместимость:
	ATmega8 : No
	ATmega8L : No
	ATmega8A : No
	ATmega168 : No
	ATmega168A : Yes
	ATmega168P : Yes
	ATmega328 : Yes
	ATmega328P : Yes
	ATmega1280 (Arduino Mega) : No
	ATmega2560 (Arduino Mega 2560) : No
	ATmega32U4 (Arduino Leonardo) : Yes
	
	Возможности:
	- получение температуры процессора
	- настройка параметра смещения (компенсации, offset) температуры
	- настройка параметра прироста (gain) температуры
	
	MIT License
	
	Версии:
	v1.0 - Релиз
	v1.1 - Добавлен параметр настройки усиления (прироста) gain температуры
	для более точной настройки (без объявления установлен по умолчанию - 1.22)
	v1.1.1 - Добавлены предупреждения о поддержке чипа (MCU)
	v1.2 - Оптимизация (передача параметров по ссылке)//28.01.24
*/

#pragma once
#include <Arduino.h>


#if not (						\
defined (__AVR_ATmega168A__) || \
defined (__AVR_ATmega168P__) || \
defined (__AVR_ATmega168PA__)|| \
defined (__AVR_ATmega16M1__) || \
defined (__AVR_ATmega16U4__) || \
defined (__AVR_ATmega328__)  || \
defined (__AVR_ATmega328P__) || \
defined (__AVR_ATmega32M1__) || \
defined (__AVR_ATmega32U4__) || \
defined (__AVR_ATmega48A__)  || \
defined (__AVR_ATmega48P__)  || \
defined (__AVR_ATmega48PA__) || \
defined (__AVR_ATmega64M1__) || \
defined (__AVR_ATmega88A__)  || \
defined (__AVR_ATmega88P__)  || \
defined (__AVR_ATmega88PA__))
#error "This MCU is not supported in CPUTemperature.h library"
#endif

class CPUTemperature {
public:
	CPUTemperature(const double& tempOffset = 324.31, const double& tempGain = 1.22) { // 324.31, 1.22 - параметры по умолчанию
		_tempOffset = tempOffset;
		_tempGain = tempGain;
	}

	double getCPUTemp(void) {
		unsigned int wADC;

		/*Измерение внутренней температуры должно использоваться
		с внутренним опорным напряжением 1.1V.
		8 канал не может больше использоваться с
		функцией analogRead.*/

		// Установка опорного напряжения и мультиплексора.
		ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
		ADCSRA |= _BV(ADEN);  // Включение АЦП

		delay(20);            // ждём пока напряжение стабилизируется.

		ADCSRA |= _BV(ADSC);  // Старт АЦП

		// Определение окончания конверсии
		while (bit_is_set(ADCSRA, ADSC));

		// Чтение регистра "ADCW" позаботится о том, как читать ADCL и ADCH.
		wADC = ADCW;

		// Температура в градусах Цельсия
		return (wADC - _tempOffset ) / _tempGain;
	}

private:
	double _tempOffset;
	double _tempGain;
};