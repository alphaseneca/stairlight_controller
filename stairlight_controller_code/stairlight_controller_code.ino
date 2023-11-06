  
  const int lower_pir_pin = 12;   // Pin Configuration
  const int upper_pir_pin = 14;
  const int relay_pin = 15;
  const int ldr_pin = 12;



  bool lower_pir = 0;
  bool upper_pir = 0;
  bool lowerflag = 0 ;
  bool upperflag = 0 ;
  uint16_t holdtime = 10  ;      // Delay for the light to remain on. 
  uint16_t ldrthreshold = 0 ;     // Threshold Value
  uint16_t resttime = 5000; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(lower_pir_pin, INPUT);
  pinMode(upper_pir_pin, INPUT);
  pinMode(relay_pin, OUTPUT);
  digitalWrite(relay_pin, LOW);
}


void readinput(){

  lower_pir = digitalRead(lower_pir_pin);
  upper_pir = digitalRead(upper_pir_pin);

  if (lower_pir == 1 && lowerflag == 0 && upperflag == 0){
    lowerflag = 1;
  }

  if (upper_pir == 1 && lowerflag == 0 && upperflag == 0){
    upperflag = 1;
  }

}

void stairlight(){

  if (lowerflag == 1){

    Serial.println("Ascending motion detected.");
        digitalWrite(relay_pin, HIGH);
    for (int i = 0; i<= holdtime ; i++ ){
    Serial.println(i);
    delay(1000);
    }
    Serial.println("Motion Timeout");
    lowerflag = 0 ;
    digitalWrite(relay_pin, LOW);
  }


  else if (upperflag == 1){
    Serial.println("Descending motion detected.");
        digitalWrite(relay_pin, HIGH);
    for (int i = 0; i<= holdtime ; i++ ){
    Serial.println(i);
    delay(1000);
    }
    Serial.println("Motion Timeout");
    upperflag = 0 ;
    digitalWrite(relay_pin, LOW);
  }

  else {
      digitalWrite(relay_pin, LOW);

  }
}

void loop() {

  readinput();
  stairlight();

}
