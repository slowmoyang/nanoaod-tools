#ifndef NANOAOD_TOOLS_JET_VETO_MAP_H_
#define NANOAOD_TOOLS_JET_VETO_MAP_H_

#include "ROOT/RVec.hxx"
#include "correction.h"

using namespace ROOT; // RVec using namespace correction; // correction
using namespace correction;

// https://cms-jerc.web.cern.ch/Recommendations/#jet-veto-maps
// Jet veto maps are mandatory for Run 3 analyses. The safest procedure would
// be to veto events if ANY jet with a loose selection lies in the veto
// regions.
// The nominal “loose selection” would be:
// - jet pT > 15 GeV
// - tight jet ID
// - PU jet ID for jets with pT < 50 GeV (At the moment for Run3, we do not
//   have any PU jet ID recommendations for AK4 jets since jets originating
//   from pileup are already suppressed at the jet clustering level with PUPPI)
// - jet EM fraction < 0.9
// jets that don’t overlap with PF muon (dR < 0.2)
bool getJetVetoMap(Correction::Ref jet_veto_map,
                   const std::string jet_veto_map_type,
                   const RVec<float> &eta_vec,
                   const RVec<float> &phi_vec);

#endif
