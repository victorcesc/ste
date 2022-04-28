#ifndef __ADC_H__
#define __ADC_H__

class AdcChannel{

    public:
        AdcChannel(int ch);
        int get();

    private:
        int channel;

};



#endif