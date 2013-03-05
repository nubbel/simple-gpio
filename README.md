simple-gpio
===========

*simple-gpio* is a simple command line tool designed for Raspberry Pi that allows you to export/unexport GPIO pins without sudo.


Installation
------------
```
$ sudo make
```

Installation require _sudo_!

Usage
-----
Export a GPIO pin:

```
$ simple-gpio export 17
```

Control the pin without sudo:
```
$ echo "out" > /sys/class/gpio/gpio17/direction
$ echo "1" > /sys/class/gpio/gpio17/value
```

Unxport a GPIO pin:

```
$ simple-gpio unexport 17
```
