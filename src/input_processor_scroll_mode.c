/*
 * Copyright (c) 2023 ZitaoTech
 *
 * SPDX-License-Identifier: MIT
 */

// Trackpad scroll mode, as in the stock uConsole firmware: while the host
// reports Caps Lock or Scroll Lock as on, relative motion becomes wheel
// events instead of pointer movement. Y is inverted so that dragging the
// finger down scrolls the page down.
//
// This is intentionally kept separate from the pointer scaler, so that the
// scroll speed is not affected by the pointer speed multiplier.

#define DT_DRV_COMPAT zitaotech_input_processor_scroll_mode

#include <zephyr/device.h>
#include <zephyr/input/input.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/dt-bindings/input/input-event-codes.h>

#include <drivers/input_processor.h>
#include <zmk/hid_indicators.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

struct scroll_mode_config {
    int32_t divisor;
};

struct scroll_mode_data {
    // Remainders in sensor counts, so slow movement still adds up.
    int32_t remainder[2];
};

static inline bool scroll_mode_active(void) {
    // Same set of host LED profiles as the stock firmware.
    zmk_hid_indicators_t profile = zmk_hid_indicators_get_current_profile();

    return profile == 2 || profile == 3 || profile == 4 || profile == 7;
}

static int scroll_mode_handle_event(const struct device *dev, struct input_event *event,
                                    uint32_t param1, uint32_t param2,
                                    struct zmk_input_processor_state *state) {
    const struct scroll_mode_config *cfg = dev->config;
    struct scroll_mode_data *data = dev->data;
    int axis;
    uint16_t code;

    if (event->type != INPUT_EV_REL || !scroll_mode_active()) {
        return ZMK_INPUT_PROC_CONTINUE;
    }

    switch (event->code) {
    case INPUT_REL_X:
        axis = 0;
        code = INPUT_REL_HWHEEL;
        break;
    case INPUT_REL_Y:
        axis = 1;
        code = INPUT_REL_WHEEL;
        break;
    default:
        return ZMK_INPUT_PROC_CONTINUE;
    }

    // The stock firmware negates both axes.
    int32_t total = data->remainder[axis] - event->value;
    int32_t out = total / cfg->divisor;
    data->remainder[axis] = total - out * cfg->divisor;

    event->code = code;
    event->value = out;

    return ZMK_INPUT_PROC_CONTINUE;
}

static const struct zmk_input_processor_driver_api scroll_mode_driver_api = {
    .handle_event = scroll_mode_handle_event,
};

#define SCROLL_MODE_INST(n)                                                                       \
    static struct scroll_mode_data scroll_mode_data_##n;                                         \
    static const struct scroll_mode_config scroll_mode_config_##n = {                            \
        .divisor = DT_INST_PROP(n, divisor),                                                      \
    };                                                                                            \
    DEVICE_DT_INST_DEFINE(n, NULL, NULL, &scroll_mode_data_##n, &scroll_mode_config_##n,           \
                          POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,                        \
                          &scroll_mode_driver_api);

DT_INST_FOREACH_STATUS_OKAY(SCROLL_MODE_INST)
