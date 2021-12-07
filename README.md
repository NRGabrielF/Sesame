# Sesame [![CMake](https://github.com/intellistream/Sesame/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/intellistream/Sesame/actions/workflows/cmake.yml)

# Time Table

1. code refactor - 8/Nov/2021
2. modularized algorithm design + workflow diagram - 10/Nov/2021
3. experimental test - 17/Nov/2021
4. first complete draft - 24/Nov/2021
5. first submission - 1/Dec/2021

Add-on. Learn how to draw figure using python -- Zhonghao.

# DataSet

| DaTaset           | Used by | characteristics       |
| ----------------- | ------- | --------------------- |
| KDD-99            |         |                       |
| ForestType        |         |                       |
| Powersupply       |         |                       |
| Synthetic Diamond |         | has concept drift     |
| Synthetic Zelnik  |         | containing noise data |



# ForesetType

| Algorithm    | CMM    | Purity | Parameter                                       |
| ------------ | ------ | ------ | ----------------------------------------------- |
| StreamKMeans | 0.7998 | 0.4485 | clusterNumber = 3; coresetSize = 600; seed = 10 |
| BIRCH        |        |        |                                                 |
| EDMStream    |        |        |                                                 |



# KDD-99

| Algorithm    | CMM    | Purity | Parameter                                       |
| ------------ | ------ | ------ | ----------------------------------------------- |
| StreamKMeans | 0.7998 | 0.4485 | clusterNumber = 3; coresetSize = 600; seed = 10 |
| BIRCH        |        |        |                                                 |
| EDMStream    |        |        |                                                 |



# PowerSupply

| Algorithm    | CMM    | Purity | Parameter                                         |
| ------------ | ------ | ------ | ------------------------------------------------- |
| StreamKMeans | 0.7577 | 0.5993 | clusterNumber = 24; coresetSize = 4800; seed = 10 |
| BIRCH        |        |        |                                                   |
| EDMStream    |        |        |                                                   |



# Diamond

| Algorithm    | CMM    | Purity | Parameter                                        |
| ------------ | ------ | ------ | ------------------------------------------------ |
| StreamKMeans | 0.7394 | 0.5217 | clusterNumber = 9; coresetSize = 1800; seed = 10 |
| BIRCH        |        |        |                                                  |
| EDMStream    |        |        |                                                  |



# Zelnik

| Algorithm    | CMM  | Purity | Parameter                                      |
| ------------ | ---- | ------ | ---------------------------------------------- |
| StreamKMeans | 0.75 | 0.246  | clusterNumber = 4; coresetSize = 80; seed = 10 |
| BIRCH        |      |        |                                                |
| EDMStream    |      |        |                                                |

