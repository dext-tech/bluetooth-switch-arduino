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
  
  if (stringComplete) {
  
    
    inputString.trim();
    
    if(inputString=="ON"){
      
        digitalWrite(bulb,HIGH);
        digitalWrite(bulb2,HIGH);
      
    }
    else if (inputString=="OFF"){
        digitalWrite(bulb,LOW);
        digitalWrite(bulb2,LOW);
    }

    else if (inputString=="INTERRUPT"){
        if(digitalRead(bulb)==HIGH){
        digitalWrite(bulb,LOW);
        digitalWrite(bulb2,LOW);
        Serial.println("negative");
        }
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


void serialEvent() {
  while (Serial.available()) {
      char inChar = (char)Serial.read();
      inputString += inChar;
      if (inChar == '\n') {
      stringComplete = true;
      }
  }
}
