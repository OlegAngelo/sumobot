  /*  Arduino DC Motor Control - PWM | H-Bridge | L298N
          Example 02 - Arduino Robot Car Control
      by Dejan Nedelkovski, www.HowToMechatronics.com
  */

  // motor A connections
  #define enA 9
  #define in1 8
  #define in2 7

  // motor B connections
  #define enB 3
  #define in3 5
  #define in4 4

  void setup() {
    // Set all the motor control pins to outputs
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    // Turn off motors - Initial state
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    Serial.begin(9600);
  }

  void loop() {
    // If joystick stays in middle the motors set 0 unless acted upon
    int motorSpeedA = 0;
    int motorSpeedB = 0;

    int xAxis = analogRead(A0);  // Read Joysticks X-axis
    int yAxis = analogRead(A1);  // Read Joysticks Y-axis

    Serial.print("X: ");
    Serial.println(xAxis);
    Serial.print("Y: ");
    Serial.println(yAxis);

    // Y-axis used for forward and backward control
    if (yAxis <= 470) {
      Serial.println("inside yAxis less than 470"); 
      // Set Motor A backward
      digitalWrite(in1, 0);
      digitalWrite(in2, 1);
      // Set Motor B backward
      digitalWrite(in3, 1);
      digitalWrite(in4, 0);
      // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(yAxis, 470, 0, 0, 255);
      motorSpeedB = map(yAxis, 470, 0, 0, 255);

      Serial.print("motorSpeedA: ");
      Serial.println(motorSpeedA);
      Serial.print("motorSpeedB: ");
      Serial.println(motorSpeedB);
    } else if (yAxis >= 535) {
      Serial.println("inside greater than 535 yAxis");
      // Set Motor A forward
      digitalWrite(in1, 1);
      digitalWrite(in2, 0);
      // Set Motor B forward
      digitalWrite(in3, 0);
      digitalWrite(in4, 1);
      // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(yAxis, 535, 1023, 0, 255);
      motorSpeedB = map(yAxis, 535, 1023, 0, 255);

      Serial.print("motorSpeedA: ");
      Serial.println(motorSpeedA);
      Serial.print("motorSpeedB: ");
      Serial.println(motorSpeedB);
    }

    // X-axis used for left and right control
    if (xAxis <= 470) {
      // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
      int xMapped = map(xAxis, 470, 0, 0, 255);
      // Move to left - decrease left motor speed, increase right motor speed
      motorSpeedA = motorSpeedA - xMapped;
      motorSpeedB = motorSpeedB + xMapped;
      // Confine the range from 0 to 255
      if (motorSpeedA < 0) {
        motorSpeedA = 0;
      }
      if (motorSpeedB > 255) {
        motorSpeedB = 255;
      }
    }
    if (xAxis >= 471) {
      // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
      int xMapped = map(xAxis, 550, 1023, 0, 255);
      // Move right - decrease right motor speed, increase left motor speed
      motorSpeedA = motorSpeedA + xMapped;
      motorSpeedB = motorSpeedB - xMapped;
      // Confine the range from 0 to 255
      if (motorSpeedA > 255) {
        motorSpeedA = 255;
      }
      if (motorSpeedB < 0) {
        motorSpeedB = 0;
      }
    }

    // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
    if (motorSpeedA < 70) {
      motorSpeedA = 0;
    }
    if (motorSpeedB < 70) {
      motorSpeedB = 0;
    }

    analogWrite(enA, motorSpeedA);  // Send PWM signal to motor A
    // Serial.print("end: motorSpeedA");
    // Serial.println(motorSpeedA);

    analogWrite(enB, motorSpeedB);  // Send PWM signal to motor B
    // Serial.print("end : motorSpeedB");
    // Serial.println(motorSpeedB);
    delay(1000);
  }
