#ifndef DATA_TRANSFER_H
#define DATA_TRANSFER_H

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "dataTransfer_Config.h"

class Transfer {
  public:
    Transfer(int CE, int CSN, int byteCount);

    bool init(uint8_t pipe, CommunicatorType communicatorType, const uint8_t* radioAddress);

    void write(BIT_OR_BYTE bitOrByte, int index, int value = 1);
    byte read(BIT_OR_BYTE bitOrByte, int index);  // true = bit, false = byte

    void send(bool resetBuffer = true);  // It is HIGHLY recommended that resetBuffer stays true; otherwise you will will continue to add bits and make your data nonsensical
    bool receive();   // returns true when data is received, false if otherwise

    uint8_t * _dataArray;  // buffer for all the data. This must be determined correctly; the first few bytes are for determining which sensors have data, and the bytes thereafter hold relevant data that require their own bytes. 

  private:
    
    RF24 radio;

    int _byteCount;

    // uint8_t * _dataArray;  // buffer for all the data. This must be determined correctly; the first few bytes are for determining which sensors have data, and the bytes thereafter hold relevant data that require their own bytes. 

};

#endif