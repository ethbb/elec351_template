#include "SD_Card.hpp"
#include <cstdint>

#ifdef USE_SD_CARD
#include "SDBlockDevice.h"
#include "FATFileSystem.h"
// Instantiate the SDBlockDevice by specifying the SPI pins connected to the SDCard
// socket. The PINS are: (This can also be done in the JSON file see mbed.org Docs API Storage SDBlockDevice)
// PB_5    MOSI (Master Out Slave In)
// PB_4    MISO (Master In Slave Out)
// PB_3    SCLK (Serial Clock)
// PF_3    CS (Chip Select)
//
// and there is a Card Detect CD on PF_4 ! (NB this is an Interrupt capable pin..)
SDBlockDevice sd(PB_5, PB_4, PB_3, PF_3);


int write_sdcard()
{
    printf("Initialise and write to a file\n");
int err;
    // call the SDBlockDevice instance initialisation method.

    err=sd.init();
    if ( 0 != err) {
        printf("Init failed %d\n",err);
        return -1;
    }
    
    FATFileSystem fs("sd", &sd);
    FILE *fp = fopen("/sd/test.txt","w");
    if(fp == NULL) {
        error("Could not open file for write\n");
        sd.deinit();
        return -1;
    } else {
        //Put some text in the file...
        fprintf(fp, "Martin Says Hi!\n");
        //Tidy up here
        fclose(fp);
        printf("SD Write done...\n");
        sd.deinit();
        return 0;
    }
    
}

int read_sdcard()
{
    printf("Initialise and read from a file\n");

    // call the SDBlockDevice instance initialisation method.
    if ( 0 != sd.init()) {
        printf("Init failed \n");
        return -1;
    }
    
    FATFileSystem fs("sd", &sd);
    FILE *fp = fopen("/sd/test.txt","r");
    if(fp == NULL) {
        error("Could not open or find file for read\n");
        sd.deinit();
        return -1;
    } else {
        //Put some text in the file...
        char buff[64]; buff[63] = 0;
        while (!feof(fp)) {
            fgets(buff, 63, fp);
            printf("%s\n", buff);
        }
        //Tidy up here
        fclose(fp);
        printf("SD Write done...\n");
        sd.deinit();
        return 0;
    }
}

void sdCard::test()
{
    //Test SD Card
    #ifdef USE_SD_CARD
    write_sdcard();
    read_sdcard();
    #endif
}
#endif