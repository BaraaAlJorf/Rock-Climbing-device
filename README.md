# Rock-Climbing-device
Description: This is a project I worked on with three other students over a period of three weeks. Our main goal was to create a device that could facilitate rock-climbing bouldering competitions. Bouldering competitions are timed climbing competitions in which the climber who climbs the heighest in the alotted time wins. One problem we thought climbers might face is the inability to comfortably track their height and the time remaining. In order to solve this, Our team set to create a device that measures the height of the climber and displays the remaining time.
# The Concept
Initially, we were debating different ways to measure the height. At first, we thought using an accelerometer to measure the momentary acceleration and then double integrate it to calculate the height would work, but practically speaking, the accelerometers were not accurate when itegrating. We therefore resorted to a more reliable and accurate method of measurement which was to use air pressure. We decided to use the BMP280 air pressure sensor and add it to our circuitboard. Air pressure is more accurate because it requires only one conversion to calculate the height. The BMP280 chip is also decently priced and is pretty small so attaching it to our circuitboard was a wise decision.
# The device

 ![Alt Text](https://github.com/BaraaAlJorf/PerformingRobots/blob/master/October4/20201004_212302.jpg)
 ![Alt Text](https://github.com/BaraaAlJorf/PerformingRobots/blob/master/October4/20201004_212302.jpg)

The device mainly consists of our circuitboard which included two sets of five LEDs. The set on the left corresponds to remaining time and the one on the left corresponds to height above ground. The set on the left is initally all lit up and the LEDs turn off every one minute (there are four white LEDs that turn off and one yellow LED that indicates that this is the time column.) The set on the right is intially all off (except for one LED at the bottom which indicates that this is the height column.) Every one meter that the climber climbs, an LED is lit up. The circuitboard is covered by a two layers of resin one transparent layer at the top and one white layer at the bottom. The white layer is attached to a resin hook that in turn attaches to the climbing rope.

# Video of Functionality

 ![Alt Text](https://drive.google.com/file/d/1YkaZkCXYiNBTf-IOtIrgaM6jbR-h7BGu/view?usp=sharing)
 
As the person goes up the stairs holding the device, more height LEDS light up and as time passes the time LEDs turn off
