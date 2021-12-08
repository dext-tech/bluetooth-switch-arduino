
int ldr=A2;
int ldrvalue=0;
int sensor=8;
int button=3;
String state="OFF";
String inputString="";
bool inter=false;
bool stringComplete = false;
bool detectState=false;

void setup() {
  pinMode(ldr,INPUT);
  pinMode(sensor,INPUT);
  pinMode(button,INPUT);
  inputString.reserve(200);
  pinMode(button,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3),InterruptFunction,RISING);
  Serial.begin(38400);
}

void loop() {
  
  bool detected=digitalRead(sensor);
  bool buttonRead=digitalRead(button);
  ldrvalue=analogRead(ldr);

  //Prints out the state of the motion detector
  if(detected==HIGH && detectState==false){
    Serial.println("motion");
    detectState=true;
  }
  else if(detected==LOW && detectState==true){
      Serial.println("no motion");
      detectState=false;
  }

//runs when the data being received from the slave is complete
  if(stringComplete && inter==true){
    //cleans the received data
    inputString.trim();
    Serial.println(inputString);

  //Changes the state of the system when the slave toggles the light
    if(inputString=="negative"){
      state="OFF";
    }
    else if(inputString=="positive"){
      state="ON";
    }
      inputString = "";
      stringComplete = false;
      //sets the interrupts state to false after we are done with the interrupt
      inter=false;
      delay(15000);
  }
  //Switches on the light with the condition of the state, ldr value and the interrupt state
  if( state== "OFF" && ldrvalue > 50 && inter==false){
      Serial.println("ON");
      state=" ON";
  }  
    //Switches on the light with the condition of the state, ldr value, motion sensor and the interrupt state
  else if (state=="OFF" && (ldrvalue < 50) && detected == HIGH && inter==false){
      Serial.println("ON");
      state="ON";
  }   
}
//Receiving data from the slave
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
//sends INTERRUPT to the slave
void InterruptFunction(){
    Serial.println("INTERRUPT");
    //sets the interrupt state to true
    inter=true;
}
  


 
