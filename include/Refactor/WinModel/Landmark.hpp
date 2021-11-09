//
// Created by tuidan on 2021/11/7.
//

#ifndef SESAME_SRC_REFACTOR_WINMODEL_LANDMARK_HPP_
#define SESAME_SRC_REFACTOR_WINMODEL_LANDMARK_HPP_
#include <Algorithm/DataStructure/Point.hpp>
#include <Algorithm/OfflineClustering/KMeans.hpp>
#include <Sinks/DataSink.hpp>
#include <Refactor/AlgorithmRegroup.hpp>
#include <Refactor/Structure/MCluster.hpp>
#include <Refactor/Structure/OutlierBuffer.hpp>
#include <vector>
namespace SESAME{
class Landmark;
class LandmarkParameter;
typedef std::shared_ptr<Landmark> LandmarkPtr;
typedef std::shared_ptr<LandmarkParameter> LandmarkParametersPtr;

class LandmarkParameter: public RegroupParameters {
 public:
  int windowLength;
  int thresholdCount;
  double thresholdDistance;
  double thresholdOutlierCount;
};

class Landmark : public AlgorithmRegroup {
 public:
  LandmarkParameter parameters;
  void runAlgorithm(PointPtr &input, DataSinkPtr &sinkPtr) override;
  void runOnline(PointPtr &input) override;
  void runOffline(DataSinkPtr &sinkPtr) override;
  void getFinalClusterCenter() override;
};
}
#endif //SESAME_SRC_REFACTOR_WINMODEL_LANDMARK_HPP_
