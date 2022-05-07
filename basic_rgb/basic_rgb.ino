void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void Color(int R, int G, int B) {
  analogWrite(9 , R) ;   // Red
  analogWrite(10, G) ;   // Green
  analogWrite(11, B) ;   // Blue
}

void loop() {
  Color(0,255,255) ;  //cyan
  delay(500);
  Color(0,255, 167) ;   //green + cyan
  delay(500);
  Color(0,255,0) ;  //green
  delay(500);
  Color(127,255,0); //green + yellow
  delay(500);
  Color(255,255,0) ;  //yelow
  delay(500);
  Color(255,127,0) ;  //orange
  delay(500);
  Color(255,0,0) ;   //red
  delay(500);
  Color(255,0,127) ;  //red + magenta
  delay(500);
  Color(255,0,255); //magenta
  delay(500);
  Color(127,0,255) ;  //blue + magenta
  delay(500);
  Color(0,0,255); //blue
  delay(500);
  Color(0,127,255) ;  //blue + cyan
  delay(500);
}
