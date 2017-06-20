# megadmx
An ATmega88 based LED dimmer, strobe and fog controller.

For a small project I needed an DMX controller for a 30W-70W white LED stroboscope, a length of RGB LED tape and a relay controlling a Eurolite N10 fog machine. The circutry is based on an ATmega88 controller (hence the repository name), with cheap
FETs for dimming and a beefy FET for the strobe. Cheap 24V 3A and 12V 2A switching power supplies from ebay power the device.

## DMX Channels
The controller uses 7 DMX channels. The starting address can be set with software or a 5 pin jumper header. Therefore, without firmware flashing only 32 different addresses are possible. :/

| Channel | Function                      |
| :-----: | :---------------------------- |
| 1       | Tape Dimmer 0-255             |
| 2       | Tape Red 0-255                |
| 3       | Tape Green 0-255              |
| 4       | Tape Blue  0-255              |
| 5       | Tape Strobe 1-255, 0 off      |
| 6       | LED Power Strobe 1-255, 0 off |
| 7       | Fog Off 0-126, Fog On 127-255 |

## Hardware Description
### LED Tape Connection
### Power Strobe Connection
### Fog Machine Conection

## Software Description


