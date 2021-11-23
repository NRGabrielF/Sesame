//
// Created by tuidan on 2021/11/22.
//

#ifndef SESAME_INCLUDE_REFACTOR_MODULE_CONCEPTDRIFT_HPP_
#define SESAME_INCLUDE_REFACTOR_MODULE_CONCEPTDRIFT_HPP_
#include <memory>
#include <vector>
#include <Algorithm/DataStructure/Point.hpp>
#include <Refactor/Structure/RefactorParameters.hpp>

namespace SESAME {
enum cDType {Density_CD, Time_CD};

class ConceptDrift;
typedef std::shared_ptr<ConceptDrift> ConceptDriftPtr;

class ConceptDrift {
 public:
  ConceptDrift();
  SESAME::MClusterPtr fillDensityTransformation(SESAME::RefactorParametersPtr &para, double minDensity);
  SESAME::MClusterPtr fillTimeTransformation(SESAME::RefactorParametersPtr &para, double currentTime, double thresholdMininterval);
  void runConceptDrift(SESAME::cDType cd, SESAME::RefactorParametersPtr &para);
};
}

#endif //SESAME_INCLUDE_REFACTOR_MODULE_CONCEPTDRIFT_HPP_
