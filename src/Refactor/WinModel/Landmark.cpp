//
// Created by tuidan on 2021/11/7.
//

#include <Refactor/WinModel/Landmark.hpp>
#include <Algorithm/DataStructure/DataStructureFactory.hpp>
#include <cfloat>
#include <Utils/BenchmarkUtils.hpp>

/**
 * Data Structure: Micro Cluster
 * Window Model: Landmark Window Model
 * Outlier Detection: Distance Based
 * Concept Drift Handling: Count Based
 * Offline Refinement: KMeans++
 */

void SESAME::Landmark::runOnlineClustering(PointPtr input) {
  count++;
  MClusterPtr closestCluster = std::make_shared<MCluster>(this->parameters.dimension);
  double minDistance = DBL_MAX;
  for (int i = 0; i < this->microClusters.size(); i++) {
    double dist = microClusters[i]->calCentroidDistance(input);
    if (dist < minDistance) {
      closestCluster = microClusters[i]->copy();
      minDistance = dist;
    }
  }

  // distance is too large then throw the point into outliers
  if(minDistance > this->parameters.thresholdDistance) {
    this->outliers->insertOutlierCluster(input, this->parameters.thresholdDistance);
    MClusterPtr newCluster = this->outliers->fillTransformation(this->parameters.thresholdOutlierCount);
    SESAME_INFO(this->outliers->getOutlierClusters().size());
    if(newCluster != nullptr) {
      this->microClusters.push_back(newCluster); // update transformation
    }
  } else {
    if(closestCluster->getN() >= this->parameters.thresholdCount) {
      MClusterPtr newCluster = std::make_shared<MCluster>(this->parameters.dimension);
      newCluster->updateAttribute(input);
      this->microClusters.push_back(newCluster);
    } else{
      closestCluster->updateAttribute(input);  // else normally insert into the micro-clusters
    }
  }
}

void SESAME::Landmark::getFinalClusterCenter() {
  for(int i = 0; i < this->microClusters.size(); i++) {
    MClusterPtr mc = this->microClusters.at(i);
    PointPtr center = DataStructureFactory::createPoint(i,1,this->parameters.dimension, 0);
    center->setClusteringCenter(i);
    for(int j = 0; j < this->parameters.dimension; j++) {
      center->setFeatureItem(mc->getCentroid().at(j), j);
    }
    this->finalClusterCenters.push_back(center);
  }
}

void SESAME::Landmark::runOfflineClustering(SESAME::DataSinkPtr sinkPtr) {
  this->getFinalClusterCenter();
  vector <vector<PointPtr>> groups;

  std::vector<std::vector<PointPtr>> oldGroups, newGroups;

  this->km.runKMeans(this->parameters.numberOfClusters,
                     this->microClusters.size(),
                     this->finalClusterCenters,
                     oldGroups,
                     newGroups,
                     true);
  // store the result input output
  this->km.produceResult(oldGroups, sinkPtr);
}
SESAME::Landmark::Landmark(param_t &cmd_params) {
  this->parameters.pointNumber = cmd_params.pointNumber;
  this->parameters.dimension = cmd_params.dimension;
  this->parameters.numberOfClusters = cmd_params.clusterNumber;
  this->parameters.thresholdOutlierCount = 5;
  this->parameters.thresholdDistance = 2;
  this->parameters.thresholdCount = 20;
  this->outliers = std::make_shared<OutlierBuffer>();
  this->count = 0;
}
void SESAME::Landmark::Initilize() {
  SESAME_INFO(1);
}
SESAME::Landmark::~Landmark() {

}
