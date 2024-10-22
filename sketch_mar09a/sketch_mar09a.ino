#define VRX_PIN  36 // Arduino pin connected to VRX pin
#define VRY_PIN  37 // Arduino pin connected to VRY pin

int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis

void setup() {
  Serial.begin(9600) ;
}

void loop() {
  // read analog X and Y analog values
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);

  //Scaling
  xValue = (xValue * 1000)/4095 - 500;
  yValue = (yValue * 1000)/4095 - 500;

  //DeadZone
  if(xValue < 70 && xValue > -70){xValue = 0;}
  if(yValue < 70 && yValue > -70){yValue = 0;}

  // print data to Serial Monitor on Arduino IDE
  Serial.print("x = ");
  Serial.print(xValue);
  Serial.print(", y = ");
  Serial.println(yValue);
  delay(200);
}
