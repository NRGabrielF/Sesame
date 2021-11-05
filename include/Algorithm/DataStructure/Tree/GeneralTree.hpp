//
// Created by tuidan on 2021/11/2.
//

#ifndef SESAME_INCLUDE_ALGORITHM_DATASTRUCTURE_TREE_GENERALTREE_HPP_
#define SESAME_INCLUDE_ALGORITHM_DATASTRUCTURE_TREE_GENERALTREE_HPP_

#include <Algorithm/DataStructure/Point.hpp>
#include <memory>
#include <vector>

namespace SESAME {

class GeneralTree;
typedef std::shared_ptr<GeneralTree> GeneralTreePtr;


/**
 * The general template treeNode of the tree model data structure
 * @tparam T1: clusterPoints' data structure
 * */
template <class T1>
class GeneralTreeNode {
 public:
  //array with pointers on points
  T1 clusterPoints;

  bool isLeaf;

  //pointer on the centre of the treenode
  std::vector<T1> clusteringCentre;

  std::vector<GeneralTreePtr> children;

  //pointer on the parent node
  GeneralTreePtr parent;
  void setIsLeaf(bool leaf);
  bool getIsLeaf();
  void calculateDistance(PointPtr &p);
  void searchNodeToInsert(PointPtr &p);
  void splitNode();
  void adjustClusterCenter();
  void mergeTwoNode();
  void pointSwitchNode();
  void
};
}
#endif //SESAME_INCLUDE_ALGORITHM_DATASTRUCTURE_TREE_GENERALTREE_HPP_
