#ifndef DECIMATE_H
#define DECIMATE_H

#include <boost/circular_buffer.hpp>
#include <vector>
#include <immintrin.h>

#define HALF_FILTER_SIZE 24

class Decimate
{
public:
    Decimate(size_t numberOfChannels);
    bool AddSample(std::vector<float>& samples);
    void GetDecSample(std::vector<float>& samples);

private:
    bool currentSubEven = true;

    std::vector<boost::circular_buffer<float> > samplesSubEven;
    std::vector<boost::circular_buffer<float> > samplesSubOdd;

    static const float subfilterEven[HALF_FILTER_SIZE];
    static const float subfilterOdd[HALF_FILTER_SIZE];

    __m256 avxFilterEven1;
    __m256 avxFilterEven2;
    __m256 avxFilterEven3;
    __m256 avxFilterOdd1;
    __m256 avxFilterOdd2;
    __m256 avxFilterOdd3;

};

#endif // DECIMATE_H

