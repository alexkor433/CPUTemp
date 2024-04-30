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
