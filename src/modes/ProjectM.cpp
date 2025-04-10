#include "modes/ProjectM.hpp"

#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

ProjectM::ProjectM() : ControllerMode() {
    _horizontal_socd = false;
}

void ProjectM::SetConfig(GameModeConfig &config, const ProjectMOptions options) {
    InputMode::SetConfig(config);
    _options = options;
}

void ProjectM::HandleSocd(InputState &inputs) {
    _horizontal_socd = inputs.lf3 && inputs.lf1;
    InputMode::HandleSocd(inputs);
}

void ProjectM::UpdateDigitalOutputs(const InputState &inputs, OutputState &outputs) {
    outputs.a = inputs.rt1;
    outputs.b = inputs.rf1;
    outputs.y = inputs.rf2;
    // True Z press vs macro lightshield + A.
    if (_options.true_z_press || inputs.lt1) {
        outputs.buttonR = inputs.rf3;
    } else {
        outputs.a = inputs.rt1 || inputs.rf3;
    }
    if (inputs.nunchuk_connected) {
        outputs.triggerLDigital = inputs.nunchuk_z;
    } else {
        outputs.triggerLDigital = inputs.lf4;
    }
    outputs.triggerRDigital = inputs.rf5;
    outputs.start = inputs.mb1;

    // Activate D-Pad layer by holding Mod X + Mod Y or Nunchuk C button.
    if ((inputs.lt1 && inputs.lt2) || inputs.nunchuk_c) {
        outputs.dpadUp = inputs.rt4;
        outputs.dpadDown = inputs.rt2;
        outputs.dpadLeft = inputs.rt3;
        outputs.dpadRight = inputs.rt5;
    }

    // Don't override dpad up if it's already pressed using the MX + MY dpad
    // layer.
    outputs.dpadUp = outputs.dpadUp || inputs.rf8;

    if (inputs.mb3)
        outputs.dpadLeft = true;
    if (inputs.mb2)
        outputs.dpadRight = true;

    if (inputs.lt3) {
        outputs.y = false;
        outputs.x = inputs.rf2;
    }

    // Hidden Buttons for remapp.ing options
    outputs.leftStickClick = inputs.lf6;
    outputs.rightStickClick = inputs.lf7;
    outputs.capture = inputs.lf8;
    outputs.dpadDown = inputs.lf10;
    outputs.dpadLeft = inputs.lf11;
    outputs.dpadRight = inputs.lf12;
    outputs.select = inputs.mb2;
    outputs.home = inputs.mb3;
}

