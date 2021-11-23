//
// Created by tuidan on 2021/11/22.
//

#ifndef SESAME_INCLUDE_REFACTOR_MODULE_OUTLIERDETECT_HPP_
#define SESAME_INCLUDE_REFACTOR_MODULE_OUTLIERDETECT_HPP_
#include <memory>
#include <vector>
#include <Algorithm/DataStructure/Point.hpp>
#include <Refactor/Module/Window.hpp>
#include <Refactor/Structure/RefactorParameters.hpp>
namespace SESAME {
enum oDType {Density_OD, Time_OD};

class OutlierDetection;
typedef std::shared_ptr<OutlierDetection> OutlierDetectionPtr;

class OutlierDetection {
 public:
  OutlierDetection();
  void runOutlierDetection(SESAME::windowType w, SESAME::oDType o, SESAME::RefactorParametersPtr &para);
};
}

#endif //SESAME_INCLUDE_REFACTOR_MODULE_OUTLIERDETECT_HPP_
