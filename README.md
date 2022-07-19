# AirCommanderEntireControl
Arduino library for serial communication with the Air Commander Entire. 

Version 1.0.0

The Air Commander Entire Control Library has been created to be used with Arduino-based systems that are directly interfaced with the Air Commander Entire. The Air Commander Entire speaks over UART (baud:115200) with 3.3V logic levels. To connect, you just need to connect the GND, TX, and RX pins to a device that is 3.3V-UART compatible. Reference the below link for a pinout of the connector. The Air Commander Entire needs to have the respective connector configured to be used with an Air Commander Link since this library uses the same protocol the Link controller uses. 

https://airpixel.cz/docs/serial-api-control/
