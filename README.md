# T-Junction Traffic Light Control System

## Project Documentation

A microcontroller-based embedded systems project developed using an **Arduino Uno** to simulate a **T-Junction traffic light control system**.  
The system manages multiple vehicle streams and pedestrian crossings with safety-focused sequencing, interrupt-driven inputs, and audible feedback.

**Core Concept:**  
**Sense (Inputs) → Decide (Logic) → Actuate (Lights & Buzzer)**

---

## 1. Introduction

This project focuses on the design, implementation, and testing of a traffic light control system for a T-junction using an Arduino Uno microcontroller.

The system controls:
- **Three vehicle traffic clusters**
- **Two pedestrian crossings**
- **Audible alerts for accessibility**
- **Interrupt-driven pedestrian requests**

The aim is to ensure **traffic safety**, **efficient vehicle flow**, and **safe pedestrian crossing**, reflecting real-world traffic control principles.

---

## 2. Rationale

### Purpose of the System
- Prevent collisions between traffic streams
- Provide safe and timed pedestrian crossings
- Improve traffic flow efficiency at intersections

### Why This Solution Matters
Traditional fixed-time traffic systems are not adaptive.  
This system improves responsiveness by:
- Allowing **pedestrian-initiated crossings**
- Using **interrupts** for immediate input detection
- Providing **audible feedback** for visually impaired users

Key concepts demonstrated:
- Real-time input processing
- Interrupt handling
- Timing and sequencing
- Safety-critical embedded system design

---

## 3. System Specification

### Hardware Components
- Arduino Uno microcontroller
- 9 LEDs for vehicle signals (Red, Yellow, Green × 3)
- 4 LEDs for pedestrian signals (Red & Green × 2)
- 2 pedestrian push buttons
- 1 piezo buzzer
- 13 × 220 Ω resistors
- Breadboards and jumper wires

### Functional Requirements

#### Vehicle Traffic Control
- Three independent traffic streams
- Red, Yellow, Green light sequencing
- Minimum green time: **7 seconds**
- Yellow warning time: **1.5 seconds**

#### Pedestrian Safety Features
- Two pedestrian crossings
- Button-triggered crossing phases
- Blinking green as crossing countdown
- Audible buzzer during crossing
- All vehicle lights turn red during pedestrian crossing

---

## 4. Design

### Hardware Design

The Arduino Uno acts as the central controller.  
Each traffic cluster consists of Red, Yellow, and Green LEDs connected through current-limiting resistors.  
Pedestrian systems include LEDs, push buttons, and a buzzer for audio feedback.

### Pin Configuration

#### Vehicle Light Clusters
- Cluster 1: Red (8), Yellow (9), Green (10)
- Cluster 2: Red (11), Yellow (12), Green (13)
- Cluster 3: Red (4), Yellow (5), Green (6)

#### Pedestrian Systems
- Crossing 1: Red (7), Green (A3), Button (2)
- Crossing 2: Red (A1), Green (A2), Button (3)

#### Buzzer
- Pin A0

---

## 5. Software Design

- Written in **Arduino C/C++**
- Uses **interrupt service routines (ISR)** for pedestrian buttons
- Pedestrian requests are latched and serviced safely after each traffic phase
- Program runs in three repeating traffic phases corresponding to each cluster

---

## 6. Build

The circuit was constructed using breadboards with clearly separated traffic and pedestrian sections.  
All LEDs were connected via 220 Ω resistors, and push buttons were configured using `INPUT_PULLUP` for stability.

---

## 7. Code Overview (Arduino / C++)

- Digital outputs control LEDs and buzzer
- Interrupts capture pedestrian button presses
- Timing controlled using `delay()`
- Audible and visual feedback provided during pedestrian crossing phases

---

## 8. Testing

The system was tested under multiple scenarios:
- Normal traffic flow without pedestrian requests
- Pedestrian button pressed during each traffic phase
- Verification of correct light sequencing and safety states

Results confirmed:
- Correct vehicle light transitions
- Immediate but safe pedestrian response
- Reliable buzzer operation

---

## 9. Conclusion

Building the T-Junction Traffic Light Control System provided valuable hands-on experience in **embedded systems design**.

Key learnings include:
- Effective use of interrupts
- Real-time system responsiveness
- Safety-focused design decisions
- Practical application of Arduino programming

This project strengthened skills in **C++ programming**, **circuit design**, and **problem-solving**, while demonstrating how embedded systems are used in real-world traffic control applications.

---

## License

Educational / Academic Use

