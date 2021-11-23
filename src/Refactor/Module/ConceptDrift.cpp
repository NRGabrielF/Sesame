//
// Created by tuidan on 2021/11/22.
//

#include <Refactor/Module/ConceptDrift.hpp>
SESAME::MicroClusterPtr SESAME::ConceptDrift::fillDensityTransformation(SESAME::RefactorParametersPtr &para, double minDensity) {
  for(int i = 0; i < para->outlierClusters.size(); i++) {
    if(para->outlierClusters[i]->weight >= minDensity) {
      MicroClusterPtr temp = para->outlierClusters[i]->copy();
      SESAME_INFO("Outliers transform into clusters!!!");
      para->outlierClusters.erase(para->outlierClusters.begin() + i);
      return temp;
    }
  }
  return nullptr;
}
SESAME::MicroClusterPtr SESAME::ConceptDrift::fillTimeTransformation(SESAME::RefactorParametersPtr &para,
                                                                 double currentTime, double thresholdMininterval) {
  for(int i = 0; i < para->outlierClusters.size(); i++) {
    if(currentTime - para->outlierClusters[i]->lastUpdateTime >= thresholdMininterval) {
      MicroClusterPtr temp = para->outlierClusters[i]->copy();
      SESAME_INFO("Outliers transform into clusters!!!");
      para->outlierClusters.erase(para->outlierClusters.begin() + i);
      return temp;
    }
  }
  return nullptr;
}

void SESAME::ConceptDrift::runConceptDrift(SESAME::cDType cd, SESAME::RefactorParametersPtr &para) {
  if(cd == SESAME::Density_CD) {
    this->fillDensityTransformation(para, para->minDensityTransform);
  } else if(cd == SESAME::Time_CD) {
    this->fillTimeTransformation(para, para->currentTime, para->minTimeTransform);
  } else throw std::invalid_argument("Unsupported");
}
