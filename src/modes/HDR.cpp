#include "modes/HDR.hpp"

#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

HDR::HDR(socd::SocdType socd_type) {
    _socd_pair_count = 5;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left,    &InputState::right,   socd_type},
        socd::SocdPair{ &InputState::down,   &InputState::up,      socd_type},
        socd::SocdPair{ &InputState::down,   &InputState::up2,     socd_type},
        socd::SocdPair{ &InputState::c_left, &InputState::c_right, socd_type},
        socd::SocdPair{ &InputState::c_down, &InputState::c_up,    socd_type},
    };
}

void HDR::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    outputs.a = inputs.a;
    outputs.b = inputs.b;
    outputs.x = inputs.x;
    outputs.y = inputs.y;
    outputs.buttonL = inputs.lightshield;
    outputs.buttonR = inputs.z;
    outputs.triggerLDigital = inputs.l;
    outputs.triggerRDigital = inputs.r;
    outputs.start = inputs.start;
    outputs.select = inputs.select;
    outputs.home = inputs.home;

    // Turn on D-Pad layer by holding Mod X + Mod Y or Nunchuk C button.
    if ((inputs.mod_x && inputs.mod_y) || inputs.nunchuk_c) {
        outputs.dpadUp = inputs.c_up;
        outputs.dpadDown = inputs.c_down;
        outputs.dpadLeft = inputs.c_left;
        outputs.dpadRight = inputs.c_right;
    }

    // Activate select by holding Mod X
    if ((inputs.mod_x)) {
        outputs.select = inputs.start;
    }
    // Activate home by holding Mod Y
    if ((inputs.mod_y)) {
        outputs.home = inputs.start;
    }
    // Don't override dpad up if it's already pressed using the MX + MY dpad
    // layer.
    outputs.dpadUp = outputs.dpadUp || inputs.midshield;
}

void HDR::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    // Coordinate calculations to make modifier handling simpler.
    UpdateDirections(
        inputs.left,
        inputs.right,
        inputs.down,
        inputs.up || inputs.up2,
        inputs.c_left,
        inputs.c_right,
        inputs.c_down,
        inputs.c_up,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );

    bool shield_button_pressed = inputs.l || inputs.r;

    if (directions.diagonal) {
        // down + horizontal + B outputs down special
        if (inputs.b && directions.y == -1) {
            outputs.leftStickX = 128 + (directions.x * 28);
            outputs.leftStickY = 128 + (directions.y * 85);
        }
    }

    if (inputs.mod_x) {
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 70);
        }
        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 61);
        }

        if (directions.cx != 0) {
            outputs.rightStickX = 128 + (directions.cx * 65);
            outputs.rightStickY = 128 + (directions.y * 44);
        }

        if (directions.diagonal) {
            outputs.leftStickX = 128 + (directions.x * 70);
            outputs.leftStickY = 128 + (directions.y * 34);

            if (inputs.b) {
                outputs.leftStickX = 128 + (directions.x * 85);
                outputs.leftStickY = 128 + (directions.y * 31);
            }

            if (inputs.r) {
                outputs.leftStickX = 128 + (directions.x * 96);
                outputs.leftStickY = 128 + (directions.y * 28);
            }

            if (inputs.c_down) {
                outputs.leftStickX = 128 + (directions.x * 99);
                outputs.leftStickY = 128 + (directions.y * 40);
            }

            if (inputs.c_left) {
                outputs.leftStickX = 128 + (directions.x * 95);
                outputs.leftStickY = 128 + (directions.y * 50);
            }

            if (inputs.c_up) {
                outputs.leftStickX = 128 + (directions.x * 86);
                outputs.leftStickY = 128 + (directions.y * 57);
            }

            if (inputs.c_right) {
                outputs.leftStickX = 128 + (directions.x * 93);
                outputs.leftStickY = 128 + (directions.y * 76);
            }
        }
    }

    if (inputs.mod_y) {
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 35);
        }
        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 70);
        }

        if (directions.diagonal) {
            outputs.leftStickX = 128 + (directions.x * 28);
            outputs.leftStickY = 128 + (directions.y * 58);

            // MY Pivot Uptilt/Dtilt
            if (inputs.a) {
                outputs.leftStickX = 128 + (directions.x * 38);
                outputs.leftStickY = 128 + (directions.y * 69);
            }

            if (inputs.r) {
                outputs.leftStickX = 128 + (directions.x * 51);
                outputs.leftStickY = 128 + (directions.y * 82);
            }

            if (inputs.b) {
                outputs.leftStickX = 128 + (directions.x * 28);
                outputs.leftStickY = 128 + (directions.y * 96);
            }

            if (inputs.c_down) {
                outputs.leftStickX = 128 + (directions.x * 40);
                outputs.leftStickY = 128 + (directions.y * 99);
            }

            if (inputs.c_left) {
                outputs.leftStickX = 128 + (directions.x * 50);
                outputs.leftStickY = 128 + (directions.y * 95);
            }

            if (inputs.c_up) {
                outputs.leftStickX = 128 + (directions.x * 57);
                outputs.leftStickY = 128 + (directions.y * 86);
            }

            if (inputs.c_right) {
                outputs.leftStickX = 128 + (directions.x * 76);
                outputs.leftStickY = 128 + (directions.y * 93);
            }
        }
    }

    /* if (inputs.up2) {
        // Up2 Nair
        outputs.leftStickX = 128;
        outputs.leftStickY = 128;
    } */

    // C-stick ASDI Slideoff angle overrides any other C-stick modifiers (such as
    // angled fsmash).
    // We don't apply this for c-up + c-left/c-right in case we want to implement
    // C-stick nair somehow.
    if (directions.cx != 0 && directions.cy == -1) {
        // 3000 9875
        outputs.rightStickX = 128 + (directions.cx * 35);
        outputs.rightStickY = 128 + (directions.cy * 98);
    }

    if (inputs.l) {
        outputs.triggerLAnalog = 140;
    }

    if (inputs.r) {
        outputs.triggerRAnalog = 140;
    }

    // Shut off C-stick when using D-Pad layer.
    if ((inputs.mod_x && inputs.mod_y) || inputs.nunchuk_c) {
        outputs.rightStickX = 128;
        outputs.rightStickY = 128;
    }

    // Turns off Start when holding Mod X or Mod Y
    if ((inputs.mod_x || inputs.mod_y)) {
        outputs.start = false;
    }

    // Nunchuk overrides left stick.
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }
}