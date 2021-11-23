//
// Created by tuidan on 2021/11/9.
//

#ifndef SESAME_INCLUDE_REFACTOR_STRUCTURE_OUTLIERBUFFER_HPP_
#define SESAME_INCLUDE_REFACTOR_STRUCTURE_OUTLIERBUFFER_HPP_
#include <Algorithm/DataStructure/Point.hpp>
//#include <Refactor/Structure/MCluster.hpp>
#include <Algorithm/DataStructure/MicroCluster.hpp>
namespace SESAME {
class OutlierBuffer;
typedef std::shared_ptr<OutlierBuffer> OutlierBufferPtr;

class OutlierBuffer {
 private:
  std::vector<MicroClusterPtr> outlierClusters;
 public:
  OutlierBuffer();
  ~OutlierBuffer();
  std::vector<MicroClusterPtr> getOutlierClusters();
  MicroClusterPtr fillDensityTransformation(int thresholdCount); // concept drift
  MicroClusterPtr fillTimeTransformation(double currentTime, double thresholdMinInterval); // concept drift
  MicroClusterPtr discardOutliersThroughDensity(int thresholdCount);  // outlier detection
  MicroClusterPtr discardOutliersThroughTime(int thresholdCount); // outlier detection
  void insertOutlierCluster(PointPtr &p, int thresholdDistance);


};
}
#endif //SESAME_INCLUDE_REFACTOR_STRUCTURE_OUTLIERBUFFER_HPP_
