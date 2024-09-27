int ir = 2;   //Declaring pin no for ir sensor
int led = 4;  //Declaring pin no for led
int var;      //Global variable

void setup() {
  Serial.begin(9600);

  pinMode(ir, INPUT);  //Setting pinmode for ir sensor
  pinMode(4, OUTPUT);  //Setting pinmode for led
}

void loop() {
  var = digitalRead(ir);  //Reading value from ir sensor

  if (var == LOW) {                         //Decision making
    Serial.println("Object detected");      //Printing on serial monitor
    digitalWrite(led, HIGH);                //Led on
  } else {                                  //Decision making
    Serial.println("Object not detected");  //Printing on serial monitor
    digitalWrite(4, LOW);                   //Led off
  }
  delay(400);  //Delay
}