# Hexapod-movement-system
I built this code for my physical Hexapod project. The chassis was 3D-printed using ABS plastic, and all joints are powered by MG90S metal-gear servos

The firmware is designed for an Arduino-based microcontroller to control custom tripod gait walking sequences (`MoveForward`, `TurnRight`, `TurnLeft`) with smooth servo interpolation.

## Hardware & Pinout Arrangement

* **Microcontroller:** Arduino Uno 
* **Actuators:** 12x MG90S Servos
* **Chassis Material:** 3D-Printed ABS Plastic
* **Power Supply:** External 5V high-current power supply 

## How It Works

**Physical Servo Calibration (`baseAngles`):**
* Uses a custom angle array to compensate for individual horn offsets and mechanical variations on each physical joint.

**Smooth Movement Engine (`moveMultipleSmooth`):**
* Incremental joint stepping logic that moves all 12 servos simultaneously, preventing high current spikes and sudden mechanical jerk.

**Tripod Gait Engine (`groupA` / `groupB`):**
* Alternates two sets of 3 legs (`{4, 0, 8}` and `{6, 10, 2}`) to execute forward movement and turns while maintaining constant static stability.
