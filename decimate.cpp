#include "decimate.h"
#include <stddef.h>
#include <iostream>

using namespace std;

const float Decimate::subfilterEven[HALF_FILTER_SIZE] = {0.000351300968081,
                                                     -0.000993492892699,
                                                      0.002204029354477,
                                                     -0.003996538310521,
                                                      0.005694104512935,
                                                     -0.005880476544078,
                                                      0.002645194320828,
                                                      0.005984463754494,
                                                     -0.021725335732865,
                                                      0.046518486309819,
                                                     -0.086512770274383,
                                                      0.188972935647546,
                                                      0.397974423850271,
                                                     -0.028991541109885,
                                                     -0.013197192022979,
                                                      0.024631140915737,
                                                     -0.024300666126915,
                                                      0.018684970470861,
                                                     -0.011630985162763,
                                                      0.005540255420496,
                                                     -0.001516632751836,
                                                     -0.000434310459263,
                                                      0.000994006674784,
                                                     -0.001015370812141};

const float Decimate::subfilterOdd[HALF_FILTER_SIZE] = {-0.001015370812141,
                                                       0.000994006674784,
                                                      -0.000434310459263,
                                                      -0.001516632751836,
                                                       0.005540255420496,
                                                      -0.011630985162763,
                                                       0.018684970470861,
                                                      -0.024300666126915,
                                                       0.024631140915737,
                                                      -0.013197192022979,
                                                      -0.028991541109885,
                                                       0.397974423850271,
                                                       0.188972935647546,
                                                      -0.086512770274383,
                                                       0.046518486309819,
                                                      -0.021725335732865,
                                                       0.005984463754494,
                                                       0.002645194320828,
                                                      -0.005880476544078,
                                                       0.005694104512935,
                                                      -0.003996538310521,
                                                       0.002204029354477,
                                                      -0.000993492892699,
                                                       0.000351300968081};


Decimate::Decimate(size_t numberOfChannels)
{
    currentSubEven = true;

    samplesSubEven.reserve(numberOfChannels);
    samplesSubOdd.reserve(numberOfChannels);

    for (size_t i=0; i<numberOfChannels; i++) {
        samplesSubEven[i].set_capacity(HALF_FILTER_SIZE);
        samplesSubOdd[i].set_capacity(HALF_FILTER_SIZE);
    }

    avxFilterEven1 = _mm256_load_ps(&(subfilterEven[0]));
    avxFilterEven2 = _mm256_load_ps(&(subfilterEven[8]));
    avxFilterEven3 = _mm256_load_ps(&(subfilterEven[16]));
    avxFilterOdd1 = _mm256_load_ps(&(subfilterOdd[0]));
    avxFilterOdd2 = _mm256_load_ps(&(subfilterOdd[8]));
    avxFilterOdd3 = _mm256_load_ps(&(subfilterOdd[16]));
}

bool Decimate::AddSample(std::vector<float>& samples) {
    if (currentSubEven) {
        for (size_t i=0; i<samples.size(); i++)
            samplesSubEven[i].push_back(samples[i]);
        currentSubEven = false;
        return false;
    } else {
        for (size_t i=0; i<samples.size(); i++)
            samplesSubOdd[i].push_back(samples[i]);
        currentSubEven = true;
    }

    return (samplesSubOdd[0].size() == samplesSubOdd[0].capacity());
}

void Decimate::GetDecSample(std::vector<float> &samples) {
    for (size_t i=0; i<samples.size(); i++) {
        // first subfilter
        float *data = samplesSubEven[i].linearize();
        __m256 avxData1 = _mm256_load_ps(data);
        __m256 avxData2 = _mm256_load_ps(&(data[8]));
        __m256 avxData3 = _mm256_load_ps(&(data[16]));

        __m256 avxResult1;
        __m256 avxResult2;
        __m256 avxResult3;

        avxResult1 = _mm256_mul_ps(avxFilterEven1, avxData1);
        avxResult2 = _mm256_mul_ps(avxFilterEven2, avxData2);
        avxResult3 = _mm256_add_ps(avxResult1, avxResult2);
        avxResult2 = _mm256_mul_ps(avxFilterEven3, avxData3);
        avxResult1 = _mm256_add_ps(avxResult2, avxResult3);

        __m128 hiQuad = _mm256_extractf128_ps(avxResult1, 1);
        __m128 loQuad = _mm256_castps256_ps128(avxResult1);
        __m128 sumQuad = _mm_add_ps(loQuad, hiQuad);
        __m128 loDual = sumQuad;
        __m128 hiDual = _mm_movehl_ps(sumQuad, sumQuad);
        __m128 sumDual = _mm_add_ps(loDual, hiDual);
        __m128 lo = sumDual;
        __m128 hi = _mm_shuffle_ps(sumDual, sumDual, 0x1);
        __m128 sum = _mm_add_ss(lo, hi);

        float sample = _mm_cvtss_f32(sum);

        //start = high_resolution_clock::now();
        //end = high_resolution_clock::now();
        //cout<<"output: "<<output<<endl;
        //ns = duration_cast<nanoseconds>(end - start);
        //cout<<"Elapsed nanosecs: "<<ns.count()<<endl;

        // second subfilter
        data = samplesSubOdd[i].linearize();
        avxData1 = _mm256_load_ps(data);
        avxData2 = _mm256_load_ps(&(data[8]));
        avxData3 = _mm256_load_ps(&(data[16]));

        avxResult1 = _mm256_mul_ps(avxFilterOdd1, avxData1);
        avxResult2 = _mm256_mul_ps(avxFilterOdd2, avxData2);
        avxResult3 = _mm256_add_ps(avxResult1, avxResult2);
        avxResult2 = _mm256_mul_ps(avxFilterOdd3, avxData3);
        avxResult1 = _mm256_add_ps(avxResult2, avxResult3);

        hiQuad = _mm256_extractf128_ps(avxResult1, 1);
        loQuad = _mm256_castps256_ps128(avxResult1);
        sumQuad = _mm_add_ps(loQuad, hiQuad);
        loDual = sumQuad;
        hiDual = _mm_movehl_ps(sumQuad, sumQuad);
        sumDual = _mm_add_ps(loDual, hiDual);
        lo = sumDual;
        hi = _mm_shuffle_ps(sumDual, sumDual, 0x1);
        sum = _mm_add_ss(lo, hi);

        sample += _mm_cvtss_f32(sum);

        samples[i] = sample;
    }
}

