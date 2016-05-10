#include <Wire.h>
#include <HMC5883L.h>

HMC5883L compass;
int error = 0;
long int tiempo1,tiempo0,tiempof;
uint16_t delta=0;
uint16_t gradosant=0;
void setup()
{
  Serial.begin(2000000);
  Wire.begin(); 
  compass = HMC5883L(); // Construct a new HMC5883 compass.
  error = compass.SetScale(1.3); // Set the scale of the compass.
  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  delay(4000);
  tiempo0=millis();
}

void loop(){
MagnetometerScaled scaled = compass.ReadScaledAxis();
float heading = atan2(scaled.YAxis, scaled.XAxis);
float declinationAngle = 0.029;
heading += declinationAngle;
if(heading < 0)
heading += 2*PI;
if(heading > 2*PI)
heading -= 2*PI;
float headingDegrees = heading * 180/M_PI; 
Output(headingDegrees);
tiempo1=millis();
tiempof=tiempo1-tiempo0;
if(tiempof>20000){
   Serial.write(0xff);
    Serial.write(0xff);
     Serial.write(0xff);
    Serial.write(0xff);
  while(1){
    }
  }

}

void Output(float headingDegrees){
  uint8_t x=0;
  uint8_t y=0;
  uint8_t d1,d2;
  uint16_t aux=uint16_t(headingDegrees);
  if (headingDegrees >270) {
    x=byte(64-(64*(360-aux)/90));
    y=byte(64+(64*(aux-270)/90));
  }else if (headingDegrees> 180){
    x=byte(64-(64*(aux-180)/90));
    y=byte(64-(64*(270-aux)/90));
  }else if(headingDegrees>90){
    x=byte(64+(64*(180-aux)/90));
    y=byte(64-(64*(aux-90)/90));
  }else{
    x=byte(64+(64*aux/90));
    y=byte(64+(64*(90-aux)/90));
  }
  if(x>127){
    x=127;
    }
  if(y>127){
    y=127;
    }  
  delta=delta+7000;
  if(delta>65535){
    delta=0;
    }
  //if(aux>gradosant){
//    x=x|0x80;
//    y=y|0x80;
    d1=(delta>>8)&0xff;
    d2=delta&0xff;
    Serial.write(y);
    Serial.write(x);
    Serial.write(d1);
    Serial.write(d2);
//    gradosant=aux;
//  }else if(aux<gradosant){
//    y=y|0x80;
//    d1=(delta>>8)&0xff;
//    d2=delta&0xff;
//    Serial.write(y);
//    Serial.write(x);
//    Serial.write(d1);
//    Serial.write(d2);
//    gradosant=aux;
//  }else{
//  }
    delay(7);
    
}
