#include "nanoaod_tools/btagging.h"

#include "ROOT/RVec.hxx"
#include "Math/GenVector/PtEtaPhiM4D.h"
#include "Math/Vector4D.h"
#include "Math/Vector4Dfwd.h"
#include "Math/GenVector/VectorUtil.h"

#include "TRandom3.h"
#include "correction.h"
#include <memory>

using namespace ROOT::VecOps;
using namespace ROOT::Math;
using namespace correction;

// https://btv-wiki.docs.cern.ch/
RVec<float>
getBTaggingFixedWPCorrection(
    const RVec<uint8_t>& jet_hadron_flavour_vec,
    const RVec<PtEtaPhiMVector>& jet_p4_vec,
    Correction::Ref correction_bc,
    Correction::Ref correction_light,
    const std::string systematic,
    const std::string working_point) {
  RVec<float> weight_vec;
  for (size_t idx = 0; idx < jet_hadron_flavour_vec.size(); idx++) {
    const uint8_t hadron_flavour = jet_hadron_flavour_vec.at(idx);

    const PtEtaPhiMVector& p4 = jet_p4_vec.at(idx);
    const float abs_eta = std::abs(p4.eta());
    const float pt = p4.pt();

    const bool is_bc = (hadron_flavour == 5) or (hadron_flavour == 4);
    auto correction = is_bc ? correction_bc : correction_light;

    const float weight = correction_bc->evaluate({
        systematic, working_point, hadron_flavour, abs_eta, pt});
    weight_vec.push_back(weight);
  }
  return weight_vec;
}


RVec<float>
getBTaggingShapeCorrection(
    const RVec<uint8_t>& jet_hadron_flavour_vec,
    const RVec<PtEtaPhiMVector>& jet_p4_vec,
    const RVec<float>& jet_btag_discriminant_vec,
    Correction::Ref correction,
    const std::string systematic) {

  RVec<float> weight_vec;
  for (size_t idx = 0; idx < jet_hadron_flavour_vec.size(); idx++) {
    const uint8_t hadron_flavour = jet_hadron_flavour_vec.at(idx);
    const PtEtaPhiMVector& p4 = jet_p4_vec.at(idx);
    const float abs_eta = std::abs(p4.eta());
    const float pt = p4.pt();
    const float btag_discriminant = jet_btag_discriminant_vec.at(idx);

    float weight = 1.0;
    if ((hadron_flavour == 5) or (hadron_flavour == 4)) {
      weight *= correction->evaluate({
          systematic,
          hadron_flavour,
          abs_eta,
          pt,
          btag_discriminant
      });
    }
    weight_vec.push_back(weight);
  }
  return weight_vec;
};
