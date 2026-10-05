#include <Arduino.h>
#include <PID_v1.h>

int ch1 = 0;
int ch2 = 1;

volatile float motorSpeed = 150;
float setpoint = 1; //rps
volatile float previousTime = 0;
volatile float dt = 1;


void setup() {
  ledcAttachPin(9,ch1);
  ledcAttachPin(9,ch2);
  pinMode(A5,INPUT_PULLUP);
}

void loop() {
  if (analogRead(A5) < 20){
    unsigned long currentTime = millis();

    dt = (currentTime - previousTime) / 1000.0; //in seconds

    if (dt <= 0) {
    return;
    }
    previousTime = currentTime;
  }

  if(dt > setpoint && motorSpeed < 256) {
    motorSpeed = motorSpeed + 1;
  }
  if(dt < setpoint && motorSpeed <256){
    motorSpeed = motorSpeed + 1;
  }
  ledcWrite(ch1, motorSpeed);
  delay(1000);

    // Debugging
  Serial.print("Light: ");
  Serial.print(analogRead(A5));

  Serial.print("  dt: ");
  Serial.print(dt);

  Serial.print("  Motor: ");
  Serial.println(motorSpeed);
}