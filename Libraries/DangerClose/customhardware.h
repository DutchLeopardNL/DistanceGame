#ifndef CUSTOMHARDWARE_H
#define CUSTOMHARDWARE_H


//A struct for a RGBled
typedef struct
{
  char name[20];
  int redPin;
  int greenPin;
  int bluePin;
} RGBled;

//A struct for a piezzo buzzer
typedef struct
{
  char name[20];
  int buzzerPin;
  int defaultFrequency;
} Buzzer;

//A struct for a ultrasonic sensor
typedef struct
{
  char name[20];
  int triggerPin;
  int echoPin;
} UltraSone;

//A struct for a red led
typedef struct 
{
  char name[20];
  int pin;
} RLed;




#endif