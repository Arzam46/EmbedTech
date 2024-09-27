#include <DHT.h>  //Library for DHT11

#define DHTPIN 2       //Defining pin number for DHT
#define DHTTYPE DHT11  //Defining type of DHT

DHT dht(DHTPIN, DHTTYPE);  //Object for class DHT

int led = 4;  //Declaring pin no for led

void setup() {
  dht.begin();  //DHT initialization
  Serial.begin(9600);
  pinMode(4, OUTPUT);  //Setting pinmode for led
}

void loop() {
  float tc = dht.readTemperature();  //Read temperature from DHT11
  float h = dht.readHumidity();      //Read humidity from DHT11
  int fc = dht.convertCtoF(tc);      //Read temperature from DHT11 in Celcius and converting it farenheit
  int i = dht.computeHeatIndex();    //Compute heat index from DHT11,Heat index is comination of temperature and humidity to estimate temperature feels to human body

  Serial.println("Temperature in C");  //Printing on serial monitor
  Serial.println(tc);                  //Printing on serial monitor
  Serial.println("Humidity");          //Printing on serial monitor
  Serial.println(h);                   //Printing on serial monitor
  Serial.println("Temperature in F");  //Printing on serial monitor
  Serial.println(fc);                  //Printing on serial monitor
  Serial.println("index");             //Printing on serial monitor
  Serial.println(i);                   //Printing on serial monitor

  if (tc > 20) {            //Decision making
    digitalWrite(4, LOW);   //Led off
    delay(100);             //Delay
    digitalWrite(4, HIGH);  //led on
    delay(100);             //Delay
  } else {                  //Decision making
    digitalWrite(4, HIGH);  //led on
  }
  delay(2000);  //Delay
}