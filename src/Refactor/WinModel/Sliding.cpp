//
// Created by tuidan on 2021/11/7.
//

#include <Refactor/WinModel/Sliding.hpp>
#include <Algorithm/DataStructure/DataStructureFactory.hpp>
#include <cfloat>
#include <Utils/BenchmarkUtils.hpp>

/**
 * Data Structure: Micro Cluster
 * Window Model: Sliding Window Model， length = 1
 * Outlier Detection: Distance Based
 * Concept Drift Handling: Count Based
 * Offline Refinement: KMeans++
 */

void SESAME::Sliding::runOnlineClustering(PointPtr input) {
  input->setTimeStamp(input->getIndex() / 4); // TODO: note to change， here we assume the data comes every 0.25s
  if(input->getTimeStamp() > this->stampCount * this->parameters.timeInterval ||
      input->getIndex() == this->parameters.pointNumber -1) {
    for(int i = 0; i < this->buffer.size(); i++) {
      auto p = buffer[i];
      int closestClusterID;
      double minDistance = DBL_MAX;
      for (int i = 0; i < this->midClusters.size(); i++) {
        double dist = this->midClusters[i]->calCentroidDistance(input);
        if (dist < minDistance) {
          closestClusterID = i;
          minDistance = dist;
        }
      }
      if(this->midClusters.size() == 0) {
        MClusterPtr newCluster = std::make_shared<MCluster>(this->parameters.dimension);
        newCluster->updateAttribute(input);
        newCluster->setLastModifyTime(input->getTimeStamp());
        this->midClusters.push_back(newCluster);
      } else{
        // distance is too large then throw the point into outliers
        if(minDistance > this->parameters.thresholdDistance) {
          this->outliers->insertOutlierCluster(input, this->parameters.thresholdDistance);
          MClusterPtr newCluster = this->outliers->fillTransformation(this->parameters.thresholdOutlierCount);
          // SESAME_INFO(this->outliers->getOutlierClusters().size());
          if(newCluster != nullptr) {
            this->midClusters.push_back(newCluster); // update transformation
          }
        } else {
          if(this->midClusters[closestClusterID]->getN() >= this->parameters.thresholdCount) {
            MClusterPtr newCluster = std::make_shared<MCluster>(this->parameters.dimension);
            newCluster->updateAttribute(input);
            this->midClusters.push_back(newCluster);
          } else{
            this->midClusters[closestClusterID]->updateAttribute(input);  // else normally insert into the micro-clusters
          }
        }
      }
    }
    for(int i = 0; i < this->midClusters.size(); i++) {
      this->finalClusters.push_back(this->midClusters[i]);
    }
    if(input->getIndex() == this->parameters.pointNumber - 1) {
      SESAME_INFO("The mid cluster number is:" << this->midClusters.size());
    }
    this->midClusters.clear();
  } else {
    buffer.push_back(input);
  }
}

void SESAME::Sliding::getFinalClusterCenter() {
  for(int i = 0; i < this->finalClusters.size(); i++) {
    MClusterPtr mc = this->finalClusters.at(i);
    PointPtr center = DataStructureFactory::createPoint(i,1,this->parameters.dimension, 0);
    center->setClusteringCenter(i);
    for(int j = 0; j < this->parameters.dimension; j++) {
      center->setFeatureItem(mc->getCentroid().at(j), j);
    }
    this->finalClusterCenters.push_back(center);
  }
}

void SESAME::Sliding::runOfflineClustering(SESAME::DataSinkPtr sinkPtr) {
  this->getFinalClusterCenter();
  vector <vector<PointPtr>> groups;

  std::vector<std::vector<PointPtr>> oldGroups, newGroups;

  this->km.runKMeans(this->parameters.numberOfClusters,
                     this->finalClusters.size(),
                     this->finalClusterCenters,
                     oldGroups,
                     newGroups,
                     true);
  // store the result input output
  this->km.produceResult(oldGroups, sinkPtr);
}
SESAME::Sliding::Sliding(param_t &cmd_params) {
  this->parameters.pointNumber = cmd_params.pointNumber;
  this->parameters.dimension = cmd_params.dimension;
  this->parameters.numberOfClusters = cmd_params.clusterNumber;
  this->parameters.thresholdOutlierCount = 2;
  this->parameters.thresholdDistance = 7;
  this->parameters.thresholdCount = 10;
  this->parameters.timeInterval = 4;
  this->stampCount = 1;
  this->outliers = std::make_shared<OutlierBuffer>();
}
void SESAME::Sliding::Initilize() {}

SESAME::Sliding::~Sliding() {}
