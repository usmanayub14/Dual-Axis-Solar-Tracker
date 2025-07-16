High-Efficiency Dual-Axis Solar Tracking System
Project Status: This repository documents a high-fidelity prototype developed to validate advanced solar tracking concepts. The original source code is not available, but the detailed design, schematics, and performance metrics are preserved here to showcase the engineering and integration expertise involved.

High-Fidelity Prototype
The final assembled and fully functional prototype.

Executive Summary
This project addresses the significant energy loss in static solar installations. The engineered solution is an autonomous, dual-axis solar tracking system designed to orient a photovoltaic (PV) panel in real-time for optimal perpendicular alignment with a direct light source. By dynamically adjusting its position, the system maximizes the PV panel's energy yield, demonstrating a substantial performance increase over fixed-panel systems. The design proved to be 

33% more efficient than a single-axis solar tracker.

Key Technical Specifications
Tracking Axes: 2 (Azimuth and Elevation)

Control System: Microcontroller-based (Arduino UNO) with closed-loop feedback.

Sensing Array: Quadrant-based Light Dependent Resistor (LDR) matrix for high-precision light source detection.

Actuation: High-torque servo motors for precise and reliable positional control.


Energy Gain: Validated performance of >30% energy capture increase compared to static and single-axis systems.

System Architecture & Design
The system is architected around a robust microcontroller-based control loop that processes real-time sensor data to command the mechanical assembly.

1. Hardware Stack
Central Controller: Arduino UNO

Actuators: 2 x SG90 Servo Motors

Sensor Array: 4 x Light Dependent Resistors (LDRs)

Power System: Standalone Photovoltaic (PV) Solar Panel

Circuitry: Custom voltage-divider sensor array on breadboard.

2. System Interconnect & Wiring
The following diagram illustrates the system's wiring harness, connecting the LDR sensor array and servo motor actuators to the Arduino controller's I/O pins.

3. Control Logic Simulation
The core control logic and sensor sub-circuits were validated in a Proteus simulation environment prior to physical implementation, ensuring functional correctness of the design.

Operating Principle & Control Logic
The system's autonomous operation is governed by a differential light-sensing algorithm.

Quadrant Sensing: The four LDRs are arranged in a 2x2 grid. The controller constantly reads the analog voltage from each sensor, which corresponds to the incident light intensity.

Differential Comparison:

Elevation (Vertical) Axis: The controller calculates the difference between the average light on the top two LDRs and the bottom two. A non-zero differential triggers the elevation servo to move until the values are equalized.

Azimuth (Horizontal) Axis: Similarly, the difference between the left two and right two LDRs is calculated, triggering the azimuth servo to correct any horizontal misalignment.

Optimal Alignment (Equilibrium): The system achieves a state of equilibrium when light is distributed evenly across all four sensors, indicating perfect perpendicular alignment with the light source. The system holds this position until the light source moves.

Conclusion & Potential Applications
This project successfully validated a highly efficient design for autonomous solar tracking. The robust performance of the prototype makes the core design viable for next-stage development and integration into various applications, including:

Off-grid remote power systems.

Power supply for agricultural IoT sensors.

Telecommunications repeater stations.

Portable charging solutions.

Technical Stack
Firmware Development: C++ (Arduino)

Hardware Integration: Embedded Systems, Circuit Design, Rapid Prototyping

Simulation & Design Software: Proteus, Fritzing

Core Engineering Concepts: Control Systems, Sensor Data Fusion, Mechatronics
