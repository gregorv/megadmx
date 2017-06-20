# megadmx
An ATmega88 based LED dimmer, strobe and fog controller.

For a small project I needed an DMX controller for a 30W-70W white LED stroboscope, a length of RGB LED tape and a relay controlling a Eurolite N10 fog machine. The circutry is based on an ATmega88 controller (hence the repository name), with cheap
FETs for dimming and a beefy FET for the strobe. Cheap 24V 3A and 12V 2A switching power supplies from ebay power the device.

## DMX Channels
The controller uses 7 DMX channels. The starting address can be set with software or a 5 pin jumper header. Therefore, without firmware flashing only 32 different addresses are possible. :/

| Channel | Function                                |
| :-----: | :-------------------------------------- |
| 1       | Tape Dimmer 0-255                       |
| 2       | Tape Red 0-255                          |
| 3       | Tape Green 0-255                        |
| 4       | Tape Blue  0-255                        |
| 5       | Tape Strobe Frequency 1-255, 0 off      |
| 6       | LED Power Strobe Frequency 1-255, 0 off |
| 7       | Fog Off 0-126, Fog On 127-255           |

## Hardware Description
The mainboard is powered with +12V over a two pin connector. The supply current is used to light the LED tape. A 7805 generates the voltage for the microprocessor. A standard SP485 IC is used as DMX interface.

The PCB is designed to be home-etchable with the photo-transfer method. The PCB size can be _significantly_ reduced if a proper plated 2-layer layout is used.

### LED Tape Connection
A four pin connector is used for connecting a standard 12V LED tape with common anode. The pin layout follows the standard cabling order for this kind of tape.

| Pin | Function |
| :-: | -------- |
| 1   | +12 V    |
| 2   | Green    |
| 3   | Red      |
| 4   | Blue     |

### Power Strobe Connection
The power LED strobe circuit is a IRF540N Power-MOSFET switching a screw terminal input to ground. Connect a power LED low-side equiped with a suitable power supply (read: constant current / current limited). Note: the LED flashes when the circuit is turned on, because the FET driving ciruit invertes the logic state of the processor pin. This is a nice visual feedback that the device is switched on.

### Fog Machine Connection
We use a Eurolite N10 smoke machine. It is very cheap (less than 40€), the remote control switches mains voltages for the fluid pump, making it very simple to interface the machine with a simple relay. Note that part of the circuit is live on mains voltage, use the N10 control only if you know about the risks and neccessary safety procedures.

## Software Description

Peter Flery UART library for DMX reception.

TIMER0 overflow interrupt generates 3 channel PWM for LED tape.

TIMER2 in CTC interrupt generates strobe for tape and power LED.
