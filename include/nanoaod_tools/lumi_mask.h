#ifndef NANOAOD_TOOLS_LUMIMASK_H_
#define NANOAOD_TOOLS_LUMIMASK_H_
// https://twiki.cern.ch/twiki/bin/view/CMS/PdmVRun3Analysis
// https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGoodLumiSectionsJSONFile
//
// https://github.com/cms-sw/cmssw/blob/CMSSW_14_1_0_pre4/FWCore/Sources/interface/EventSkipperByID.h
// https://github.com/cms-sw/cmssw/blob/CMSSW_14_1_0_pre4/FWCore/Sources/src/EventSkipperByID.cc
// https://github.com/cms-sw/cmssw/blob/CMSSW_14_1_0_pre4/DataFormats/Provenance/interface/LuminosityBlockRange.h
// https://github.com/cms-sw/cmssw/blob/CMSSW_14_1_0_pre4/DataFormats/Provenance/src/LuminosityBlockRange.cc

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>

namespace fs = std::filesystem;

struct LuminosityBlockRange {
 public:
  uint32_t run;
  uint32_t first_lumi_block;
  uint32_t last_lumi_block;

  LuminosityBlockRange(uint32_t run,
                       uint32_t first_lumi_block,
                       uint32_t last_lumi_block)
      : run(run),
        first_lumi_block(first_lumi_block),
        last_lumi_block(last_lumi_block) {
  }

  friend bool operator<(const LuminosityBlockRange& lhs,
                        const LuminosityBlockRange& rhs) {
    return (lhs.run == rhs.run) ? (lhs.last_lumi_block < rhs.first_lumi_block) : (lhs.run < rhs.run);
  }
};

class LumiMask {
 public:
  LumiMask(const std::vector<LuminosityBlockRange> data);

  static std::shared_ptr<LumiMask> fromJSON(const fs::path& golden_json_path);

  static std::vector<LuminosityBlockRange> parseJSON(const fs::path& golden_json_path);

  bool select(uint32_t run, uint32_t luminosity_block) const;

  bool operator()(uint32_t run, uint32_t luminosity_block) const;

 private:
  const std::vector<LuminosityBlockRange> data_;
};


#endif // NANOAOD_TOOLS_LUMIMASK_H_
