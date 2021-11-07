//
// Created by tuidan on 2021/11/7.
//

#ifndef SESAME_SRC_REFACTOR_WINMODEL_LANDMARK_HPP_
#define SESAME_SRC_REFACTOR_WINMODEL_LANDMARK_HPP_
#include <Algorithm/DataStructure/Point.hpp>
#include <Algorithm/OfflineClustering/KMeans.hpp>
#include <Sinks/DataSink.hpp>
#include <Refactor/AlgorithmRegroup.hpp>

class Landmark;
typedef std::shared_ptr<Landmark> LandmarkPtr;

namespace SESAME{
class Landmark : public AlgorithmRegroup {
 public:
  void runAlgorithm(PointPtr input, DataSinkPtr sinkPtr);
  void initialize();
  void runOnline(PointPtr input);
  void runOffline(DataSinkPtr sinkPtr);
};
}
#endif //SESAME_SRC_REFACTOR_WINMODEL_LANDMARK_HPP_
