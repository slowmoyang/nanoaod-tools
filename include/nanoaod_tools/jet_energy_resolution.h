#ifndef NANOAOD_TOOLS_JET_ENERGY_RESOLUTION_H_
#define NANOAOD_TOOLS_JET_ENERGY_RESOLUTION_H_

#include "ROOT/RVec.hxx"
#include "Math/GenVector/PtEtaPhiM4D.h"
#include "Math/Vector4D.h"
#include "Math/Vector4Dfwd.h"
#include "Math/GenVector/VectorUtil.h"

#include "TRandom3.h"
#include "correction.h"
#include <algorithm>
#include <memory>

using namespace ROOT::VecOps;
using namespace ROOT::Math;
using namespace correction;

float runJERStochasticMethod(const float sigma_jer,
                             const float s_jer,
                             const std::shared_ptr<TRandom3> prng);

// Returns a RVec of JER correction factors
// https://cms-jerc.web.cern.ch/JER/
// https://github.com/cms-nanoAOD/nanoAOD-tools/blob/master/python/postprocessing/modules/jme/jetSmearer.py#L101-L193
RVec<float>
getJetEnergyResolutionCorrectionFactor(
    const RVec<PtEtaPhiMVector>& rec_jet_vec,
    const RVec<int16_t>& rec_jet_gen_jet_idx_vec,
    const RVec<PtEtaPhiMVector>& gen_jet_vec,
    const float rho,
    Correction::Ref resolution_correction,
    Correction::Ref scale_factor_correction,
    const std::string systematic,
    const std::shared_ptr<TRandom3> prng);

#endif // NANOAOD_TOOLS_JET_ENERGY_RESOLUTION_H_
