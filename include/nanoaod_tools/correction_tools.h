#ifndef NANOAOD_TOOLS_CORRECTION_TOOLS_H_
#define NANOAOD_TOOLS_CORRECTION_TOOLS_H_

#include "correction.h"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <filesystem>

using namespace correction;
namespace fs = std::filesystem;


// mapping is supposed to be CorrectionSet or CompoundCorrection
template<typename T>
bool checkIfCorrectionExists(const T& mapping,
                             const std::string key) {
  bool found = false;
  for (auto [k, v] : mapping) {
    if (key == k) {
      found = true;
      break;
    }
  }
  return found;
}


std::unique_ptr<CorrectionSet> getCorrectionSet(const fs::path json_path);


Correction::Ref getCorrection(const std::unique_ptr<CorrectionSet>& correction_set,
                              const std::string name);

Correction::Ref getCorrection(const fs::path json_path,
                              const std::string name);

// TODO CompoundCorrectionRef

std::shared_ptr<const CompoundCorrection>
getCompoundCorrection(const std::unique_ptr<CorrectionSet>& correction_set,
                      const std::string name);

#endif // NANOAOD_TOOLS_CORRECTION_TOOLS_H_
