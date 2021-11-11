//
// Created by tuidan on 2021/11/7.
//

#ifndef SESAME_SRC_REFACTOR_WINMODEL_DAMPED_HPP_
#define SESAME_SRC_REFACTOR_WINMODEL_DAMPED_HPP_
#include <Algorithm/DataStructure/Point.hpp>
#include <Algorithm/OfflineClustering/KMeans.hpp>
#include <Sinks/DataSink.hpp>
#include <Algorithm/Algorithm.hpp>
#include <Refactor/Structure/MCluster.hpp>
#include <Refactor/Structure/OutlierBuffer.hpp>
#include <Utils/BenchmarkUtils.hpp>
#include <vector>
namespace SESAME{

class DampedParameter: public AlgorithmParameters {
 public:
  //int windowLength;
  double alpha;
  double lambda;
  int thresholdCount;
  double thresholdDistance;
  double thresholdOutlierCount;
};

class Damped : public Algorithm {
 public:
  DampedParameter parameters{};
  std::vector<MClusterPtr> microClusters;
  OutlierBufferPtr outliers;
  std::vector<PointPtr> finalClusterCenters;
  KMeans km;

  Damped(param_t &cmd_params);

  ~Damped();

  void getFinalClusterCenter();

  void Initilize() override;

  void runOnlineClustering(PointPtr input) override;

  void runOfflineClustering(DataSinkPtr sinkPtr) override;
};
}

#endif //SESAME_SRC_REFACTOR_WINMODEL_DAMPED_HPP_
