#ifndef NANOAOD_TOOLS_JET_ENERGY_SCALE_H_
#define NANOAOD_TOOLS_JET_ENERGY_SCALE_H_

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
// - Run3
//   - https://cms-jerc.web.cern.ch/JECUncertaintySources/
//   - https://cms-jerc.web.cern.ch/Recommendations/#jet-energy-scale_1
// - Run2
//   - https://twiki.cern.ch/twiki/bin/view/CMS/JECUncertaintySources
RVec<float>
getJESUncertaintyCorrectionFactor(
    const RVec<PtEtaPhiMVector>& jet_vec,
    const Correction::Ref jes_unc_correction,
    const std::string systematic);

#endif // NANOAOD_TOOLS_JET_ENERGY_SCALE_H_
