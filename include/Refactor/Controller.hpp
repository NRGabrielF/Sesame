//
// Created by tuidan on 2021/11/22.
//

#ifndef SESAME_INCLUDE_REFACTOR_CONTROLLER_HPP_
#define SESAME_INCLUDE_REFACTOR_CONTROLLER_HPP_
#include <Refactor/Module/Window.hpp>
#include <Refactor/Module/OutlierDetect.hpp>
#include <Refactor/Module/Offline.hpp>
#include <Refactor/Module/ConceptDrift.hpp>
#include <Refactor/Structure/MCluster.hpp>
#include <Algorithm/Algorithm.hpp>
#include <Utils/BenchmarkUtils.hpp>
#include <Refactor/RefactorParameters.hpp>

namespace SESAME {

class Controller;
typedef std::shared_ptr<Controller> ControllerPtr;
class Controller  : public Algorithm{
 public:
  RefactorParametersPtr parameters;

  windowType window_model_type;
  cDType concept_drift_handling_type;
  oDType outlier_detection_type;
  offlineType  offline_refinement_type;

  WindowModelPtr window_model;
  ConceptDriftPtr cd_handling;
  OutlierDetectionPtr outlier_detection;
  OfflineRefinementPtr offline_refinement;
  Controller(param_t &cmd_params);

  ~Controller();

  void Initilize() override;

  void runOnlineClustering(PointPtr input) override;

  void runOfflineClustering(DataSinkPtr sinkPtr) override;
};
}

#endif //SESAME_INCLUDE_REFACTOR_CONTROLLER_HPP_
