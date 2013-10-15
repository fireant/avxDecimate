#include <iostream>
#include <fstream>
#include <iomanip> // setprecision

#include "decimate.h"

using namespace std;

int main()
{
    /// 4 test cases:
    /// 1. 20 Hz + 12000 Hz
    /// 2. 20 Hz +  6250 Hz
    /// 3. 20 Hz +  3000 Hz
    /// 4. 20 Hz +  1000 Hz

    ////////////////////////////////////////////////////////////////////////////
    /// 20 Hz cosine + 12000 Hz cosine
    ////////////////////////////////////////////////////////////////////////////

    // file to store original signal
    ofstream signalFile("signal1.csv");
    signalFile<<fixed<<setprecision(10);
    // file to store decimated signal
    ofstream decSignalFile("decimated_signal1.csv");
    decSignalFile<<fixed<<setprecision(10);

    size_t sampling_frq = 25000; // Hz

    // signal generating function
    double (*funcp)(double) = cos;
    float signal_loamp = 100.0f; // signal amplitude
    float signal_hiamp = 10.0f; // signal amplitude
    float signal_hifrq = 12000.0f; // Hz
    float signal_lofrq = 20.0f; // Hz

    size_t numberOfChannels = 60;
    vector<float> samples(numberOfChannels);
    vector<float> decimatedSamples(numberOfChannels);

    Decimate decimate1(numberOfChannels);

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
        if (decimate1.AddSample(samples)) {
            // get decimated samples
            // this vector should have the correct size before passing to the function
            decimate1.GetDecSample(decimatedSamples);

            // write decimatedSamples into file
            decSignalFile<<float(i)/float(sampling_frq)<<","; // time
            for (size_t ch=0; ch<numberOfChannels; ch++)
                decSignalFile<<decimatedSamples[ch]<<","; // channels in columns
            decSignalFile<<endl;
        }
    }

    signalFile.close();
    decSignalFile.close();

    ////////////////////////////////////////////////////////////////////////////
    /// 20 Hz cosine + 6250 Hz cosine
    ////////////////////////////////////////////////////////////////////////////

    // file to store original signal
    signalFile.open("signal2.csv");
    // file to store decimated signal
    decSignalFile.open("decimated_signal2.csv");

    signal_hifrq = 6250.0f; // Hz

    Decimate decimate2(numberOfChannels);

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
        if (decimate2.AddSample(samples)) {
            // get decimated samples
            // this vector should have the correct size before passing to the function
            decimate2.GetDecSample(decimatedSamples);

            // write decimatedSamples into file
            decSignalFile<<float(i)/float(sampling_frq)<<","; // time
            for (size_t ch=0; ch<numberOfChannels; ch++)
                decSignalFile<<decimatedSamples[ch]<<","; // channels in columns
            decSignalFile<<endl;
        }
    }

    signalFile.close();
    decSignalFile.close();

    ////////////////////////////////////////////////////////////////////////////
    /// 20 Hz cosine + 3000 Hz cosine
    ////////////////////////////////////////////////////////////////////////////

    // file to store original signal
    signalFile.open("signal3.csv");
    // file to store decimated signal
    decSignalFile.open("decimated_signal3.csv");

    signal_hifrq = 3000.0f; // Hz

    Decimate decimate3(numberOfChannels);

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
        if (decimate3.AddSample(samples)) {
            // get decimated samples
            // this vector should have the correct size before passing to the function
            decimate3.GetDecSample(decimatedSamples);

            // write decimatedSamples into file
            decSignalFile<<float(i)/float(sampling_frq)<<","; // time
            for (size_t ch=0; ch<numberOfChannels; ch++)
                decSignalFile<<decimatedSamples[ch]<<","; // channels in columns
            decSignalFile<<endl;
        }
    }

    signalFile.close();
    decSignalFile.close();

    ////////////////////////////////////////////////////////////////////////////
    /// 20 Hz cosine + 1000 Hz cosine
    ////////////////////////////////////////////////////////////////////////////

    // file to store original signal
    signalFile.open("signal4.csv");
    // file to store decimated signal
    decSignalFile.open("decimated_signal4.csv");

    signal_hifrq = 1000.0f; // Hz

    Decimate decimate4(numberOfChannels);

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
        if (decimate4.AddSample(samples)) {
            // get decimated samples
            // this vector should have the correct size before passing to the function
            decimate4.GetDecSample(decimatedSamples);

            // write decimatedSamples into file
            decSignalFile<<float(i)/float(sampling_frq)<<","; // time
            for (size_t ch=0; ch<numberOfChannels; ch++)
                decSignalFile<<decimatedSamples[ch]<<","; // channels in columns
            decSignalFile<<endl;
        }
    }

    signalFile.close();
    decSignalFile.close();

    return 0;
}

