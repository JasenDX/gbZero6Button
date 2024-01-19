/*
    Author: Jason Mele
    Date Created: 12/17/2023
    Purpose: Translate the input from a Game Boy Zero DMG-01 6 button PCB to ASCII so it functions as a keyboard & can be read by the Pi
            Based on the program found on https://sudomod.com/game-boy-zero-guide-part-2/ written by wermy
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
  keys[0] = key('w', 2); //up arrow
  keys[1] = key('a', 3); //left arrow
  keys[2] = key('s', 4); //down arrow
  keys[3] = key('d', 5); //right arrow
  keys[4] = key('e', 6); //a
  keys[5] = key('f', 7); //b
  keys[6] = key('v', 8); //l1
  keys[7] = key('r', 9); //x
  keys[8] = key('g', 10); //y
  keys[9] = key('b', 16); //r1
  keys[10] = key('+',14); //start
  keys[11] = key('-',15); //select
  keys[12] = key('o',A0); //l2
  keys[13] = key('p',A1); //r2
  keys[14] = key('*',A2); //unused
  keys[15] = key('*',A3); //unused
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
