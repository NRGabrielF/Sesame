//
// Created by tuidan on 2021/11/22.
//

#include <Refactor/Module/OutlierDetect.hpp>
#include <Algorithm/DataStructure/Point.hpp>
#include <Refactor/Module/Window.hpp>
#include <cfloat>

void SESAME::OutlierDetection::runOutlierDetection(SESAME::windowType w,SESAME::oDType o, SESAME::RefactorParametersPtr &para) {
  int closestClusterID;
  double minDistance = DBL_MAX;
  for(auto el : para->windowElement) {
    for (int i = 0; i < para->microClusters.size(); i++) {
      if(w == SESAME::Damped){
        para->microClusters[i]->updateAttribute(el->getTimeStamp(),
                                                para->alpha,
                                                para->lambda);
      }
      double dist = para->microClusters[i]->calCentroidDistance(el);
      if (dist < minDistance) {
        closestClusterID = i;
        minDistance = dist;
      }
    }
    // new outlier cluster
    if(minDistance <= para->maxInsertDistance) {
      para->microClusters[closestClusterID]->updateAttribute(el);  // else normally insert into the micro-clusters
    } else{
      // distance is too large then throw the point into outliers
      para->outliers->insertOutlierCluster(el, para->maxInsertDistance);
    }

  }
  if(o == SESAME::Density_OD) {

  } else if(o == SESAME::Time_OD) {


  } else throw std::invalid_argument("Unsupported");
}
