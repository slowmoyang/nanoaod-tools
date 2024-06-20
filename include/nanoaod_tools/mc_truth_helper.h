#ifndef NANOAOD_TOOLS_MC_TRUTH_HELPER_H_
#define NANOAOD_TOOLS_MC_TRUTH_HELPER_H_

#include <cstdint>
#include <set>
#include "ROOT/RVec.hxx"

using namespace ROOT;

// coped from https://github.com/cms-sw/cmssw/blob/master/DataFormats/HepMCCandidate/interface/GenStatusFlags.h
enum StatusBitEnum {
  kIsPrompt = 0,
  kIsDecayedLeptonHadron,
  kIsTauDecayProduct,
  kIsPromptTauDecayProduct,
  kIsDirectTauDecayProduct,
  kIsDirectPromptTauDecayProduct,
  kIsDirectHadronDecayProduct,
  kIsHardProcess,
  kFromHardProcess,
  kIsHardProcessTauDecayProduct,
  kIsDirectHardProcessTauDecayProduct,
  kFromHardProcessBeforeFSR,
  kIsFirstCopy,
  kIsLastCopy,
  kIsLastCopyBeforeFSR
};

bool hasStatusBit(const uint16_t flag, const StatusBitEnum bit);

bool hasStatusBit(const uint16_t flag, const std::set<StatusBitEnum>& bit_set);

RVec<bool> hasStatusBit(const RVec<uint16_t> flag, const StatusBitEnum bit);

RVec<bool> hasStatusBit(const RVec<uint16_t> flag_vec,
                        const std::set<StatusBitEnum>& status_bit_vec);

int16_t findLastCopy(const int16_t start_idx,
                    const RVec<int32_t>& pdg_id_vec,
                    const RVec<int16_t>& mother_idx_vec);

int16_t findCopy(const int16_t start_idx,
                 const std::set<StatusBitEnum>& status_bit_set,
                 const RVec<int32_t>& pdg_id_vec,
                 const RVec<uint16_t>& status_flags_vec,
                 const RVec<int16_t>& mother_idx_vec);

#endif // NANOAOD_TOOLS_MC_TRUTH_HELPER_H_
