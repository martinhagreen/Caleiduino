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


void updateMasks() { 
  upImg.mask(upImgMask);
  downImg.mask(downImgMask);
    //image(image, 0, 0);
    pushMatrix();
    translate(initXPos, initYPos);
      stroke(0);
      noFill();
      triangle(0, blockHeight, blockWidth/2, 0, blockWidth, blockHeight);
    popMatrix();
    //image(upImgMask, 400, 0);
    //image(upImg, 700, 0);
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