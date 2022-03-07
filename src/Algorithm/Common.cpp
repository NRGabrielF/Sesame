#include "Algorithm/Algorithm.hpp"

namespace SESAME{

template<typename W, typename P, typename G>
class StreamClusteringAlgorithm {
public:
    StreamClusteringAlgorithm() = default;
    ~StreamClusteringAlgorithm() = default;
    void Initilize();
    void runOnlineClustering(PointPtr input);
    void runOfflineClustering(DataSinkPtr ptr);
    void store(std::string outputPath, int dimension, std::vector<PointPtr> results);
private:
};

template<typename W, typename P, typename G>
void StreamClusteringAlgorithm<W, P, G>::Initilize() {
    
}

}