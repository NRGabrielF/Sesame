//
// Created by tuidan on 2021/11/22.
//

#ifndef SESAME_INCLUDE_REFACTOR_CONTROLLER_HPP_
#define SESAME_INCLUDE_REFACTOR_CONTROLLER_HPP_
#include <Refactor/Module/Window.hpp>
#include <Refactor/Module/OutlierDetction.hpp>
#include <Refactor/Module/Offline.hpp>
#include <Refactor/Module/ConceptDrift.hpp>
#include <Refactor/Structure/MCluster.hpp>
namespace SESAME {

class Controller;
typedef std::shared_ptr<Controller> ControllerPtr;

class Controller {
 public:
  std::vector<SESAME::MClusterPtr> MicroClusters;
  WindowModel window_model;
  ConceptDriftHandling cd_handling;
  OutlierDetection outlier_detection;
  OfflineRefinement offline_refinement;
  Controller();
  void RegroupControl(SESAME::PointPtr p, windowType w, oDType o, cDType c, offlineType offline);
};
}

#endif //SESAME_INCLUDE_REFACTOR_CONTROLLER_HPP_
