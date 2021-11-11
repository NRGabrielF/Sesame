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
#include <Algorithm/DataStructure/Point.hpp>
#include <Utils/Logger.hpp>

SESAME::MCluster::MCluster(int d) {
  this->Pnum = 0;
  this->radius = 0;
  this->dimension = d;
  this->weight = 1;
  std::vector<double> zeros;
  for(int i = 0; i < d; i++) {
    zeros.push_back(0);
  }
  this->LS = zeros;
  this->SS = zeros;
  this->centroid = zeros;
}

int SESAME::MCluster::getN() {
  return this->Pnum;
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
  this->Pnum = n;
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
  for(int i = 0; i < this->dimension; i++) {
    this->centroid.at(i) = (this->LS.at(i) + p->getFeatureItem(i)) / (this->Pnum + 1);
  }
}
void SESAME::MCluster::setRadius(SESAME::PointPtr &p) {
  if(this->Pnum == 0) {
    this->radius = 0;
  } else {
    for(int i = 0; i < this->dimension; i++) {
      this->radius = this->SS.at(i) + pow(p->getFeatureItem(i), 2) - 2 * this->LS.at(i) * p->getFeatureItem(i);
    }
    this->radius = sqrt(this->radius / (this->Pnum * ( this->Pnum + 1)));
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
double SESAME::MCluster::calCentroidDistance(PointPtr &p){

  double temp=0;
  for(int i=0; i<dimension; i++){
    double diff=centroid[i]-p->getFeatureItem(i);
    temp+=(diff*diff);
  }
  return sqrt(temp);
}

SESAME::MClusterPtr SESAME::MCluster::copy() {
  return std::make_shared<MCluster>(*this);
}
void SESAME::MCluster::updateAttribute(SESAME::PointPtr &p) {
  this->setRadius(p);
  this->setCentroid(p);
  this->setLS(p);
  this->setSS(p);
  this->Pnum = this->Pnum + 1;
}
double SESAME::MCluster::getLastModifyTime() {
  return this->lastModifyTime;
}
void SESAME::MCluster::setLastModifyTime(double t) {
  this->lastModifyTime =t;
}
void SESAME::MCluster::updateAttribute(double time, double alpha, double lambda) {
  for(int i = 0; i < this->dimension; i++) {
    this->LS[i] = this->LS[i] * pow(alpha, lambda * (time - this->lastModifyTime));
    this->SS[i] = this->SS[i] * pow(alpha, lambda * (time - this->lastModifyTime));
    if(this->Pnum == 0) {
      SESAME_ERROR("ERROR! Point number equals 0!");
    } else {
      this->centroid[i] = this->LS[i] * pow(alpha, lambda * (time - this->lastModifyTime)) / this->Pnum;
    }
  }
}

