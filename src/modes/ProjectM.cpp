#include "modes/ProjectM.hpp"

#define ANALOG_STICK_MIN 1
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 255

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
    outputs.a = inputs.rf1;
    outputs.b = inputs.rf2;
    outputs.x = inputs.rt6;
    outputs.y = inputs.rf3;
    // True Z press vs macro lightshield + A.
    if (_options.true_z_press || inputs.lt1) {
        outputs.buttonR = inputs.rf6;
    } else {
        outputs.a = inputs.rf1 || inputs.rf6;
    }
    if (inputs.nunchuk_connected) {
        outputs.triggerLDigital = inputs.nunchuk_z;
    } else {
        outputs.triggerLDigital = inputs.lf4;
    }
    outputs.triggerRDigital = inputs.rf5;
    outputs.start = inputs.mb1;

    // Activate D-Pad layer by holding RF8 or Nunchuk C button.
    if (inputs.rf8 || inputs.nunchuk_c) {
        outputs.dpadUp = inputs.lf4;
        outputs.dpadDown = inputs.lf2;
        outputs.dpadLeft = inputs.lf3;
        outputs.dpadRight = inputs.lf1;
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
        inputs.lf4, // Up
        inputs.rt3, // C-Left
        inputs.rt5, // C-Right
        inputs.rt2, // C-Down
        inputs.rt4, // C-Up
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );

    bool shield_button_pressed = inputs.rf4 || inputs.rf5 || inputs.rf7;

    /* X1 */
    if (inputs.lt1) {
        outputs.leftStickX = 128 + (directions.x * 40);
    }

    /* Y1 */
    if (inputs.lt2) {
        if (directions.y == 1) {
            outputs.leftStickY = 128 + (directions.y * 52);
        }

        if (inputs.rf5) {
            // Max wavedash
            outputs.leftStickX = 128 + (directions.x * 120);
            outputs.leftStickY = 128 + (directions.y * 35);
        }
    }

    /* Tilt1 */
    if (inputs.lt3) {
        outputs.leftStickX = 128 + (directions.x * 60);
        outputs.leftStickY = 128 + (directions.y * 63);
    }

    /* Tilt2 */
    if (inputs.lt4) {
        outputs.leftStickX = 128 + (directions.x * 55);
        outputs.leftStickY = 128 + (directions.y * 69);
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

    // Attack stick nairs
    if (inputs.rt1) {
        outputs.rightStickX = 88;
        outputs.rightStickY = 88;
    }


    if (inputs.rf7) {
        outputs.triggerRAnalog = 49;
    }

    if (inputs.rf4) {
        outputs.triggerLAnalog = 49;
    }

    if (outputs.triggerLDigital) {
        outputs.triggerLAnalog = 140;
    }

    if (outputs.triggerRDigital) {
        outputs.triggerRAnalog = 140;
        
        // holding R + analog L -> R + L
        if (inputs.rf4) {
            outputs.triggerLAnalog = 140;
        }
    }

    // Shut off control stick when using D-Pad layer.
    if (inputs.rf8 || inputs.nunchuk_c) {
        outputs.leftStickX = 128;
        outputs.leftStickY = 128;
    }

    // Nunchuk overrides left stick.
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }
}
