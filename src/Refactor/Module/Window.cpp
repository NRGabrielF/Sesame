//
// Created by tuidan on 2021/11/22.
//

#include <Refactor/Module/Window.hpp>
#include <cfloat>

SESAME::WindowModel::WindowModel() {}

bool SESAME::WindowModel::runWindowModel(SESAME::windowType w, SESAME::RefactorParametersPtr &para,PointPtr p) {
  if(w == SESAME::Landmark) {
    if(para->windowElement.size() < para->windowSize) {
      para->windowElement.push_back(p);
      return false;
    } else return true;
  } else if(w == SESAME::Sliding) {
    if(para->windowElement.size() < para->windowSize) {
      para->windowElement.push_back(p);
      return false;
    } else {
      para->windowElement.erase(para->windowElement.begin());
      para->windowElement.push_back(p);
    }
  } else if(w == SESAME::Damped) {
    para->windowElement.clear();
    para->windowElement.push_back(p);
    return true;
    //  TODO: need to store the time?
  } throw std::invalid_argument("Unsupported");
}
