//
// Created by tuidan on 2021/10/11.
//

#ifndef ONLINEMLBENCHMARK_PURITY_HPP_
#define ONLINEMLBENCHMARK_PURITY_HPP_
#include <Algorithm/DataStructure/Point.hpp>
#include <vector>
namespace SESAME {

class Purity {
 private:
  static void pointToGroup(const std::vector<SESAME::PointPtr> &input,
                           std::vector<std::vector<PointPtr>> &group, int number);
  static int calculateBelongsFromTwo(std::vector<SESAME::PointPtr> &groupA,
                                     std::vector<SESAME::PointPtr> &groupB);
  static double getMaxBelongs(std::vector<SESAME::PointPtr> &singleSample,
                              std::vector<std::vector<PointPtr>> &GT);
 public:
   static double purityCost(const std::vector<PointPtr> &input,
                         const std::vector<PointPtr> &result,
                         int dimension);
};

}
#endif