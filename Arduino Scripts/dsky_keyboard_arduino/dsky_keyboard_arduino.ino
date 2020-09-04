/* @file CustomKeypad.pde
  || @version 1.0
  || @author Alexander Brevig
  || @contact alexanderbrevig@gmail.com
  ||
  || @description
  || | Demonstrates changing the keypad size and key values.
  || #
*/
#include <Keypad.h>
#include "Keyboard.h"

const byte ROWS = 5; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
//DONE: Converted numbers and symbols to ascii codes
//222 '\336' Keypad -
//223 '\337' Keypad +
//224 '\340' Keypad ENTER
//225 '\341' Keypad 1 and End
//226 '\342' Keypad 2 and Down Arrow
//227 '\343' Keypad 3 and PageDn
//228 '\344' Keypad 4 and Left Arrow
//229 '\345' Keypad 5
//230 '\346' Keypad 6 and Right Arrow
//231 '\347' Keypad 7 and Home
//232 '\350' Keypad 8 and Up Arrow
//233 '\351' Keypad 9 and PageUp
//234 '\352' Keypad 0 and Insert
char hexaKeys[ROWS][COLS] = {
  {'C', 'P', 'K', 'E'},
  {'\351', '\346', '\343', 'R'},
  {'\350', '\345', '\342', 'E'},
  {'\347', '\344', '\341', 'N'},
  {'\337', '\336', '\352', 'V'}
};
byte rowPins[ROWS] = {6, 5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {10, 9, 8, 7}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey) {
    Serial.println(customKey);
    Keyboard.print(customKey);
  }
}
