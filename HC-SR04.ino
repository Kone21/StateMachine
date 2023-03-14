#define PIN_TRIG 9
#define PIN_ECHO 10

#define MTR_1 4 //left
#define MTR_2 5

#define MTR_3 7 //right
#define MTR_4 6

int IRpin = 0;



long duration, cm;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  //Определяем вводы и выводы
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  pinMode(MTR_1, OUTPUT);
  pinMode(MTR_2, OUTPUT);
  pinMode(MTR_3, OUTPUT);
  pinMode(MTR_4, OUTPUT);
  


}

void loop() {

float volts = analogRead(IRpin) * 0.0048828125;
float distance_R = 65*pow(volts, -1.10);
Serial.print("LED distance: ");
Serial.println(distance_R);
delay(100);

  // put your main code here, to run repeatedly:
// Сначала генерируем короткий импульс длительностью 2-5 микросекунд.

  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);

  // Выставив высокий уровень сигнала, ждем около 10 микросекунд. В этот момент датчик будет посылать сигналы с частотой 40 КГц.
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  //  Время задержки акустического сигнала на эхолокаторе.
  duration = pulseIn(PIN_ECHO, HIGH);

  // Теперь осталось преобразовать время в расстояние
  cm = (duration / 2) / 29.1;

  Serial.print("Расстояние до объекта: ");
  Serial.print(cm);
  Serial.println(" см.");

  // Задержка между измерениями для корректной работы скеча
  delay(250);

  

if (cm >= 10 && distance_R <= 25){ //move forward
  digitalWrite(MTR_1, HIGH);
  analogWrite(MTR_2, 500);

  digitalWrite(MTR_3, HIGH);
  analogWrite(MTR_4, 500);

}

else if (cm <= 10 && distance_R <= 25){ //turn Right
  digitalWrite(MTR_1, HIGH);
  analogWrite(MTR_2, 500);

  digitalWrite(MTR_3, LOW);
  analogWrite(MTR_4, 500);

}

else if (cm > 20 && distance_R > 35){ //turn Left
  digitalWrite(MTR_1, LOW);
  analogWrite(MTR_2, 500);

  digitalWrite(MTR_3, HIGH);
  analogWrite(MTR_4, 500);

}

}
