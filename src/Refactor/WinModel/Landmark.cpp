//
// Created by tuidan on 2021/11/7.
//

#include <Refactor/WinModel/Landmark.hpp>
#include <Algorithm/DataStructure/DataStructureFactory.hpp>
#include <cfloat>
#include <Utils/BenchmarkUtils.hpp>

/**
 * Data Structure: Micro Cluster
 * Window Model: Landmark Window Model， length = 1
 * Outlier Detection: Density Based
 * Concept Drift Handling: Density Based
 * Offline Refinement: KMeans++
 */

void SESAME::Landmark::runOnlineClustering(PointPtr input) {
  int closestClusterID;
  double minDistance = DBL_MAX;
  for (int i = 0; i < this->microClusters.size(); i++) {
    double dist = microClusters[i]->calCentroidDistance(input);
    if (dist < minDistance) {
      closestClusterID = i;
      minDistance = dist;
    }
  }

  if(this->microClusters.size() == 0) {
    MClusterPtr newCluster = std::make_shared<MCluster>(this->parameters.dimension);
    newCluster->updateAttribute(input);
    this->microClusters.push_back(newCluster);
  } else{
    // distance is too large then throw the point into outliers
    if(minDistance > this->parameters.thresholdMaxDistance) {
      this->outliers->insertOutlierCluster(input, this->parameters.thresholdMaxDistance);
      MClusterPtr newCluster = this->outliers->fillDensityTransformation(this->parameters.thresholdMinDensity);
      // SESAME_INFO(this->outliers->getOutlierClusters().size());
      if(newCluster != nullptr) {
        this->microClusters.push_back(newCluster); // update transformation
      }
    } else {
        this->microClusters[closestClusterID]->updateAttribute(input);  // else normally insert into the micro-clusters
    }
  }
}

void SESAME::Landmark::getFinalClusterCenter() {
  SESAME_INFO("The mid cluster number is:" << this->microClusters .size());
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
  this->parameters.thresholdMinDensity = 2;
  this->parameters.thresholdMaxDistance = 7;
  this->outliers = std::make_shared<OutlierBuffer>();
}
void SESAME::Landmark::Initilize() {}

SESAME::Landmark::~Landmark() {}
