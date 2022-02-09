// Copyright (C) 2021 by the IntelliStream team (https://github.com/intellistream)

//
// Created by shuhao zhang on 8/8/2021.
//
#include <filesystem>
#include <gtest/gtest.h>
#include <Utils/BenchmarkUtils.hpp>
#include <Utils/Logger.hpp>
#include <Sources/DataSourceFactory.hpp>
#include <Sinks/DataSinkFactory.hpp>
#include <Algorithm/AlgorithmFactory.hpp>

TEST(SystemTest, CluStreamTest) {
  //Setup Logs.
  setupLogging("benchmark.log", LOG_DEBUG);
  // [529, 999, 1270, 1624, 2001, 2435, 2648, 3000]
  // [3, 3, 4, 6, 6, 7, 9, 9]
  //Parse parameters.
  param_t cmd_params;
  cmd_params.pointNumber = 3000;
  cmd_params.dimension = 2;
  cmd_params.clusterNumber = 9;
  cmd_params.lastArrivingNum = 12;
  cmd_params.timeWindow = 200;
  cmd_params.timeInterval = 8;
  cmd_params.onlineClusterNumber =60;
  cmd_params.radiusFactor =0.5;
  cmd_params.initBuffer = 200;
  cmd_params.offlineTimeWindow = 0;
  cmd_params.GTClusterNumber = 9;
  //cmd_params.timeDecay = true;
  cmd_params.inputPath = std::filesystem::current_path().generic_string() + "/datasets/Diamond.txt";
  cmd_params.outputPath = "results.txt";
  cmd_params.algoType = SESAME::CluStreamType;

  std::vector<SESAME::PointPtr> input;
  std::vector<SESAME::PointPtr> results;

  //Create Spout.
  SESAME::DataSourcePtr sourcePtr = SESAME::DataSourceFactory::create();
  //Directly load data from file. TODO: configure it to load from external sensors, e.g., HTTP.
  BenchmarkUtils::loadData(cmd_params, sourcePtr);

  //Create Sink.
  SESAME::DataSinkPtr sinkPtr = SESAME::DataSinkFactory::create();

  //Create Algorithm.
  SESAME::AlgorithmPtr algoPtr = SESAME::AlgorithmFactory::create(cmd_params);

  //Run algorithm producing results.
  BenchmarkUtils::runBenchmark(cmd_params, sourcePtr, sinkPtr, algoPtr);
}