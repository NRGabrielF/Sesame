// Copyright (C) 2021 by the IntelliStream team (https://github.com/intellistream)

#include <Evaluation/Evaluation.hpp>
#include <Evaluation/Purity.hpp>
#include <Evaluation/CMM.hpp>
#include <cmath>
#include <Utils/Logger.hpp>

void SESAME::Evaluation::runEvaluation(int dimension,
                                       int clusterNumber,
                                       const std::vector<PointPtr> &inputs,
                                       const std::vector<PointPtr> &center,
                                       const std::vector<PointPtr> &result) {
  double purity =SESAME::Purity::purityCost(inputs, result,center.size(),clusterNumber);

  double cmm = SESAME::CMM::CMMCost(dimension,result,center);

  std::cout << "   cmm: " << round(cmm * 10000) / 10000 << "   purity: " << round(purity * 10000) / 10000;
}
