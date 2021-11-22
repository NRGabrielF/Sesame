//
// Created by tuidan on 2021/11/9.
//

#ifndef SESAME_INCLUDE_REFACTOR_STRUCTURE_OUTLIERBUFFER_HPP_
#define SESAME_INCLUDE_REFACTOR_STRUCTURE_OUTLIERBUFFER_HPP_
#include <Algorithm/DataStructure/Point.hpp>
#include <Refactor/Structure/MCluster.hpp>
namespace SESAME {
class OutlierBuffer;
typedef std::shared_ptr<OutlierBuffer> OutlierBufferPtr;

class OutlierBuffer {
 private:
  std::vector<MClusterPtr> outlierClusters;
 public:
  OutlierBuffer();
  ~OutlierBuffer();
  std::vector<MClusterPtr> getOutlierClusters();
  MClusterPtr fillDensityTransformation(int thresholdCount); // concept drift
  MClusterPtr fillTimeTransformation(double currentTime, double thresholdMininterval);
  MClusterPtr discardOutliersThroughDensity(int thresholdCount);
  MClusterPtr discardOutliersThroughTime(int thresholdCount);
  void insertOutlierCluster(PointPtr &p, int thresholdDistance);


};
}
#endif //SESAME_INCLUDE_REFACTOR_STRUCTURE_OUTLIERBUFFER_HPP_
