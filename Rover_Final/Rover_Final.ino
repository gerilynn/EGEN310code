#include <Servo.h>

int stepnumber = 0;
int data = 0;
int LED1 = 0;
int LED2 = 0;
int i = 0;
int step_speed = 2;
int count = 0;
int inflate_time = 90000;

Servo servoRLeft; 
Servo servoRRight;
Servo servoFRight;
Servo servoFLeft;

void setup() {
  
  // servos for wheels
  servoRLeft.attach(9);
  servoRRight.attach(6);
  servoFRight.attach(11);
  servoFLeft.attach(10);
  servoFLeft.writeMicroseconds(1500);
  servoFRight.writeMicroseconds(1500);
  servoRLeft.writeMicroseconds(1500);
  servoRRight.writeMicroseconds(1500);

  //stepper motor for retrieval
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);

  // LEDs
 
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  // Relay

  pinMode(3, OUTPUT);

  Serial.begin(9600); 
}

void loop() {

  if(LED1 == 1){
    digitalWrite(4, HIGH);
  }
  else if(LED1 == 0){
    digitalWrite(4, LOW);
  }
  if(LED2 == 1){
    digitalWrite(5, HIGH);
  }
  else if(LED2 == 0){
    digitalWrite(5, LOW);
  }
  if(Serial.available() > 0){
    data = Serial.read();
    Serial.println(data);
     
// Rover stop
    
  if(data == 88){
   digitalWrite(3, LOW);
   servoRLeft.writeMicroseconds(1500);
   servoRRight.writeMicroseconds(1500); 
   servoFLeft.writeMicroseconds(1500);
   servoFRight.writeMicroseconds(1500); 
  }

  // Rover Reverse
    
  else if(data == 66){
   servoRLeft.writeMicroseconds(1450);
   servoRRight.writeMicroseconds(1550); 
   servoFLeft.writeMicroseconds(1450);
   servoFRight.writeMicroseconds(1550);
  }

  // Rover Forward
    
  else if(data == 70){
   servoRLeft.writeMicroseconds(1550);
   servoRRight.writeMicroseconds(1450); 
   servoFLeft.writeMicroseconds(1550);
   servoFRight.writeMicroseconds(1450);
  }

  // Turn Right
  else if(data == 82){
   servoRLeft.writeMicroseconds(1550);
   servoRRight.writeMicroseconds(1550); 
   servoFLeft.writeMicroseconds(1550);
   servoFRight.writeMicroseconds(1550);
  }
  // Turn Left
  else if(data == 76){
   servoRLeft.writeMicroseconds(1450);
   servoRRight.writeMicroseconds(1450); 
   servoFLeft.writeMicroseconds(1450);
   servoFRight.writeMicroseconds(1450);
  }
     
  // Balloon Launch
  else if(data == 86){          // ON
      //digitalWrite(3, HIGH);    // trigger relay turning on heater/fan
      //for(i=0; i<inflate_time; i++){   // LEDs flash while heater/fan runs for 3 min
        //digitalWrite(5, HIGH);
        //delay(1000);
        //digitalWrite(5, LOW);
        //delay(1000);
      //}
    digitalWrite(3, LOW);          // turn off heater fan
    for(int i=0; i<20380; i++){   // stepper turns on after 3 min
      OneStep(true);
      delay(step_speed);
      count++;

      if(Serial.available() > 0){
       data = Serial.read();
       Serial.println(data);

         // Stepper speed

      if(data <= 59){
      switch(data){
        case 49:
          step_speed = 2;
          break;
  
        case 50:
          step_speed = 2.5;
          break;

        case 51:
          step_speed = 3;
          break;
        
        case 52:
          step_speed = 3.5;
          break;

        case 53:
          step_speed = 4;
          break;

        case 54:
          step_speed = 4.5;
          break;

        case 55:
          step_speed = 5;
          break;

        case 56:
          step_speed = 5.5;
          break;

        case 57:
          step_speed = 6;
          break;

        case 58:
          step_speed = 6.5;
          break;

        case 59:
          step_speed = 7;
          break;
        }
       }
     }
   }
 }
  else if(data == 118){          // Off
    for(int i=0; i<count; i++){   // stepper motor retrieves the balloon
    OneStep(false);
    delay(step_speed);
       
    if(Serial.available() > 0){
      data = Serial.read();
      Serial.println(data);
         
  // Stepper speed

  if(data <= 59){
    switch(data){
      case 49:
        step_speed = 2;
        break;
  
        case 50:
          step_speed = 2.5;
          break;

        case 51:
          step_speed = 3;
          break;
        
        case 52:
          step_speed = 3.5;
          break;

        case 53:
          step_speed =4;
          break;

        case 54:
          step_speed =4.5;
          break;

        case 55:
          step_speed = 5;
          break;

        case 56:
          step_speed = 5.5;
          break;

        case 57:
          step_speed = 6;
        break;

        case 58:
        step_speed = 6.5;
        break;

        case 59:
        step_speed = 7;
        break;
        
        }
      }
    }
  }
}
 // Yellow LEDs

  else if(data == 87){  // Lights on
    LED1 = 1;
    delay(100);
    }
  else if(data == 119){ // Lights off
    LED1 = 0;
    delay(100);
    } 
  // Red LEDs

  else if(data == 85){  // Lights on
    LED2 = 1;
    delay(100);
    }
  else if(data == 117){ // Lights off
    LED2 = 0;
    delay(100);
    } 
  }
}
 

void OneStep(bool dir){
  
  if(dir){
    switch(stepnumber){
      case 0:   
        digitalWrite(13, HIGH);
        digitalWrite(12, LOW);
        digitalWrite(8, LOW);
        digitalWrite(7, LOW);
        break;

      case 1:
        digitalWrite(13, LOW);
        digitalWrite(12, HIGH);
        digitalWrite(8, LOW);
        digitalWrite(7, LOW);
        break;

      case 2: 
        digitalWrite(13, LOW);
        digitalWrite(12, LOW);
        digitalWrite(8, HIGH);
        digitalWrite(7, LOW);
        break;
 
      case 3:
        digitalWrite(13, LOW);
        digitalWrite(12, LOW);
        digitalWrite(8, LOW);
        digitalWrite(7, HIGH);
        break;
      }
    }else{
      switch(stepnumber){
        case 0:   
          digitalWrite(13, LOW);
          digitalWrite(12, LOW);
          digitalWrite(8, LOW);
          digitalWrite(7, HIGH);
          break;

        case 1:
          digitalWrite(13, LOW);
          digitalWrite(12, LOW);
          digitalWrite(8, HIGH);
          digitalWrite(7, LOW);
          break;

        case 2: 
          digitalWrite(13, LOW);
          digitalWrite(12, HIGH);
          digitalWrite(8, LOW);
          digitalWrite(7, LOW);
          break;

        case 3:
          digitalWrite(13, HIGH);
          digitalWrite(12, LOW);
          digitalWrite(8, LOW);
          digitalWrite(7, LOW);
          break;
        }
      }
      stepnumber++;
      if(stepnumber > 3){
        stepnumber = 0;
      }
    }
