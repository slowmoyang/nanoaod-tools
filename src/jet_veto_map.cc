#include "nanoaod_tools/jet_veto_map.h"


bool getJetVetoMap(Correction::Ref jet_veto_map,
                   const std::string jet_veto_map_type,
                   const RVec<float> &eta_vec,
                   const RVec<float> &phi_vec) {
  bool passed = true;

  for (size_t idx = 0; idx < eta_vec.size(); idx++){
    const float eta = std::clamp(eta_vec.at(idx), -5.191f, +5.191f); // FIXME
    const float phi = std::clamp(phi_vec.at(idx), -3.14159f, +3.14159f); // FIXME
    const double result = jet_veto_map->evaluate(
        {jet_veto_map_type, eta, phi});
    if (result != 0) {
      passed = false;
      break;
    }
  }
  return passed;
};

