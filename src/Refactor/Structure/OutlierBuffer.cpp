//
// Created by tuidan on 2021/11/9.
//
#include <Refactor/Structure/OutlierBuffer.hpp>
#include <Refactor/Structure/MCluster.hpp>
#include <cfloat>
std::vector<SESAME::MClusterPtr> SESAME::OutlierBuffer::getOutlierClusters() {
  return this->outlierClusters;
}
SESAME::MClusterPtr SESAME::OutlierBuffer::fillTransformation(int thresholdCount) {
  for(int i = 0; i < this->outlierClusters.size(); i++) {
    if(this->outlierClusters[i]->getN() >= thresholdCount) {
      MClusterPtr temp = this->outlierClusters[i]->copy();
      this->outlierClusters.erase(this->outlierClusters.begin() + i);
      return temp;
    }
  }
}
void SESAME::OutlierBuffer::insertOutlierCluster(SESAME::PointPtr &p) {
  double minDistance = DBL_MAX;
  int closestClusterID = 0;
  for (int i = 0; i < this->outlierClusters.size(); i++) {
    double dist = this->outlierClusters[i]->calCentroidDistance(p);
    if (dist < minDistance) {
      closestClusterID = i;
      minDistance = dist;
    }
  }
  this->outlierClusters.at(closestClusterID)->updateAttribute(p);
}

