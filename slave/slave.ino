
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


if(detected==HIGH && detectState==false){
  Serial.println("motion");
  detectState=true;
  }
  else if(detected==LOW && detectState==true){
    Serial.println("no motion");
    detectState=false;
  }


if(stringComplete && inter==true){
 
  inputString.trim();
  Serial.println(inputString);

  if(inputString=="negative"){
    state="OFF";
  }
  else if(inputString=="positive"){
    state="ON";
  }
  
  inputString = "";
    stringComplete = false;
    inter=false;


    delay(15000);
   

}



 if( state== "OFF" && ldrvalue > 50 && inter==false){
  
    Serial.println("ON");
    state=" ON";
  
    
  }
  
else if (state=="OFF" && (ldrvalue < 50) && detected == HIGH && inter==false){
  
    Serial.println("ON");
    state="ON";
  
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

  void InterruptFunction(){
    
    Serial.println("INTERRUPT");
    inter=true;
    
  }
  


 
