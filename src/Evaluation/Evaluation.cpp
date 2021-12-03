// Copyright (C) 2021 by the IntelliStream team (https://github.com/intellistream)

#include <Evaluation/Evaluation.hpp>
#include <Evaluation/Euclidean.hpp>
#include <Evaluation/Purity.hpp>
#include <Evaluation/CMM.hpp>
#include <cmath>
#include <Utils/Logger.hpp>
#include <fstream>
#include <iostream>

void SESAME::Evaluation::runEvaluation(int seed,
                                       int clusterNumber,
                                       int coresetSize,
                                       int dimension,
                                       std::ofstream &outfile,
                                       const std::vector<PointPtr> &inputs,
                                       const std::vector<PointPtr> &center) {
  double purity =SESAME::Purity::purityCost(center, inputs, dimension);

  double cmm = SESAME::CMM::CMMCost(dimension,inputs,center);

  // store the evaluation results into file
  std::string temp = "seed: ";
  temp.append(std::to_string(seed));
  temp.append("   ClusterNumber: ");
  temp.append(std::to_string(clusterNumber));
  temp.append("   CoresetSize: ");
  temp.append(std::to_string(coresetSize));
  temp.append( "   cmm: ");
  temp.append(std::to_string(round(cmm * 10000) / 10000));
  temp.append("   purity: ");
  temp.append(std::to_string(round(purity * 10000) / 10000));
  outfile << temp;
  outfile << std::endl;

//  std::cout << "seed: " << seed << "   ClusterNumber: " << clusterNumber << "   CoresetSize: "<< coresetSize <<
//  "   cmm: " << round(cmm * 10000) / 10000 << "   purity: " << round(purity * 10000) / 10000;
}
