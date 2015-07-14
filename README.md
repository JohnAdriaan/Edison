SparkFun GPIO Block for Edison C++ Examples
===========================================

SparkFun's GPIO Block for Edison provides access to 16 of the Edison's GPIO
pins. Each channel passes through a level shifter which allows it to interface
with higher voltage signals than the nominal 1.8V which the Edison uses for
its own signal switching levels. The voltage can be selected with an on-board
solder jumper to be either 3.3V or to be the current VSYS voltage.

Here's a list of the signals available on the block:

Edison Pin | MRAA Pin | Secondary Use | Notes  
---------------------------------------------  
GP12       | 20       | PWM0          | 1  
GP13       | 14       | PWM1          | 1  
GP14       | 36       | None          | 1,2  
GP15       | 48       | None          | 1,2  
GP44       | 31       | None          | 2  
GP45       | 45       | None          | 2  
GP46       | 32       | None          | 2,3  
GP47       | 46       | None          | 1,2,3  
GP48       | 33       | None          | 1,2,3  
GP49       | 47       | None          | 1,2,3  
GP128      | 13       | UART1 CTS     |   
GP129      | 25       | UART1 RTS     |  
GP130      | 26       | UART1 RX      | 4  
GP131      | 35       | UART1 TX      | 4  
GP182      | 0        | PWM2          |  
GP183      | 21       | PWM3          |    

Notes:  
1 - Signal also used on H-Bridge Block  
2 - Signal also used on OLED Block  
3 - Signal also used on 9DOF Block  
4 - Signal also available on UART Block  

Repository Contents
-------------------

* **SparkFun_GPIO_Edison_Block_Example.cpp** - example code which will show you
how to access all of the functions in the library.

Documentation
--------------

* **[Programming the Intel Edison](https://learn.sparkfun.com/tutorials/edison-getting-started-guide)** -
Getting up and running with the Edison. Start here!
* **[General Block Information](https://learn.sparkfun.com/tutorials/general-guide-to-sparkfun-blocks-for-intel-edison)** - 
Information applicable to all blocks, such as power requirements and how to
install them.
* **[Programming the Edison](https://learn.sparkfun.com/tutorials/programming-the-intel-edison-beyond-the-arduino-ide)** -
This library uses Intel's [mraa](https://github.com/intel-iot-devkit/mraa) 
library to access hardware resources. This tutorial will help you get started
using mraa to write code in C++. **This is not an Arduino library.**
* **[GPIO Block Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-blocks-for-intel-edison---gpio-block)** - 
Hookup guide specific to this block, which includes information on the circuits
used in the demo code.

Products that use this Library 
---------------------------------

* [GPIO Block](https://www.sparkfun.com/products/13038)

License Information
-------------------

This product is _**open source**_! 

The code is released under GPL. 

Distributed as-is; no warranty is given.

- Your friends at SparkFun.

