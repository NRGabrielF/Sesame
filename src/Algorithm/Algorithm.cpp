// Copyright (C) 2021 by the IntelliStream team (https://github.com/intellistream)

//
// Created by tuidan on 2021/7/22.
//

#include <Algorithm/Algorithm.hpp>
#include <Utils/UtilityFunctions.hpp>

void SESAME::Algorithm::store(std::string outputPath,
                              int dimension,
                              std::vector<SESAME::PointPtr> center,
                              std::vector<SESAME::PointPtr> input) {
  std::vector<PointPtr> result;
  UtilityFunctions::groupByCenters(input, center, result, dimension);
  int numberOfPoints = (int)result.size();
  FILE *out = fopen(outputPath.c_str(), "w");
  for (int i = 0; i < numberOfPoints; i++) {
    int l;
    for (l = 0; l < dimension; l++) {
      fprintf(out, "%f,", result[i]->getFeatureItem(l));
    }
    fprintf(out, "%d", result[i]->getClusteringCenter());
    fprintf(out, "\n");
  }
  fclose(out);
}
