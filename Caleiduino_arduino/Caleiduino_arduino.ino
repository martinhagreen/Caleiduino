/***************************************************************

      xxxx  xxxx  x     xxxx  x  xxx   x  x  x  x  x  xxxx
      x     x  x  x     x     x  x  x  x  x  x  xx x  x  x
      x     xxxx  x     xxx   x  x  x  x  x  x  x xx  x  x
      x     x  x  x     x     x  x  x  x  x  x  x  x  x  x
      xxxx  x  x  xxxx  xxxx  x  xxx   xxxx  x  x  x  xxxx (1)

  Este ejemplo de CALEIDUINO se basa en las librerias de Adafruit GFX
  y ST_7735, que hacen posible conectar Arduino con una pantalla TFT
  de 1.8'. Gracias a Arduino y a Adafruit por desarrollar el hardware
  y el software que hacen posible el proyecto CALEIDUINO. Este sketch
  de codigo es abierto y de dominio publico. Esta a disposicion de
  cualquiera que desee crear su propio CALEIDUINO.

  ¡¡Animate y crea tu propio caleidoscopio digital sonoro!!

  (CC)Jose Manuel Gonzalez 2016

***************************************************************/

// Conexiones a la pantalla TFT
// #define sclk 13 / Usa esta linea si prefieres Opcion 1 (lento)
// #define mosi 11 / Usa esta linea si prefieres Opcion 1 (lento)
#define cs 8
#define dc 9
#define rst 10 // Se puede conectar tambien al PIN RESET 
// (no con placa CALEIDUINO)

// #include "pitches.h" / Para el caso que quieras jugar con las
// notas de la carpeta "pitches.h" que aparecen más abajo.
// Mas informacion: https://www.arduino.cc/en/Tutorial/ToneMelody
#include <Adafruit_GFX.h> // Libreria para programar los graficos
#include <Adafruit_ST7735.h> // Libreria que permite usar el chip 
//especifico de la pantalla TFT
#include <SPI.h> // Libreria para que la Arduino se comunique con
// la pantalla TFT mediante protocolo Serial

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

// Opcion 1: Usa todos los PINES pero la pantalla funciona un poco
// mas lento:
// Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, mosi, sclk, rst);

// Opcion 2: Debe usar los PINES SPI. Este metodo es mas rapido:
Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);
// float p = 3.1415926;

// Los 3 inputs analogicos del acelerometro, que corresponden con
// los 3 ejes X, Y y Z, se conectan a los PIN ES de la placa
// Arduino en A0, A1 y A2:

const int xPin = A0;
const int yPin = A1;
const int zPin = A2;

// Generamos un mapeado de los valores del sensor.
// El valor minimo es 260 y el maximo 420:

int minVal = 260;
int maxVal = 420;

// Valores que entran por los PINES A0, A1 y A2:

int valX = 0;
int valY = 0;
int valZ = 0;
int sound = 0;
int color;

  int sensorValue1;
  int oldSensorValue1;
  
  int sensorValue2;
  int oldSensorValue2;
  int sensorValue3;
  int oldSensorValue3;

bool staticX, staticY, staticZ;

int active;

String colorinchi;


void setup(void) {
  Serial.begin(9600);

  // Inicializamos la pantalla TFT en negro:

  tft.initR(INITR_BLACKTAB);
  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);

  // PIN 4 de salida al borne (+) del piezoelectrico(sonido):

 // pinMode(4, OUTPUT);
}

