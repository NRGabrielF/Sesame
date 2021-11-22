//
// Created by tuidan on 2021/11/22.
//

#ifndef SESAME_INCLUDE_REFACTOR_MODULE_OFFLINE_HPP_
#define SESAME_INCLUDE_REFACTOR_MODULE_OFFLINE_HPP_
#include <memory>
#include <vector>
#include <Algorithm/DataStructure/Point.hpp>
namespace SESAME {
enum offlineType {KMeans, KMeansPP, DBSCAN, Connection};

class OfflineRefinement;
typedef std::shared_ptr<OfflineRefinement> OfflineRefinementPtr;

class OfflineRefinementParameters {
 public:
  int WindowSize;
};

class OfflineRefinement {
 public:
  OfflineRefinementParameters parameters;
  std::vector<SESAME::PointPtr> windowElement;
  OfflineRefinement();
  std::vector<SESAME::PointPtr> getWindowElement();
  bool setWindow(SESAME::windowType w, PointPtr p);
};
}

#endif //SESAME_INCLUDE_REFACTOR_MODULE_OFFLINE_HPP_
