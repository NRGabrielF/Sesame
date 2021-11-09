//
// Created by tuidan on 2021/11/7.
//

#ifndef SESAME_INCLUDE_REFACTOR_ALGORITHMREGROUP_HPP_
#define SESAME_INCLUDE_REFACTOR_ALGORITHMREGROUP_HPP_
#include <Algorithm/DataStructure/Point.hpp>
#include <Algorithm/OfflineClustering/KMeans.hpp>
#include <Refactor/Structure/MCluster.hpp>
#include <Refactor/Structure/OutlierBuffer.hpp>
#include <Sinks/DataSink.hpp>
namespace SESAME{

class AlgorithmRegroup;
class RegroupParameters;

typedef std::shared_ptr<AlgorithmRegroup> GeneralGroupPtr;
typedef std::shared_ptr<RegroupParameters> AlgorithmPtr;
class RegroupParameters {
 public:
  int pointNumber;
  int dimension;
  int numberOfClusters;
};

class AlgorithmRegroup {
 public:
  std::vector<MClusterPtr> microClusters;
  OutlierBufferPtr outliers;
  std::vector<PointPtr> finalClusterCenters;
  KMeans km;
  AlgorithmRegroup() = default;
  virtual ~AlgorithmRegroup() = default;

  virtual void runAlgorithm(PointPtr &input, DataSinkPtr &sinkPtr); // controller

  virtual void initialize();
  virtual void runOnline(PointPtr &input);
  virtual void runOffline(DataSinkPtr &sinkPtr); // the main three phases of all of the algorithms
  virtual void getFinalClusterCenter();

  void store(std::string outputPath, std::vector<PointPtr> results);
};
}
#endif //SESAME_INCLUDE_REFACTOR_ALGORITHMREGROUP_HPP_
