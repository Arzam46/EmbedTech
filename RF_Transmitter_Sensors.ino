#include <DHT.h>   //Library for DHT11
#include <RF24.h>  //Library for interfacing with NRF24L01 modules

#define DHTPIN 12      //Defining pin number for DHT
#define DHTTYPE DHT11  //Defining type of DHT

DHT dht(DHTPIN, DHT11);  //Object for class DHT

RF24 radio(2, 5);  //Object for class RF24 and the parameters are CE(Chip Enable) and CSN(Chip Select Not)

const byte address[] = "node1";  //Address for radio communication

struct sensordata {  //Structure
  float temp;        //Member
  float humid;       //Member
  int gas;           //Member
};
sensordata data;  //Structure variable

int ir = 25;  //Declaring pin no for ir sensor
int mq = 26;  //Declaring pin no for MQ-135 sensor

void setup() {
  Serial.begin(9600);

  radio.begin();  //RF24 initialization

  dht.begin();  //DHT initialization

  radio.openWritingPipe(address);  //Configure module to send data to the specified adress
  radio.setPALevel(RF24_PA_MIN);   //Set amplifier level to minimum
  radio.stopListening();           //Configure the module to send data instead of receiving data,Setting module to tansmitt mode

  pinMode(25, INPUT);  //Setting pinmode for ir sensor
  pinMode(26, INPUT);  //Setting pinmode for MQ-135 sensor
}
void loop() {

  int ir_data = digitalRead(ir);  //Reading value from ir sensor

  if (ir_data == LOW) {                 //Decision making
    Serial.println("Object detected");  //Printing on serial monitor

    data.temp = dht.readTemperature();  //Read temperature from DHT11
    data.humid = dht.readHumidity();    //Read humidity from DHT11
    data.gas = digitalRead(4);          //Reading value from MQ-135 sensor

    Serial.print("Temp: ");    //Printing on serial monitor
    Serial.print(data.temp);   //Printing on serial monitor
    Serial.println(" C");      //Printing on serial monitor
    Serial.print("Humid: ");   //Printing on serial monitor
    Serial.print(data.humid);  //Printing on serial monitor
    Serial.println(" %");      //Printing on serial monitor

    if (data.gas == LOW) {                 //Decision making
      Serial.println("Gas detected");      //Printing on serial monitor`
    } else {                               //Decision making
      Serial.println("Gas not detected");  //Printing on serial monitor
    }
    radio.write(&data, sizeof(data));  //Sends the "data" value over RF24, Sending data of sensors over RF24

  } else {                                  //Decision making
    Serial.println("Object not detected");  //Printing on serial monitor
  }
  delay(400);  //Delay
}