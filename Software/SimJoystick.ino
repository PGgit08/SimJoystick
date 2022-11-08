#include <Joystick.h>


// declare axis and throttle pins
#define XPIN 2
#define YPIN 1
#define THROTTLEPIN 0

// declare offsets for axis (like a trim wheel)
#define XOFF 0
#define YOFF 0


// declare button count
const int BUTTON_AMOUNT = 9;

// declare pins 
const int BUTTONPINS[BUTTON_AMOUNT] = {4, 5, 6, 7, 8, 9, 10, 16, 14};

// create a structure for a digital button (can also be a switch)
typedef struct Button {
  int pin;
  int id;
};

// list containing all digital buttons
Button buttons[BUTTON_AMOUNT];

// button index for assignment
int buttonIndex = 0;

// button id for assignment
int buttonId = 0;

// create a new Joystick object
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
  BUTTON_AMOUNT, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  true, true,          // Yes rudder and throttle
  false, false, false);  // No accelerator, brake, or steering

// controller variables
int throttle;
int x;
int y;


void setup() {
  // set up digital buttons 
  for (int i = 0; i <= (BUTTON_AMOUNT - 1); i++){
    // create a new button
    Button newButton;
    newButton.pin = BUTTONPINS[i];
    newButton.id = buttonId;
    
    buttons[buttonIndex] = newButton;

    // update assignment vars
    buttonIndex ++;
    buttonId ++;

    // set up button
    pinMode(newButton.pin, INPUT_PULLUP);
  }

  // set up Joystick
  Joystick.begin();
  Joystick.setXAxisRange(0, 1023);
  Joystick.setYAxisRange(0, 1023);
  Joystick.setRudderRange(0, 1023);
  Joystick.setThrottleRange(430, 700);
}

void loop() {
  // iterate through buttons and get their inputs
  for (int i = 0; i <= (BUTTON_AMOUNT - 1); i++){
    Button currentButton = buttons[i];
    // send button state based on readings
    if (digitalRead(currentButton.pin) == LOW){
      Joystick.setButton(currentButton.id, 1);
    }

    if (digitalRead(currentButton.pin) == HIGH){
      Joystick.setButton(currentButton.id, 0);
    }
  }

  // set Joystick axis values and throttle values
  throttle = analogRead(THROTTLEPIN);
  x = analogRead(XPIN) + XOFF;
  y = analogRead(YPIN) + YOFF;

  
  Joystick.setXAxis(x);
  Joystick.setYAxis(y);
  Joystick.setRudder(x);
  Joystick.setThrottle(throttle);
}
