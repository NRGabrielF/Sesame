//
// Created by tuidan on 2021/11/22.
//

#ifndef SESAME_INCLUDE_REFACTOR_MODULE_OUTLIERDETCTION_HPP_
#define SESAME_INCLUDE_REFACTOR_MODULE_OUTLIERDETCTION_HPP_
#include <memory>
#include <vector>
#include <Algorithm/DataStructure/Point.hpp>
namespace SESAME {
enum oDType {Density_OD, Time_OD};

class OutlierDetection;
typedef std::shared_ptr<OutlierDetection> OutlierDetectionPtr;

class OutlierDetectionParameters {
 public:
  int WindowSize;
};

class OutlierDetection {
 public:
  OutlierDetectionParameters parameters;
  std::vector<SESAME::PointPtr> windowElement;
  OutlierDetection();
  std::vector<SESAME::PointPtr> getWindowElement();
  bool setWindow(SESAME::windowType w, PointPtr p);
};
}

#endif //SESAME_INCLUDE_REFACTOR_MODULE_OUTLIERDETCTION_HPP_
