#include <nanoaod_tools/jet_energy_resolution.h>

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
                             const std::shared_ptr<TRandom3> prng) {
  const float eps = prng->Gaus(0.f, sigma_jer);

  return 1.f + eps * std::sqrt(std::max(std::pow(s_jer, 2.f) - 1.0f, 0.f));
}

// Returns a RVec of JES correction factors
// Rho_fixedGridRhoFastjetAll
// https://cms-jerc.web.cern.ch/JER/#smearing-procedures
RVec<float> getJetEnergyResolutionCorrectionFactor(const RVec<PtEtaPhiMVector>& rec_jet_vec,
                                                   const RVec<int16_t>& rec_jet_gen_jet_idx_vec,
                                                   const RVec<PtEtaPhiMVector>& gen_jet_vec,
                                                   const float rho,
                                                   Correction::Ref resolution_correction,
                                                   Correction::Ref scale_factor_correction,
                                                   const std::string systematic,
                                                   const std::shared_ptr<TRandom3> prng) {


  const size_t rec_jet_size = rec_jet_vec.size();

  // output
  RVec<float> correction_factor_vec;
  correction_factor_vec.reserve(rec_jet_size);

  for (size_t rec_jet_idx = 0; rec_jet_idx < rec_jet_size; rec_jet_idx++) {
    float correction_factor = -1.0f;

    const PtEtaPhiMVector& rec_jet = rec_jet_vec.at(rec_jet_idx);
    const int16_t gen_jet_idx = rec_jet_gen_jet_idx_vec.at(rec_jet_idx);

    // the relative pT resolution as measured in simulation
    const float sigma_jer = resolution_correction->evaluate({
      std::clamp(rec_jet.eta(), -5.191, +5.191),
      rec_jet.pt(),
      rho,
    });

    // the data-to-simulation core resolution scale factor
    const float s_jer = scale_factor_correction->evaluate({
      std::clamp(rec_jet.eta(), -5.191, +5.191),
      rec_jet.pt(),
      systematic,
    });

    if (gen_jet_idx >= 0) {
      const PtEtaPhiMVector& gen_jet = gen_jet_vec.at(gen_jet_idx);
      const float dr = VectorUtil::DeltaR(rec_jet, gen_jet);
      const float dpt = rec_jet.pt() - gen_jet.pt();

      const bool is_good_match_dr = (dr < 0.2); // FIXME 0.2 = R_cone / 2 = 0.4 / 0.2
      const bool is_good_match_dpt = std::abs(dpt) < (3 * s_jer * rec_jet.pt()); // FIXME
      const bool is_good_match = is_good_match_dr and is_good_match_dpt;
      if (is_good_match) {
        // scaling method
        correction_factor = 1. + (s_jer - 1) * dpt / rec_jet.pt();

      } else {
        correction_factor = runJERStochasticMethod(sigma_jer, s_jer, prng);
      }

    } else {
      correction_factor = runJERStochasticMethod(sigma_jer, s_jer, prng);

    } // condition on gen_jet_idx

    correction_factor_vec.push_back(correction_factor);
  }

  return correction_factor_vec;
};
