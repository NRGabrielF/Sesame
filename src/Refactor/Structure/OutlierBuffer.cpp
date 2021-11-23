//
// Created by tuidan on 2021/11/9.
//
#include <Refactor/Structure/OutlierBuffer.hpp>
#include <Refactor/Structure/MCluster.hpp>
#include <cfloat>

//TODO All need modify
std::vector<SESAME::MicroClusterPtr> SESAME::OutlierBuffer::getOutlierClusters() {
  return this->outlierClusters;
}
SESAME::MicroClusterPtr SESAME::OutlierBuffer::fillDensityTransformation(int minDensity) {
  for(int i = 0; i < this->outlierClusters.size(); i++) {
    if(this->outlierClusters[i]->weight >= minDensity) {
      MicroClusterPtr temp = this->outlierClusters[i]->copy();
      SESAME_INFO("Outliers transform into clusters!!!");
      this->outlierClusters.erase(this->outlierClusters.begin() + i);
      return temp;
    }
  }
  return nullptr;
}
void SESAME::OutlierBuffer::insertOutlierCluster(SESAME::PointPtr &p, int thresholdDistance) {
  double minDistance = DBL_MAX;
  int closestClusterID = 0;
  for (int i = 0; i < this->outlierClusters.size(); i++) {
    double dist = this->outlierClusters[i]->calCentroidDistance(p);
    if (dist < minDistance) {
      closestClusterID = i;
      minDistance = dist;
    }
  }
  if(minDistance <= thresholdDistance) {
    this->outlierClusters.at(closestClusterID)->updateAttribute(p);
    this->outlierClusters.at(closestClusterID)->setLastModifyTime(p->getTimeStamp());
  } else {
    MicroClusterPtr m = std::make_shared<SESAME::MicroCluster>(p->getDimension());
    m->updateAttribute(p);
    m->setLastModifyTime(p->getTimeStamp());
    this->outlierClusters.push_back(m);
  }

}
SESAME::OutlierBuffer::OutlierBuffer() {

}
SESAME::OutlierBuffer::~OutlierBuffer() {

}
SESAME::MicroClusterPtr SESAME::OutlierBuffer::fillTimeTransformation(double currentTime, double thresholdMininterval) {
  for(int i = 0; i < this->outlierClusters.size(); i++) {
    if(currentTime - this->outlierClusters[i]->getLastModifyTime() >= thresholdMininterval) {
      MicroClusterPtr temp = this->outlierClusters[i]->copy();
      SESAME_INFO("Outliers transform into clusters!!!");
      this->outlierClusters.erase(this->outlierClusters.begin() + i);
      return temp;
    }
  }
  return nullptr;
}

