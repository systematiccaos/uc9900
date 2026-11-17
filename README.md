# First thanks to [Zitaotech](https://github.com/ZitaoTech)

I modify his fireware to our project,whitout his help ,we cannt see trackpad on uconsole ,thanks to him and his many interesting productions.

# uconsole BB9900 wireless/usb Keyboard: zmk-config
------------------------------

The key:

Part ONE--USB

1.when connect uconsole via usb,ble dont work!

Part TWO--BLE

1.RFN+1 2 3 is three different equipment ,RFN+ESC is Clean BLE(when you wanna connect new equipment and clean you ble info)  

2.RFN+ (\\|) is bootloader

3.RFN+LFN is soft-reset


New update need you help

1.LFN +trackpad is ↑↓←→

2.Caps light！！

3.outside Crystal oscillator works！

--------------------------------
Hey 👋 welcome. Use this repo to generate your own ZMK keymap for the BB9900 BLE keyboard.  
[Keycode that you can use in ZMK firmware](https://zmk.dev/docs/codes)  
[Different behaviors that you can use in ZMK firmware](https://zmk.dev/docs/behaviors)  
## Get started
0. Register a github account if you don't have one.
1. Fork this repo.![fork](https://github.com/ZitaoTech/zmk-config_9900/assets/145678024/4ffc71b9-0ed3-4ae9-ace7-99078dd1d9bc)  
2. Open up `config/bb9900.keymap` and edit the keymap to your liking.![image](https://github.com/ZitaoTech/zmk-config_9900/assets/145678024/a0900a5c-6650-4794-9d11-a17c380a973d)  
3. After editing the keymap, choose commit changes![image](https://github.com/ZitaoTech/zmk-config_9900/assets/145678024/c708dbd0-6c90-49da-aeda-053668ae43c8)
 and then check the Github Actions section.![image](https://github.com/ZitaoTech/zmk-config_9900/assets/145678024/fb534054-add6-4517-8643-8270cbf6d8c7)
 Your new firmware file should be available for download.![image](https://github.com/ZitaoTech/zmk-config_9900/assets/145678024/ae6a1646-c8ab-4966-b969-12e68ecaa0ab)
 ![image](https://github.com/ZitaoTech/zmk-config_9900/assets/145678024/a6140108-9e27-4d51-aa42-ba12233b8738)
5. Unzip the firmware.zip file. You should see one files: `bb9900-zmk.uf2`.  
6. Flash the keyboard with your new firmware.[How to flash the firmware](https://github.com/ZitaoTech/BB9900-USB_BLE_Keyboard?tab=readme-ov-file#-how-to-update-the-firmware---) 

## ZMK Studio

This config now builds against **upstream ZMK v0.3.0** (`config/west.yml`)
instead of the old ZitaoTech fork, because ZMK Studio does not exist in the fork.
v0.3.0 still uses the same Zephyr 3.5 the fork pinned, so the legacy board and
the custom trackpad/LED code keep working; they are vendored in this repo as a
small ZMK module (`boards/arm/bb9900`, `drivers/`, `src/`, `Kconfig`,
`CMakeLists.txt`, `zephyr/module.yml`).

ZMK Studio is enabled: edit the keymap live over USB at
<https://zmk.studio> without reflashing.

To unlock the keyboard after connecting:

1. Hold the **right Fn** key (`&mo UPPER`).
2. Press the **`/`** key in the top row. That binding is `&studio_unlock` in the
   UPPER layer, on the same physical key as `&kp FSLH` in BASE.

Unlock once per power cycle, then connect with ZMK Studio.

> Once you change the keymap in ZMK Studio, the changes are stored on the
> keyboard and `config/bb9900.keymap` is no longer applied on boot. Use
> **Restore Stock Settings** in ZMK Studio to go back to the keymap in this
> repo.

## Layout

| Path | What it is |
| --- | --- |
| `config/bb9900.keymap` | Keymap (BASE, SYM, UPPER) |
| `config/bb9900.conf` | Settings: backlight, indicators, scrolling, Studio |
| `config/info.json` | Key positions for keymap-editor (not used by ZMK) |
| `boards/arm/bb9900/` | Legacy board definition + physical layout for Studio |
| `drivers/input/input_a320.c` | ADBS-A320 trackpad driver |
| `src/` | LED indicators and trackpad scroll mode |
