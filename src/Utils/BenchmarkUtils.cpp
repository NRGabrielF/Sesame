// Copyright (C) 2021 by the IntelliStream team (https://github.com/intellistream)

#include <Utils/BenchmarkUtils.hpp>
#include <Utils/Logger.hpp>
#include <Sources/DataSource.hpp>
#include <Sinks/DataSink.hpp>
#include <Engine/SimpleEngine.hpp>
#include <Evaluation/Evaluation.hpp>
#include <Evaluation/Purity.hpp>
#include <Algorithm/AlgorithmFactory.hpp>
#include <Utils/UtilityFunctions.hpp>
#include <Algorithm/DataStructure/DataStructureFactory.hpp>
#include <filesystem>
#include <numeric>
#include <MacTypes.h>

using namespace std;

/**
 * @Description: get the super parameters from the command line and store into the param_t structure
 * @Param: argc: the first parameter of main function
 * @Param: argv: the second parameter of main function
 * @Param: cmd_params: the dataset attribute received from the command line such as p,c,d,s...
 * @Return: void
 */
void BenchmarkUtils::parseArgs(int argc, char **argv, param_t &cmd_params) {

  int c;
  while (1) {
    static struct option long_options[] =
        {
            {"help", no_argument, 0, 'h'},
            {"point_number", required_argument, 0, 'p'},
            {"cluster_number", required_argument, 0, 'c'},
            {"dimension", required_argument, 0, 'd'},
            {"coreset_size", required_argument, 0, 's'},
            {"seed", required_argument, 0, 'S'},
            {"lastArrivingNum", required_argument, 0, 'a'},
            {"timeWindow", required_argument, 0, 'T'},
            {"timeInterval", required_argument, 0, 't'},
            {"onlineClusterNumber", required_argument, 0, 'C'},
            {"radiusFactor", required_argument, 0, 'r'},
            {"initBuffer", required_argument, 0, 'b'},
            {"offlineTimeWindow", required_argument, 0, 'O'},
//          {"input_path", required_argument, 0, 'i'},
//          {"output_path", required_argument, 0, 'o'},
        };
    /* getopt_long stores the option index here. */
    int option_index = 0;

    c = getopt_long(argc, argv, "A:p:c:d:s:S:a:T:t:C:r:b:O:h:D:m:M:N:l:L:w:W:n:e:B:u:q:R:p:x:X:g:k:e",
                    long_options, &option_index);

    /* Detect the end of the options. */
    if (c == -1)
      break;
    switch (c) {//TODO: change to string type in future. char is limited..
      case 0:
        /* If this option set a flag, do nothing else now. */
        if (long_options[option_index].flag != 0)
          break;
        SESAME_INFO("option " << long_options[option_index].name);
        if (optarg) SESAME_INFO(" with arg " << optarg);
        break;

      case 'h':
      case '?':
        /* getopt_long already printed an error message. */
        print_help(argv[0]);
        exit(EXIT_SUCCESS);
        break;
      case 'p':cmd_params.pointNumber = atoi(optarg);
        SESAME_INFO("configure cmd_params.pointNumber: " << cmd_params.pointNumber);
        break;
      case 'c':cmd_params.clusterNumber = atoi(optarg);
        SESAME_INFO("configure cmd_params.clusterNumber: " << cmd_params.clusterNumber);
        break;
      case 'd':cmd_params.dimension = atoi(optarg);
        SESAME_INFO("configure cmd_params.dimension: " << cmd_params.dimension);
        break;
      case 's':cmd_params.coresetSize = atoi(optarg);
        SESAME_INFO("configure cmd_params.coresetSize: " << cmd_params.coresetSize);
        break;
      case 'S':cmd_params.seed = atoi(optarg);
        SESAME_INFO("configure cmd_params.seed: " << cmd_params.seed);
        break;
      case 'A':cmd_params.a = atof(optarg);
        SESAME_INFO("configure cmd_params.a: " << cmd_params.a);
        break;
      case 'a':
        if(atoi(optarg) == 0) cmd_params.algoType = SESAME::StreamKMeansType;
        else if(atoi(optarg) == 1) cmd_params.algoType = SESAME::BirchType;
        else if(atoi(optarg) == 2) {
          cmd_params.algoType = SESAME::EDMStreamType;
          cmd_params.a = 0.998;
          cmd_params.lambda = 1;
          cmd_params.beta = 0.0021;
          cmd_params.opt = 2;
        }
        else if(atoi(optarg) == 3) cmd_params.algoType = SESAME::DBStreamType;
        else if(atoi(optarg) == 4) cmd_params.algoType = SESAME::CluStreamType;
        else if(atoi(optarg) == 5) cmd_params.algoType = SESAME::DenStreamType;
        else if(atoi(optarg) == 6) cmd_params.algoType = SESAME::DStreamType;
        else SESAME_ERROR("non selected algorithm! ");
        SESAME_INFO("configure cmd_params.algoType: ");
        break;
      case 'm': cmd_params.maxLeafNodes = atoi(optarg);
      SESAME_INFO("configure cmd_params.maxLeafNodes: " << cmd_params.maxLeafNodes);
        break;
      case 'M': cmd_params.maxInternalNodes = atoi(optarg);
      SESAME_INFO("configure cmd_params.maxInternalNodes: " << cmd_params.maxInternalNodes);
        break;
      case 'D': cmd_params.thresholdDistance = atof(optarg);
        SESAME_INFO("configure cmd_params.thresholdDistance: " << cmd_params.thresholdDistance);
        break;
      case 'r': cmd_params.radius = atof(optarg);
        SESAME_INFO("configure cmd_params.radius: " << cmd_params.radius);
        break;
      case 'e': cmd_params.delta = atoi(optarg);
        SESAME_INFO("configure cmd_params.delta: " << cmd_params.delta);
        break;
      case 'b': cmd_params.beta = atof(optarg);
        SESAME_INFO("configure cmd_params.beta: " << cmd_params.beta);
        break;
      case 'C': cmd_params.cacheNum = atoi(optarg);
        SESAME_INFO("configure cmd_params.cacheNum: " << cmd_params.cacheNum);
        break;
      case 'T': cmd_params.cacheNum = atoi(optarg);
        SESAME_INFO("configure cmd_params.thresholdDistance: " << cmd_params.thresholdDistance);
        break;
      case 'B': cmd_params.initBuffer = atoi(optarg);
        SESAME_INFO("configure cmd_params.initBuffer: " << cmd_params.initBuffer);
        break;
      case 'N': cmd_params.onlineClusterNumber = atoi(optarg);
        SESAME_INFO("configure cmd_params.onlineClusterNumber: " << cmd_params.onlineClusterNumber);
        break;
      case 'F': cmd_params.radiusFactor = atoi(optarg);
        SESAME_INFO("configure cmd_params.radiusFactor: " << cmd_params.radiusFactor);
        break;
      case 'l': cmd_params.lastArrivingNum = atoi(optarg);
        SESAME_INFO("configure cmd_params.lastArrivingNum: " << cmd_params.lastArrivingNum);
        break;
      case 'W': cmd_params.timeWindow = atoi(optarg);
        SESAME_INFO("configure cmd_params.timeWindow: " << cmd_params.timeWindow);
        break;
      case 't': cmd_params.timeInterval = atoi(optarg);
        SESAME_INFO("configure cmd_params.timeInterval: " << cmd_params.timeInterval);
        break;
      case 'w': cmd_params.offlineTimeWindow = atoi(optarg);
        SESAME_INFO("configure cmd_params.offlineTimeWindow: " << cmd_params.offlineTimeWindow);
        break;
      case 'n': cmd_params.minPoints = atoi(optarg);
        SESAME_INFO("configure cmd_params.minPoints: " << cmd_params.minPoints);
        break;
      case 'E': cmd_params.epsilon = atoi(optarg);
        SESAME_INFO("configure cmd_params.epsilon: " << cmd_params.epsilon);
        break;
      case 'H': cmd_params.base = atoi(optarg);
        SESAME_INFO("configure cmd_params.base: " << cmd_params.base);
        break;
      case 'L': cmd_params.lambda = atoi(optarg);
        SESAME_INFO("configure cmd_params.lambda: " << cmd_params.lambda);
        break;
      case 'u': cmd_params.mu = atoi(optarg);
        SESAME_INFO("configure cmd_params.mu: " << cmd_params.mu);
        break;
      case 'q': cmd_params.beta = atoi(optarg);
        SESAME_INFO("configure cmd_params.beta: " << cmd_params.beta);
        break;
      case 'R': cmd_params.radius = atoi(optarg);
        SESAME_INFO("configure cmd_params.radius: " << cmd_params.radius);
        break;
      case 'U': cmd_params.cleanUpInterval = atoi(optarg);
        SESAME_INFO("configure cmd_params.cleanUpInterval: " << cmd_params.cleanUpInterval);
        break;
      case 'g': cmd_params.weightMin = atoi(optarg);
        SESAME_INFO("configure cmd_params.weightMin: " << cmd_params.weightMin);
        break;
      case 'P': cmd_params.alpha = atoi(optarg);
        SESAME_INFO("configure cmd_params.alpha: " << cmd_params.alpha);
        break;
      case 'x': cmd_params.cm = atoi(optarg);
        SESAME_INFO("configure cmd_params.cm: " << cmd_params.cm);
        break;
      case 'X': cmd_params.cl = atoi(optarg);
        SESAME_INFO("configure cmd_params.cl: " << cmd_params.cl);
        break;
      case 'G': cmd_params.gridWidth = atoi(optarg);
        SESAME_INFO("configure cmd_params.gridWidth: " << cmd_params.gridWidth);
        break;
      case 'O': cmd_params.datasetOption = atoi(optarg);
        if(cmd_params.datasetOption == 0) cmd_params.inputPath = std::filesystem::current_path().generic_string() + "/datasets/CoverType.txt";
        else if(cmd_params.datasetOption == 1) cmd_params.inputPath = std::filesystem::current_path().generic_string() + "/datasets/KDD99.txt";
        else if(cmd_params.datasetOption == 2) cmd_params.inputPath = std::filesystem::current_path().generic_string() + "/datasets/PowerSupply.txt";
        else if(cmd_params.datasetOption == 3) cmd_params.inputPath = std::filesystem::current_path().generic_string() + "/datasets/Diamond.txt";
        else if(cmd_params.datasetOption == 4) cmd_params.inputPath = std::filesystem::current_path().generic_string() + "/datasets/Zelnik.txt";
        SESAME_INFO("configure cmd_params.datasetOption: " << cmd_params.datasetOption);
        break;

      case 'i':cmd_params.inputPath = optarg;
        SESAME_INFO("configure input path: " << cmd_params.inputPath);
        break;
      case 'o':cmd_params.outputPath = optarg;
        SESAME_INFO("configure output path: " << cmd_params.outputPath);
        break;
      default:break;
    }
  }

  /* Print any remaining command line arguments (not options). */
  if (optind < argc) {
    SESAME_ERROR("non-option arguments: ");
    while (optind < argc) SESAME_ERROR(" " << argv[optind++]);
  }
}

