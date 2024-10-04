#ifndef _MODES_PROJECTMBIDOU_HPP
#define _MODES_PROJECTMBIDOU_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

typedef struct {
    bool true_z_press = false;
    bool ledgedash_max_jump_traj = true;
} ProjectMBidouOptions;

class ProjectMBidou : public ControllerMode {
  public:
    ProjectMBidou(socd::SocdType socd_type, ProjectMBidouOptions options = {});

  private:
    ProjectMBidouOptions _options;
    bool _horizontal_socd;

    void HandleSocd(InputState &inputs);
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif
