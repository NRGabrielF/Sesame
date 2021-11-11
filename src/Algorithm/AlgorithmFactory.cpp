// Copyright (C) 2021 by the IntelliStream team (https://github.com/intellistream)

//
// Created by Shuhao Zhang on 26/07/2021.
//

#include <Algorithm/StreamKM.hpp>
#include <Algorithm/CluStream.hpp>
#include <Algorithm/DenStream.hpp>
#include <Algorithm/DBStream.hpp>
#include <Algorithm/Birch.hpp>
#include <Algorithm/EDMStream.hpp>
#include <Refactor/WinModel/Landmark.hpp>
#include <Refactor/WinModel/Damped.hpp>
#include <Algorithm/AlgorithmFactory.hpp>

SESAME::AlgorithmPtr SESAME::AlgorithmFactory::create(param_t &cmd_params) {
  if (cmd_params.algoType == SESAME::StreamKMeansType) {
    shared_ptr<StreamKM> streamkm = std::make_shared<StreamKM>(cmd_params);;
    return (SESAME::AlgorithmPtr) streamkm;
  }
  if (cmd_params.algoType == SESAME::CluStreamType) {
    shared_ptr<CluStream> cluStream = std::make_shared<CluStream>(cmd_params);
    return (SESAME::AlgorithmPtr) cluStream;
  }
  if (cmd_params.algoType == SESAME::BirchType) {
    shared_ptr<Birch> birch = std::make_shared<Birch>(cmd_params);
    return (SESAME::AlgorithmPtr) birch;
  }
  if (cmd_params.algoType == SESAME::DenStreamType) {
    shared_ptr<DenStream> denStream = std::make_shared<DenStream>(cmd_params);
    return (SESAME::AlgorithmPtr) denStream;
  }
  if (cmd_params.algoType == SESAME::EDMStreamType) {
    shared_ptr<EDMStream> eDMStream = std::make_shared<EDMStream>(cmd_params);
    return (SESAME::AlgorithmPtr) eDMStream;
  }
  if (cmd_params.algoType == SESAME::DBStreamType) {
    shared_ptr<DBStream> dbStream = std::make_shared<DBStream>(cmd_params);
    return (SESAME::AlgorithmPtr) dbStream;
  }
  if (cmd_params.algoType == SESAME::LandmarkType) {
    shared_ptr<Landmark> landmark = std::make_shared<Landmark>(cmd_params);
    return (SESAME::AlgorithmPtr) landmark;
  }
  if (cmd_params.algoType == SESAME::DampedType) {
    shared_ptr<Damped> damped = std::make_shared<Damped>(cmd_params);
    return (SESAME::AlgorithmPtr) damped;
  }
  throw std::invalid_argument("Unsupported");

}
