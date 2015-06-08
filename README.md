# QuadWheelATR
Example code for our four wheeled vectoring robot plaforms. Example code includes support for a variety of motor controllers including our [LMD18200 motor controller](http://www.superdroidrobots.com/shop/item.aspx/pwm-motor-controller-3a-12-55v/583/ "SDR PWM Motor Controller") and Dimension Engineering's [Sabertooth motor controller](http://www.superdroidrobots.com/shop/item.aspx/sabertooth-dual-25a-motor-driver/822/ "Sabertooth Dual 25A Motor Controller") with and without the [Kangaroo motion controller](http://www.superdroidrobots.com/shop/item.aspx/kangaroo-x2-motion-controller/1514/ "Kangaroo Motion Controller"). 

## PWM Motor Controller Example
Motor demonstration using our [LMD18200 motor controller](http://www.superdroidrobots.com/shop/item.aspx/pwm-motor-controller-3a-12-55v/583/ "SDR PWM Motor Controller") (TE-058-000) which accepts a PWM input and a direction signal. This example should be easily portable to a variety of motor controllers.

## Sabertooth Motor Controller Example
Motor demonstration using a Dimension Engineering [Sabertooth 25A motor controller (TE-091-225)](http://www.superdroidrobots.com/shop/item.aspx/sabertooth-dual-25a-motor-driver/822/ "Sabertooth Dual 25A"). This example relies on the Sabertooth library linked below. 

## Kangaroo Motion Controller Example
Motor demonstration using a [Kangaroo motion controller (TE-180-000)](http://www.superdroidrobots.com/shop/item.aspx/kangaroo-x2-motion-controller/1514/ "Kangaroo Motion Controller") that's attached to a Sabertooth Dual 25A motor controller. The advantage to using the motion controller add-on is the ability to perform speed or position control. This example relies on the Kangaroo library linked below. 

# External Library Dependencies
__Sabertooth__ -   Library developed by Dimension Engineering for control of the Sabertooth and Syren motor controllers. 
http://www.dimensionengineering.com/info/arduino

__Kangaroo__ -   Library developed by Dimension Engineering to interface with the Kangaroo Motion Controller. 
http://www.dimensionengineering.com/info/arduino

# Updates
June 8th, 2015:
Added the Kangaroo example, added additional comments and general maintainence to the repo.

April 29th, 2015:
Added a second Arduino source file to provide support for Dimension Engineering Sabertooth motor controllers. 
