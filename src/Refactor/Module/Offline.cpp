//
// Created by tuidan on 2021/11/22.
//
#include <Sinks/DataSink.hpp>
#include <Refactor/Module/Offline.hpp>
#include <Algorithm/DataStructure/DataStructureFactory.hpp>
#include <Refactor/RefactorParameters.hpp>

void SESAME::OfflineRefinement::getFinalClusterCenter(SESAME::RefactorParametersPtr &para) {
  SESAME_INFO("The mid cluster number is:" << para->microClusters .size());
  for(int i = 0; i < para->microClusters.size(); i++) {
    MicroClusterPtr mc = para->microClusters.at(i);
    PointPtr center = DataStructureFactory::createPoint(i,1,para->dimension, 0);
    center->setClusteringCenter(i);
    for(int j = 0; j < para->dimension; j++) {
      center->setFeatureItem(mc->getCentroid().at(j), j);
    }
    para->finalClusterCenters.push_back(center);
  }
}

void SESAME::OfflineRefinement::runOfflineRefinement(SESAME::offlineType offline,
                                                     SESAME::RefactorParametersPtr &para,
                                                     SESAME::DataSinkPtr sinkPtr) {
  this->getFinalClusterCenter(para);
  vector <vector<PointPtr>> groups;
  std::vector<std::vector<PointPtr>> oldGroups, newGroups;
  if(offline == SESAME::KM) {
    this->k_means.runKMeans(para->numberOfClusters,
                       para->microClusters.size(),
                       para->finalClusterCenters,
                       oldGroups,
                       newGroups,
                       false);
    // store the result input output
    this->k_means.produceResult(oldGroups, sinkPtr);

  } else if(offline == SESAME::KMPP) {
    this->k_means.runKMeans(para->numberOfClusters,
                             para->microClusters.size(),
                             para->finalClusterCenters,
                             oldGroups,
                             newGroups,
                             true);

    this->k_means.produceResult(oldGroups, sinkPtr);

  } else if(offline == SESAME::DB) {
    this->db_scan.run(para->finalClusterCenters);
    this->db_scan.produceResult(para->finalClusterCenters, sinkPtr);

  } else if(offline == SESAME::Connection) {

  } else throw std::invalid_argument("Unsupported");
}
