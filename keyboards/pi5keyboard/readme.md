# Pi5 Keyboard

![Pi5 Keyboard](https://www.flickr.com/photos/155567752@N02/52522025465/)

A 38 key split ortho using the Raspberry Pi Pico.

* Keyboard Maintainer: [Luke Schutt](https://github.com/luke-schutt)
* Hardware Supported: Pi5 Keyboard
* Hardware Availability: [Keyboard and mounting plate PCBs](https://github.com/luke-schutt/Pi5Keyboard)

Make example for this keyboard (after setting up your build environment):

    make pi5keyboard:default

Flashing example for this keyboard:

    make pi5keyboard:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

To enter the bootloader use the "boot" button on the Raspberry Pi Pico by either:

* Unplugging from USB, holding the "boot" button, plug the USB cable back in, then releasing the "boot" button.
* Hold the "reset" button, press the "boot" button", release the "reset" button, then release the "boot" button.