/**
 * @Description: Set the default algorithm SKM++ and the default parameters to run the algorithm
 * void -p 1000 -c 10 -d 54 -s 100 -S 10
 * @Param: cmd_params: param_t &
 * @Return:
 */
void BenchmarkUtils::defaultParam(param_t &cmd_params) {
  cmd_params.pointNumber = 100; // number of the data points in the dataset, use the whole dataset to run benchmark
  cmd_params.clusterNumber = 10;
  cmd_params.dimension = 768;

  // SKM
  cmd_params.seed = 30;
  cmd_params.coresetSize = 2000;

  // BIRCH
  cmd_params.maxLeafNodes = 50;
  cmd_params.maxInternalNodes = 20;
  cmd_params.thresholdDistance = 0.1;

  //EDMStream
  cmd_params.a = 0.998;
  cmd_params.cacheNum = 1000;
  cmd_params.radius = 250;
  cmd_params.lambda = 1;
  cmd_params.delta = 1500;
  cmd_params.beta = 0.0021;
  cmd_params.opt = 2;

  //DenStream
  cmd_params.minPoints = 10; //
  cmd_params.epsilon = 50;
  cmd_params.base = 2;
  cmd_params.lambda = 1.8; // 1.8
  cmd_params.mu = 7;
  cmd_params.beta = 5; // 5
  cmd_params.initBuffer = 100;

//  // DB-Stream
//  cmd_params.radius = 250;
//  cmd_params.lambda = ;
//  cmd_params.cleanUpInterval;
//  cmd_params.weightMin;
//  cmd_params.alpha;
//  cmd_params.base;

  //Clustream
  cmd_params.initBuffer = 500;
  cmd_params.lastArrivingNum = 60;
  cmd_params.timeWindow = 6;
  cmd_params.timeInterval = 4;
  cmd_params.onlineClusterNumber = 15;
  cmd_params.radiusFactor = 70;
  cmd_params.offlineTimeWindow = 2;


  cmd_params.datasetOption = 0;
  cmd_params.inputPath = std::filesystem::current_path().generic_string() + "/datasets/Sentiment140.txt";
  cmd_params.positivePath = std::filesystem::current_path().generic_string() + "/datasets/Positive.txt";
  cmd_params.negativePath = std::filesystem::current_path().generic_string() + "/datasets/Negative.txt";

  SESAME_INFO("Default Input Data Directory: " + cmd_params.inputPath);
  cmd_params.outputPath = "results.txt";
  cmd_params.algoType = SESAME::BirchType;
}

