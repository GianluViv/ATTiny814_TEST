#include <Arduino.h>
#include "global.h"
#include "PinDefinitionsAndMore.h" // Set IR_RECEIVE_PIN for different CPU's
#include "TinyIRReceiver.hpp" 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_TINYIR));
  // Enables the interrupt generation on change of IR input signal
  if (!initPCIInterruptForTinyReceiver()) {
    Serial.println(F("No interrupt available for pin " STR(IR_RECEIVE_PIN))); // optimized out by the compiler, if not required :-)
    }
#if defined(USE_FAST_PROTOCOL)
  Serial.println(F("Ready to receive Fast IR signals at pin " STR(IR_RECEIVE_PIN)));
#else
  Serial.println(F("Ready to receive NEC IR signals at ARDUINO pin " STR(IR_RECEIVE_PIN)));
#endif
  }

void loop() {
  if (TinyReceiverDecode()) {

#if !defined(USE_FAST_PROTOCOL)
    // We have no address at FAST protocol
    Serial.print(F("Address=0x"));
    Serial.print(TinyIRReceiverData.Address, HEX);
    Serial.print(' ');
#endif

    Serial.print(F("Command=0x"));
    Serial.print(TinyIRReceiverData.Command, HEX);
    if (TinyIRReceiverData.Flags == IRDATA_FLAGS_IS_REPEAT) {
      Serial.print(F(" Repeat"));
      }
    if (TinyIRReceiverData.Flags == IRDATA_FLAGS_PARITY_FAILED) {
      Serial.print(F(" Parity failed"));

#if !defined(USE_EXTENDED_NEC_PROTOCOL) && !defined(USE_ONKYO_PROTOCOL)
      Serial.print(F(", try USE_EXTENDED_NEC_PROTOCOL or USE_ONKYO_PROTOCOL"));
#endif

      }
    Serial.println();
    }
  }

