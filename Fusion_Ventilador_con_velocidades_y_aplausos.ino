#include <IRremote.h>

IRrecv IR(3);
int microfono = 4;
int lectura_microfono = 0;
int vel3 = 10;
int a = 0;
int b = 0;
int vel1 = 8;
int vel2 = 9;



void setup() {
  //pinMode(10, OUTPUT);
  Serial.begin(9600);
  IR.enableIRIn();
  pinMode(microfono, INPUT);
  pinMode(vel1, OUTPUT);
  pinMode(vel2, OUTPUT);
  pinMode(vel3, OUTPUT);
  Serial.begin(9600);
}

void loop() {

lectura_microfono=digitalRead (microfono); //LEEMOS EL ESTADO QUE TIENE EL MICROFONO

if (lectura_microfono==HIGH) //SI TENEMOS UN APLAUSO?
{
  a=a+1;  // A=0+1=1 TENEMOS UN APLAUSO Y SEGUIRA AUMENTANDO CON CADA APLUSO 
  b=0;    //B=0 BANDERA PARA ENTRAR A BUCLES
  delay(200);
}
if(a==1 && b==0)   // SI TENEMOS 1 APLAUSO Y B=0 ENTONCES ENCENDEMOS EL FOCO
{
Serial.println("ENCENDIDO");
digitalWrite(vel3,HIGH);      //ENCENDEMOS FOCO
b=1;                         //B=1 PARA SALIR DE BUCLE Y PODER CAMBIAR
}

if (a==2)       //SI TENEMOS 2 APALUSOS?
   {
    Serial.println ("APAGADO"); //APAGAMOS
    digitalWrite(vel3,LOW);
    a=0;                       //REGRESAMOS EL CONTADOR A 0
   }

  if(Serial.available()){
    int dato=Serial.read();
    if(dato=='A'){
      digitalWrite(vel3, HIGH);
      delay(10);
    }
    if(dato=='B'){
      digitalWrite(vel3, LOW);
      delay(10);
    }
  }
  if (IR.decode()){
    Serial.println(IR.decodedIRData.decodedRawData, HEX);
          if (IR.decodedIRData.decodedRawData == 0xEE11FB04){
      digitalWrite(vel1, HIGH);
    }
          if (IR.decodedIRData.decodedRawData == 0xF708FB04){
      digitalWrite(vel1, LOW);
    }
         /* if (IR.decodedIRData.decodedRawData == 0xED12FB04){
      digitalWrite(vel3, HIGH);
    }
          if (IR.decodedIRData.decodedRawData == 0xF708FB04){
      digitalWrite(vel3, LOW);
    }*/
          if (IR.decodedIRData.decodedRawData == 0xED12FB04){
      digitalWrite(vel2, HIGH);
    }
          if (IR.decodedIRData.decodedRawData == 0xF708FB04){
      digitalWrite(vel2, LOW);
    }
   
    delay(10);
    IR.resume();
   }
  }
