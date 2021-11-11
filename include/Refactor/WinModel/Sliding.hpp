//
// Created by tuidan on 2021/11/7.
//

#ifndef SESAME_SRC_REFACTOR_WINMODEL_SLIDING_HPP_
#define SESAME_SRC_REFACTOR_WINMODEL_SLIDING_HPP_
#include <Algorithm/DataStructure/Point.hpp>
#include <Algorithm/OfflineClustering/KMeans.hpp>
#include <Sinks/DataSink.hpp>
#include <Algorithm/Algorithm.hpp>
#include <Refactor/Structure/MCluster.hpp>
#include <Refactor/Structure/OutlierBuffer.hpp>
#include <Utils/BenchmarkUtils.hpp>
#include <vector>
namespace SESAME{

class SlidingParameter: public AlgorithmParameters {
 public:
  double timeInterval; // collect all the points into a window per timeInterval seconds.
  int thresholdCount;
  double thresholdDistance;
  double thresholdOutlierCount;
};

class Sliding : public Algorithm {
 public:
  SlidingParameter parameters{};
  int stampCount;
  std::vector<SESAME::PointPtr> buffer;
  std::vector<MClusterPtr> finalClusters;
  std::vector<MClusterPtr> midClusters;
  OutlierBufferPtr outliers;
  std::vector<PointPtr> finalClusterCenters;
  KMeans km;

  Sliding(param_t &cmd_params);

  ~Sliding();

  void getFinalClusterCenter();

  void Initilize() override;

  void runOnlineClustering(PointPtr input) override;

  void runOfflineClustering(DataSinkPtr sinkPtr) override;
};
}
#endif //SESAME_SRC_REFACTOR_WINMODEL_SLIDING_HPP_
