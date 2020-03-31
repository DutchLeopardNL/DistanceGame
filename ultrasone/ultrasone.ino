
#include <PinDefines.h>
#include <frequencies.h>
#include <customhardware.h>
#include <Servo.h>
long distanceInTime, distance, randomNumber;
int angle;

Buzzer buzzer;
UltraSone ultraSone;
RGBled rgbled;
RLed ledLeft;
RLed ledRight;
Servo servoMotor;


//Prototype methods
void RGB_color();
void blinkLights();
void waveTheFlag();
void youWon();
long randomNumberGenerator();


void setup() {
  //Serial Port begin
  Serial.begin (9600);

  //Initiate RGBled
  strcpy(rgbled.name, "RGBled");
  rgbled.redPin = 4;
  rgbled.greenPin = 3;
  rgbled.bluePin = 2;
  pinMode(rgbled.redPin, OUTPUT);
  pinMode(rgbled.greenPin, OUTPUT);
  pinMode(rgbled.bluePin, OUTPUT);

  //Initiate Buzzer
  strcpy(buzzer.name, "buzzerOne");
  buzzer.buzzerPin = PIN9;
  buzzer.defaultFrequency = LowFrequency;
  pinMode(buzzer.buzzerPin, OUTPUT);

  //Initiate UltraSonic Sensor
  strcpy(ultraSone.name, "ultraSoneSensorOne");
  ultraSone.triggerPin = PIN11;
  ultraSone.echoPin = PIN12;
  pinMode(ultraSone.triggerPin, OUTPUT);
  pinMode(ultraSone.echoPin, INPUT);

    //Initiate left red led 
  strcpy(ledLeft.name, "leftLed");
  ledLeft.pin = PIN6;
  pinMode(ledLeft.pin, OUTPUT);

  //Initiate right red led 
  strcpy(ledRight.name, "rightLed");
  ledLeft.pin = PIN5;
  pinMode(ledRight.pin, OUTPUT);

  servoMotor.attach(PIN13);
  
  randomNumber = randomNumberGenerator();
}

void loop() {
  
  delay(1000);
  //UltraSone setup for getting the distance
  digitalWrite(ultraSone.triggerPin, LOW);
  delayMicroseconds(5);
  digitalWrite(ultraSone.triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultraSone.triggerPin, LOW);
  distanceInTime = pulseIn(ultraSone.echoPin, HIGH);
  distance = (distanceInTime / 2) / 29.1; // Distance is in cm which can later be compared to numbers easily

  //If else for the distance algorithm with different outputs per distance
  if(distance <= randomNumber + 5 && distance >= randomNumber - 5)
  {
    youWon();
  }
    
  else if(distance <= randomNumber + 15 && distance >= randomNumber - 15 && distance >= randomNumber + 5 || distance <= randomNumber + 15 && distance >= randomNumber - 15 && distance <= randomNumber - 5){
    Serial.println("Close......");
    RGB_color(200, 0, 0);
    tone(buzzer.buzzerPin, NOTE_D8);
    delay(50);
    noTone(buzzer.buzzerPin);
  }

  else if(distance <= randomNumber + 30 && distance >= randomNumber - 30 && distance >= randomNumber + 15 || distance <= randomNumber + 15 && distance >= randomNumber - 15 && distance <= randomNumber - 15){
    Serial.println("Decently close......");
    RGB_color(150, 0, 0);
    tone(buzzer.buzzerPin, NOTE_D6);
    delay(200);
    noTone(buzzer.buzzerPin);
  }

  else if(distance <= randomNumber + 45 && distance >= randomNumber - 45 && distance >= randomNumber + 30 || distance <= randomNumber + 15 && distance >= randomNumber - 15 && distance <= randomNumber - 30){
    Serial.println("Decent......");
    RGB_color(100, 0, 0);
    tone(buzzer.buzzerPin, NOTE_D4);
    delay(200);
    noTone(buzzer.buzzerPin);
  }

  else if(distance <= randomNumber + 60 && distance >= randomNumber - 60 && distance >= randomNumber + 45 || distance <= randomNumber + 15 && distance >= randomNumber - 15 && distance <= randomNumber - 45){
    Serial.println("Less far......");
    RGB_color(50, 0, 0);
    tone(buzzer.buzzerPin, NOTE_D2);
    delay(200);
    noTone(buzzer.buzzerPin);
  }

  else if(distance <= randomNumber + 75 && distance >= randomNumber - 75 && distance >= randomNumber + 60 || distance <= randomNumber + 15 && distance >= randomNumber - 15 && distance <= randomNumber - 60){
    Serial.println("Far......");
    RGB_color(0, 250, 0);
    noTone(buzzer.buzzerPin);
    delay(200);
  }
  else
  {
    RGB_color(0, 255, 0);
    delay(50);
     RGB_color(0, 0, 0);
    delay(50);
    RGB_color(0, 255, 0);
    delay(50);
    RGB_color(0, 0, 0);
  }

  //If else to show the user if he has passed the distance or not
  if(distance < randomNumber)
  {
   digitalWrite(ledRight.pin, LOW);
   digitalWrite(ledLeft.pin, HIGH);
  }
  else if(distance > randomNumber)
  {
   digitalWrite(ledLeft.pin, LOW);
   digitalWrite(ledRight.pin, HIGH);
  }
  Serial.println(randomNumber);
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
  
  
  delay(250);
}

 //RGB color setup method
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(rgbled.redPin, red_light_value);
  analogWrite(rgbled.greenPin, green_light_value);
  analogWrite(rgbled.bluePin, blue_light_value);
}

//BLinking lights
void blinkLights(){
    digitalWrite(ledRight.pin, HIGH);
    digitalWrite(ledLeft.pin, HIGH);
    delay(200);
    digitalWrite(ledRight.pin, LOW);
    digitalWrite(ledLeft.pin, LOW);
    delay(200);
}

//Everything that happens if you win in a method
void youWon()
{
    Serial.println("CONGRATS! YOU WON!");
    RGB_color(255, 0, 0);
    waveTheFlag();
    blinkLights();
    blinkLights();
    blinkLights();
    RGB_color(0, 0, 255);
    playWinSound(buzzer.buzzerPin);
    randomNumber = randomNumberGenerator();  
}

//Make the servo wave a flag
void waveTheFlag()
{
    for ( angle = 10; angle < 180; angle++)
    {
        servoMotor.write(angle);
        delay(15);
    }
    for(angle = 180; angle > 10; angle--)    
    {                                
        servoMotor.write(angle);           
        delay(15);       
    }
    
}

//Generate a random number
long randomNumberGenerator()
{
  long randomNum;
  randomSeed(analogRead(0));
  randomNum = random(6, 50);
  return randomNum;
}
