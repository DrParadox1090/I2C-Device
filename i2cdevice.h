#ifndef i2cdevice_H
#define i2cdevice_H
#include <Arduino.h>
#include <Wire.h>

 class i2cdevice 
{
    protected:
        byte address_;
        unsigned int port_no_;
        TwoWire *wire1;
   
    public:
    //Initializer Functions

        i2cdevice() =default;
        i2cdevice(byte address,TwoWire *wire );
        bool checkConnection();
        
        
        //read Functions
        void readBytesFromReg (byte regadd, unsigned int count, byte* values);
        byte readByteFromReg (byte regadd);
        byte readBitsFromReg(byte regadd,byte bitmask);
        void readShortIntsFromReg (byte regadd, unsigned int count, short int* values);
        short int  readShortIntFromReg (byte regadd);
        
        //write Functions
        void  writeBytesToReg(byte regadd,unsigned int count,byte* value);
        void  writeByteToReg(byte regadd,byte value);
        void  writeBitsToReg(byte regadd, byte bitmask,byte value);

    protected:
        void setupDevice(byte address, TwoWire *wire );
        
};
#endif