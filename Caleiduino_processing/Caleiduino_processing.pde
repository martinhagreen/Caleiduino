/*
Caleiduino visualizer
Marta Verde. 2017
Based on the original code by Sam Brenner 
*/


import processing.serial.*;
int x, y, z;
String colorIn;
Serial myPort;
int colorinchi;
PGraphics maskImage;
PGraphics image; 

PImage upImg;
PImage downImg;
PGraphics upImgMask;
PGraphics downImgMask;
boolean first = true;
int sourceWidth;
int sourceHeight;
int blockHeight;
int blockWidth;
int cellSpace;
int totalBlockPixels;
int rows;
int cols;
float TWO_PI_OVER_3 = TWO_PI/3;
boolean inverted = false;

int active;
int initXPos;
int initYPos;

int red, blue, green;


void setup() {
  size(1920,1080);
  //this line prints the devices connected to the computer
  println(Serial.list());
  frameRate(12);
  //replace the port String with the port where your Arduino is connected
  myPort = new Serial(this, "/dev/tty.wchusbserial1450", 9600);
  myPort.bufferUntil('\n');
  background(0);
  //screen source dimensions
  sourceWidth = 160;
  sourceHeight = 128;
  //A rectangle able to have an equilateral triangle inscribed in it (where h = sqrt(3)/2 * w)
  blockHeight = 73;
  blockWidth = 84;
  totalBlockPixels = blockWidth * blockHeight;

  initCellImages();
  initCellSpacing();
  image = createGraphics(sourceWidth, sourceHeight);
}

void draw() {
  background(0);
    initMasks();
    generateSourceImages();
    updateMasks();
    
    for(int i = -1; i < cols; i++) {
      for(int j = -1; j < rows; j++) {
        drawHexagonPattern(i * cellSpace, (j * blockHeight * 2) + ((i%2 == 0) ? blockHeight : 0));
      }
    }
   // Comment this block to hide triangle info "panel"
   fill(0);
   noStroke();
   rect(0,0, image.width * 2, image.height);
   image(image, 0, 0);
   pushMatrix();
    translate(initXPos, initYPos);
    stroke(0);
    noFill();
    triangle(0, blockHeight, blockWidth/2, 0, blockWidth, blockHeight);
   popMatrix();
   image(upImg, 200, initYPos);
}

void generateSourceImages() {
  if(active == 1){
     image.beginDraw();
     image.noStroke();
     image.fill(red, green, blue); 
     image.pushMatrix();
       image.translate(160, 128);
       image.scale(-1, -1);
    
       //HERE is where we draw our graphics according to Arduino code.
       /*
          TFTscreen.fill(blue, green, red);
          TFTscreen.triangle(valX, valY, valZ, valX, 0, 0);
          TFTscreen.stroke(255, 255, 255);
          TFTscreen.line(valX, valY, valZ, valY + random(50));
       */
       //=======
       image.triangle(x, y, z, x, 0, 0);
       image.stroke(255);
       image.line(x, y, z, y + random(50));
       //======
     image.popMatrix();
     image.endDraw();
  }
  //clear drawing on stand-by mode 
  if(active == 0){
      image.beginDraw(); 
      image.clear();
      image.endDraw(); 
  }

  initXPos = 30;
  initYPos = 20;
  int count = 0;
  
  for(int j = 0; j < blockHeight; j++) {
    for(int i = 0; i < blockWidth; i++) {
      int targetX = initXPos + i;
      int targetY = initYPos + j;
      
      color sourcePixel = image.pixels[targetY * sourceWidth + targetX];
      upImg.pixels[count] = sourcePixel;
      downImg.pixels[((blockHeight - j - 1) * blockWidth) + i] = sourcePixel;
      upImg.updatePixels();
      downImg.updatePixels(); 
      count++;
    }
  }
}

//save frame with keyboard
void keyReleased(){
  if(key == 's'){
    saveFrame("caleiduino-####.png");
 }
}