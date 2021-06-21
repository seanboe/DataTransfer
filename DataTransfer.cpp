#include "DataTransfer.h"


Transfer::Transfer(int CE, int CSN, int byteCount) : radio(CE, CSN)  {

  _byteCount = byteCount;

  _dataArray = (byte *) malloc(_byteCount);
  for (int x = 0; x < _byteCount; x++)
    _dataArray[x] = 0;

};

bool Transfer::init(uint8_t pipe, CommunicatorType communicatorType, const uint8_t* radioAddress) {
  if (!radio.begin()) return false;
  radio.setChannel(CHANNEL);
  switch (communicatorType) {
    case RECEIVER:    radio.openReadingPipe(pipe, radioAddress); break;
    case TRANSMITTER: radio.openWritingPipe(radioAddress); break;
  }
  radio.setPALevel(RF24_PA_MIN);
  switch (communicatorType) {
    case RECEIVER:    radio.startListening(); break;
    case TRANSMITTER: radio.stopListening(); break;
  }
  return true;
};


void Transfer::write(BIT_OR_BYTE bitOrByte, int index, int value) {
  if (bitOrByte == BIT) {
    switch(value) {
      case 0: 
        if (read(BIT, index)) 
          _dataArray[((int)ceil(((index - (index % 8))/8)))] -= BITS[index % 8];
        break;
      case 1: 
        if (!read(BIT, index))
          _dataArray[((int)ceil(((index - (index % 8))/8)))] += BITS[index % 8];
        break;
    }
  }
  else if (bitOrByte == BYTE) {
    _dataArray[index] = value;
  }
};


byte Transfer::read(BIT_OR_BYTE bitOrByte, int index) {

  // index serves two roles:
  // when returning bits, index represents the index of bits in the array of bytes (_dataArray)
  // when returning bytes, index represents the index of bytes in _dataArray (or just the array index)

  if (bitOrByte == BIT) {
    if ((_dataArray[((int)ceil(((index - (index % 8))/8)))] & BITS[index % 8]) == BITS[index % 8])
      return 1;
    else 
      return 0;
  }

  // else, the user is requesting a Byte
  else
    return _dataArray[index];
};

void Transfer::send(bool resetBuffer) {
  // uint8_t dataArray[5] = {0,1,2,3,4};
  radio.write(_dataArray, _byteCount);      // possibly incorrect

  if (resetBuffer) {
    for (int x = 0; x < _byteCount; x++) 
      _dataArray[x] = 0;
  }
};

bool Transfer::receive() {
  if (radio.available()) {
      radio.read(_dataArray, _byteCount);
    return true;
  }
  return false;
}