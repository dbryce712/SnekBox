/* CONVERTED TO BUFFED MELEE MODE */
#include "modes/Rivals2.hpp"

#define ANALOG_STICK_MIN 48
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 208

Rivals2::Rivals2() : ControllerMode() {}

void Rivals2::UpdateDigitalOutputs(const InputState &inputs, OutputState &outputs) {
    outputs.a = inputs.rt1;
    outputs.b = inputs.rf1;
    outputs.x = inputs.rf2;
    outputs.y = inputs.rf6;
    outputs.buttonR = inputs.rf3;
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

    if (inputs.mb3)
        outputs.dpadLeft = true;
    if (inputs.mb2)
        outputs.dpadRight = true;
}

void Rivals2::UpdateAnalogOutputs(const InputState &inputs, OutputState &outputs) {
    // Coordinate calculations to make modifier handling simpler.
    UpdateDirections(
        inputs.lf3,
        inputs.lf1,
        inputs.lf2,
        inputs.rf4,
        inputs.rt3,
        inputs.rt5,
        inputs.rt2,
        inputs.rt4,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );

    bool shield_button_pressed = inputs.lf4 || inputs.rf5 || inputs.rf7 || inputs.rf8;
    
    if (directions.diagonal) {
        // q1/2 = 7000 7000
        outputs.leftStickX = 128 + (directions.x * 56);
        outputs.leftStickY = 128 + (directions.y * 56);
        // L, R, LS, and MS + q3/4 = 7000 6875 (For vanilla shield drop. Gives 44.5
        // degree wavedash). Also used as default q3/4 diagonal if crouch walk option select is
        // enabled.
        if (directions.y == -1) {
            /* // DBooC
            if (!inputs.rf1) {
            outputs.leftStickX = 128 + (directions.x * 80);
            outputs.leftStickY = 128 + (directions.y * 60);
            } */
            
            if (shield_button_pressed) {
                outputs.leftStickX = 128 + (directions.x * 56);
                outputs.leftStickY = 128 + (directions.y * 55);
            }     
        }
    }

    if (inputs.lt1) {
        // MX + Horizontal (even if shield is held) = 6625 = 53
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 53);
        }
        // MX + Vertical (even if shield is held) = 5375 = 43
        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 43);

            // shine on platform without falling through
            if (inputs.rf1) {
                outputs.leftStickY = 128 + (directions.y * 45);
            }
        }
        if (directions.diagonal && shield_button_pressed) {
            // 9500 2875 = 76 23
            outputs.leftStickX = 128 + (directions.x * 76);
            outputs.leftStickY = 128 + (directions.y * 23);
        }

        if (directions.diagonal && !shield_button_pressed) {
            // 22.9638 - 7375 3125 = 59 25
            outputs.leftStickX = 128 + (directions.x * 59);
            outputs.leftStickY = 128 + (directions.y * 25);

            /* Up B Angles */
            if (inputs.rf1) {
                outputs.leftStickX = 128 + (directions.x * 76);
                outputs.leftStickY = 128 + (directions.y * 23);
            }
            if (inputs.rt2) {
                outputs.leftStickX = 128 + (directions.x * 75);
                outputs.leftStickY = 128 + (directions.y * 31);
            }
            if (inputs.rt3) {
                outputs.leftStickX = 128 + (directions.x * 73);
                outputs.leftStickY = 128 + (directions.y * 39);
            }
            if (inputs.rt4) {
                outputs.leftStickX = 128 + (directions.x * 69);
                outputs.leftStickY = 128 + (directions.y * 46);
            }
            if (inputs.rt5) {
                outputs.leftStickX = 128 + (directions.x * 50);
                outputs.leftStickY = 128 + (directions.y * 41);
            }
            
        }

        // Angled fsmash
        if (directions.cx != 0) {
            // 8500 5250 = 68 42
            outputs.rightStickX = 128 + (directions.cx * 68);
            outputs.rightStickY = 128 + (directions.y * 42);
        }
    }

    if (inputs.lt2) {
        // MY + Horizontal (even if shield is held) = 3375 = 27
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 27);
        }
        // MY + Vertical = 7375 = 59
        if (directions.vertical) {
            if (directions.y == 1) {
                outputs.leftStickY = 128 + (directions.y * 52);
            }
            if (directions.y == -1) {
                outputs.leftStickY = 128 + (directions.y * 59);
            }

            if (shield_button_pressed) {
                outputs.leftStickY = 128 + (directions.y * 55);
            }
        }
        if (directions.diagonal && shield_button_pressed) {
            // MY + L, R, LS, and MS + q1/2 = 4750 8750 = 38 70
            outputs.leftStickX = 128 + (directions.x * 38);
            outputs.leftStickY = 128 + (directions.y * 70);
            // MY + L, R, LS, and MS + q3/4 = 5000 8500 = 40 68

            // Parasol dash
            if (directions.y == 1 && (inputs.rf2 || inputs.rf6)) {
                outputs.leftStickX = 128 + (directions.x * 40);
                outputs.leftStickY = 128 + (directions.y * 68);
            }

            /* // steepest wavedash
            if (directions.y == -1) {
                // 2875 9500 = 23 76
                outputs.leftStickX = 128 + (directions.x * 23);
                outputs.leftStickY = 128 + (directions.y * 76);
            } */
        }


        if (directions.diagonal && !shield_button_pressed) {
            // buffered turnaround vertical tilts
            if (directions.y == -1) {
                outputs.leftStickX = 128 + (directions.x * 23);
                outputs.leftStickY = 128 + (directions.y * 53);
            }

            if (directions.y == 1) {
                outputs.leftStickX = 128 + (directions.x * 23);
                outputs.leftStickY = 128 + (directions.y * 52);
            }

            /* Up B Angles */
            if (inputs.rf1) {
                outputs.leftStickX = 128 + (directions.x * 23);
                outputs.leftStickY = 128 + (directions.y * 76);
            }
            if (inputs.rt2) {
                outputs.leftStickX = 128 + (directions.x * 31);
                outputs.leftStickY = 128 + (directions.y * 75);
            }
            if (inputs.rt3) {
                outputs.leftStickX = 128 + (directions.x * 39);
                outputs.leftStickY = 128 + (directions.y * 75);
            }
            if (inputs.rt4) {
                outputs.leftStickX = 128 + (directions.x * 46);
                outputs.leftStickY = 128 + (directions.y * 69);
            }
            if (inputs.rt5) {
                outputs.leftStickX = 128 + (directions.x * 41);
                outputs.leftStickY = 128 + (directions.y * 50);
            }
        }

        // Slight angled fsmash
        if (directions.cx != 0) {
            // 9500 2875 = 76 23
            outputs.rightStickX = 128 + (directions.cx * 76);
            outputs.rightStickY = 128 + (directions.y * 23);
        }
    }

    /* if (inputs.lf5) {
        // Up2 Nair
        outputs.leftStickX = 128;
        outputs.leftStickY = 128;
    } */

    // C-stick ASDI Slideoff angle overrides any other C-stick modifiers (such as
    // angled fsmash).
    if (directions.cx != 0 && directions.cy != 0) {
        // 2875 9500 = 23 76
        outputs.rightStickX = 128 + (directions.cx * 23);
        outputs.rightStickY = 128 + (directions.cy * 76);
    }

    if (inputs.rf7) {
        outputs.triggerRAnalog = 43;
    }
    if (inputs.rf8) {
        outputs.triggerRAnalog = 94;
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

        // slight angled ftilts
        if (inputs.rt1 && directions.diagonal) {
            // 9500 2875 = 76 23
            outputs.leftStickX = 128 + (directions.x * 76);
            outputs.leftStickY = 128 + (directions.y * 23);
        }

        // Pikachu/Pichu double up-special
        if (inputs.rf1 && inputs.rf4) {
            outputs.leftStickY = 128 - (directions.y * 40);
        }
    }

    // Nunchuk overrides left stick.
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }
}