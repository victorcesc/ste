int potMax = 0;
int potMin = 1023;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  
  calibratePot();  
  

}

void loop() {
  int pot = analogRead(A0);
  int led = Pmap(pot);
  //Serial.print(led);
  //Serial.print("pot:");
  //Serial.print(pot);
  Serial.print(potMax);
  Serial.print("\n");
  Serial.print(potMin);
  Serial.print("\n");
  //Serial.print("\n");
  analogWrite(3,led);

}

void calibratePot(){
  for(int i=0;i<1000;i++){
  int pot = analogRead(A0);  
  if(pot < potMin){
      potMin = pot;
  }
  if(pot > potMax){
      potMax = pot; 
  }
  
  delay(10);
  }
}
int Pmap(int pot){
    int range = (int) pot - potMin + 1;
    int teste = range/255;
    int result = pot/teste;
    if(result < 0) return 0;
    else if (result > 255) return 255;
    else return 0;        
}