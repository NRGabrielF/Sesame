//
// Created by tuidan on 2021/11/23.
//

#ifndef SESAME_INCLUDE_REFACTOR_STRUCTURE_REFACTORPARAMETERS_HPP_
#define SESAME_INCLUDE_REFACTOR_STRUCTURE_REFACTORPARAMETERS_HPP_
#include <memory>
#include <vector>
#include <Algorithm/DataStructure/Point.hpp>
#include <Refactor/Structure/OutlierBuffer.hpp>
#include <Refactor/Structure/MCluster.hpp>

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
  std::vector<MClusterPtr> outlierClusters;
  std::vector<PointPtr> windowElement;
  std::vector<MClusterPtr> microClusters;
  OutlierBufferPtr outliers;
  std::vector<PointPtr> finalClusterCenters;
};
}

#endif //SESAME_INCLUDE_REFACTOR_STRUCTURE_REFACTORPARAMETERS_HPP_
