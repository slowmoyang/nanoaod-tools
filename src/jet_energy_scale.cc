#include "nanoaod_tools/jet_energy_scale.h"

// https://cms-jerc.web.cern.ch/Recommendations/#jet-energy-scale_1
// https://docs.google.com/spreadsheets/d/1JZfk78_9SD225bcUuTWVo4i02vwI5FfeVKH-dwzUdhM/edit#gid=1345121349

#include "ROOT/RVec.hxx"
#include "Math/GenVector/PtEtaPhiM4D.h"
#include "Math/Vector4D.h"
#include "Math/Vector4Dfwd.h"
#include "Math/GenVector/VectorUtil.h"


#include "correction.h"

#include <string>
#include <vector>

using namespace ROOT::VecOps;
using namespace ROOT::Math;
using namespace correction;

// returns JES uncertainty correction factor
RVec<float> getJESUncertaintyCorrectionFactor(const RVec<PtEtaPhiMVector>& jet_vec,
                                              const Correction::Ref jes_unc_correction,
                                              const std::string systematic) {
  if (systematic == "nom") { // FIXME
    return RVec<float>(jet_vec.size(), 1.0f);
  }

  RVec<float> correction_factor_vec{};
  correction_factor_vec.reserve(jet_vec.size());

  const float mult = systematic == "up" ? +1.f : -1.f;

  for (const PtEtaPhiMVector& jet : jet_vec) {
    const float correction_factor = 1 + mult * jes_unc_correction->evaluate({jet.eta(), jet.pt()});
    correction_factor_vec.push_back(correction_factor);
  }

  return correction_factor_vec;
}

