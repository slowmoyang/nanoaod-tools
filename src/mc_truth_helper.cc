#include <nanoaod_tools/mc_truth_helper.h>

#include <cstdint>
#include <set>
#include <stdexcept>

#include "ROOT/RVec.hxx"


using namespace ROOT;

bool hasStatusBit(const uint16_t flag, const StatusBitEnum bit) {
  return (flag & (1 << bit)) != 0;
}

bool hasStatusBit(const uint16_t flag, const std::set<StatusBitEnum>& bit_set) {
  bool has_bits = true;
  for (const StatusBitEnum bit : bit_set) {
    has_bits &= hasStatusBit(flag, bit);
  }
  return has_bits;
}

RVec<bool> hasStatusBit(const RVec<uint16_t> flag, const StatusBitEnum bit) {
  return (flag & (1 << bit)) != 0;
}

RVec<bool> hasStatusBit(const RVec<uint16_t> flag_vec, const std::set<StatusBitEnum>& status_bit_vec) {
  RVec<bool> output(flag_vec.size(), true);
  for (const StatusBitEnum status_bit : status_bit_vec) {
    output &= hasStatusBit(flag_vec, status_bit);
  }
  return output;
}

int16_t findLastCopy(const int16_t start_idx,
                    const RVec<int32_t>& pdg_id_vec,
                    const RVec<int16_t>& mother_idx_vec) {

  const int32_t pdg_id = pdg_id_vec.at(start_idx);

  RVec<int16_t> output;

  int16_t last_idx = start_idx;

  bool found_copy = true;
  while (found_copy) {
    const RVecB daughter_mask = mother_idx_vec == last_idx;
    const RVecUL daughter_idx_vec = VecOps::Nonzero(daughter_mask);

    const RVecI daughter_pdg_id_vec = VecOps::Take(pdg_id_vec, daughter_idx_vec);
    const RVecB daughter_copy_mask = daughter_pdg_id_vec == pdg_id;
    found_copy = VecOps::Any(daughter_copy_mask);
    if (found_copy) {
      last_idx = VecOps::Nonzero(daughter_copy_mask).at(0); // FIXME
    }
  }

  return last_idx;
}


int16_t findCopy(const int16_t start_idx,
                const std::set<StatusBitEnum>& status_bit_set,
                const RVec<int32_t>& pdg_id_vec,
                const RVec<uint16_t>& status_flags_vec,
                const RVec<int16_t>& mother_idx_vec) {
  const int32_t pdg_id = pdg_id_vec.at(start_idx);

  int16_t idx = start_idx;
  while (not hasStatusBit(status_flags_vec.at(idx), status_bit_set)) {
    const RVec<int16_t> daughter_idx_vec = VecOps::Nonzero(mother_idx_vec == idx);
    const RVec<int32_t> daughter_pdg_id_vec = VecOps::Take(pdg_id_vec, daughter_idx_vec);
    const RVec<bool> daughter_copy_mask = daughter_pdg_id_vec == pdg_id;

    const RVec<int16_t> daughter_copy_idx_vec = VecOps::Nonzero(daughter_copy_mask);

    const int16_t copy_size = daughter_copy_idx_vec.size();
    if (copy_size == 1) {
      idx = daughter_idx_vec.at(daughter_copy_idx_vec.at(0));

    } else {
      throw std::runtime_error("???");

    }

  }

  if (pdg_id_vec.at(idx) != pdg_id) {
    throw std::runtime_error("copy's pdg id is different from the original pdg id");
  }

  return idx;
}
