# TI_LLC_100kW Software
This is the project for the integrated LLC and buck-boost converter for fuel cell electric vehicle using TMS320F2837xS MCU.

# What was Done:
- Create low-level software for ADC, ePWM, CAN communication to operate the LLC full-brige resonant converter topology

- Config a high-speed CAN protocol 500kbps to communicate with other ECUs in a vehicle. ADC software was also added to provide ADC sensor value for the double-loop controller in application software.

- In the application parts, the doubled-loop controller is used to regulate the output voltage and current of the LDC converter.

- In diagnostic parts, LDC will detect the failure of over current, over/under voltage, and over temperature to protect the converter when it works in the abnormal condition. The fault signals are then sent to the vehicle control unit (VCU) via the CAN bus.
