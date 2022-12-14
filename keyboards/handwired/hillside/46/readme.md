# Hillside 46

![hillside](https://imgur.com/VFA9E4Yh.png)

[Hillside 46](https://github.com/mmccoyd/hillside)
 is a split ergonomic keyboard with 3x6+5 choc-spaced keys,
 splayed ring and pinkie columns, aggressive column stagger,
 a longer thumb arc and a breakoff outer-pinkie column.

* Keyboard Maintainer: [Michael McCoyd](https://github.com/mmccoyd)
* Hardware Supported: ProMicro/Elite-C and compatible
* Hardware Availability: https://github.com/mmccoyd/hillside

Make example for this keyboard (after setting up your build environment):

    make handwired/hillside/46:default

Flashing example for this keyboard:

    make handwired/hillside/46:default:flash

## Bootloader

Enter the bootloader by either:

* **Physical reset button**: Briefly press the button on the front of the PCB.
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
