# Sesame [![CMake](https://github.com/intellistream/Sesame/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/intellistream/Sesame/actions/workflows/cmake.yml)

# Time Table

1. code refactor - 8/Nov/2021
2. modularized algorithm design + workflow diagram - 10/Nov/2021
3. experimental test - 17/Nov/2021
4. first complete draft - 24/Nov/2021
5. first submission - 1/Dec/2021

Add-on. Learn how to draw figure using python -- Zhonghao.

# DataSet

| DaTaset     | Atrtribute | Point Number | Used by | characteristics       |
| ----------- | ---------- | ------------ | ------- | --------------------- |
| KDD-99      | 41         | 494021       |         |                       |
| ForestType  | 54         | 15120        |         |                       |
| Powersupply | 2          | 29928        |         |                       |
| Diamond     | 2          | 3000         |         | has concept drift     |
| Zelnik      | 2          | 622          |         | containing noise data |



# ForesetType(1512)

| Algorithm    | CMM    | Purity | Time        | Throughput | Parameter                                                |
| ------------ | ------ | ------ | ----------- | ---------- | -------------------------------------------------------- |
| StreamKMeans | 0.7998 | 0.4485 | 27589875 us | 0.548 Tpt. | clusterNumber = 3; coresetSize = 600; seed = 10          |
| BIRCH        | 0.727  | 0.8049 | 1920530 us  | 0.787      | InnerNode = 20; LeafNode = 40; distance = 10             |
| EDMStream    | 0.8927 | 0.8152 | 3542147 us  | 0.42       | Radius = 20, delta = 120,  beta = 0.01, bufferSize = 150 |



# KDD-99(4940)

| Algorithm    | CMM    | Purity | Time         | Throughput | Parameter                                                |
| ------------ | ------ | ------ | ------------ | ---------- | -------------------------------------------------------- |
| StreamKMeans | 0.8248 | 0.9425 | 80185514 us  | 0.06       | ClusterNumber = 23, coresetSize = 4600, seed = 10        |
| BIRCH        | 0.79   | 0.9985 | 70325122 us  | 0.07       | InnerNode = 20; LeafNode = 40; distance = 10             |
| EDMStream    | 0.8987 | 0.8235 | 122352352 us | 0.04       | Radius = 75, delta = 100,  beta = 0.07, bufferSize = 400 |



# PowerSupply(1000)

| Algorithm    | CMM    | Purity | Time       | Throughput | Parameter                                               |
| ------------ | ------ | ------ | ---------- | ---------- | ------------------------------------------------------- |
| StreamKMeans | 0.7577 | 0.5993 | 5545046 us | 0.18 Tpt.  | clusterNumber = 24; coresetSize = 4800; seed = 10       |
| BIRCH        | 0.7235 | 0.319  | 1486000 us | 0.67 Tpt.  | InnerNode = 10; LeafNode = 10; distance = 8             |
| EDMStream    | 0.7342 | 0.4835 | 8928463 us | 0.112      | Radius = 10, delta = 25,  beta = 0.01, bufferSize = 100 |



# Diamond(3000)

| Algorithm    | CMM    | Purity | Time      | Throughput | Parameter                                               |
| ------------ | ------ | ------ | --------- | ---------- | ------------------------------------------------------- |
| StreamKMeans | 0.7764 | 0.6023 | 395250 us | 7.59 Tpt.  | clusterNumber = 9; coresetSize = 1800; seed = 10        |
| BIRCH        | 0.7891 | 0.8877 | 675450 us | 4.44 Tpt.  | InnerNode = 10; LeafNode = 40; distance = 0.6           |
| EDMStream    | 0.7612 | 0.6458 | 692351 us | 4.33       | Radius = 0.2, delta =5 ,  beta = 0.01, bufferSize = 200 |



# Zelnik(622)

| Algorithm    | CMM    | Purity | Time      | Throughput | Parameter                                                |
| ------------ | ------ | ------ | --------- | ---------- | -------------------------------------------------------- |
| StreamKMeans | 0.7249 | 0.5981 | 104548 us | 5.95 Tpt.  | clusterNumber = 4; coresetSize = 300; seed = 10          |
| BIRCH        | 0.75   | 0.7653 | 81532 us  | 7.63 Tpt.  | InnerNode = 10; LeafNode = 10; distance = 0.2            |
| EDMStream    | 0.86   | 0.7925 | 402653 us | 1.54       | Radius = 0.45, delta = 3,  beta = 0.01, bufferSize = 100 |

