#include <AFMotor.h> 
#include <Servo.h> 
#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
#define MAX_SPEED 190 // sets speed of DC motors
#define MAX_SPEED_OFFSET 20
AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo; 
boolean goesForward=false;
int distance = 100;
int speedSet = 0;
long duration;
void setup() {
 myservo.attach(10); 
 myservo.write(95); 
 pinMode(TRIG_PIN, OUTPUT); 
 pinMode(ECHO_PIN, INPUT); 
 delay(500);
}
void loop() {
int distanceR = 0;
int distanceL = 0;
delay(40);
digitalWrite(TRIG_PIN, LOW);
 delayMicroseconds(2);
 digitalWrite(TRIG_PIN, HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIG_PIN, LOW);
 duration = pulseIn(ECHO_PIN, HIGH);
 distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
 // Displays the distance on the Serial Monitor
 Serial.print("Distance: ");
 Serial.print(distance);
 Serial.println(" cm");
if(distance<=15)
{
 moveStop();
 delay(100);
 moveBackward();
 delay(750);
25
 moveStop();
 delay(200);
 distanceR = lookRight();
 delay(200);
 distanceL = lookLeft();
 delay(200);
 if(distanceR>distanceL)
 {
 turnRight();
 moveStop();
 }
 else if(distanceR<distanceL)
 {
 turnLeft();
 moveStop();
 }
 
}else
{
 moveForward();
}
//distance = readPing();
}
int lookRight()
{
 myservo.write(50); 
 delay(500);
digitalWrite(TRIG_PIN, LOW);
 delayMicroseconds(2);
 digitalWrite(TRIG_PIN, HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIG_PIN, LOW);
 duration = pulseIn(ECHO_PIN, HIGH);
 distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
 // Displays the distance on the Serial Monitor
 Serial.print("Distance: ");
 Serial.print(distance);
 Serial.println(" cm");
 delay(500);
 myservo.write(95); 
 return distance;
}
int lookLeft()
{
 myservo.write(135); 
 delay(500);
 digitalWrite(TRIG_PIN, LOW);
 delayMicroseconds(2);
 digitalWrite(TRIG_PIN, HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIG_PIN, LOW);
 duration = pulseIn(ECHO_PIN, HIGH);
 distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
 // Displays the distance on the Serial Monitor
 Serial.print("Distance: ");
 Serial.print(distance);
 Serial.println(" cm");
 delay(500);
 myservo.write(95); 
 return distance;
 // delay(100);
}
void moveStop() {
 motor1.run(RELEASE); 
 motor2.run(RELEASE);
 motor3.run(RELEASE);
 motor4.run(RELEASE);
 } 
 
void moveForward() {
if(!goesForward)
 {
 goesForward=true;
 motor1.run(FORWARD); 
 motor2.run(FORWARD);
 motor3.run(FORWARD); 
 motor4.run(FORWARD); 
 for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down 
the batteries too quickly
 {
 motor1.setSpeed(speedSet);
 motor2.setSpeed(speedSet);
 motor3.setSpeed(speedSet);
 motor4.setSpeed(speedSet);
 delay(5);
 }
 }
}
void moveBackward() {
 goesForward=false;
 motor1.run(BACKWARD); 
 motor2.run(BACKWARD);
 motor3.run(BACKWARD);
 motor4.run(BACKWARD); 
 for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down 
the batteries too quickly
 {
 motor1.setSpeed(speedSet);
 motor2.setSpeed(speedSet);
 motor3.setSpeed(speedSet);
 motor4.setSpeed(speedSet);
 delay(5);
 }
} 
void turnRight() {
 motor1.run(RELEASE);
 motor2.run(FORWARD);
 motor3.run(FORWARD);
 motor4.run(RELEASE); 
 delay(2000);
 motor1.run(FORWARD); 
 motor2.run(FORWARD);
 motor3.run(FORWARD);
 motor4.run(FORWARD); 
} 
void turnLeft() {
 motor1.run(FORWARD); 
 motor2.run(RELEASE); 
 motor3.run(RELEASE);
 motor4.run(FORWARD); 
 delay(2000);
 motor1.run(FORWARD); 
 motor2.run(FORWARD);
 motor3.run(FORWARD);
 motor4.run(FORWARD);
}
