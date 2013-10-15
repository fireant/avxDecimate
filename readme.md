Decimation:
----------
This library implements a polyphase FIR decimation filter. The decimation class is used to decimate the input signal by a factor of two.

Low-pass filter:
---------------
This matlab command is used to generate the FIR filter:

b = fir1(47,0.43);

the impulse response of the filter in time and frequency domains:

![timersp](doc/time_response.png)

![frqrsp](doc/frq_response.png)

Tests:
------

Simulated signal with two components:
1- cosine at 1700 Hz
2- cosine at 20 Hz

and sampling rate at 25000 Hz:

![signal](doc/signal.png)
![signal2](doc/zoomsignal.png)
![decimated](doc/decsignal.png)
![decimated2](doc/zoomdecsignal.png)

![diff1](doc/diff1.png)



Needed libraries:
------
1. Boost::Circular_buffer

Compile:
-------
cmake based


