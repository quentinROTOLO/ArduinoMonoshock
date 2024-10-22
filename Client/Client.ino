#include <WiFi.h>

//____________Defines for Joystick 1____________ 
#define VRX_PIN  36 // Arduino pin connected to VRX pin
#define VRY_PIN  37 // Arduino pin connected to VRY pin
#define SW_PIN 13 // Arduino push button

//____________Defines for Joystick 2____________  
#define VRX_PIN_2  38 // Arduino pin connected to VRX 2 pin  
#define VRY_PIN_2  39 // Arduino pin connected to VRY 2 pin  
#define SW_PIN_2 12 // Arduino push button 2 

//____________LED_________________________
#define LEDR_PIN 15
#define LEDG_PIN 2
#define LEDB_PIN 4

//____________Buttons_____________________
#define DOWN_PIN 14
#define LEFT_PIN 27
#define UP_PIN 17
#define RIGHT_PIN 25

//https://arduinogetstarted.com/tutorials/arduino-joystick
//https://randomnerdtutorials.com/ttgo-lora32-sx1276-arduino-ide/
//https://techtutorialsx.com/2018/05/17/esp32-arduino-sending-data-with-socket-client/
//https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
//https://gist.github.com/Flandan/fdadd7046afee83822fcff003ab47087 vjoy py

//____________Variables for Joystick 1____________ 
int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis
int pValue = 0; // To store value of the push button

//____________Variables for Joystick 2____________  
int xValue2 = 0; // To store value of the X axis
int yValue2 = 0; // To store value of the Y axis
int pValue2 = 0; // To store value of the push button

//____________Variables for buttons_______________
int dValue = 0;
int lValue = 0;
int uValue = 0;
int rValue = 0;

char returned; // Returned form the server
 
//const char* ssid = "projet-info";
//const char* password =  "projetinfort";
const char* ssid = "Lucas";
const char* password =  "tupuducu";

 
const uint16_t port = 8090;
//const char * host = "192.168.56.1";
const char * host = "192.168.32.148";

WiFiClient client;
 
void setup()
{
 
  Serial.begin(115200);

  //PinMode Joysticks
  pinMode(SW_PIN,INPUT_PULLUP);                         //ATTENTION 2 AXES INVERSES
  pinMode(SW_PIN_2,INPUT_PULLUP);
  //PinMode LED
  pinMode(LEDR_PIN, OUTPUT);
  pinMode(LEDG_PIN, OUTPUT);
  pinMode(LEDB_PIN, OUTPUT);
  //PinMode Buttons
  pinMode(DOWN_PIN, INPUT_PULLUP);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(UP_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());

  while(true)
  {
    if (!client.connect(host, port)) {
   
          Serial.println("Connection to host failed");
   
          //delay(1000); //whatever
          delay(500);
    } else {
         Serial.println("Connection to host successful");
        break;
    }
  }
  
} // fin setup 
 
void loop()
{
    //__________Pin into Variables__________
    //Joystick 1    
    xValue = analogRead(VRX_PIN);
    yValue = analogRead(VRY_PIN);
    pValue = !digitalRead(SW_PIN);
    //Joystick 2
    xValue2 = analogRead(VRX_PIN_2);
    yValue2 = analogRead(VRY_PIN_2);
    pValue2 = !digitalRead(SW_PIN_2);
    //Buttons
    dValue = !digitalRead(DOWN_PIN);
    lValue = !digitalRead(LEFT_PIN);
    uValue = !digitalRead(UP_PIN); 
    rValue = !digitalRead(RIGHT_PIN);   
    
    //__________Scaling__________
    //Joystick 1
    xValue = (xValue>>4) - 128;
    yValue = (yValue>>4) - 128;    
    if(xValue < 90 && xValue > -90){xValue = 0;}
    if(yValue < 90 && yValue > -90){yValue = 0;}
    //Joystick 2
    xValue2 = (xValue2>>4) - 128;
    yValue2 = (yValue2>>4) - 128;
    if(xValue2 < 90 && xValue2 > -90){xValue2 = 0;}
    if(yValue2 < 90 && yValue2 > -90){yValue2 = 0;}

    // print data to Serial Monitor on Arduino IDE
    //Joystick 1
    Serial.print("x = ");
    Serial.print(xValue);
    Serial.print(", y = ");
    Serial.print(yValue);
    Serial.print(", p = ");
    Serial.print(pValue);
    //Joystick 2
    Serial.print("x2 = ");
    Serial.print(xValue2);
    Serial.print(", y2 = ");
    Serial.print(yValue2);
    Serial.print(", p2 = ");
    Serial.print(pValue2);
    //Buttons
    Serial.print(", r = ");
    Serial.print(rValue);
    Serial.print(", l = ");
    Serial.print(lValue);
    Serial.print(", u = ");
    Serial.print(uValue);
    Serial.print(", d = ");
    Serial.println(dValue);
    
    //delay(200); //usefull ? nah
    delay(50);  

    //__________Trame__________
    //Joystick 1
    client.write(xValue);
    client.write(yValue);
    client.write(xValue2);
    client.write(yValue2);
    //Buttons
    client.write(pValue|pValue2<<1|dValue<<2|lValue<<3|uValue<<4|rValue<<5);
    /*
    client.write(dValue);
    client.write(lValue);
    client.write(uValue);
    client.write(rValue);*/

    //__________Retour__________

 /*   returned = (char)client.read();
    switch(returned){
      case 'r':
        SetLED(255,0,0);
        break;
      case 'g':
        SetLED(0,255,0);
        break;
      case 'b':
        SetLED(0,0,255);
        break;
      default:
        SetLED(0,0,0);
        break;  
    }*/
    //client.stop(); 
}

void SetLED(int redValue, int greenValue, int blueValue) {
  analogWrite(LEDR_PIN, redValue);
  analogWrite(LEDG_PIN, greenValue);
  analogWrite(LEDB_PIN, blueValue);
}
