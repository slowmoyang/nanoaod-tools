#include <nanoaod_tools/lumi_mask.h>

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>

namespace fs = std::filesystem;


LumiMask::LumiMask(const std::vector<LuminosityBlockRange> data)
  : data_(data) {
}

std::shared_ptr<LumiMask>
LumiMask::fromJSON(
    const fs::path& golden_json_path) {
  if (fs::exists(golden_json_path)) {
    throw std::runtime_error("golden json not found: " + golden_json_path.string());
  }

  auto data = LumiMask::parseJSON(golden_json_path);
  return std::make_shared<LumiMask>(data);
}

std::vector<LuminosityBlockRange>
LumiMask::parseJSON(
    const fs::path& golden_json_path) {
  std::ifstream stream{golden_json_path};
  nlohmann::json data = nlohmann::json::parse(stream);

  std::vector<LuminosityBlockRange> good_lumi_block_range_vec{};
  for (const auto& [run_str, lumi_block_vec] : data.items()) {
    const uint32_t run = std::stoul(run_str.data());

    for (const auto& lumi_block : lumi_block_vec) {
      if (lumi_block.size() != 2) {
        // throw
      }
      const uint32_t first_lumi_block = lumi_block.at(0);
      const uint32_t last_lumi_block = lumi_block.at(1);

      good_lumi_block_range_vec.emplace_back(run, first_lumi_block, last_lumi_block);
    }
  }

  std::sort(good_lumi_block_range_vec.begin(),
            good_lumi_block_range_vec.end());

  return good_lumi_block_range_vec;
}

bool LumiMask::select(uint32_t run, uint32_t luminosity_block) const {
  return std::binary_search(data_.begin(), data_.end(), LuminosityBlockRange{run, luminosity_block, luminosity_block});
}

bool LumiMask::operator()(uint32_t run, uint32_t luminosity_block) const {
  return this->select(run, luminosity_block);
}
