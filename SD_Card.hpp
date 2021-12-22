#ifndef __SD_CARD__
#define __SD_CARD__
#include "mbed.h"

// SD Support?
#if (MBED_CONF_RTOS_PRESENT == 1)
#if (MBED_CONF_SD_FSFAT_SDCARD_INSTALLED == 1)
#define USE_SD_CARD
#endif
#endif
//            "target.components_add": ["SD"],  

class sdCard
{

    public:

        void test();

};






#endif
