uint32_t tmp=0,t0=0,tf=0;
uint8_t tmp1=0,tmp2=0,tmp3=0,tmp4=0;
long int timer0,timer1,timerf;
///////////////////////////////////////CÓDIGO PARA ULTRASONIDO, ENVÍA DELTA DE TIEMPO Y SI HAY SPK O NO
void setup(){
  Serial.begin(2000000);
  pinMode(9, OUTPUT); /*activación del pin 9 como salida: para el pulso ultrasónico*/
  pinMode(3, INPUT); /*activación del pin 8 como entrada: tiempo del rebote del ultrasonido*/
 /*activación del pin 9 como salida: para el pulso ultrasónico*/
  delay(4000);
  timer0=millis();
}

void loop(){
  
  digitalWrite(9,LOW); /* Por cuestión de estabilización del sensor*/
  delayMicroseconds(5);
  digitalWrite(9, HIGH); /* envío del pulso ultrasónico*/
  delayMicroseconds(10);
  tmp=pulseIn(3, HIGH); /* Función para medir la longitud del pulso entrante. Mide el tiempo que transcurrido entre el envío
  del pulso ultrasónico y cuando el sensor recibe el rebote, es decir: desde que el pin 12 empieza a recibir el rebote, HIGH, hasta que
  deja de hacerlo, LOW, la longitud del pulso entrante*/
  tmp1=(tmp>>24)&0xff;
  tmp2=(tmp>>16)&0xff;
  tmp3=(tmp>>8)&0xff;
  tmp4=tmp&0xff;
  Serial.write(tmp1);
  Serial.write(tmp2);
  Serial.write(tmp3);
  Serial.write(tmp4);//350 micros aprox
   delay(14);
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
  
}
