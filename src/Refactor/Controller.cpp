//
// Created by tuidan on 2021/11/22.
//

#include <Refactor/Controller.hpp>
#include <cfloat>
SESAME::Controller::Controller() {

}
void SESAME::Controller::RegroupControl(SESAME::PointPtr p,
                                        SESAME::windowType w,
                                        SESAME::oDType o,
                                        SESAME::cDType c,
                                        SESAME::offlineType offline) {
  bool flag = this->window_model.setWindow(w, p);
  if(flag) {
    if(w == SESAME::Damped) {

    } else {
      int closestClusterID;
      double minDistance = DBL_MAX;
      for (int i = 0; i < this->MicroClusters.size(); i++) {
        double dist = MicroClusters[i]->calCentroidDistance(p);
        if (dist < minDistance) {
          closestClusterID = i;
          minDistance = dist;
        }
      }
    }
  }

}
