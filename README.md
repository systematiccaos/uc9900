# uConsole BB9900 keyboard firmware (ZMK)

ZMK firmware for the uConsole keyboard with the BB9900 trackpad, based on
**upstream ZMK main** instead of the unmaintained 2024 ZitaoTech fork. The
trackpad, backlight and indicator LED support that used to live in the fork now
lives in this repo as a small ZMK module (`boards/`, `drivers/`, `src/`,
`Kconfig`, `CMakeLists.txt`).

ZMK is pinned to a known-good commit in `config/west.yml`; bump it to pick up
newer ZMK releases.

## ZMK Studio

ZMK Studio is enabled: edit the keymap live over USB (or BLE) at
<https://zmk.studio> without reflashing.

To unlock the keyboard after connecting:

1. Hold the **right Fn** key (`&mo UPPER`).
2. Press the **`/`** key in the top row (the slot that used to be `&none` in
   the UPPER layer). That binding is `&studio_unlock`.

Unlock once per power cycle, then connect with ZMK Studio.

> Once you change the keymap in ZMK Studio, the changes are stored on the
> keyboard and `config/bb9900.keymap` is no longer applied on boot. Use
> **Restore Stock Settings** in ZMK Studio to go back to the keymap in this
> repo.

## What changed from the old fork setup

| | Old | Now |
| --- | --- | --- |
| Base | `ZitaoTech/zmk` @ `bbkeyboard_tp` (Sep 2024) | `zmkfirmware/zmk` main (pinned commit) |
| Board | legacy board in the ZMK fork | HWMv2 board in `boards/zitaotech/bb9900` |
| Trackpad | sensor driver polled from `main()` | `drivers/input/input_a320.c`, input subsystem |
| LED indicators | patched into the ZMK fork | `src/indicator_led.c`, `src/indicator_capslock.c` |
| Scrolling | `main()` HID-indicator check | `src/input_processor_scroll_mode.c` |
| Studio | not available | `studio-rpc-usb-uart` snippet + `CONFIG_ZMK_STUDIO` |

Kept on purpose for compatibility with the stock firmware:

- the trackpad light is also the Caps Lock indicator;
- the trackpad scrolls instead of moving the pointer while the host reports
  Caps Lock or Scroll Lock (`CONFIG_ZMK_TRACKPAD_SCROLL_DIVISOR`);
- pointer speed is the stock 1.5x (`&zip_xy_scaler 3 2` in the board overlay);
- the big-button light shows the active layer.

`&mkp C_PAUSE` in the old keymap was replaced with `&mkp MCLK` (middle click);
on upstream ZMK the parameter is a mouse-button bitmask, so `C_PAUSE` pressed
several buttons at once.

## Building

GitHub Actions builds every push with the
[`build-user-config.yml`](.github/workflows/blank.yml) workflow from the same
pinned ZMK commit as `config/west.yml`. Download
`bb9900-zmk.uf2` from the workflow artifacts and copy it onto the `NICENANO`
drive while the keyboard is in UF2 bootloader mode (hold the bootloader key
combo, or use the `&bootloader` binding: UPPER/SYM + the key bound to
`&bootloader`).

Local build (same flags as CI):

```sh
west init -l config
west update
west build -s zmk/app -d build -b bb9900//zmk -S studio-rpc-usb-uart -- \
  -DZMK_CONFIG="$PWD/config" -DZMK_EXTRA_MODULES="$PWD" -DCONFIG_ZMK_STUDIO=y
```

The output is `build/zephyr/zmk.uf2`.

## Layout

| Path | What it is |
| --- | --- |
| `config/bb9900.keymap` | Keymap (BASE, SYM, UPPER) |
| `config/bb9900.conf` | Settings: backlight, indicators, scrolling, Studio |
| `config/info.json` | Key positions for keymap-editor (not used by ZMK) |
| `boards/zitaotech/bb9900/` | Board definition, physical layout for Studio |
| `drivers/input/input_a320.c` | ADBS-A320 trackpad driver |
| `src/` | LED indicators and trackpad scroll mode |

## Flashing / hardware

See the original hardware documentation for the uConsole keyboard and UF2
flashing: <https://github.com/ZitaoTech/BB9900-USB_BLE_Keyboard>.

## Credits

- ZitaoTech — original BB9900 board support, trackpad and indicator code.
- [schlarpc/zmk-bb9900](https://github.com/schlarpc/zmk-bb9900) — upstream ZMK
  port whose A320 input driver and module layout this repo is based on (MIT).
- The ZMK contributors.
