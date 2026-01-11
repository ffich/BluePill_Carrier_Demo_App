# BluePill Carrier Demo Application

This repository contains a **demo firmware application for the STM32F103 “Blue Pill”**, developed to validate and showcase the functionality of a **custom BluePill carrier board**.

The project integrates **CAN bus communication**, **ADC-based sensor acquisition**, and a lightweight **task-oriented execution model** using **CHAOS RTOS**, providing a clean and deterministic embedded architecture suitable for real hardware bring-up and experimentation.

---

## ✨ Features

### 🚗 CAN Bus Communication
- CAN transmission and reception using STM32 **bxCAN** peripheral (HAL)
- Polling-based CAN RX
- Configurable acceptance filters
- Tested on a real CAN bus with external transceiver

### 🌡️ ADC Sensor Acquisition
- ADC1 multi-channel scan conversion
- LM35 temperature sensor support (LM35DMX/NOPB on IN2)
- Conversion from raw ADC values to temperature in °C
- Proper sampling time configuration for stable measurements

### 🧠 CHAOS RTOS Integration
- Cooperative task execution model
- Deterministic scheduling
- Minimal runtime overhead
- Clear separation between hardware access and application logic
- Suitable for low-resource microcontrollers

### 🔌 Board Bring-Up & Validation
- Designed as a functional demo for a custom BluePill carrier board
- Validates:
  - Power rails
  - Analog inputs
  - CAN communication
- Acts as a reference firmware for hardware validation

---

## 🧩 Project Architecture

The application logic is implemented in:
os_integration/chaos_demo_tasks.c


The firmware is structured around **CHAOS RTOS tasks**, each responsible for a specific subsystem:

- CAN message handling (TX/RX)
- ADC sampling and temperature computation
- Periodic system activities

This task-based structure ensures:
- Predictable execution
- Easy extensibility
- High readability
- Clean separation of concerns







