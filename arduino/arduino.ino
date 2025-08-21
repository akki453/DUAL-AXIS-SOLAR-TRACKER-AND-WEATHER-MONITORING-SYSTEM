 #include <Servo.h>

// Define the servo objects

Servo horizontalServo;

Servo verticalServo;

// Define the LDR sensor pins

int ldrPins[] = {A0, A1, A2, A3};
int numSensors = sizeof(ldrPins) / sizeof(ldrPins[0]);

// Define the servo angle limits

int horizontalMinAngle = 0;

int horizontalMaxAngle = 180;

int verticalMinAngle = 0;

int verticalMaxAngle = 180;

// Define the threshold for light intensity

int lightThreshold = 500;

void setup() {

// Attach servos to corresponding pins

horizontalServo.attach(9);

verticalServo.attach(10);
horizontalServo.write(horizontalMinAngle);

verticalServo.write(verticalMinAngle);

// Set LDR sensor pins as INPUT

for (int i = 0; i < numSensors; i++) {

pinMode(ldrPins[i], INPUT);

}

}

void loop() {

// Read light intensity from LDR sensors

int sensorValues[numSensors];

for (int i = 0; i < numSensors; i++) {

sensorValues[i] = analogRead(ldrPins[i]);

}
int avgIntensity = 0;

for (int i = 0; i < numSensors; i++) {

avgIntensity += sensorValues[i];

}

avgIntensity /= numSensors;

// Check if light intensity is above threshold

if (avgIntensity > lightThreshold) {

// Calculate servo angles based on sensor readings

int horizontalAngle = map(sensorValues[1] — sensorValues[0], 0, 1023, horizontalMinAngle, horizontalMaxAngle);

int verticalAngle = map(sensorValues[3] — sensorValues[2], 0, 1023, verticalMinAngle, verticalMaxAngle);

// Set servo angles to track the light source

horizontalServo.write(horizontalAngle);

verticalServo.write(verticalAngle);

}
// Delay before next iteration

delay(100);

}