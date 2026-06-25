# WIP PS1 to PC SPI Bridge

This is a personal hardware and firmware project where I'm using an **ATmega32U4** microcontroller to read inputs from an original PlayStation 1 controller and send them to a PC.

## The Setup
I built this from the ground up by directly soldering the microcontroller to the PS1 controller's pins. It uses the ATmega's hardware SPI pins, plus a couple of standard GPIOs for the Chip Select and ACK lines to handle the original Sony protocol.

## Under the Hood
The ATmega acts as the SPI Master and talks to the controller at 250kHz (SPI_MODE3, LSBFIRST).
It runs on a strict Full-Duplex loop: 
- Dropping the CS line to open the communication frame.
- Sending the Start command (0x01) followed by the actual Polling command (0x42) on the MOSI line.
- Reading the controller's ID (e.g., 0x41 for Digital) and button states on the MISO line simultaneously.
- I use a hardware interrupt on the ACK line to wait for the controller to process each byte. This is crucial to avoid overflowing its internal processor!

## Huge Thanks & Credits
A massive shoutout to **Jacques Gagnon** for his amazing reverse-engineering documentation on the PlayStation SPI interface during the development of his *BlueRetro* project. 

PlayStation SPI Interface Documentation by Jacques Gagnon (https://hackaday.io/project/170365-blueretro/log/186471-playstation-playstation-2-spi-interface)

His detailed logic analyzer traces and deep dive into the PSX command payloads were absolutely crucial for this project. The documentation provided the exact timings, the ACK line behavior, and the precise breakdown of the data packets based on the controller ID, which made building the theoretical frame architecture possible.
