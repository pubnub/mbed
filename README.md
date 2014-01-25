mbed
====

PubNub Client SDK for mbed platform

Long-term, we will be tracking this on mbed.org. This is just
a work in progress snapshot of the early development.


Implementation Notes
--------------------

With PubNub Client SDKs, we normally follow the principle that we
offer an asynchronous API to allow our users to perform other tasks
during communication with PubNub.  We make an exception for mbed
since the overarching principle of the mbed RTOS is to use multiple
threads whenever multiple tasks need to be done at once.  TODO:
Make a demo of this during subscribe (LED flashing in parallel?).

The PubNub context is designed to be used only by a single thread
at once.

TODO: See PubNub.hpp
