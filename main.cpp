#include <iostream>
#include <fstream>

#include "decimate.h"

using namespace std;

int main()
{
    // file to store original signal
    ofstream signalFile("signal.csv");
    // file to store decimated signal
    ofstream decSignalFile("decimated_signal.csv");

    size_t sampling_frq = 25000; // Hz

    // signal generating function
    double (*funcp)(double) = cos;
    float signal_loamp = 100.0f; // signal amplitude
    float signal_hiamp = 10.0f; // signal amplitude
    float signal_hifrq = 17000.0f; // Hz
    float signal_lofrq = 20.0f; // Hz

    size_t numberOfChannels = 60;
    vector<float> samples(numberOfChannels);
    vector<float> decimatedSamples(numberOfChannels);

    Decimate decimate(numberOfChannels);

    // 1 second signal
    for (size_t i = 0; i <= sampling_frq; i++ ) {
        signalFile<<float(i)/float(sampling_frq)<<",";

        for (size_t ch=0; ch<numberOfChannels; ch++) {
            samples[ch] = (*funcp)(2.0*M_PI * float(i)/float(sampling_frq) * signal_hifrq) * signal_hiamp
                         + (*funcp)(2.0*M_PI * float(i)/float(sampling_frq) * signal_lofrq) * signal_loamp;

            signalFile<<samples[ch]<<",";
        }

        signalFile<<endl;

        // call getDecSample when enough number of samples are given
        if (decimate.AddSample(samples)) {
            // get decimated samples
            // this vector should have the correct size before passing to the function
            decimate.GetDecSample(decimatedSamples);

            // write decimatedSamples into file
            decSignalFile<<float(i)/float(sampling_frq)<<","; // time
            for (size_t ch=0; ch<numberOfChannels; ch++)
                decSignalFile<<decimatedSamples[ch]<<","; // channels in columns
            decSignalFile<<endl;
        }
    }

    return 0;
}

