//
// Created by tuidan on 2021/11/7.
//

#include <Refactor/WinModel/Damped.hpp>
#include <Algorithm/DataStructure/DataStructureFactory.hpp>
#include <cfloat>
#include <Utils/BenchmarkUtils.hpp>

/**
 * Data Structure: Micro Cluster
 * Window Model: Damped Window Model， length = 1
 * Outlier Detection: Distance Based
 * Concept Drift Handling: Count Based
 * Offline Refinement: KMeans++
 */

void SESAME::Damped::runOnlineClustering(PointPtr input) {
  input->setTimeStamp(input->getIndex() / 4); // TODO: note to change， here we assume the data comes every 0.25s
  int closestClusterID;
  double minDistance = DBL_MAX;
  for (int i = 0; i < this->microClusters.size(); i++) {
    this->microClusters[i]->updateAttribute(input->getTimeStamp(),
                                                           this->parameters.alpha,
                                                           this->parameters.lambda);
    double dist = this->microClusters[i]->calCentroidDistance(input);
    if (dist < minDistance) {
      closestClusterID = i;
      minDistance = dist;
    }
  }

  if(this->microClusters.size() == 0) {
    MClusterPtr newCluster = std::make_shared<MCluster>(this->parameters.dimension);
    newCluster->updateAttribute(input);
    newCluster->setLastModifyTime(input->getTimeStamp());
    this->microClusters.push_back(newCluster);
  } else{
    // distance is too large then throw the point into outliers
    if(minDistance > this->parameters.thresholdDistance) {
      this->outliers->insertOutlierCluster(input, this->parameters.thresholdDistance);
      MClusterPtr newCluster = this->outliers->fillTransformation(this->parameters.thresholdOutlierCount);
      // SESAME_INFO(this->outliers->getOutlierClusters().size());
      if(newCluster != nullptr) {
        this->microClusters.push_back(newCluster); // update transformation
      }
    } else {
      if(this->microClusters[closestClusterID]->getN() >= this->parameters.thresholdCount) {
        MClusterPtr newCluster = std::make_shared<MCluster>(this->parameters.dimension);
        newCluster->updateAttribute(input);
        this->microClusters.push_back(newCluster);
      } else{
        this->microClusters[closestClusterID]->updateAttribute(input);  // else normally insert into the micro-clusters
      }
    }
  }
}

void SESAME::Damped::getFinalClusterCenter() {
  SESAME_INFO("The mid cluster number is:" << this->microClusters.size());
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

void SESAME::Damped::runOfflineClustering(SESAME::DataSinkPtr sinkPtr) {
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
SESAME::Damped::Damped(param_t &cmd_params) {
  this->parameters.pointNumber = cmd_params.pointNumber;
  this->parameters.dimension = cmd_params.dimension;
  this->parameters.numberOfClusters = cmd_params.clusterNumber;
  this->parameters.thresholdOutlierCount = 2;
  this->parameters.thresholdDistance = 7;
  this->parameters.thresholdCount = 10;
  this->parameters.alpha = cmd_params.alpha;
  this->parameters.lambda = cmd_params.lambda;
  this->outliers = std::make_shared<OutlierBuffer>();
}
void SESAME::Damped::Initilize() {}

SESAME::Damped::~Damped() {}
