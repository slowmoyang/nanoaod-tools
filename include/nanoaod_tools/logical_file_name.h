#ifndef NANOAOD_TOOLS_UTILS_H_
#define NANOAOD_TOOLS_UTILS_H_

#include "Math/GenVector/PtEtaPhiM4D.h"
#include "Math/Vector4Dfwd.h"
#include "Math/GenVector/VectorUtil.h"


#include <string>
#include <memory>
#include <filesystem>

using namespace ROOT::Math;
namespace fs = std::filesystem;

// https://indico.cern.ch/event/669506/contributions/2782205/attachments/1560005/2455367/171116_-_DOMA_workshop_-_HEP_Data_Management_Introduction.pdf
struct LogicalFileName {
public:
  const fs::path root_dir;
  const std::string type;
  const std::string era;
  const std::string primary_dataset;
  const std::string data_tier;
  const std::string processed_dataset; // including version
  const std::string counter;
  const std::string filename;

  static LogicalFileName fromPath(const fs::path lfn_path);

  bool isData() const;

  bool isMC() const;

  int year() const;

  bool isTTto4Q() const;
};

#endif // NANOAOD_TOOLS_UTILS_H_