void ProjectM::UpdateAnalogOutputs(const InputState &inputs, OutputState &outputs) {
    UpdateDirections(
        inputs.lf3, // Left
        inputs.lf1, // Right
        inputs.lf2, // Down
        inputs.rf4, // Up
        inputs.rt3, // C-Left
        inputs.rt5, // C-Right
        inputs.rt2, // C-Down
        inputs.rt4, // C-Up
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );

    bool shield_button_pressed = inputs.lf4 || inputs.rf5;

    if (directions.diagonal) {
        // Up smash without letting go of forward
        if ((inputs.rt1 || inputs.rf3) && directions.y == 1) {
            outputs.leftStickX = 128 + (directions.x * 83);
            outputs.leftStickY = 128 + (directions.y * 93);
        }

        // 45° notch + B outputs vertical special when grounded
        if (inputs.rf1) {
            outputs.leftStickX = 128 + (directions.x * 57);
            outputs.leftStickY = 128 + (directions.y * 57);
        }
    }

    /* Mod X */
    if (inputs.lt1) {
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 70);
        }
        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 61);
        }

        if (directions.cx != 0) {
            outputs.rightStickX = 128 + (directions.cx * 65);
            outputs.rightStickY = 128 + (directions.y * 23);
        }

        if (directions.diagonal) {
            // Default MX Diagonal
            outputs.leftStickX = 128 + (directions.x * 70);
            outputs.leftStickY = 128 + (directions.y * 34);

            // Airdodge angle
            if (inputs.rf5) {
                if (_options.has_custom_airdodge) {
                    outputs.leftStickX = 128 + (directions.x * _options.custom_airdodge.x);
                    outputs.leftStickY = 128 + (directions.y * _options.custom_airdodge.y);
                } else {
                    outputs.leftStickX = 128 + (directions.x * 96);
                    outputs.leftStickY = 128 + (directions.y * 28);
                }
            }

            // MX Firefox angles
            if (inputs.rf1) {
                outputs.leftStickX = 128 + (directions.x * 96);
                outputs.leftStickY = 128 + (directions.y * 28);
            }

            if (inputs.rt2) {
                outputs.leftStickX = 128 + (directions.x * 99);
                outputs.leftStickY = 128 + (directions.y * 40);
            }
            
            if (inputs.rt3) {
                outputs.leftStickX = 128 + (directions.x * 95);
                outputs.leftStickY = 128 + (directions.y * 50);
            }

            if (inputs.rt4) {
                outputs.leftStickX = 128 + (directions.x * 86);
                outputs.leftStickY = 128 + (directions.y * 57);
            }

            if (inputs.rt5) {
                outputs.leftStickX = 128 + (directions.x * 93);
                outputs.leftStickY = 128 + (directions.y * 76);
            }
        }
    }

    /* Mod Y */
    if (inputs.lt2) {
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 35);
        }
        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 67);

            // (Shield) drop through platforms
            if (directions.y == -1) {
                outputs.leftStickY = 128 + (directions.y * 69);
            }
        }

        if (directions.diagonal) {
            outputs.leftStickX = 128 + (directions.x * 28);
            outputs.leftStickY = 128 + (directions.y * 58);

            // Diagonal shield drop, wavedash
            if (shield_button_pressed && directions.y == -1) {
                outputs.leftStickX = 128 + (directions.x * 45);
                outputs.leftStickY = 128 + (directions.y * 72);
            }

            // MY Firefox angles
            if (inputs.rf1) {
                outputs.leftStickX = 128 + (directions.x * 28);
                outputs.leftStickY = 128 + (directions.y * 96);
            }
            
            if (inputs.rt2) {
                outputs.leftStickX = 128 + (directions.x * 40);
                outputs.leftStickY = 128 + (directions.y * 99);
            }
            
            if (inputs.rt3) {
                outputs.leftStickX = 128 + (directions.x * 50);
                outputs.leftStickY = 128 + (directions.y * 95);
            }

            if (inputs.rt4) {
                outputs.leftStickX = 128 + (directions.x * 57);
                outputs.leftStickY = 128 + (directions.y * 86);
            }

            if (inputs.rt5) {
                outputs.leftStickX = 128 + (directions.x * 76);
                outputs.leftStickY = 128 + (directions.y * 93);
            }
        }
    }

    // snekdash modifier
    if (inputs.lt3) {
        if (directions.diagonal) {
            outputs.leftStickX = 128 + (directions.x * 120);
            outputs.leftStickY = 128 + (directions.y * 84);
        }
    }

    // Attack c-stick nair
    if (inputs.lf16) {
        outputs.rightStickX = 88;
        outputs.rightStickY = 88;
    }

    // C-stick ASDI Slideoff angle overrides any other C-stick modifiers (such as
    // angled fsmash).
    // We don't apply this for c-up + c-left/c-right in case we want to implement
    // C-stick nair somehow.
    if (directions.cx != 0 && directions.cy == -1) {
        // 3000 9875 = 30 78
        outputs.rightStickX = 128 + (directions.cx * 35);
        outputs.rightStickY = 128 + (directions.cy * 98);
    }

    // Horizontal SOCD overrides X-axis modifiers (for ledgedash maximum jump
    // trajectory).
    if (!_options.disable_ledgedash_socd_override && _horizontal_socd && !directions.vertical &&
        !shield_button_pressed) {
        outputs.leftStickX = 128 + (directions.x * 100);
    }

    /* if (inputs.rf7) {
        outputs.triggerRAnalog = 49;
    } */

    // Send lightshield input if we are using Z = lightshield + A macro.
    if (inputs.rf3 && !(inputs.lt1 || _options.true_z_press)) {
        outputs.triggerRAnalog = 49;
    }

    if (outputs.triggerLDigital) {
        outputs.triggerLAnalog = 140;
    }

    if (outputs.triggerRDigital) {
        outputs.triggerRAnalog = 140;
    }

    // Shut off C-stick when using D-Pad layer.
    if ((inputs.lt1 && inputs.lt2) || inputs.nunchuk_c) {
        outputs.rightStickX = 128;
        outputs.rightStickY = 128;
    }

    // Nunchuk overrides left stick.
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }
}
