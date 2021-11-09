//
// Created by tuidan on 2021/11/6.
//

#ifndef SESAME_INCLUDE_REFACTOR_STRUCTURE_MCLUSTER_HPP_
#define SESAME_INCLUDE_REFACTOR_STRUCTURE_MCLUSTER_HPP_

#include <Algorithm/DataStructure/Point.hpp>
#include <Utils/Logger.hpp>
#include <vector>
#include <cmath>

namespace SESAME{
class MCluster;
typedef std::shared_ptr<MCluster> MClusterPtr;

class MCluster {
 private:
  int Pnum;  // number of points in the micro clusters
  std::vector<double> LS;
  std::vector<double> SS;
  std::vector<double> centroid;
  double radius;
  double weight;
  int dimension;
 public:
  MCluster(int d);
  int getN();
  std::vector<double> getLS();
  std::vector<double> getSS();
  std::vector<double> getCentroid();
  double getRadius();
  double getWeight();
  int getDimension();
  double calCentroidDistance(PointPtr &p);
  SESAME::MClusterPtr copy();
  void setN(int n);
  void setLS(PointPtr &p);
  void setSS(PointPtr &p);
  void setCentroid(PointPtr &p);
  void setRadius(PointPtr &p);
  void updateAttribute(PointPtr &p);
  void setLSByIndex(int index, double value);
  void setSSByIndex(int index, double value);
  void setRadius(double r);
  void setWeight(double w);
  void setDimension(int d);

};
}
#endif //SESAME_INCLUDE_REFACTOR_STRUCTURE_MCLUSTER_HPP_
