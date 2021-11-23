//
// Created by tuidan on 2021/11/22.
//

#ifndef SESAME_INCLUDE_REFACTOR_MODULE_OFFLINE_HPP_
#define SESAME_INCLUDE_REFACTOR_MODULE_OFFLINE_HPP_
#include <memory>
#include <vector>
#include <Algorithm/DataStructure/Point.hpp>
#include <Refactor/Structure/RefactorParameters.hpp>
#include <Algorithm/OfflineClustering/KMeans.hpp>
#include <Algorithm/OfflineClustering/DBSCAN.hpp>
#include <Sinks/DataSink.hpp>

namespace SESAME {
enum offlineType {KMeans, KMeansPP, DBSCAN, Connection};

class OfflineRefinement;
typedef std::shared_ptr<OfflineRefinement> OfflineRefinementPtr;

class OfflineRefinement {
 public:
  class KMeans k_means;
  class DBSCAN db_scan;
  //TODO Need to add connection based offline refinement
  OfflineRefinement();
  void getFinalClusterCenter(SESAME::RefactorParametersPtr &para);
  void runOfflineRefinement(SESAME::offlineType offline, SESAME::RefactorParametersPtr &para, SESAME::DataSinkPtr sinkPtr);
};
}
#endif //SESAME_INCLUDE_REFACTOR_MODULE_OFFLINE_HPP_
