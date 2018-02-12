# Arduino-Sentry
Pixy camera vision system, both remote control and automatic control

The phone app is called "Arduino bluetooth controller" 

This project aims to utilize the Pixy Camera in conjunction with a Bluetooth module and a Samsung Galaxy S7 smart phone, using a Bluetooth terminal application. This project has 2 modes, manual mode and auto mode.

Manual Mode: In manual mode we coded the Bluetooth terminal to accept values from 0 to 4, using a Left, Right, Up, and Down controller configuration to move the Pixy camera via Bluetooth. When pushing these buttons, the Pixy camera would move accordingly until a stop button which is labeled “Start” on the terminal controller.

Auto Mode: In this mode we coded the circle, square, triangle and X buttons to accept the different colored signatures the we programmed into Pixy, those colors are Blue, Red, Green, and Purple. So when we pushed one of those 4 buttons it would then track that color and that color only. Any other colors that came into contact with the Pixy with not their color chosen were then just disregarded and ignored by the Pixy, even with their color showing up on Pixy’s LED.
