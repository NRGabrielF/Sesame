//
// Created by tuidan on 2021/11/22.
//

#include <Refactor/Module/OutlierDetect.hpp>
#include <Algorithm/DataStructure/Point.hpp>
#include <Refactor/Module/Window.hpp>
#include <cfloat>

void SESAME::OutlierDetection::insertOutlierCluster(SESAME::PointPtr &p, SESAME::RefactorParametersPtr &para) {
  double minDistance = DBL_MAX;
  int closestClusterID = 0;
  for (int i = 0; i < para->outlierClusters.size(); i++) {
    double dist = para->outlierClusters[i]->calCentroidDistance(p);
    if (dist < minDistance) {
      closestClusterID = i;
      minDistance = dist;
    }
  }
  if(minDistance <= para->maxInsertDistance) {
    para->outlierClusters.at(closestClusterID)->insert(p, p->getTimeStamp());
//    para->outlierClusters.at(closestClusterID)->setLastModifyTime(p->getTimeStamp());
  } else {
    MicroClusterPtr m = std::make_shared<MicroCluster>(p->getDimension(), 0);
    m->insert(p, p->getTimeStamp());
  //  para->outlierClusters.push_back(m);
  }

}
void SESAME::OutlierDetection::runOutlierDetection(SESAME::windowType w,SESAME::oDType o, SESAME::RefactorParametersPtr &para) {
  int closestClusterID;
  double minDistance = DBL_MAX;
  for(auto el : para->windowElement) {
    for (int i = 0; i < para->microClusters.size(); i++) {
      if(w == SESAME::Damped){
        para->microClusters[i]->insert(el,para->alpha,para->lambda);
      }
      double dist = para->microClusters[i]->calCentroidDistance(el);
      if (dist < minDistance) {
        closestClusterID = i;
        minDistance = dist;
      }
    }
    // new outlier cluster
    if(minDistance <= para->maxInsertDistance) {
      para->microClusters[closestClusterID]->insert(el, el->getTimeStamp());  // else normally insert into the micro-clusters
    } else{
      // distance is too large then throw the point into outliers
      this->insertOutlierCluster(el, para);
    }
  }
  if(o == SESAME::Density_OD) {

  } else if(o == SESAME::Time_OD) {


  } else throw std::invalid_argument("Unsupported");
}
