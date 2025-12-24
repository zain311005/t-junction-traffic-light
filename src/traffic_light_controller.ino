/*
  T-Junction Traffic Light Control System (Arduino Uno)
  -----------------------------------------------------
  - 3 vehicle clusters (R/Y/G)
  - 2 pedestrian crossings (R/G) with push buttons
  - Interrupts used to latch pedestrian requests
  - Buzzer sounds during pedestrian "walk" phase
  - Safety rule: all vehicles RED during pedestrian crossing
*/

#include <Arduino.h>

// Vehicle lights
const int Red1 = 8,  Yellow1 = 9,  Green1 = 10;
const int Red2 = 11, Yellow2 = 12, Green2 = 13;
const int Red3 = 4,  Yellow3 = 5,  Green3 = 6;

// Pedestrian lights
const int PedRed1 = 7,  PedGreen1 = A3;
const int PedRed2 = A1, PedGreen2 = A2;

// Buzzer and buttons
const int PedBuzz = A0;
const int PedButton1 = 2;
const int PedButton2 = 3;

// Timing (ms)
const unsigned long GREEN_MS  = 7000;
const unsigned long YELLOW_MS = 1500;
const unsigned long ALL_RED_MS = 400;
const unsigned long WALK_MS = 6000;
const unsigned long FLASH_TOTAL_MS = 2400;
const unsigned long BLINK_ON_MS = 200;
const unsigned long BLINK_OFF_MS = 200;
const unsigned long DEBOUNCE_MS = 200;

volatile bool ped1Requested = false;
volatile bool ped2Requested = false;
volatile unsigned long lastPed1Press = 0;
volatile unsigned long lastPed2Press = 0;

// Helper functions
void setVehicleCluster(int r, int y, int g, bool redOn, bool yellowOn, bool greenOn) {
  digitalWrite(r, redOn ? HIGH : LOW);
  digitalWrite(y, yellowOn ? HIGH : LOW);
  digitalWrite(g, greenOn ? HIGH : LOW);
}

void allVehiclesRed() {
  digitalWrite(Red1, HIGH); digitalWrite(Red2, HIGH); digitalWrite(Red3, HIGH);
  digitalWrite(Yellow1, LOW); digitalWrite(Green1, LOW);
  digitalWrite(Yellow2, LOW); digitalWrite(Green2, LOW);
  digitalWrite(Yellow3, LOW); digitalWrite(Green3, LOW);
}

void allPedsRed() {
  digitalWrite(PedRed1, HIGH); digitalWrite(PedGreen1, LOW);
  digitalWrite(PedRed2, HIGH); digitalWrite(PedGreen2, LOW);
}

void runVehiclePhase(int r, int y, int g) {
  allVehiclesRed();
  delay(ALL_RED_MS);
  setVehicleCluster(Red1, Yellow1, Green1, true, false, false);
  setVehicleCluster(Red2, Yellow2, Green2, true, false, false);
  setVehicleCluster(Red3, Yellow3, Green3, true, false, false);
  setVehicleCluster(r, y, g, false, false, true);
  delay(GREEN_MS);
  setVehicleCluster(r, y, g, false, true, false);
  delay(YELLOW_MS);
  setVehicleCluster(r, y, g, true, false, false);
}

void runPedCrossing(int pedRedPin, int pedGreenPin) {
  allVehiclesRed();
  delay(ALL_RED_MS);
  allPedsRed();
  digitalWrite(pedRedPin, LOW);
  digitalWrite(pedGreenPin, HIGH);
  tone(PedBuzz, 800);
  delay(WALK_MS);
  noTone(PedBuzz);
  unsigned long start = millis();
  while (millis() - start < FLASH_TOTAL_MS) {
    digitalWrite(pedGreenPin, HIGH);
    delay(BLINK_ON_MS);
    digitalWrite(pedGreenPin, LOW);
    delay(BLINK_OFF_MS);
  }
  digitalWrite(pedGreenPin, LOW);
  digitalWrite(pedRedPin, HIGH);
}

bool consumePed1Request() {
  noInterrupts();
  bool req = ped1Requested;
  ped1Requested = false;
  interrupts();
  return req;
}

bool consumePed2Request() {
  noInterrupts();
  bool req = ped2Requested;
  ped2Requested = false;
  interrupts();
  return req;
}

void servicePedRequests() {
  bool doP1 = consumePed1Request();
  bool doP2 = consumePed2Request();
  if (doP1) runPedCrossing(PedRed1, PedGreen1);
  if (doP2) runPedCrossing(PedRed2, PedGreen2);
  allPedsRed();
  allVehiclesRed();
  delay(ALL_RED_MS);
}

// Interrupts
void ped1_ISR() {
  unsigned long now = millis();
  if (now - lastPed1Press < DEBOUNCE_MS) return;
  lastPed1Press = now;
  ped1Requested = true;
}

void ped2_ISR() {
  unsigned long now = millis();
  if (now - lastPed2Press < DEBOUNCE_MS) return;
  lastPed2Press = now;
  ped2Requested = true;
}

void setup() {
  pinMode(Red1, OUTPUT); pinMode(Yellow1, OUTPUT); pinMode(Green1, OUTPUT);
  pinMode(Red2, OUTPUT); pinMode(Yellow2, OUTPUT); pinMode(Green2, OUTPUT);
  pinMode(Red3, OUTPUT); pinMode(Yellow3, OUTPUT); pinMode(Green3, OUTPUT);
  pinMode(PedRed1, OUTPUT); pinMode(PedGreen1, OUTPUT);
  pinMode(PedRed2, OUTPUT); pinMode(PedGreen2, OUTPUT);
  pinMode(PedBuzz, OUTPUT);
  pinMode(PedButton1, INPUT_PULLUP);
  pinMode(PedButton2, INPUT_PULLUP);
  allVehiclesRed();
  allPedsRed();
  attachInterrupt(digitalPinToInterrupt(PedButton1), ped1_ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(PedButton2), ped2_ISR, FALLING);
}

void loop() {
  runVehiclePhase(Red1, Yellow1, Green1);
  servicePedRequests();
  runVehiclePhase(Red2, Yellow2, Green2);
  servicePedRequests();
  runVehiclePhase(Red3, Yellow3, Green3);
  servicePedRequests();
}
