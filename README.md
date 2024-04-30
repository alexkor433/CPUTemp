# CPUTemperature
### Библиотека для получения температуры процессора микроконтроллеров AVR

## Содержание
- [Совместимость](#compatibility)
- [Возможности](#capabilities)
- [Пример](#example)
- [Версии](#versions)

<a id="compatibility"></a>
## Совместимость
- ATmega8 : No
- ATmega8L : No
- ATmega8A : No
- ATmega168 : No
- ATmega168A : Yes
- ATmega168P : Yes
- ATmega328 : Yes
- ATmega328P : Yes
- ATmega1280 (Arduino Mega) : No
- ATmega2560 (Arduino Mega 2560) : No
- ATmega32U4 (Arduino Leonardo) : Yes

`Канал 8 невозможно больше использовать с функцией analogRead`

<a id="capabilities"></a>
## Возможности
- получение температуры процессора
- настройка параметра смещения (компансации, offset) температуры
- настройка параметра прироста (gain) температуры
<a id="example"></a>
## Пример
```cpp
#include <CPUTemperature.h>

// необходимо подобрать значения экспериментально
CPUTemperature temp; 				// можно не указывать параметры (будут по умолчанию - 324.31, 1.22)
//CPUTemperature temp (331.0);		// конструктор с параметром смещения
//CPUTemperature temp (331.0, 1.11);	// конструктор с указанием смещения и прироста

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(temp.getCPUTemp());
  delay(1000);
}
```

<a id="versions"></a>
## Версии
- v1.0 - релиз
- v1.1 - добавлен параметр настройки усиления (прироста) gain температуры
для более точной настройки (без объявления установлен по умолчанию - 1.22)
- v1.1.1 - Добавлены предупреждения о поддержке чипа (MCU)
- v1.2 - Оптимизация
- v1.2.1 - Использование списка инициализации конструктора вместо присваивания