void loop() {

   sensorValue1 = analogRead(xPin);
   sensorValue2 = analogRead(yPin);
   sensorValue3 = analogRead(zPin);

  // Convertimos la salida analogica (que va de 0 - 1023) a
  // voltaje (0 - 5V):

 // float voltage1 = sensorValue1;
  //float voltage2 = sensorValue2;
  //float voltage3 = sensorValue3;

  // Mapeamos los valores entrantes del acelerometro para usarlos
  // despues en la pantalla TFT

  // +---------- 160px -----------+
  // +                            +
  // +                            +
  // 128px                        +
  // +                            +
  // +                            +
  // +----------------------------+

  // De 0 a 160px ancho de pantalla:
  valX = map(sensorValue1, minVal, maxVal, 1, 160);
  // De 0 a 128px alto de pantalla:
  valY = map(sensorValue2, minVal, maxVal, 1, 128);
  // De 0 a 128px alto de pantalla:
  valZ = map(sensorValue3, minVal, maxVal, 1, 128);

  // Mapeamos los valores de valX para crear valores sonoros.
  // Mira los valores de la tabla de abajo:

 // sound = map(voltage3, minVal, maxVal, 31, 4978);

  // La funcion tone(PIN, Frecuencia, Duracion). Mas informacion en:
  // https://www.arduino.cc/en/Reference/Tone
  // Aqui añadimos aleatoriedad random() a la duracion de
  // los sonidos del piezoelectrico para que sean mas locos:

  //tone(4, sound, valZ / random(10));
//
  // Gracias al puerto Serial, podemos visualizar en la pantalla los
  // valores entrantes del acelerometro y en consecuencia, los
  // valores de sonido lanzados al piezoelectrico. Esto ocurrira
  // mientras tengamos la placa Arduino conectada mediante el
  // cable USB.
  // Puede ser util para calibrar los valores en razon de nuestras
  // necesidades:


  /*
  //Comprobar posicion estatica
  Serial.print(sensorValue1);
  Serial.print(",");
  Serial.print(sensorValue2);
  Serial.print(",");
  Serial.print(sensorValue3);
  Serial.println(",");
  */

  colorinchi = "00FFE0";
  //color = int(colorinchi);

/*
 // color = 0xFFE0;
  Serial.print(valX);
  Serial.print(",");
  Serial.print(valY);
  Serial.print(",");
  Serial.print(valZ);
  Serial.print(",");
  Serial.print(colorinchi);
  Serial.print(",");
  Serial.print(active);
  Serial.println(",");
  
  */
 // Serial.print("sound =");
 // Serial.println(sound);

  /* Aqui hay varios ejemplos de las funciones graficas que permite
    la libreria de Adafruit GFX. Funciona de forma parecida a las
    funciones basicas de dibujo de Processing. Nos permite dibujar
    triangulos, rectangulos, circulos, elipses, lineas verticales, horizontales, oblicuas, etc... Juega con las diferentes
    posibilidades y combinalas para que los graficos de tu
    pantalla TFT hagan formas caleidoscopicas interesantes y
    divertidas. Mas informacion en:

    https://github.com/adafruit/Adafruit-GFX-Library

    A continuacion vamos a dibujar un triangulo relleno de color.
    Para entender esta funcion, y todas las demas, fijate que hay
    7 valores entre parentesis.

    La funcion funciona asi:

    tft.fillTriangle(X1, Y1, X2, Y2, X3, Y3, Color);

    X1 / Y1 --> coordenadas del primer vertice del triangulo
    X2 / Y2 --> coordenadas del segundo vertice del triangulo
    X3 / Y3 --> coordenadas del tercer vertice del triangulo
    Color ----> cifra de 16 bits, ROJO(0/31), VERDE(0/63) y AZUL(0/31)
  */

 

//Checkear si esta apoyado en posicion vertical

if(sensorValue1 == 294 || sensorValue1 == 293){
     staticX = true;
} else {
     staticX = false;
}

if(sensorValue2 == 360 || sensorValue2 == 361){
     staticY = true;
} else {
    staticY = false;
}

if(sensorValue2 == 360 || sensorValue2 == 361){
     staticZ = true;

} else {
    staticZ = false;
}


//Mantener la pantalla negra 

if(staticX == true && staticY == true && staticZ == true){
    tft.fillScreen(ST7735_BLACK);
    active = 0;
   
} else {
   active = 1;
   
   
   int colorinchis = random(316331);
 
 
   
   tft.fillTriangle(valX, valY, valZ, valX, 0, 0, colorinchis);
   tft.drawLine(valX, valY, valZ, valY + random(50), 0xFFFF);
}



   

  // Dibuja rectangulos con los vertices redondeados de color aleatorio:

 // tft.fillRoundRect(valX, valY, random(10, 80), random(10, 80), 5, random(316331));

  // Dibuja perimetro de circunferencia de un color aleatorio:

 // tft.drawCircle(valX, valZ, valY / 3, random(316331));

  // Dibuja circulo relleno de un color aleatorio:

 // tft.fillCircle(valX, valY, random(30), random(316331));

  // Dibuja lineas verticales de color aleatorio:

 // tft.drawFastVLine(valY, 0, tft.height(), random(316331));

  // Dibuja lineas oblicuas de color aleatorio:

 // tft.drawLine(valX, valY, valZ, valY + random(50), random(316331));

  // Dibuja perimetro de un rectangulo de color aleatorio:

 // tft.drawRect(valY, random(128), random(60), random(60), random(316331));

  // El tiempo de refresco de los graficos nunca debe ser = 0, de lo
  // contrario la pantalla TFT se vuelve loca:

  if (valX < 1) {
    valX = 1;
  }

  // El delay() permite al loop() respirar y aqui lo define el valor
  // analogico del PIN A0, con lo que controlamos la velocidad de
  // refresco de los graficos segun la posicion del CALEIDUINO:

  delay(50);
}

// FIN

