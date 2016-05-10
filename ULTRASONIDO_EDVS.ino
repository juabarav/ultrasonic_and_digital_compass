short unsigned int distanciaant=0;
short unsigned int distancia;
long df=8;
long tiempo,timer0,timer1,timerf;
byte Ycoor=0x8A;
uint16_t tim1=0,tim2=0,tim3=0,tim4=0;
short unsigned int t1=0x00;
long tiempoant=0;
void printtime();

void setup(){
  Serial.begin(2000000);
  pinMode(9, OUTPUT); /*activación del pin 9 como salida: para el pulso ultrasónico*/
  pinMode(3, INPUT); /*activación del pin 8 como entrada: tiempo del rebote del ultrasonido*/
  delay(4000);
  timer0=millis();
}

void loop(){
  uint8_t Xaux,tm1,tm2;
  double aux;
  int auxint;
  tim1=(uint16_t)micros();
  digitalWrite(9,LOW); /* Por cuestión de estabilización del sensor*/
  delayMicroseconds(5);
  digitalWrite(9, HIGH); /* envío del pulso ultrasónico*/
  delayMicroseconds(10);
  tiempo=pulseIn(3, HIGH); /* Función para medir la longitud del pulso entrante. Mide el tiempo que transcurrido entre el envío
 */
 
  tim2=(uint16_t)micros();
  tim3=tim2-tim1;
  
  if(tim3>65533){
    tim3=0;
    }
 if(tiempo>10000){
  tiempo=10000;
  }
  aux=.014*tiempo;
  auxint=(int)aux;
  if(tiempo>tiempoant){
    tm1=(tim3>>8)&0xff;
    tm2=tim3&0xff; 
    Xaux=(uint8_t)auxint;//.00647 para 20000 max
    Xaux=Xaux|0x80;
    Serial.write(Ycoor);
    Serial.write(Xaux); 
    Serial.write(tm1);
    Serial.write(tm2); 
  }else if(tiempo<tiempoant){
    tm1=(tim3>>8)&0xff;
    tm2=tim3&0xff;  
    Xaux=(uint8_t)auxint;//.00647 para 20000 max
    Xaux=Xaux&0x7f;
    Serial.write(Ycoor);
    Serial.write(Xaux); 
    Serial.write(tm1);
    Serial.write(tm2); 
    }
    timer1=millis();
    timerf=timer1-timer0;
    if(timerf>20000){
      Serial.write(0xff);
    Serial.write(0xff); 
    Serial.write(0xff);
    Serial.write(0xff); 
      while(1){
        }
      }
  tiempoant=tiempo;
  delay(14);
  
}

void printtime(){
  /*
  if(t1==0xff){
    tim3++;
    t1=0;
      if(tim3==0xff){
        tim3=0;
        tim2++;
        if(tim2==0xff){
          tim2=0;
          tim1++;
          if(tim1==0xff){
            tim1=0;
            tim2=0;
            tim3=0;
            t1=0;
            }
          }
        
        }
   }
      Serial.write(tim1);
      Serial.write(tim2);
      Serial.write(tim3);
      Serial.write(t1);
      //Serial.println(".");
    */  
   
}
