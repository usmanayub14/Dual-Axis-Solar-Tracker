/*****************************************************************************************
 *
 * Project: High-Efficiency Dual-Axis Solar Tracker
 * Author: Usman Ayub
 * Date: July 2024
 *
 * Description:
 * This firmware controls a dual-axis solar tracker. It uses four Light Dependent
 * Resistors (LDRs) to detect the direction of the brightest light source. Based on the
 * sensor readings, it commands two servo motors to adjust the solar panel's orientation
 * on both the horizontal (azimuth) and vertical (elevation) axes to maximize light exposure.
 *
 * This code is a professional reconstruction of the original project firmware.
 *
 * Hardware:
 * - Arduino UNO or compatible microcontroller
 * - 2 x SG90 or similar servo motors
 * - 4 x Light Dependent Resistors (LDRs)
 * - 4 x 10k Ohm pull-down resistors
 * - Solar Panel and mechanical assembly
 *
 * Pinout:
 * - Horizontal Servo: Pin 9
 * - Vertical Servo:   Pin 10
 * - LDR Top-Left:     Analog Pin A0
 * - LDR Top-Right:    Analog Pin A1
 * - LDR Bottom-Left:  Analog Pin A2
 * - LDR Bottom-Right: Analog Pin A3
 *
 *****************************************************************************************/

// Include the Servo library to control the motors
#include <Servo.h>

// --- Configuration Constants ---

// Create servo objects to control the two servos
Servo horizontalServo;
Servo verticalServo;

// Define the analog pins for the LDR sensors
const int LDR_PIN_TL = A0; // Top-Left
const int LDR_PIN_TR = A1; // Top-Right
const int LDR_PIN_BL = A2; // Bottom-Left
const int LDR_PIN_BR = A3; // Bottom-Right

// Define the digital pins for the servo motors
const int SERVO_PIN_H = 9;  // Horizontal servo
const int SERVO_PIN_V = 10; // Vertical servo

// Define the sensitivity threshold. A larger value means the system will only
// react to larger differences in light levels, making it less "twitchy".
const int SENSITIVITY_THRESHOLD = 20;

// Define servo movement limits to prevent mechanical damage (0-180 degrees)
const int H_SERVO_MIN = 0;
const int H_SERVO_MAX = 180;
const int V_SERVO_MIN = 45; // Often, vertical servos don't need the full range
const int V_SERVO_MAX = 135;

// Define the step size for servo movement. Smaller values result in smoother tracking.
const int SERVO_STEP = 1;

// --- Global Variables ---

// Variables to store the current position of the servos
int servoH_pos = 90;
int servoV_pos = 90;

// Variables to store the raw values from the LDR sensors
int ldr_tl_val;
int ldr_tr_val;
int ldr_bl_val;
int ldr_br_val;


void setup() {
  // Initialize Serial communication for debugging purposes
  Serial.begin(9600);
  Serial.println("Dual-Axis Solar Tracker Initializing...");

  // Attach the servo objects to their respective pins
  horizontalServo.attach(SERVO_PIN_H);
  verticalServo.attach(SERVO_PIN_V);

  // Set the initial position of the servos to the center
  horizontalServo.write(servoH_pos);
  verticalServo.write(servoV_pos);

  // Allow servos time to move to the initial position
  delay(1000);
  Serial.println("Initialization Complete. Starting tracking loop.");
}


void loop() {
  // --- 1. Read Sensor Values ---
  // Read the analog values from all four LDRs
  ldr_tl_val = analogRead(LDR_PIN_TL);
  ldr_tr_val = analogRead(LDR_PIN_TR);
  ldr_bl_val = analogRead(LDR_PIN_BL);
  ldr_br_val = analogRead(LDR_PIN_BR);

  // --- 2. Calculate Average Light Levels ---
  // Calculate the average light level for each quadrant
  int avg_top = (ldr_tl_val + ldr_tr_val) / 2;
  int avg_bottom = (ldr_bl_val + ldr_br_val) / 2;
  int avg_left = (ldr_tl_val + ldr_bl_val) / 2;
  int avg_right = (ldr_tr_val + ldr_br_val) / 2;

  // --- 3. Calculate Light Differentials ---
  // Calculate the difference in light between opposing quadrants
  int diff_vertical = avg_top - avg_bottom;
  int diff_horizontal = avg_left - avg_right;

  // --- 4. Control Logic for Servo Movement ---

  // Vertical Axis Control (Elevation)
  if (abs(diff_vertical) > SENSITIVITY_THRESHOLD) {
    if (avg_top > avg_bottom) {
      // If top is brighter, move the panel up (decrease servo angle)
      servoV_pos = max(V_SERVO_MIN, servoV_pos - SERVO_STEP);
    } else {
      // If bottom is brighter, move the panel down (increase servo angle)
      servoV_pos = min(V_SERVO_MAX, servoV_pos + SERVO_STEP);
    }
    verticalServo.write(servoV_pos);
  }

  // Horizontal Axis Control (Azimuth)
  if (abs(diff_horizontal) > SENSITIVITY_THRESHOLD) {
    if (avg_left > avg_right) {
      // If left is brighter, move the panel left (increase servo angle)
      servoH_pos = min(H_SERVO_MAX, servoH_pos + SERVO_STEP);
    } else {
      // If right is brighter, move the panel right (decrease servo angle)
      servoH_pos = max(H_SERVO_MIN, servoH_pos - SERVO_STEP);
    }
    horizontalServo.write(servoH_pos);
a  }

  // --- 5. Debugging Output (Optional) ---
  // Print sensor values and servo positions to the Serial Monitor for debugging
  /*
  Serial.print("H: ");
  Serial.print(servoH_pos);
  Serial.print(" | V: ");
  Serial.print(servoV_pos);
  Serial.print(" | DiffV: ");
  Serial.print(diff_vertical);
  Serial.print(" | DiffH: ");
  Serial.println(diff_horizontal);
  */

  // Add a small delay to prevent the system from being too reactive and to save power
  delay(50);
}
