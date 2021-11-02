//
// Created by tuidan on 2021/11/2.
//

#ifndef SESAME_INCLUDE_ALGORITHM_DATASTRUCTURE_DATASTRUCTURE_HPP_
#define SESAME_INCLUDE_ALGORITHM_DATASTRUCTURE_DATASTRUCTURE_HPP_
#include <Algorithm/DataStructure/Point.hpp>
#include <Sinks/DataSink.hpp>
#include <string>
#include <vector>
#include <memory>
using namespace std;
namespace SESAME {

enum StructureType { CoresetType, FeatureVectureType, MicroClusterType, DenStreamType, DBStreamType, EDMStreamType};

class DataStructureParameters {
 public:
  int pointNumber;
  int dimension;
};

class DataStructure;
typedef std::shared_ptr<DataStructure> DataStructurePtr;

class DataStructure {
 public:
  DataStructure() = default;
  virtual ~DataStructure() = default;
  virtual void Initilize() = 0;
  virtual void DataInsertion(SESAME::PointPtr input) = 0;
};
}

#endif //SESAME_INCLUDE_ALGORITHM_DATASTRUCTURE_DATASTRUCTURE_HPP_
