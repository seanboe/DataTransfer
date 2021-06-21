// This is where important radio parameters are defined


// size of your data buffer. This MUST be the same on both devices that are communicating
#define BUFFER_SIZE   5
#define CHANNEL       125

const uint8_t BITS[8] = {0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b10000000};

typedef enum {
  BIT, BYTE
} BIT_OR_BYTE;

typedef enum {
  RECEIVER, TRANSMITTER
} CommunicatorType;