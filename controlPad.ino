/*
    Author: Jason Mele
    Date Created: 12/17/2023
    Purpose: Translate the input from a Game Boy Zero DMG-01 6 button PCB to ASCII so it functions as a keyboard & can be read by the Pi
*/


#include <Bounce2.h>
#include <Keyboard.h>

#define NUM_KEYS 16

struct Key {
  char keycode;
  Bounce* bounce;
};

Key keys[NUM_KEYS];

Key key(char keycode, int pin) {
  Key *ret = new Key;
  ret->keycode = keycode;
  ret->bounce = new Bounce(pin, 10);
  pinMode(pin, INPUT_PULLUP);
  return *ret;
}

void setupKeys() {
  keys[0] = key('w', 2);
  keys[1] = key('s', 3);
  keys[2] = key('a', 4);
  keys[3] = key('d', 5);
  keys[4] = key('p', 6);
  keys[5] = key('l', 7);
  keys[6] = key('o', 8);
  keys[7] = key('k', 9);
  keys[8] = key('x', 10);
  keys[9] = key('z', 16);
  keys[10] = key('q',14);
  keys[11] = key('e',15);
  keys[12] = key('m',A0);
  keys[13] = key('n',A1);
  keys[14] = key('b',A2);
  keys[15] = key('c',A3);
}

void setup() {
  setupKeys();
  Keyboard.begin();
  //  pinMode(0, INPUT_PULLUP);
}

void loop() {
  for (int i = 0; i < NUM_KEYS; i++) {
    keys[i].bounce->update();
    if (keys[i].bounce->fallingEdge()) {
      Keyboard.press(keys[i].keycode);
    } else if (keys[i].bounce->risingEdge()) {
      Keyboard.release(keys[i].keycode);
    }
  }
}
