//
// Created by tuidan on 2021/11/22.
//

#include <Refactor/Module/Window.hpp>

SESAME::WindowModel::WindowModel() {}

bool SESAME::WindowModel::setWindow(SESAME::windowType w, PointPtr p) {
  if(w == SESAME::Landmark) {
    if(this->windowElement.size() < this->parameters.WindowSize) {
      this->windowElement.push_back(p);
      return false;
    } else return true;
  } else if(w == SESAME::Sliding) {
    if(this->windowElement.size() < this->parameters.WindowSize) {
      this->windowElement.push_back(p);
      return false;
    } else {
      this->windowElement.erase( this->windowElement.begin());
      this->windowElement.push_back(p);
    }
  } else if(w == SESAME::Damped) {
    this->windowElement.clear();
    this->windowElement.push_back(p);
    //  TODO: need to store the time?
  } throw std::invalid_argument("Unsupported");
}
std::vector<SESAME::PointPtr> SESAME::WindowModel::getWindowElement() {
  return this->windowElement;
}
