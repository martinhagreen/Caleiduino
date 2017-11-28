
import processing.serial.*;

int x;       
int y;     
int z;  
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


void setup() {
  size(1920,1080);

  println(Serial.list());
  myPort = new Serial(this, "/dev/tty.wchusbserial1410", 9600);
  myPort.bufferUntil('\n');
  background(0);
//  frameRate(12);
  
  sourceWidth = 160;
  sourceHeight = 128;
  //TODO: Make this programatic
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
  
  if(active == 1){
    initMasks();
    generateSourceImages();
    updateMasks();

 
  pushMatrix();
  translate(0, 480);
  for(int i = -1; i < cols; i++) {
    for(int j = -1; j < rows; j++) {
      drawHexagonPattern(i * cellSpace, (j * blockHeight * 2) + ((i%2 == 0) ? blockHeight : 0));
    }
  }
  
  popMatrix();
  
  } else {
    fill(0, 10);
    rect(0, 0, width, height);
  
  }
  
}

void initCellImages() {
  upImg = createImage(blockWidth, blockHeight, RGB);
  downImg = createImage(blockWidth, blockHeight, RGB);
  
  upImg.loadPixels();
  downImg.loadPixels();
  
  upImgMask = createGraphics(blockWidth, blockHeight, JAVA2D);
  downImgMask = createGraphics(blockWidth, blockHeight, JAVA2D);
}

void initCellSpacing() {
  cellSpace = floor(blockWidth + (blockWidth * cos(PI/3))); 
  cols = ceil(width / cellSpace) + 2;
  rows = ceil(height / (blockHeight * 2)) + 2;
}

void generateSourceImages() {
 image.beginDraw();
   //image.background(255);
   image.noStroke();
   image.fill(random(255), random(255), random(255)); 
   image.pushMatrix();
   image.translate(159, 0);
   image.rotate(-1.5708 );
   image.scale(-1, -1);
   //image.translate(50,0);
   // CALEIDUINO
   image.triangle(x,y,z, x, 0, 0);
   image.stroke(255);
   image.line(x, y, z, y + random(50));
   image.popMatrix();
 image.endDraw();

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


void updateMasks() { 
  upImg.mask(upImgMask);
  downImg.mask(downImgMask);
  
    image(image, 0, 0);
  
    pushMatrix();
    translate(initXPos, initYPos);
    stroke(0);
    noFill();
    triangle(0, blockHeight, blockWidth/2, 0, blockWidth, blockHeight);
    popMatrix();
    
    image(upImgMask, 400, 0);
    image(upImg, 700, 0);
}

void drawHexagonPattern(int offsetX, int offsetY) {
  PImage img;
  
  pushMatrix();
  translate(offsetX + blockWidth, offsetY + blockHeight);
  
  for(int i=0; i<6; i++) {        
    int drawXOffset = -blockWidth;
    int drawYOffset = -blockHeight;
  
    if(i%2==0) {
      img = downImg;
      drawYOffset = 0;
    } else {
      img = upImg;
    }
   
    image(img, drawXOffset, drawYOffset);
    
    if(i%2==1)
      rotate(TWO_PI_OVER_3);
  }
  
  popMatrix();
}

void initMasks() {
    upImgMask.beginDraw();
    upImgMask.smooth();
    upImgMask.noStroke();
    upImgMask.background(0);
    upImgMask.fill(255);
    upImgMask.pushMatrix();
    upImgMask.beginShape();
    upImgMask.vertex(0, blockHeight);
    upImgMask.vertex(blockWidth/2, 0);
    upImgMask.vertex(blockWidth, blockHeight);
    upImgMask.endShape(CLOSE);
    upImgMask.popMatrix();
    upImgMask.endDraw();
    
    downImgMask.beginDraw();
    downImgMask.smooth();
    downImgMask.noStroke();
    downImgMask.background(0);
    downImgMask.fill(255);
    downImgMask.beginShape();
    downImgMask.vertex(0, 0);
    downImgMask.vertex(blockWidth/2, blockHeight);
    downImgMask.vertex(blockWidth, 0);
    downImgMask.endShape(CLOSE);
    downImgMask.endDraw();
}


void serialEvent(Serial myPort) {
  String inString = myPort.readStringUntil('\n');
  if (inString != null) {
    inString = trim(inString);
    String[] coordinates = (split(inString, ","));
    
    if (coordinates.length >=5) {
      x = int(coordinates[0]);
      y = int(coordinates[1]);
      z = int(coordinates[2]);
      colorIn = coordinates[3];
      active = int(coordinates[4]);
     // colorIn = "FF" + colorIn;
      //colorinchi = unhex(colorIn); 
    
    }
  }
}