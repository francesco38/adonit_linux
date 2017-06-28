# Adonit pixel user level input

This is a fork of the initial work conducted by GeReV, then Amir Grozki to provide an app interfacing an [Adonit Jot Touch 4](http://www.adonit.net/jot/touch) device with the Linux `uinput`.  The main goal of this app is to enable a touchscreen-enabled laptop to work as a full drawing tablet using a pressure-sensitive Bluetooth pen.  The app uses code from [BlueZ](http://www.bluez.org).

## About the fork

The goal of this fork is to adapt the code to the [Adonit Jot Pixel](http://www.adonit.net/jot/pixel/) stylus if need be, adapt to more recent version of bluez (and remove the embedded bluez code if possible), and see how the resulting code can make the stylus be recognized as a wacom tablet by gnome to make it usable accross all desktop apps.

## Build requirements

To build you will need **[glib](https://developer.gnome.org/glib/stable)** and **[DBus](http://www.linuxfromscratch.org/blfs/view/svn/general/dbus.html)** >= 1.6.

Build using `make` command.

## Running

After building the project, run `adonit` with a user with privileges to access `/dev/uinput` and `/dev/input/event*` (i.e. Use `sudo adonit`).
You will need to provide as parameters the touchscreen device file as well as the MAC address of the bluetooth stylus, as in the example below:

```
  sudo adonit --touchscreen /dev/input/event17 --pen 00:01:02:03:04:05
```

You can add the option `--verbose` to get verbose reporting on the app behavior.
Please note that as of writing, when the app is running, the touchscreen is "muted" and can no longer be used.

## Various notes

The command `evtest` (that you generally need to run as root) can be used to see the event flow from the new device.
