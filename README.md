simple-gpio
===========

**simple-gpio** is a simple command line tool designed for Raspberry Pi that allows you to export/unexport GPIO pins without sudo.


Installation
------------
```
$ sudo make
```

Installation requires _sudo_!

Usage
-----
Export a GPIO pin:

```
$ simple-gpio export 17
```

Now you can access the pin without sudo:
```
$ echo "out" > /sys/class/gpio/gpio17/direction
$ echo "1" > /sys/class/gpio/gpio17/value
```

When you're done, unexport the GPIO pin:

```
$ simple-gpio unexport 17
```

How it works
------------
When you run `sudo make` to install **simple-gpio** three things happen:

1. simple-gpio is compiled (nothing special here)
2. The ownership of the compiled executable is set to "root".
3. The [setuid](http://en.wikipedia.org/wiki/Setuid) flag is set on the executable.

Now that the owner is "root" and the setuid flag is set, simple-gpio can be run without sudo.