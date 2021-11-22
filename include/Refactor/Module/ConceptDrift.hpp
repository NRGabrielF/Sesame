//
// Created by tuidan on 2021/11/22.
//

#ifndef SESAME_INCLUDE_REFACTOR_MODULE_CONCEPTDRIFT_HPP_
#define SESAME_INCLUDE_REFACTOR_MODULE_CONCEPTDRIFT_HPP_
#include <memory>
#include <vector>
#include <Algorithm/DataStructure/Point.hpp>
namespace SESAME {
enum cDType {Density_CD, Time_CD};

class ConceptDriftHandling;
typedef std::shared_ptr<ConceptDriftHandling> ConceptDriftHandlingPtr;

class WindowModelParameters {
 public:
  int WindowSize;
};

class ConceptDriftHandling {
 public:
  WindowModelParameters parameters;
  std::vector<SESAME::PointPtr> windowElement;
  ConceptDriftHandling();
  std::vector<SESAME::PointPtr> getWindowElement();
  bool setWindow(SESAME::windowType w, PointPtr p);
};
}

#endif //SESAME_INCLUDE_REFACTOR_MODULE_CONCEPTDRIFT_HPP_
