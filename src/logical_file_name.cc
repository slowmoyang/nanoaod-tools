#include <nanoaod_tools/logical_file_name.h>

#include <string>

using namespace ROOT::Math;


// https://indico.cern.ch/event/669506/contributions/2782205/attachments/1560005/2455367/171116_-_DOMA_workshop_-_HEP_Data_Management_Introduction.pdf
LogicalFileName LogicalFileName::fromPath(const fs::path lfn_path) {
  // /store/data/<era>/<primary dataset name>/<data tier name>/<processed dataset name>-<version>/<counter>/<filename>
  // /hdfs/mc/Run3Summer22NanoAODv12/TTto4Q_TuneCP5_13p6TeV_powheg-pythia8/NANOAODSIM/130X_mcRun3_2022_realistic_v5-v2/30000/60ff9955-8828-4462-a6d3-a2b6b3f27154.root

  const fs::path counter_dir = lfn_path.parent_path();
  // processing info and version
  const fs::path processed_version_dir = counter_dir.parent_path();
  // processed version including version
  const fs::path data_tier_dir = processed_version_dir.parent_path();
  // primary dataset
  const fs::path primary_dataset_dir = data_tier_dir.parent_path();
  const fs::path era_dir = primary_dataset_dir.parent_path();
  // data type: data or mc
  const fs::path type_dir = era_dir.parent_path();
  const fs::path root_dir = type_dir.parent_path();

  const std::string filename = lfn_path.filename();
  const std::string counter = counter_dir.filename();
  const std::string processed_dataset = processed_version_dir.filename();
  const std::string data_tier = data_tier_dir.filename();
  const std::string primary_dataset = primary_dataset_dir.filename();
  const std::string era = era_dir.filename();
  const std::string type = type_dir.filename();

  // assert type in ("data", "mc")

  return LogicalFileName{root_dir, type, era, primary_dataset, data_tier,
                         processed_dataset, counter, filename};
}

bool LogicalFileName::isData() const {
  return type == "data";
}

bool LogicalFileName::isMC() const {
  return type == "mc";
}

int LogicalFileName::year() const {
  if (era.starts_with("Run3Summer22")) {
    return 2022;

  } else {
    // FIXME
    return -1;

  }
}

bool LogicalFileName::isTTto4Q() const {
  // FIXME amcatnlo
  return primary_dataset == "TTto4Q_TuneCP5_13p6TeV_powheg-pythia8";
}



std::ostream& operator<<(std::ostream& os, const LogicalFileName& lfn) {
  os << "root_dir: "<< lfn.root_dir
     << std::endl
     << "type: " << lfn.type
     << std::endl
     << "era: " << lfn.era
     << std::endl
     << "primary_dataset: " << lfn.primary_dataset
     << std::endl
     << "data_tier: " << lfn.data_tier
     << std::endl
     << "processed_dataset: " << lfn.processed_dataset
     << std::endl
     << "counter: " << lfn.counter
     << std::endl
     << "filename: " << lfn.filename
     << std::endl;
  return os;
}