/* command line handling functions */
/**
 * TODO: Make it more useful @WangXin.
 * @param string
 */
void BenchmarkUtils::print_help(char *string) {
  SESAME_ERROR("Usage: " << string << " [options]");
  SESAME_ERROR(" Available options: ");
}

/**
 * @Description: load data from the given dataset and convert the data format into the given point data structure
 * @Param: cmd_params: the dataset attribute received from the command line such as p,c,d,s...
 * @Param: input: the vector to store the point list from the dataset
 * @Return: void
 */
void BenchmarkUtils::loadData(param_t &cmd_params, SESAME::DataSourcePtr dataSourcePtr) {
  // Pass input file as a string to DataSource.
  std::vector<std::string> data;
  ifstream infile;
  infile.open(cmd_params.inputPath);
  SESAME_INFO("Read from the file...");

  // insert the data once per line into the string vector, every string element represents a data line
  for (int i = 0; i < cmd_params.pointNumber; i++) {
    data.emplace_back();
    getline(infile, data[i]);
  }
  SESAME_INFO("Complete reading from the file...");
  infile.close();

  // convert the string format into point vector, every string represents a point
  dataSourcePtr->load(cmd_params.pointNumber, cmd_params.dimension, data);
  SESAME_INFO("Finished loading input data");
}

