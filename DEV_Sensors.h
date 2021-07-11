
////////////////////////////////////
//   DEVICE-SPECIFIC LED SERVICES //
////////////////////////////////////

#include <Wire.h>

struct DEV_TempSensor : Service::TemperatureSensor {     // A standalone Temperature sensor

  SpanCharacteristic *temp;                          // reference to the Current Temperature Characteristic
  int addr;                                          // I2C address of temperature sensor
  uint32_t timer=0;                                  // keep track of time since last update
  
  DEV_TempSensor(int addr) : Service::TemperatureSensor(){       // constructor() method

    this->addr=addr;                      // I2C address of temperature sensor

    Wire.begin();                         // start I2C in Controller Mode
    
    Wire.beginTransmission(addr);         // setup transmission
    Wire.write(0x0B);                     // ADT7410 Identification Register
    Wire.endTransmission(0);              // transmit and leave in restart mode to allow reading
    Wire.requestFrom(addr,1);             // request read of single byte
    uint8_t id = Wire.read();             // receive a byte

    Wire.beginTransmission(addr);         // setup transmission
    Wire.write(0x03);                     // ADT740 Configuration Register
    Wire.write(0xC0);                     // set 16-bit temperature resolution, 1 sampler per second
    Wire.endTransmission();               // transmit

    double tempC=getTemp();
             
    temp=new Characteristic::CurrentTemperature(tempC);       // instantiate the Current Temperature Characteristic
    temp->setRange(-50,100);                                  // expand the range from the HAP default of 0-100 to -50 to 100 to allow for negative temperatures
        
    Serial.printf("Configuring Temperature Sensor ADT7410 version 0x%02X with address 0x%02X: %0.2f C.\n",id,addr,tempC);           // initialization message

  } // end constructor

  void loop(){

    char c[64];

    if(millis()-timer>5000){                // only sample every 5 seconds
      timer=millis();
      
      Wire.beginTransmission(addr);         // setup transmission
      Wire.write(0x00);                     // ADT7410 2-byte Temperature
      Wire.endTransmission(0);              // transmit and leave in restart mode to allow reading
      Wire.requestFrom(addr,2);             // request read of two bytes
    
      double tempC=getTemp();

      if(abs(temp->getVal<double>()-tempC)>0.5){    // only update temperature if change is more than 0.5C     
        temp->setVal(tempC);                        // set the new temperature; this generates an Event Notification and also resets the elapsed time        
        sprintf(c,"ADT7410-%02X Temperature Update: %g\n",addr,tempC);
        LOG1(c);
      }
    }
    
  } // loop

  double getTemp(){
    Wire.beginTransmission(addr);         // setup transmission
    Wire.write(0x00);                     // ADT7410 2-byte Temperature
    Wire.endTransmission(0);              // transmit and leave in restart mode to allow reading
    Wire.requestFrom(addr,2);             // request read of two bytes

    double t;
    int16_t iTemp;
    
    iTemp=((int16_t)Wire.read()<<8)+Wire.read();    
    t=iTemp/128.0;
    return(t);    
  }
  
};
      
//////////////////////////////////
