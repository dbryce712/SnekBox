/* Ultimate profile by white sheep (original by Taker) */
#include "modes/Ultimate.hpp"

#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

Ultimate::Ultimate(socd::SocdType socd_type) {
    _socd_pair_count = 5;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left,    &InputState::right,   socd_type},
        socd::SocdPair{ &InputState::down,   &InputState::up,      socd_type},
        socd::SocdPair{ &InputState::down,   &InputState::up2,     socd_type},
        socd::SocdPair{ &InputState::c_left, &InputState::c_right, socd_type},
        socd::SocdPair{ &InputState::c_down, &InputState::c_up,    socd_type},
    };
}

void Ultimate::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
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

void Ultimate::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
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

    if (inputs.mod_x) {
        if (directions.horizontal) {
            // MX + Horizontal = 6625 = 53
            outputs.leftStickX = 128 + (directions.x * 53);
            // Horizontal Shield tilt = 51
            if (shield_button_pressed) {
                outputs.leftStickX = 128 + (directions.x * 51);
            }
            // Samus tilt missiles
            if (inputs.b) {
                outputs.leftStickX = 128 + (directions.x * 66);
            }
        }
        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 60);
            // Vertical Shield Tilt = 51
            if (shield_button_pressed) {
                outputs.leftStickY = 128 + (directions.y * 51);
            }
        }

        if (directions.cx != 0) {
            outputs.rightStickX = 128 + (directions.cx * 65);
            outputs.rightStickY = 128 + (directions.y * 44);
        }

        if (directions.diagonal) {
            // MX + q1/2/3/4 = 53 35
            outputs.leftStickX = 128 + (directions.x * 53);
            outputs.leftStickY = 128 + (directions.y * 35);
            if (inputs.a) {
                // DAFTs
                outputs.leftStickX = 128 + (directions.x * 70);
                outputs.leftStickY = 128 + (directions.y * 34);
            }
            if (shield_button_pressed) {
                // MX + L, R, LS, and MS + q1/2/3/4 = 6375 3750 = 51 30
                outputs.leftStickX = 128 + (directions.x * 51);
                outputs.leftStickY = 128 + (directions.y * 30);
            }

            /* Up B angles */
            if (inputs.b) {
                outputs.leftStickX = 128 + (directions.x * 76);
                outputs.leftStickY = 128 + (directions.y * 23);
                if (inputs.c_down) {
                    outputs.leftStickX = 128 + (directions.x * 75);
                    outputs.leftStickY = 128 + (directions.y * 31);
                }
                if (inputs.c_left) {
                    outputs.leftStickX = 128 + (directions.x * 73);
                    outputs.leftStickY = 128 + (directions.y * 39);
                }
                if (inputs.c_up) {
                    outputs.leftStickX = 128 + (directions.x * 72);
                    outputs.leftStickY = 128 + (directions.y * 48);
                }
                if (inputs.c_right) {
                    outputs.leftStickX = 128 + (directions.x * 50);
                    outputs.leftStickY = 128 + (directions.y * 41);
                }
            }
        }
    }

    if (inputs.mod_y) {
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 35);
        }
        // MY + Vertical (even if shield is held) = 53
        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 53);
            // MY Vertical Tilts
            if (inputs.a) {
                outputs.leftStickY = 128 + (directions.y * 36);
            }
        }

        if (directions.diagonal) {
            // MY + q1/2/3/4 = 35 53
            outputs.leftStickX = 128 + (directions.x * 35);
            outputs.leftStickY = 128 + (directions.y * 53);
            if (shield_button_pressed) {
                // MY + L, R, LS, and MS + q1/2 = 38 70
                outputs.leftStickX = 128 + (directions.x * 38);
                outputs.leftStickY = 128 + (directions.y * 70);
                // MY + L, R, LS, and MS + q3/4 = 40 68
                if (directions.x == -1) {
                    outputs.leftStickX = 128 + (directions.x * 40);
                    outputs.leftStickY = 128 + (directions.y * 68);
                }
            }
        }

        if (directions.diagonal && !shield_button_pressed) {
            // (56.56) = 35 53
            outputs.leftStickX = 128 + (directions.x * 35);
            outputs.leftStickY = 128 + (directions.y * 53);

            /* Up B Angles */
            if (inputs.b) {
                outputs.leftStickX = 128 + (directions.x * 23);
                outputs.leftStickY = 128 + (directions.y * 76);
            }
            if (inputs.c_down) {
                outputs.leftStickX = 128 + (directions.x * 31);
                outputs.leftStickY = 128 + (directions.y * 75);
            }
            if (inputs.c_left) {
                outputs.leftStickX = 128 + (directions.x * 39);
                outputs.leftStickY = 128 + (directions.y * 73);
            }
            if (inputs.c_up) {
                outputs.leftStickX = 128 + (directions.x * 48);
                outputs.leftStickY = 128 + (directions.y * 72);
            }
            if (inputs.c_right) {
                outputs.leftStickX = 128 + (directions.x * 41);
                outputs.leftStickY = 128 + (directions.y * 50);
            }

            // MY Pivot Uptilt/Dtilt
            if (inputs.a) {
                outputs.leftStickX = 128 + (directions.x * 38);
                outputs.leftStickY = 128 + (directions.y * 69);
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
    if (directions.cx != 0 && directions.cy != 0) {
        // 5250 8500 = 42 68
        outputs.rightStickX = 128 + (directions.cx * 42);
        outputs.rightStickY = 128 + (directions.cy * 68);
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