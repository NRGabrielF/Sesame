//
// Created by tuidan on 2021/11/7.
//

#ifndef SESAME_INCLUDE_REFACTOR_ALGORITHMREGROUP_HPP_
#define SESAME_INCLUDE_REFACTOR_ALGORITHMREGROUP_HPP_
#include <Algorithm/DataStructure/Point.hpp>
#include <Algorithm/OfflineClustering/KMeans.hpp>
#include <Sinks/DataSink.hpp>

class AlgorithmRegroup;
typedef std::shared_ptr<AlgorithmRegroup> GeneralGroupPtr;

namespace SESAME{
class AlgorithmRegroup {
 public:
  AlgorithmRegroup() = default;
  virtual ~AlgorithmRegroup() = default;

  virtual void runAlgorithm(PointPtr input, DataSinkPtr sinkPtr); // controller

  virtual void initialize();
  virtual void runOnline(PointPtr input);
  virtual void runOffline(DataSinkPtr sinkPtr); // the main three phases of all of the algorithms

  void store(std::string outputPath, std::vector<PointPtr> results);
};
}
#endif //SESAME_INCLUDE_REFACTOR_ALGORITHMREGROUP_HPP_
