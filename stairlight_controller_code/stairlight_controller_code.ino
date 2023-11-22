
/* 
This is the code for the stairlight_controller.
Author: Ukesh Aryal
Date Created: 22/11/2023
*/

const int lower_pir_pin = D5;   // Set the lower_pir_pin
const int upper_pir_pin = D0;   // Set the upper_pir_pin
const int relay_pin = D2;       // Set the relay pin
const int led_pin = D4;         // Set the led pin
bool lower_pir = 0;             // Initialize all the flag and setup values as 0. 
bool upper_pir = 0;
bool lowerflag = 0;
bool upperflag = 0;
uint16_t threshold = 45;   // Light threshold that if crossed below activates the system.
uint16_t hold_time = 20;   // Time for the light to remain on.


void setup() {
  Serial.begin(9600);
  Serial.println("Hello, stairlight_controller!");

  pinMode(lower_pir_pin, INPUT);    // Define all the pin functions.
  pinMode(upper_pir_pin, INPUT);
  pinMode(relay_pin, OUTPUT);
  pinMode(led_pin, OUTPUT);
}


void readinput() {                  // Takes the input from the pins and sets the value of the flag.

  lower_pir = digitalRead(lower_pir_pin);
  upper_pir = digitalRead(upper_pir_pin);

  if (lower_pir == 1 && lowerflag == 0 && upperflag == 0) {
    lowerflag = 1;
  }
  if (upper_pir == 1 && lowerflag == 0 && upperflag == 0) {
    upperflag = 1;
  }
}

void stairlight() {                 /*  Checks the flag and if the flag is high then turns off
                                        the input for the time the light is on.  */
  if (lowerflag == 1) {

    Serial.println("Motion Detected. L_U");
    digitalWrite(relay_pin, HIGH);
    for (int i = 0; i <= hold_time; i++) {
      Serial.println(i);
      delay(1000);
    }
    Serial.println("Motion Timeout");
    lowerflag = 0;
    digitalWrite(relay_pin, LOW);
  }


  else if (upperflag == 1) {
    Serial.println("Motion Detected. U_L");
    digitalWrite(relay_pin, HIGH);
    for (int i = 0; i <= hold_time; i++) {
      Serial.println(i);
      delay(1000);
    }
    Serial.println("Motion Timeout");
    upperflag = 0;
    digitalWrite(relay_pin, LOW);
  }

  else {
    digitalWrite(relay_pin, LOW);
  }
}

void loop() {

  int ldr_value = analogRead(A0);       // Store the analogvalue read from A0 to the ldr_value.

  Serial.println(ldr_value);            
  if (ldr_value <= threshold){          // If the ldr_value is less than the threshold then it activates the system.
    Serial.println("Stairlights Active.");
    digitalWrite(led_pin, HIGH);        // Activate the on_board led
    readinput();
    stairlight();
  }

  else {
  digitalWrite(relay_pin, LOW);
  }
  delay(1);                              // Delay in between reads for stability



}
