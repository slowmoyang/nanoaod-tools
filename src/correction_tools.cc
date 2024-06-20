#include <nanoaod_tools/correction_tools.h>

#include <correction.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <filesystem>

using namespace correction;
namespace fs = std::filesystem;

std::unique_ptr<CorrectionSet> getCorrectionSet(const fs::path json_path) {
  std::cout << "load " << json_path << std::endl;
  if (not fs::exists(json_path)) {
    throw std::runtime_error("puWeights not found: " + json_path.string());
  }

  return CorrectionSet::from_file(json_path);
}


Correction::Ref getCorrection(const std::unique_ptr<CorrectionSet>& correction_set,
                              const std::string name) {
  if (not checkIfCorrectionExists(*correction_set, name)) {
    throw std::runtime_error("CorrectionNotFound: " + name);
  }

  return correction_set->at(name);
}


Correction::Ref getCorrection(const fs::path json_path,
                              const std::string name) {

  Correction::Ref correction{nullptr};
  if (auto correction_set = getCorrectionSet(json_path)) {
    correction = getCorrection(correction_set, name);
  }
  return correction;
}


// TODO CompoundCorrectionRef


std::shared_ptr<const CompoundCorrection> getCompoundCorrection(const std::unique_ptr<CorrectionSet>& correction_set,
                                                                const std::string name) {

  if (not checkIfCorrectionExists(correction_set->compound(), name)) {
    std::cerr << "CorrectionNotFound: " << name << std::endl;
    return nullptr;
  }

  return correction_set->compound().at(name);
}
