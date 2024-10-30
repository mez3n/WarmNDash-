# WarmNDash-


This project implements a **car seat heater control system** using the [**FreeRTOS kernel**](https://www.freertos.org/Documentation/00-Overview) on the [**TM4C123GH6PM microcontroller**](https://www.ti.com/product/TM4C123GH6PM). The system divides responsibilities into **tasks**, enabling precise control of seat temperature, real-time error reporting, and efficient CPU utilization. The heater intensity adjusts based on **ambient temperature** readings from the **ADC driver**, with **buttons for manual adjustment**. An **EEPROM-based error reporting** module ensures persistence, and the entire project is **event-driven** with a CPU load as low as **2%.**

---

## Project Features

- **Modular task design**: Each core functionality is encapsulated in an independent task.
- **Temperature adjustment per seat**: Buttons allow the user to set individual seat temperatures.
- **Adaptive heater intensity**: Ambient car temperature (via ADC) dynamically adjusts heater output.
- **EEPROM-based error reporting**: Persistent storage of error events and status for diagnostics.
- **CPU load optimization**: Event-driven design results in minimal CPU usage (as low as 2%).
- **Runtime measurement tracking**: Measure runtime for each task to analyze system performance and reports using the UART driver.

---

## System Architecture

The project is implemented with **FreeRTOS tasks** to handle various operations:

1. **Button Handler Task**  
   - Monitors user input to increase or decrease seat temperature for each seat.
   - Sends events to adjust the target temperature.

2. **Temperature Control Task**  
   - Reads the ambient temperature using the **ADC driver**.  
   - Adjusts heater intensity dynamically based on temperature readings.  

3. **Heater Control Task**  
   - Modulates the heater intensity based on input from the temperature task.  
   - Sends feedback on the heater's status to the error module if needed.

4. **Error Reporting Task**  
   - Uses the **EEPROM driver** to store errors persistently (e.g., sensor failures, button malfunctions).  
   - Provides diagnostic information during system boot-up.

5. **Runtime Monitoring Task**  
   - Tracks and logs runtime for each task to ensure performance targets are met.  
   - Provides insights into **CPU load** and task execution times for debugging and optimization.

---

## Hardware Components

- **TM4C123GH6PM Microcontroller**  
- **Buttons** for manual seat temperature control  
- **Temperature Sensor** (via ADC) for ambient temperature measurement simulated with potentiometers
- **Heaters** for each seat  simulated as LEDS

---

## How to Build and Flash the Code

1. download the .bin file
   ```
2. flash the code using Texas insteruments [LM flash programmer](https://www.ti.com/tool/LMFLASHPROGRAMMER)

---


## Error Handling and Diagnostics

- **EEPROM Error Reports**:  
  Stores errors related to button malfunctions, ADC failures, or heater issues.  

---

## Performance Metrics

- **CPU Load**:  
  The system is designed to be **event-driven**, with a CPU load as low as **2%** during idle periods.
- **Runtime Measurements**:  
  Each task's execution time is tracked to ensure efficient scheduling.

---



