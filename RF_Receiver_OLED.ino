#include <SPI.h>               //Library for Serial Peripheral Interface communication
#include <nRF24L01.h>          //Library for NRF24L01 module containing specific definitions for NRF24L01 module
#include <RF24.h>              //Library for interfacing with NRF24L01 modules
#include <DHT.h>               //Library for DHT11
#include <Adafruit_GFX.h>      //Library for Graphics
#include <Adafruit_SSD1306.h>  //Library for OLED

RF24 radio(2, 5);                //Object for class RF24 and the parameters are CE(Chip Enable) and CSN(Chip Select Not)
const byte address[] = "node1";  //Address for radio communication

#define SCREEN_WIDTH 128                                                   //Defining screen width
#define SCREEN_HEIGHT 64                                                   //Defining screen height
#define OLED_RESET -1                                                      //Defining reset pin  , Reset pin is used to initialize or reset display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  //Object for class Adafruit_SSD1306
 
struct SensorData {  //Structure
  float temp;        //Member
  float humid;       //Member
  int gas;           //Member
};
SensorData data;  //Structure variable

void setup() {
  Serial.begin(9600);

  radio.begin();  //RF24 initialization

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  //Initializing OLED,SSD1306_SWITCHCAPVCC is specific power configuration,0x3c is adress
  display.setTextColor(SSD1306_WHITE);        //Setting colour
  display.clearDisplay();                     //Clearing display
  display.setCursor(0, 0);                    //Setting cursor


  display.println("Welcome");
   display.display();

  radio.openReadingPipe(0, address);  //Configure module to receive data on pipe 0 on the address
  radio.setPALevel(RF24_PA_MIN);      //Set amplifier level to minimum
  radio.startListening();             //Configure the module to receive data instead of sending data,Setting module to receiver mode
}

void loop() {
  display.clearDisplay();   //Clearing display

  if (radio.available()) {            //Decision making
    radio.read(&data, sizeof(data));  //Receive the "data" value over RF24, Receiving data of sensors via RF24

    display.print("Temp: ");   //Printing on display
    display.print(data.temp);  //Printing on display
    display.println(" C");     //Printing on display

    display.print("Humid: ");   //Printing on display
    display.print(data.humid);  //Printing on display
    display.println(" %");      //Printing on display

    if (data.gas == LOW) {                  //Decision making
      display.println("Gas detected");      //Printing on display
    } else {                                //Decision making
      display.println("Gas not detected");  //Printing on display
    }

    Serial.print("Temp: ");   //Printing on serial monitor
    Serial.print(data.temp);  //Printing on serial monitor
    Serial.println(" C");     //Printing on serial monitor

    Serial.print("Humid: ");   //Printing on serial monitor
    Serial.print(data.humid);  //Printing on serial monitor
    Serial.println(" %");      //Printing on serial monitor

    if (data.gas == LOW) {                 //Decision making
      Serial.println("Gas detected");      //Printing on serial monitor
    } else {                               //Decision making
      Serial.println("Gas not detected");  //Printing on serial monitor
    }
  } else {                                //Decision making
    display.println("No data received");  //Printing on serial monitor
  }

  display.display();  //Updating OLED,this command takes everything from buffer and send to actual OLED screen

  delay(400);  //Delay
}
