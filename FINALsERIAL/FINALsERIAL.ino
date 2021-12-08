int bulb=7;
int bulb2=10;
String inputString = "";         
bool stringComplete = false;  

void setup() {
  pinMode(bulb,OUTPUT);
  pinMode(bulb2,OUTPUT);
  Serial.begin(38400);
  inputString.reserve(200);
}

void loop() {
  //Runs when data is received from the master
  if (stringComplete) {
    //cleans up the received string 
    inputString.trim();
    //turns on the light when it receives ON
    if(inputString=="ON"){
        digitalWrite(bulb,HIGH);
        digitalWrite(bulb2,HIGH);
   }
    //turns off the light when it receives OFF
    else if (inputString=="OFF"){
        digitalWrite(bulb,LOW);
        digitalWrite(bulb2,LOW);
    }
    //This block runs when it receives INTERRUPT from the master
    else if (inputString=="INTERRUPT"){
      //Turns off the light when it was on at the time the interrupt was received
        if(digitalRead(bulb)==HIGH){
          digitalWrite(bulb,LOW);
          digitalWrite(bulb2,LOW);
          Serial.println("negative");
        }
       //Turns on the light when it was off at the time the interrupt was received
        else if (digitalRead(bulb)==LOW){
          digitalWrite(bulb,HIGH);
          digitalWrite(bulb2,HIGH);
          Serial.println("positive");
      } 
    }
    inputString = "";
    stringComplete = false;
  }
}

//Receives data from the master 
void serialEvent() {
  while (Serial.available()) {
      char inChar = (char)Serial.read();
      inputString += inChar;
      if (inChar == '\n') {
        stringComplete = true;
      }
  }
}
