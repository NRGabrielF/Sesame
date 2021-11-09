//
// Created by tuidan on 2021/11/7.
//

#ifndef SESAME_SRC_REFACTOR_WINMODEL_LANDMARK_HPP_
#define SESAME_SRC_REFACTOR_WINMODEL_LANDMARK_HPP_
#include <Algorithm/DataStructure/Point.hpp>
#include <Algorithm/OfflineClustering/KMeans.hpp>
#include <Sinks/DataSink.hpp>
#include <Algorithm/Algorithm.hpp>
#include <Refactor/Structure/MCluster.hpp>
#include <Refactor/Structure/OutlierBuffer.hpp>
#include <Utils/BenchmarkUtils.hpp>
#include <vector>
namespace SESAME{

class LandmarkParameter: public AlgorithmParameters {
 public:
  //int windowLength;
  int thresholdCount;
  double thresholdDistance;
  double thresholdOutlierCount;
};

class Landmark : public Algorithm {
 public:
  LandmarkParameter parameters{};
  std::vector<MClusterPtr> microClusters;
  OutlierBufferPtr outliers;
  std::vector<PointPtr> finalClusterCenters;
  KMeans km;
  int count;

  Landmark(param_t &cmd_params);

  ~Landmark();

  void getFinalClusterCenter();

  void Initilize() override;

  void runOnlineClustering(PointPtr input) override;

  void runOfflineClustering(DataSinkPtr sinkPtr) override;
};
}
#endif //SESAME_SRC_REFACTOR_WINMODEL_LANDMARK_HPP_
