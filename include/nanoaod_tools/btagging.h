#ifndef NANOAOD_TOOLS_BTAGGING_H_
#define NANOAOD_TOOLS_BTAGGING_H_

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


// https://btv-wiki.docs.cern.ch
const std::map<std::string, std::string> kBTagAlgoBranchMap = {
    {"robustParticleTransformer", "RobustParT"}
};


// https://btv-wiki.docs.cern.ch/
RVec<float> getBTaggingFixedWPCorrection(
    const RVec<uint8_t>& jet_hadron_flavour_vec,
    const RVec<PtEtaPhiMVector>& jet_p4_vec,
    Correction::Ref correction_bc,
    Correction::Ref correction_light,
    const std::string systematic,
    const std::string working_point);


RVec<float> getBTaggingShapeCorrection(
    const RVec<uint8_t>& jet_hadron_flavour_vec,
    const RVec<PtEtaPhiMVector>& jet_p4_vec,
    const RVec<float>& jet_btag_discriminant_vec,
    Correction::Ref correction,
    const std::string systematic);

#endif // NANOAOD_TOOLS_BTAGGING_H_
