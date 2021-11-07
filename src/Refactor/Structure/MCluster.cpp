//
// Created by tuidan on 2021/11/6.
//
/**
 * Data Structure: CFTree
 * Window Model: Landmark
 * Outlier Detection: Distance
 * Concept Drift: Count
 * Offline Refinement: DBSCAN
 * */
#include <Refactor/Structure/MCluster.hpp>

int SESAME::MCluster::getN() {
  return this->N;
}
std::vector<double> SESAME::MCluster::getLS() {
  return this->LS;
}
std::vector<double> SESAME::MCluster::getSS() {
  return this->SS;
}
std::vector<double> SESAME::MCluster::getCentroid() {
  return this->centroid;
}
double SESAME::MCluster::getRadius() {
  return this->radius;
}
double SESAME::MCluster::getWeight() {
  return this->weight;
}
void SESAME::MCluster::setN(int n) {
  this->N = n;
}
void SESAME::MCluster::setLSByIndex(int index, double value) {
  this->LS.at(index) = value + this->LS.at(index);
}
void SESAME::MCluster::setSSByIndex(int index, double value) {
  this->SS.at(index) = value;
}
void SESAME::MCluster::setRadius(double r) {
  this->radius = r;
}
void SESAME::MCluster::setWeight(double w) {
  this->weight = w;
}
void SESAME::MCluster::setCentroid(SESAME::PointPtr &p) {
  if(this->N == 0) {
    SESAME_ERROR("Micro Cluster containing none points!!!");
  } else {
    for(int i = 0; i < this->dimension; i++) {
      this->centroid.at(i) = (this->LS.at(i) + p->getFeatureItem(i)) / this->N;
    }
  }
}
void SESAME::MCluster::setRadius(SESAME::PointPtr &p) {
  if(this->N == 0) {
    SESAME_ERROR("Micro Cluster containing none points!!!");
  } else if(this->N == 1) {
    this->radius = 0;
  } else {
    for(int i = 0; i < this->dimension; i++) {
      this->radius = this->SS.at(i) + pow(p->getFeatureItem(i), 2) - 2 * this->LS.at(i) * p->getFeatureItem(i);
    }
    this->radius = sqrt(this->radius / (this->N * ( this->N - 1)));
  }
}
int SESAME::MCluster::getDimension() {
  return this->dimension;
}
void SESAME::MCluster::setDimension(int d) {
  this->dimension = d;
}
void SESAME::MCluster::setLS(SESAME::PointPtr &p) {
  for(int i = 0; i < this->dimension; i++) {
    this->LS.at(i) += p->getFeatureItem(i);
  }
}
void SESAME::MCluster::setSS(SESAME::PointPtr &p) {
  for(int i = 0; i < this->dimension; i++) {
    this->SS.at(i) += pow(p->getFeatureItem(i), 2);
  }
}
