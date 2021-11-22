//
// Created by tuidan on 2021/11/22.
//

#ifndef SESAME_INCLUDE_REFACTOR_MODULE_WINDOW_HPP_
#define SESAME_INCLUDE_REFACTOR_MODULE_WINDOW_HPP_
#include <memory>
#include <vector>
#include <Algorithm/DataStructure/Point.hpp>
namespace SESAME {
enum windowType {Landmark, Sliding, Damped};

class WindowModel;
typedef std::shared_ptr<WindowModel> WindowModelPtr;

class WindowModelParameters {
 public:
  int WindowSize;
};

class WindowModel {
 public:
  WindowModelParameters parameters;
  std::vector<SESAME::PointPtr> windowElement;
  WindowModel();
  std::vector<SESAME::PointPtr> getWindowElement();
  bool setWindow(SESAME::windowType w, PointPtr p);
};
}

#endif //SESAME_INCLUDE_REFACTOR_MODULE_WINDOW_HPP_
