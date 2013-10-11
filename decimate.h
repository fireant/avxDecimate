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
    bool currentSub = true;

    std::vector<boost::circular_buffer<float> > samplesSub1;
    std::vector<boost::circular_buffer<float> > samplesSub2;

    static const float subfilter1[HALF_FILTER_SIZE];
    static const float subfilter2[HALF_FILTER_SIZE];

    __m256 avxFilter11;
    __m256 avxFilter12;
    __m256 avxFilter13;
    __m256 avxFilter21;
    __m256 avxFilter22;
    __m256 avxFilter23;

};

#endif // DECIMATE_H

