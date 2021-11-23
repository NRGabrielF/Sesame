//
// Created by tuidan on 2021/11/23.
//

#ifndef SESAME_INCLUDE_REFACTOR_STRUCTURE_REFACTORPARAMETERS_HPP_
#define SESAME_INCLUDE_REFACTOR_STRUCTURE_REFACTORPARAMETERS_HPP_
#include <memory>
#include <vector>
#include <Algorithm/DataStructure/Point.hpp>
#include <Refactor/Structure/OutlierBuffer.hpp>
#include <Algorithm/DataStructure/MicroCluster.hpp>

namespace SESAME {
class RefactorParameters;
typedef std::shared_ptr<RefactorParameters> RefactorParametersPtr;
class RefactorParameters {
 public:
  int dimension;
  int pointNumber;
  int windowSize;
  int numberOfClusters;
  double alpha;
  double lambda;
  double maxInsertDistance;
  double minDensityTransform;
  double minTimeTransform;
  double currentTime;
  std::vector<MicroClusterPtr> outlierClusters;
  std::vector<PointPtr> windowElement;
  std::vector<MicroClusterPtr> microClusters;
  std::vector<MicroClusterPtr> finalClusterCenters;
};
}

#endif //SESAME_INCLUDE_REFACTOR_STRUCTURE_REFACTORPARAMETERS_HPP_
