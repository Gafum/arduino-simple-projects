// ultrasonic sensor
int trigger = 7;
int echo = 6;

// LEDs Pins
int LEDred = 2;
int LEDyellow = 3;
int LEDgreen = 4;

long dauer = 0;
long entfernung =0;


void setup(){
  Serial.begin(9600);

  // Ultrasonic sensor
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT); 

  // traffic light LEDs
  pinMode(LEDred, OUTPUT);
  pinMode(LEDyellow, OUTPUT);
  pinMode(LEDgreen, OUTPUT);
}

void loop(){
  digitalWrite(LEDred, HIGH);

  digitalWrite(trigger, HIGH);
  delay(10);
  digitalWrite(trigger, LOW);
  dauer = pulseIn(echo, HIGH);
  entfernung = (dauer/2) * 0.03432;

  if(entfernung >= 500 || entfernung <= 0){
    Serial.println("there are not cordinats");
  }
  else{
    Serial.print(entfernung);
    Serial.println(" cm");
    if(entfernung<20){
      delay(2000);
      digitalWrite(LEDyellow, HIGH);
      delay(1000);
      digitalWrite(LEDred, LOW);
      digitalWrite(LEDyellow, LOW);
      digitalWrite(LEDgreen, HIGH);
      delay(3000);
      digitalWrite(LEDgreen, LOW);
      digitalWrite(LEDyellow, HIGH);
      delay(1000);
      digitalWrite(LEDyellow, LOW);
      digitalWrite(LEDred, HIGH);
      delay(2000);
    }
  }
  delay(200);
}