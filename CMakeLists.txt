# SPDX-License-Identifier: MIT

add_subdirectory(drivers)

target_sources_ifdef(CONFIG_ZMK_INDICATOR_CAPSLOCK app PRIVATE src/indicator_capslock.c)
target_sources_ifdef(CONFIG_ZMK_INDICATOR_LED app PRIVATE src/indicator_led.c)
target_sources_ifdef(CONFIG_ZMK_TRACKPAD_SCROLL_MODE app PRIVATE src/input_processor_scroll_mode.c)
