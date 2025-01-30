#ifndef _MODES_PROJECTNAIR_HPP
#define _MODES_PROJECTNAIR_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

typedef struct {
    bool true_z_press = false;
    bool ledgedash_max_jump_traj = true;
} ProjectNairOptions;

class ProjectNair : public ControllerMode {
  public:
    ProjectNair(socd::SocdType socd_type, ProjectNairOptions options = {});

  private:
    ProjectNairOptions _options;
    bool _horizontal_socd;

    void HandleSocd(InputState &inputs);
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif
