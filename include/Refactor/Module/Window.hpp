//
// Created by tuidan on 2021/11/22.
//

#ifndef SESAME_INCLUDE_REFACTOR_MODULE_WINDOW_HPP_
#define SESAME_INCLUDE_REFACTOR_MODULE_WINDOW_HPP_
#include <memory>
#include <vector>
#include <Refactor/RefactorParameters.hpp>
#include <Algorithm/DataStructure/Point.hpp>
namespace SESAME {
enum windowType {Landmark, Sliding, Damped};

class WindowModel;
typedef std::shared_ptr<WindowModel> WindowModelPtr;

class WindowModel {
 public:
  WindowModel();
  bool runWindowModel(SESAME::windowType w, SESAME::RefactorParametersPtr &para,PointPtr p);
};
}

#endif //SESAME_INCLUDE_REFACTOR_MODULE_WINDOW_HPP_
