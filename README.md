# bouncer
A garage door opener powered by an ESP8266. ([More info here](http://0xc0ded.com/category/bouncer))

My garage door opener has a wired button that gets installed next to the door to go inside. It has three buttons on it, but I'm only interested in two of them: the one that controls the lights, and the other that controls the door. Below is the schematic for those two buttons. It's wired to my garage door opener with two wires (+/-14v).

![Door Button Schematic](http://0xc0ded.com/assets/schematic-doorswitch.png)

My goal is to make those two buttons accessible from Alexa, and a web page. To do this, I'm using an [ESP8266](https://www.adafruit.com/product/2471), and a couple relays. Both buttons are toggles, so I need a way for the system to know when the door is open/closed, and when the light is on/off. For determining the state of the door, I plan on using an [hc-sr04](https://www.amazon.com/SainSmart-HC-SR04-Ranging-Detector-Distance/dp/B004U8TOE6). If I mount this module on the ceiling with the hc-sr04 pointing down, I can tell when the door is open because the door will block the hc-sr04's view of the ground. As for the light... I'm not sure I care that much. I'm ok with it just being a toggle.

I also want to add timer functionality that will close the door automatically if it's been open for x minutes after a certain time at night.

I've created an initial layout using [Fritzing](http://fritzing.org). Below is the breadboard layout.

![Bouncer Breadboard](http://0xc0ded.com/assets/breadboard-bouncer.png)

The power connector in the top right is 5v. That will power the ESP8266 and the hc-sr04. Unlike the hc-sr04, the ESP8266 is a 3.3v board. However, the Adafruit Huzzah development board I'm using has built-in voltage regulation up to 16v. The green block terminal on the bottom right, is where the 14v from the garage door opener will plug in.

For wiring up the gpio's I've found the [elinux raspberry pi gpio documentation](https://elinux.org/RPi_GPIO_Interface_Circuits) very useful. I've see examples all over the internet of people wiring the hc-sr04's 5v _echo_ pin directly to a gpio on the ESP8266. As far as I know, these are not made to handle a 5v signal. The [voltage divider](https://elinux.org/RPi_GPIO_Interface_Circuits#Voltage_divider) on the elinux documentation came in handy for knocking that 5v down to a tolerable 3.2v.

I also used the elinux examples for switching 5v loads with a 3.3v gpio pin by using NPN transistors. You can see those in the breadboard diagram next to each of the relays.
