//
// Created by tuidan on 2021/11/22.
//

#include <Refactor/Controller.hpp>
#include <cfloat>

void SESAME::Controller::Initilize() {}
SESAME::Controller::~Controller() {}

SESAME::Controller::Controller(param_t &cmd_params) {
  this->parameters->pointNumber = cmd_params.pointNumber;
  this->parameters->dimension = cmd_params.dimension;
  this->parameters->numberOfClusters = cmd_params.clusterNumber;
  this->parameters->minDensityTransform = 2;
  this->parameters->minTimeTransform = 7;
  this->parameters->outliers = std::make_shared<OutlierBuffer>();
  this->window_model_type = cmd_params.winType;
  this->concept_drift_handling_type = cmd_params.cdType;
  this->outlier_detection_type = cmd_params.odType;
  this->offline_refinement_type = cmd_params.offType;
}
void SESAME::Controller::runOnlineClustering(SESAME::PointPtr input) {
  bool flag = window_model->runWindowModel(this->window_model_type, this->parameters, input->copy());
  if(flag) {
    if(window_model_type == SESAME::Damped){

    } else{
      outlier_detection->runOutlierDetection(outlier_detection_type, this->parameters);
      cd_handling->runConceptDrift(concept_drift_handling_type, this->parameters);
    }
  }
}
void SESAME::Controller::runOfflineClustering(SESAME::DataSinkPtr sinkPtr) {
  offline_refinement->runOfflineRefinement(this->offline_refinement_type, this->parameters, sinkPtr);
}
