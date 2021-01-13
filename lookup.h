/*
    from https://www.diva-portal.org/smash/get/diva2:830195/FULLTEXT01.pdf
*/

char* layers[] = {
    "Reserved",
    "Layer III",
    "Layer II",
    "Layer I",
};

uint16_t bitrates[] = {
    -1,
    32,
    40,
    48,
    56,
    64,
    80,
    96,
    112,
    128,
    160,
    192,
    224,
    256,
    320,
    -1
};

// In Hz
uint32_t frequencies[] = {
    44100,
    48000,
    32000,
    -1
};

char* modes[] = {
    "Stereo",
    "Joint Stereo",
    "Dual Channel",
    "Single Channel"
};

// intensity stero | MS stereo
uint8_t mode_extensions[4][2] = {
    {0, 1},
    {1, 0},
    {0, 1},
    {1, 1}
};
