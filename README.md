# Sesame [![CMake](https://github.com/intellistream/Sesame/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/intellistream/Sesame/actions/workflows/cmake.yml)

# Time Table

1. code refactor - 8/Nov/2021
2. modularized algorithm design + workflow diagram - 10/Nov/2021
3. experimental test - 17/Nov/2021
4. first complete draft - 24/Nov/2021
5. first submission - 1/Dec/2021

Add-on. Learn how to draw figure using python -- Zhonghao.

# Evaluation Results

We begin with a comparison of the data structure. We then pick the best overall structure and use it to evaluate the window model, outlier detection, concept drift handling and offline refinement.

|      | Data Structure | Window model | outlier detection | concept Drift Handling | Offline Refinement | Purity | CMM   | Time |
| ---- | -------------- | ------------ | ----------------- | ---------------------- | ------------------ | ------ | ----- | ---- |
|      | CFTree         | Landmark     | Distance          | Count                  | KMeans++           | 0.412  | 0.769 |      |
|      | Coreset        | Landmark     | Distance          | Count                  | KMeans++           |        |       |      |
|      | Grid           | Landmark     | Distance          | Count                  | KMeans++           |        |       |      |
|      | Micro Cluster  | Landmark     | Distance          | Count                  | KMeans++           |        |       |      |

