#include "i2cdevice.h"
#include <Arduino.h>

//Constructor for I2C Device
i2cdevice::i2cdevice(byte address, TwoWire *wire){
    
    setupDevice(address,wire);
    if(!checkConnection()){
        Serial.println(" error getting Data! Check the address, port number and wiring ");
        delay(1000);
    }
}

//setting up device address_ and i2c port
void i2cdevice::setupDevice(byte address, TwoWire *wire){

    address_ = address;
    wire1 = wire;
    return;
}


//Checking the validity of given information
bool i2cdevice::checkConnection(){

    byte error = 0;
    // switch (port_no_)
    // {
    // case 0:
    //     Wire.begin();
    //     Wire.beginTransmission(address_);
    //     error = Wire.endTransmission();
    //     break;
    // #ifdef TEENSY
    // case 1:
    //     Wire1.begin();
    //     Wire1.beginTransmission(address_);
    //     error = Wire1.endTransmission();
    //     break;
    // case 2:
    //     Wire2.begin();
    //     Wire2.beginTransmission(address_);
    //     error = Wire2.endTransmission();
    //     break;
  
    // default:
    //     Serial.println("Invalid Port! Teensy has only 3 ports.");
    //     break;
    // #endif
    // }
   wire1->begin();
   wire1->beginTransmission(address_);
   error = wire1->endTransmission();
        
    
    return (error == 0) ? true : false;
} 


//Reads bytes and updates in provided location
void i2cdevice::readBytesFromReg (byte regadd, unsigned int count,  byte* const values)
{
    // switch (port_no_)
    // {
    // case 0:
    //     Wire.beginTransmission(address_);
    //     Wire.write(regadd);
    //     Wire.endTransmission(false);
    //     count = Wire.requestFrom(address_,count);
    //     for (int i = 0; i < count; i++)
    //     {
    //         values[i] = Wire.read();
    //     }
    //     break;    
    // #ifdef TEENSY
    // case 1:
    //     Wire1.beginTransmission(address_);
    //     Wire1.write(regadd);
    //     Wire1.endTransmission(false);
    //     count = Wire1.requestFrom(address_,count);
    //     for (int i = 0; i < count; i++)
    //     {
    //         values[i] = Wire1.read();
    //     }
    //     break;     
 

    // case 2:
    //     Wire2.beginTransmission(address_);
    //     Wire2.write(regadd);
    //     Wire2.endTransmission(false);
    //     count = Wire2.requestFrom(address_,count);
    //     for (int i = 0; i < count; i++)
    //     {
    //         values[i] = Wire2.read();
    //     }
    //     break; 
        
        
    // default:
    //     Serial.println("Invalid Port. Teensy has only 3 ports");
    //     break;
    // #endif
    // }
    wire1->beginTransmission(address_);
    wire1->write(regadd);
    wire1->endTransmission(false);
    count = wire1->requestFrom(address_ , count);
    for(int i = 0 ; i<count ; i++){
        values[i] = wire1->read();
    }
    
    return;    
}
        
       

    


//Returns a byte read from given register
byte i2cdevice::readByteFromReg(byte regadd)
{
    byte Byte;
    readBytesFromReg(regadd,1,&Byte);
    return Byte;
}


//Returns a byte  with values of required bits read from given register
byte i2cdevice::readBitsFromReg(byte regadd,byte bitmask)
{
    int value;
    value = ( readByteFromReg( regadd) & bitmask );
    return value;

}

 //Reads an array of short ints from a reg location 
 void i2cdevice::readShortIntsFromReg( byte regadd,unsigned int count,short int* values)
{
   byte Bytes[2*count];
   readBytesFromReg(regadd,2*count,Bytes);
   for (int i = 0; i < count; i++)
   {
       values[i] = ((Bytes[ (2*i) ]<<8) + Bytes[(2*i) + 1 ]);
   }

   return;
   
} 

 //Reads an short int and returns it
 short int i2cdevice::readShortIntFromReg( byte regadd)
{
    short int short_int;
    readShortIntsFromReg(regadd,1,&short_int);

    return short_int;
} 




// write an array of bytes to a register location
void i2cdevice::writeBytesToReg(byte regadd, unsigned int count,byte* values)
{
    /*
    switch (port_no_)
    {
    case 0:
        Wire.beginTransmission(address_);
        Wire.write(regadd);
        for (int i = 0;i < count; i++){
            Wire.write(values[i]);
        }
        Wire.endTransmission(true);
        break;
    #ifdef TEENSY
    case 1:
        Wire1.beginTransmission(address_);
        Wire1.write(regadd);
        for (int i = 0;i < count; i++){
            Wire1.write(values[i]);
        }
        Wire1.endTransmission(true);
        break;

    case 2:
        Wire2.beginTransmission(address_);
        Wire2.write(regadd);
        for (int i = 0;i < count; i++){
            Wire2.write(values[i]);
        }
        Wire2.endTransmission(true);
        break;
    
    default:
        break;
    #endif
    }
    */
   wire1->beginTransmission(address_);
   wire1->write(regadd);
   for(int i = 0 ; i < count ; i++){
    wire1->write(values[i]);
   }
   wire1->endTransmission(true);

       

} 

// write a byte to a register 
void i2cdevice::writeByteToReg(byte regadd,byte  value)
{
    writeBytesToReg(regadd,1,&value);
    return;
} 



//write bits to a register
void i2cdevice::writeBitsToReg(byte regadd,byte bitmask,byte value)
{
    value = ((readByteFromReg(regadd) & (~bitmask)) | (value & bitmask));
    writeByteToReg(regadd,value);
    return;
}