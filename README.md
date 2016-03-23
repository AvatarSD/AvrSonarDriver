#AvrSonarDriver
It's simple sonar(like sr04) driver, witch sending all data to UART port. Just Add any Echo-Trig sonar at maches pin, and it automatically send measured result to uart.
Also it can send a adc value for support sharp IR optical proximity sensors.

### Features
* Up to 16 echo-trig sonars
* Up to 16 optical proximity sensors
* Serial & parallel sonars measuring
* Order of sonars reading is adjusted

### Functionality
 Controller is do serial iterations. There is a one sonar measuring by one or several parallel sonars, witch do it at same time. Because we can't do measuring at all sonars at same time, we need to control witch sonars will do measuring at one iterations. This opportunity provides by this map:
```
#define NUM_OF_ITERATIONS 8
#define NUM_OF_SONARS 16
bool timingMap[NUM_OF_ITERATIONS*NUM_OF_SONARS] =
{
1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1,
0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0,
0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1,
0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1,
0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1,
0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0,
};
```
There is a one-dimension array(**NUM_OF_ITERATIONS** x **NUM_OF_SONARS**), witch provides a relations between iterations and witch sonars will do measuring at this iterations. The row(length is **NUM_OF_SONARS**) is one iteration and it match to sonar order and indicate, witch sonars will do measuring at this iteration. Must be written at internal buffer by method:
```
writeMap(timingMap, NUM_OF_ITERATIONS, NUM_OF_SONARS);
```
And save to EEPROM by:
```
saveMap();
```

### Connections
 * PORTB(PCINT0-7) is 0-7 sonars echo input
 * PORTA is trig for 0-7 sonars trig output
 * PORTC is trig for 8-15 sonars trig output
 * INT0-7 is 8-15 sonars echo input for parallel working
 * PORTF and PORTK is analog input for optical sensor
 *
 * PORTD0-3 is INT0-3
 * PORTE4-7 is INT4-7

Pins at arduino mega:
![](http://3.bp.blogspot.com/-5bIrGV8-TfE/VKSNL21TULI/AAAAAAAAAAk/UC4vz6oc-Wg/s1600/ARDUINO.Mega.Pinout.Diagram.png)

At my shield pins connections is follow:

<pre>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	0 1 2 3 4 … 14 15
Vcc	 * * * * *    * *
Trig * * * * *    * *
Echo * * * * *    * *
GND	 * * * * *    * *

Vcc	 * * * * *    * *
Vin	 * * * * *    * *
GND	 * * * * *    * *
</pre>

0-7 sonars can do only single-port measuring at one iterations opposite to 8-15 sonars, witch can do measuring in parallel mode, all at one iterations.

### Optical sensor:
Value from analog pins read after even iterations. Because relation between output and measured distance is different at different sensor, data value is raw from 10-bit adc with 2.56 volt reference voltage. In example, relations between distance and output voltage at Sharp GP2Y0A02YK0f:

![](http://a.pololu-files.com/picture/0J1124.600.png?d089c9f198a26180cccab9494b8e8c1e)

For prevent from unnecessary data from not connected ADC channel, value under 100 and greater than 1000 is dropped. There is a 100k pull-down on this inputs.

### Data Output Format

> $[char[2] portName][uint8_t pinNum][uint16_t distance][uint8_t  crc]

Where:

 **portName** is two character:
* SR - is sonar
* OP - is optical
* IT - send after even iteration, pinNum is math to 201 and distance are sonar iteration number
* SB - is "strobe", send after even cycle of iterations, **pinNum** is math to 200 and distance are increment number.

**pinNum** is number of input line.

**distance** is measured result. At sonar data is equal to cm. At optical data equal to 0.0025 volt.

**crc** is XOR of all previous byte.
