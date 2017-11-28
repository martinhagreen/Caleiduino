void serialEvent(Serial myPort) {
  String inString = myPort.readStringUntil('\n');
  if (inString != null) {
    inString = trim(inString);
    int[] coordinates = int(split(inString, ","));
    if (coordinates.length >=7) {
      x = int(coordinates[0]);
      y = int(coordinates[1]);
      z = int(coordinates[2]);
      red = coordinates[3];
      green = coordinates[4];
      blue = coordinates[5];
      active = int(coordinates[6]);
    }
  }
}