void BenchmarkUtils::load(int point_number, int dimension, vector<string> &input, vector<SESAME::PointPtr> &data) {
  SESAME::PointPtr previous;
  for (int i = 0; i < point_number; i++) {
    SESAME::PointPtr point = SESAME::DataStructureFactory::
        createPoint(i, DEFAULT_WEIGHT, dimension, DEFAULT_COST);
    char *charData = new char[INT32_MAX];
    strcpy(charData, input[i].c_str());
    const char *sep = " ";
    char *feature = strtok(charData, sep);//TODO: why this?? Read token from charData
    feature = strtok(nullptr, sep); // Skip the first token (index number)
    int index = 0;
    while (feature != nullptr) {
      if (index == dimension) {
        point->setClusteringCenter(atoi(feature));
      } else {
        point->setFeatureItem(strtod(feature, nullptr), index);
        index++;
      }
      feature = strtok(nullptr, sep);
    }
    data.push_back(point);
  }
}
void BenchmarkUtils::runBenchmark(param_t &cmd_params,
                                  SESAME::DataSourcePtr sourcePtr,
                                  SESAME::DataSinkPtr sinkPtr,
                                  SESAME::AlgorithmPtr algoPtr) {

  SESAME::SimpleEngine engine(sourcePtr, sinkPtr, algoPtr);//TODO: create multithread engine in future.

  engine.run();

  while (!sinkPtr->isFinished());//wait for sink to stop.

  //Store results.
  algoPtr->store(cmd_params.outputPath, cmd_params.dimension, sinkPtr->getResults(),sourcePtr->getInputs());
  SESAME_INFO("Finished store results: " << sinkPtr->getResults().size());

  switch (cmd_params.algoType) {
    case SESAME::StreamKMeansType:
      std::cout << "Seed: " << cmd_params.seed
      << "   ClusterNumber: " << cmd_params.clusterNumber
      << "   CoresetSize: " << cmd_params.coresetSize;
      break;
    case SESAME::BirchType:
      std::cout << "maxLeafNode: " << cmd_params.maxLeafNodes
      << "   maxInnerNodes: " << cmd_params.maxInternalNodes
      << "   thresholdDistance: " << cmd_params.thresholdDistance;
      break;
    case SESAME::EDMStreamType:
      std::cout  << "CacheNum: " << cmd_params.cacheNum
      << "   Radius: " << cmd_params.radius
      << "   MinDelta: " << cmd_params.delta;
    default:break;
  }
  std::vector<SESAME::PointPtr> outputs;
  std::vector<SESAME::PointPtr> centers;
  // test
//  std::vector<std::string> cen;
//  ifstream cent;
//  cent.open(std::filesystem::current_path().generic_string() + "/datasets/1.txt");
//  for (int i = 0; i < 10; i++) {
//    cen.emplace_back();
//    getline(cent, cen[i]);
//  }
//  cent.close();
//  load(10, cmd_params.dimension, cen, centers);
  centers = sinkPtr->getResults();

//  std::vector<SESAME::PointPtr> centers = sinkPtr->getResults();
  std::vector<SESAME::PointPtr> inputs = sourcePtr->getInputs();


  SESAME::UtilityFunctions::groupByCenters(inputs, centers, outputs, cmd_params.dimension);

  // load positive reference
  std::vector<std::string> reference_p;
  ifstream p_reference;
  p_reference.open(cmd_params.positivePath);
  for (int i = 0; i < 21; i++) {
    reference_p.emplace_back();
    getline(p_reference, reference_p[i]);
  }
  p_reference.close();

  // load negative reference
  std::vector<std::string> reference_n;
  ifstream n_reference;
  n_reference.open(cmd_params.negativePath);
  for (int i = 0; i < 21; i++) {
    reference_n.emplace_back();
    getline(n_reference, reference_n[i]);
  }
  n_reference.close();

  std::vector<SESAME::PointPtr> positive;
  std::vector<SESAME::PointPtr> negative;
  load(21, cmd_params.dimension, reference_p, positive);
  load(21, cmd_params.dimension, reference_n, negative);

   // Cosine Similarity (classification mapping)
  for(int i = 0; i < centers.size(); i++) {
    double p_distance = 0;
    double n_distance = 0;
    double x1 = 0;
    double x2 = 0;
    double x3 = 0;
    for(int j = 0; j < positive.size(); j++) {
      for(int k = 0; k < positive[j]->getDimension(); k++) {
        x1 += abs(positive[j]->getFeatureItem(k) * centers[i]->getFeatureItem(k));
        x2 += pow(positive[j]->getFeatureItem(k), 2);
        x3 += pow(centers[i]->getFeatureItem(k), 2);
      }
      p_distance += x1 / sqrt(x2 * x3);
    }
    for(int j = 0; j < negative.size(); j++) {
      for(int k = 0; k < negative[j]->getDimension(); k++) {
        x1 += abs(negative[j]->getFeatureItem(k) * inputs[i]->getFeatureItem(k));
        x2 += pow(negative[j]->getFeatureItem(k), 2);
        x3 += pow(inputs[i]->getFeatureItem(k), 2);
      }
      n_distance += x1 / sqrt(x2 * x3);
    }
    p_distance = abs(p_distance)  / positive.size();
    n_distance = abs(n_distance) / negative.size();
    if(p_distance > n_distance) centers[i]->setClusteringCenter(1); // positive-1, negative-0
    else centers[i]->setClusteringCenter(0);
  }

//    // Eulicidean Distance (classification mapping)
//    for(int i = 0; i < centers.size(); i++) {
//    double p_distance = 0;
//    double n_distance = 0;
//    double x1;
//    double x2;
//    for(int j = 0; j < positive.size(); j++) {
//      x1 = 0;
//      for(int k = 0; k < positive[j]->getDimension(); k++) {
//        x1 += pow(positive[j]->getFeatureItem(k) - centers[i]->getFeatureItem(k),2);
//      }
//      p_distance += sqrt(x1);
//
//    }
//    for(int j = 0; j < negative.size(); j++) {
//      x2 = 0;
//      for(int k = 0; k < negative[j]->getDimension(); k++) {
//        x2 += pow(negative[j]->getFeatureItem(k) - centers[i]->getFeatureItem(k),2);
//      }
//      n_distance +=  sqrt(x2);
//    }
//    p_distance = p_distance * 0.99/ positive.size();
//    n_distance = n_distance / negative.size();
//    if(p_distance > n_distance) centers[i]->setClusteringCenter(1);
//    else centers[i]->setClusteringCenter(0);
//  }


  for(int i = 0; i < outputs.size(); i++) {
    if(centers[outputs[i]->getClusteringCenter() - 1]->getClusteringCenter() == 1)outputs[i]->setClusteringCenter(1);
    else if(centers[outputs[i]->getClusteringCenter() - 1]->getClusteringCenter() == 0)outputs[i]->setClusteringCenter(0);
    else std::cout << "Error! result not only 1 or 0!" << std::endl;
  }

  // sentiment140: 0(negative), 2(neutral), 4(positive)
  // yelp:2(positive), 1(negative)
  for(int i = 0; i < cmd_params.pointNumber; i++) {
    if(inputs[i]->getClusteringCenter() == 1)inputs[i]->setClusteringCenter(0);
    else if(inputs[i]->getClusteringCenter() == 2)inputs[i]->setClusteringCenter(1);
    else std::cout << "Error! sentiment140 not only 0, 2 or 4!" << std::endl;
  }

  // Evaluation
  SESAME::Evaluation::runEvaluation(cmd_params.dimension,
                                    cmd_params.clusterNumber,
                                    outputs,
                                    centers,
                                    inputs);
  // get TP. FN, FP, TN
  int TP = 0, FN = 0, FP = 0, TN = 0; // first gt, second prediction
  std::vector<int> GT_id, GN_id, PT_id, PN_id;

  for(int i = 0; i < cmd_params.pointNumber; i++) {
    if(outputs[i]->getClusteringCenter() == 1 && inputs[outputs[i]->getIndex()]->getClusteringCenter() == 1) TP++;
    else if(outputs[i]->getClusteringCenter() == 1 && inputs[outputs[i]->getIndex()]->getClusteringCenter() == 0) FP++;
    else if(outputs[i]->getClusteringCenter() == 0 && inputs[outputs[i]->getIndex()]->getClusteringCenter() == 1) TN++;
    else if(outputs[i]->getClusteringCenter() == 0 && inputs[outputs[i]->getIndex()]->getClusteringCenter() == 0) FN++;
    else {
      std::cout<<"Error!!!";
    }
  }
  // BA
  double sensitivity = (double)TP / (double)(TP + FN);
  double specificity = (double)TN / (double)(FP + TN);
  double balance_accuracy = (sensitivity + specificity) / (double) 2;
  std::cout <<"  Balance Accuracy:" << balance_accuracy;
  // F-score
  double precision = (double)TP / (double)(TP + FP);
  double recall = sensitivity;
  double fscore =(double) 2 * precision * recall / (precision + recall);
  std::cout <<"  F-Score:" << fscore << std::endl;


  engine.stop();
}


