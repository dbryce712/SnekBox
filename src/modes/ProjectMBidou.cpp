#include "modes/ProjectMBidou.hpp"

#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

ProjectMBidou::ProjectMBidou(socd::SocdType socd_type, ProjectMBidouOptions options) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{ &InputState::left,   &InputState::right,   socd_type},
        socd::SocdPair{ &InputState::down,   &InputState::up,      socd_type},
        socd::SocdPair{ &InputState::c_left, &InputState::c_right, socd_type},
        socd::SocdPair{ &InputState::c_down, &InputState::c_up,    socd_type},
    };

    _options = options;
    _horizontal_socd = false;
}

void ProjectMBidou::HandleSocd(InputState &inputs) {
    _horizontal_socd = inputs.left && inputs.right;
    InputMode::HandleSocd(inputs);
}

void ProjectMBidou::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    outputs.a = inputs.a || inputs.up2;
    outputs.b = inputs.b;
    outputs.x = inputs.x;
    outputs.y = inputs.y;
    // True Z press vs macro lightshield + A.
    if (_options.true_z_press || inputs.mod_x) {
        outputs.buttonR = inputs.z;
    } else {
        outputs.a = inputs.a || inputs.up2 || inputs.z;
    }
    if (inputs.nunchuk_connected) {
        outputs.triggerLDigital = inputs.nunchuk_z;
    } else {
        outputs.triggerLDigital = inputs.l;
    }
    outputs.triggerRDigital = inputs.r;
    outputs.start = inputs.start;

    // Activate D-Pad layer by holding Mod X + Mod Y or Nunchuk C button.
    if ((inputs.mod_x && inputs.mod_y) || inputs.nunchuk_c) {
        outputs.dpadUp = inputs.c_up;
        outputs.dpadDown = inputs.c_down;
        outputs.dpadLeft = inputs.c_left;
        outputs.dpadRight = inputs.c_right;
    }

    // Don't override dpad up if it's already pressed using the MX + MY dpad
    // layer.
    outputs.dpadUp = outputs.dpadUp || inputs.midshield;

    if (inputs.select)
        outputs.dpadLeft = true;
    if (inputs.home)
        outputs.dpadRight = true;
}

void ProjectMBidou::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    UpdateDirections(
        inputs.left,
        inputs.right,
        inputs.down,
        inputs.up,
        inputs.c_left,
        inputs.c_right,
        inputs.c_down,
        inputs.c_up,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );

    bool shield_button_pressed = inputs.l || inputs.lightshield;

    if (directions.diagonal) {
        if (directions.y == 1) {
            outputs.leftStickX = 128 + (directions.x * 83);
            outputs.leftStickY = 128 + (directions.y * 93);
        }

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

            if (inputs.r || inputs.b) {
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

            // snekdash angle
            if (inputs.l && directions.y == 1) {
                outputs.leftStickX = 128 + (directions.x * 120);
                outputs.leftStickY = 128 + (directions.y * 84);
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
        // Smash pivot slides; inputs.b = outputs.a
        if (directions.cx != 0 && inputs.b) {
            outputs.rightStickX = 128 + (directions.cx * 35);
            outputs.rightStickY = 168;
        }
        // Attack stick nairs
        outputs.rightStickX = 168;
        outputs.rightStickY = 88;
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

    // Horizontal SOCD overrides X-axis modifiers (for ledgedash maximum jump
    // trajectory).
    if (_options.ledgedash_max_jump_traj && _horizontal_socd && !directions.vertical &&
        !shield_button_pressed) {
        outputs.leftStickX = 128 + (directions.x * 100);
    }

    if (inputs.lightshield) {
        outputs.triggerRAnalog = 49;
    }

    // Send lightshield input if we are using Z = lightshield + A macro.
    if (inputs.z && !(inputs.mod_x || _options.true_z_press)) {
        outputs.triggerRAnalog = 49;
    }

    if (outputs.triggerLDigital) {
        outputs.triggerLAnalog = 140;
    }

    if (outputs.triggerRDigital) {
        outputs.triggerRAnalog = 140;
    }

    // Shut off C-stick when using D-Pad layer.
    if ((inputs.mod_x && inputs.mod_y) || inputs.nunchuk_c) {
        outputs.rightStickX = 128;
        outputs.rightStickY = 128;
    }

    // Nunchuk overrides left stick.
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }
}
