#include <Servo.h>

// Servo
Servo servo_eyelid, servo_eye;

// Servo angles
int eyelid_min = 40, eyelid_max = 100;
int eye_min = 45, eye_max = 135;

// Current time and previous time
unsigned long prev = 0, current = 0, elapsed = 0;

// Time interval
unsigned long interval_milli_sec = 150;
unsigned long eye_interval_milli_sec = 1000;
unsigned long current_eye_interval = 0;
unsigned long eyelid_interval_milli_sec = 3000;
unsigned long current_eyelid_interval = 0;

int eyelid_basepos = eyelid_max;
int eye_motion_number = 0;
int blink_motion_number = 0;

void setup() {

  servo_eye.attach(11);
  servo_eyelid.attach(13);

}

void loop() {

  // Get the current time in milliseconds
  current = millis();

  // Calculate the time elapsed since the previous loop iteration
  elapsed = (current - prev);

  // Execute control of the eye and eyelid servos each time interval_milli_sec elapses
  if(elapsed >= interval_milli_sec){

    ///servo for eyes
    current_eye_interval += elapsed;
    if(current_eye_interval >= eye_interval_milli_sec){
      int angle = 90;
      if(eye_motion_number == 0){
        angle = eye_min;
        eye_motion_number++;
      }else if(eye_motion_number == 1){
        angle = eye_max;
        eye_motion_number++; 
      }else{
        eye_motion_number = 0;
      }
      servo_eye.write(angle);

      current_eye_interval = 0;
    }

    ///servo for eyelid
    current_eyelid_interval += elapsed;
    if(blink_motion_number == 1){
      servo_eyelid.write(eyelid_basepos);
      blink_motion_number = 0;            
    }
    if(current_eyelid_interval >= eyelid_interval_milli_sec){

      if(blink_motion_number == 0){
        servo_eyelid.write(eyelid_min);
        blink_motion_number++;
      }

      current_eyelid_interval = 0;
    }
    
    prev = current;
  }

}
