// Copyright (C) 2021 by the IntelliStream team (https://github.com/intellistream)

#include <Evaluation/Evaluation.hpp>
#include <Evaluation/Euclidean.hpp>
#include <Evaluation/Purity.hpp>
#include <Evaluation/CMM.hpp>
#include <cmath>
#include <Utils/Logger.hpp>

void SESAME::Evaluation::runEvaluation(int seed,
                                       int clusterNumber,
                                       int coresetSize,
                                       int dimension,
                                       const std::vector<PointPtr> &inputs,
                                       const std::vector<PointPtr> &center) {
  double purity =SESAME::Purity::purityCost(center, inputs, dimension);

  double cmm = SESAME::CMM::CMMCost(dimension,inputs,center);

  std::cout << "seed: " << seed << "   ClusterNumber: " << clusterNumber << "   CoresetSize: "<< coresetSize <<"   cmm: " << round(cmm * 10000) / 10000 << "   purity: " << round(purity * 10000) / 10000 << std::endl;
}
