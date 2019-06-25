/*Codigo realizado por : Saul Luna Minor -> contacto: ctiocalvis@gmail.com */
const byte servo1 = 7;
const byte servo2 = 8;
const byte servo3 = 9;
const byte servo4 = 10;
const byte servo5 = 11;
const byte dir1 = A0;
const byte dir2 = A1;
const byte luz_verde = A2;
const byte luz_azul = A3;

//const byte servo6 = 7;

void updateServo (int pin, int pulse);
unsigned long previousMillis = 0;
long interval = 20; //Intervalo de 20 milisegundos.
int pos1 = 0, pos2 = 0, pos3; 
int pulso1 = 1500, pulso2 = 2000, pulso3 = 1200;
byte datos[13];
void setup() {
 Serial.begin(9600);
  pinMode (servo1, OUTPUT);
  pinMode (servo2, OUTPUT);
  pinMode (servo3, OUTPUT);
  pinMode (servo4, OUTPUT);
  pinMode (servo5, OUTPUT);
  pinMode (dir1, OUTPUT);
  pinMode (dir2, OUTPUT);
  pinMode (luz_verde, OUTPUT);
  pinMode (luz_azul, OUTPUT);
  //pinMode (servo6, OUTPUT);

}
void loop() {
digitalWrite(dir1, LOW);
digitalWrite(dir2, LOW);
digitalWrite(luz_verde, LOW);
digitalWrite(luz_azul, LOW);

while(1){

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
     previousMillis =  millis();  
    updateServo(servo1, pulso1);
    updateServo(servo2, 1700);
    updateServo(servo3, pulso2);
    updateServo(servo4, pulso3);
    updateServo(servo5, 1511);
  }
if (Serial.available()> 13) {
  datos[0] = Serial.read();

if (datos[0] == 0x53){
datos[1] = Serial.read();
datos[2] = Serial.read();
datos[3] = Serial.read();
datos[4] = Serial.read();
datos[5] = Serial.read();
datos[6] = Serial.read();
datos[7] = Serial.read();
datos[8] = Serial.read();
datos[9] = Serial.read();
datos[10] = Serial.read();
datos[11] = Serial.read();
datos[12] = Serial.read();
datos[13] = Serial.read();
//Control de motor
if (datos[1] == 'D')
{
  digitalWrite(dir1, LOW);
digitalWrite(dir2, HIGH);
}
else if (datos[1] == 'I')
{
  digitalWrite(dir1, HIGH);
digitalWrite(dir2, LOW);
}
else
{
  digitalWrite(dir1, LOW);
digitalWrite(dir2, LOW);
}

//Control luces
if (datos[3] == 'N' ){
 digitalWrite(luz_verde, HIGH);
}
else{
  digitalWrite(luz_verde, LOW);
}
 if (datos[4] == 'N' )
 {
  digitalWrite(luz_azul, HIGH);
 }
 else
 { digitalWrite(luz_azul, LOW);
 }

pos1 = (int)(datos[6]  << 8);
pos1 = pos1 | datos[7];
pulso1 = (int)((pos1*0.8514) + 505);
pos2 = (int)(datos[8]  << 8);
pos2 = pos2 | datos[9];
pulso2 = (int)((pos2*-0.8) + 2863);

pos3 = (int)(datos[10]  << 8);
pos3 = pos3 | datos[11];
pulso3 = (int)((pos3*0.729) + 546);
}
}



}
}


void updateServo (int pin, int pulse){
  digitalWrite(pin, HIGH);
  delayMicroseconds(pulse);
  digitalWrite(pin, LOW);
}

