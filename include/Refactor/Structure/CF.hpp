//
// Created by tuidan on 2021/11/6.
//

#ifndef SESAME_INCLUDE_REFACTOR_STRUCTURE_CF_HPP_
#define SESAME_INCLUDE_REFACTOR_STRUCTURE_CF_HPP_
#include <Algorithm/DataStructure/Point.hpp>
#include <Algorithm/DataStructure/CFTree.hpp>
namespace SESAME{
Class CF {
 public:
  int maxInternalNodes; // Count based Concept Drift
  int maxLeafNodes; // Count based Concept Drift
  double thresholdDistance; // Distance based Outlier Detection
  int numberOfK; // offline KMeans++
  void runCF();
  void parameterInitial();
  void countInerNodes();
  void countLeafNodes();
  void calculateDistance();
  void normalInsert();

}
}
#endif //SESAME_INCLUDE_REFACTOR_STRUCTURE_CF_HPP_
