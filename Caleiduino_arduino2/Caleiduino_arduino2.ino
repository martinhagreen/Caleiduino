#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

#define cs 8
#define dc 9
#define rst 10 

TFT TFTscreen = TFT(cs, dc, rst);
//analog pins from the accelerometer
int xPin = A0;
int yPin = A1;
int zPin = A2;

//minimum values from the accelerometer on each axis
int minVal = 260;
int maxVal = 420;

//variables to store incoming values from the accelerometer
int sensorValue1, sensorValue2, sensorValue3;
//variables to store mapped values from the accelerometer
int valX, valY, valZ;
int sound = 0;
//booleans to check axis status
bool staticX, staticY, staticZ;
//variable to store if caleiduino is on standby mode or if its moving
int active;
//variables to store color components
int red,  blue, green;

void setup(void) {
  Serial.begin(9600);
  TFTscreen.begin();
  TFTscreen.background(0,0,0);
  // pinMode(4, OUTPUT);
}

void loop() {
   //read incoming data from 3 each accelerometer axis
   sensorValue1 = analogRead(xPin);
   sensorValue2 = analogRead(yPin);
   sensorValue3 = analogRead(zPin);

  //screen width & height dimensions

  // +---------- 160px -----------+
  // +                            +
  // +                            +
  // 128px                        +
  // +                            +
  // +                            +
  // +----------------------------+

  //map values according to screen dimensions
  valX = map(sensorValue1, minVal, maxVal, 1, 160);
  valY = map(sensorValue2, minVal, maxVal, 1, 128);
  valZ = map(sensorValue3, minVal, maxVal, 1, 128);

  // Mapeamos los valores de valX para crear valores sonoros.
  // Mira los valores de la tabla de abajo:
 // sound = map(voltage3, minVal, maxVal, 31, 4978);
  // La funcion tone(PIN, Frecuencia, Duracion). Mas informacion en:
  // https://www.arduino.cc/en/Reference/Tone
  // Aqui añadimos aleatoriedad random() a la duracion de
  // los sonidos del piezoelectrico para que sean mas locos:
  //tone(4, sound, valZ / random(10));

  //Uncomment this block to draw with party random colors
  /*
  red = random(255);
  green = random(255);
  blue = random(255);
  */
  //map color channels according to accelerometer axis
  red = map(sensorValue1, minVal,maxVal,0, 255);
  green = map(sensorValue2, minVal,maxVal,0, 255);
  blue = map(sensorValue3, minVal,maxVal,0, 255);

  //here we send information to Serial port, to check on the console or communication with our Processing sketch 
  Serial.print(valX);
  Serial.print(",");
  Serial.print(valY);
  Serial.print(",");
  Serial.print(valZ);
  Serial.print(",");
  Serial.print(red);
  Serial.print(",");
  Serial.print(green);
  Serial.print(",");
  Serial.print(blue);
  Serial.print(",");
  Serial.print(active);
  Serial.println(",");


  //Check if caleiduino is in vertical & static position 
  if(valX == 33 || valX == 34 || valX == 35){
     staticX = true;
  } else {
     staticX = false;
  }

  if(valY == 80 || valY == 81){
     staticY = true;
  } else {
    staticY = false;
  }

  if(valZ== 80 || valZ == 81){
     staticZ = true;
  } else {
    staticZ = false;
  }
  //Keep screen black if its vertical and static

  if(staticX == true && staticY == true && staticZ == true){
    TFTscreen.background(0,0,0);
    active = 0;
   
      } else {
        active = 1;
        //HERE is where we draw our stuff

        TFTscreen.noStroke();
        TFTscreen.fill(blue, green, red);
        TFTscreen.triangle(valX, valY, valZ, valX, 0, 0);
        TFTscreen.stroke(255, 255, 255);
        TFTscreen.line(valX, valY, valZ, valY + random(50));
      }

  delay(100);
}

