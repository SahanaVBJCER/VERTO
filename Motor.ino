#include <SoftwareSerial.h>

SoftwareSerial BT(10,11); // RX, TX

char command;

// Motor Driver 1 (Left Motors)
int IN1 = 2;
int IN2 = 3;
int IN3 = 4;
int IN4 = 5;

// Motor Driver 2 (Right Motors)
int IN5 = 6;
int IN6 = 7;
int IN7 = 8;
int IN8 = 9;

void setup()
{
  BT.begin(9600);
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
}

void loop()
{
  if (BT.available())
  {
    command = BT.read();
    Serial.println(command);

    switch(command)
    {
      case 'F': forward(); break;
      case 'B': backward(); break;
      case 'L': left(); break;
      case 'R': right(); break;
      case 'S': stopMotors(); break;
    }
  }
}

void forward()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

  digitalWrite(IN5,HIGH);
  digitalWrite(IN6,LOW);
  digitalWrite(IN7,HIGH);
  digitalWrite(IN8,LOW);
}

void backward()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  digitalWrite(IN5,LOW);
  digitalWrite(IN6,HIGH);
  digitalWrite(IN7,LOW);
  digitalWrite(IN8,HIGH);
}

void left()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  digitalWrite(IN5,HIGH);
  digitalWrite(IN6,LOW);
  digitalWrite(IN7,HIGH);
  digitalWrite(IN8,LOW);
}

void right()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

  digitalWrite(IN5,LOW);
  digitalWrite(IN6,HIGH);
  digitalWrite(IN7,LOW);
  digitalWrite(IN8,HIGH);
}

void stopMotors()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);

  digitalWrite(IN5,LOW);
  digitalWrite(IN6,LOW);
  digitalWrite(IN7,LOW);
  digitalWrite(IN8,LOW);
}