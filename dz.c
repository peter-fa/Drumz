


#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{

    unsigned long int miditime;
    unsigned int swing;
    char patterns[16][9][26][10]; 
    char step, instrument, pattern, bank;
    int i, j, k, m;

    char note[9];
    char velocity[18];

    unsigned int tempo;
    char ts_numerator, ts_denominator, midi_program, midi_channel;

    char command[15];
    int status;

    void help();

    miditime = 0;
    swing = 0;
    instrument = 0;
    pattern = 0;
    bank = 0;

    for (i = 0; i < 16; i++){ 
        for (j = 0; j < 9; j++){ 
            for (k = 0; k < 26; k++){ 
                for (m = 0; m < 10; m++){ 

                    patterns[i][j][k][m] = 0;

                }
            }
        }
    }

    for (i = 0; i < 9; i++){ 

        note[i] = 0;
    }

    for (i = 0; i < 18; i++){ 

        velocity[i] = 0;
    }

    tempo = 0;
    ts_numerator = 0;
    ts_denominator = 0;
    midi_program = 0;
    midi_channel = 10;

    /* ----- */


    /* General Midi */
    note[1] = 36; note[2] = 38; note[3] = 43; note[4] = 45;
    note[5] = 50; note[6] = 51; note[7] = 42; note[8] = 46;

    velocity[1] = 60; velocity[2] = 60; velocity[3] = 60; velocity[4] = 60;
    velocity[5] = 60; velocity[6] = 60; velocity[7] = 60; velocity[8] = 60;
    velocity[10] = 120; velocity[11] = 120; velocity[12] = 120; velocity[13] = 120;
    velocity[14] = 120; velocity[15] = 120; velocity[16] = 120; velocity[17] = 120;


    if (argc >= 2) {

        for (i = 2; i < argc; i++){

            /* tempo */
            if ((strlen(argv[i])) == 5 && (argv[i][0] == '-') && (argv[i][1] == 't') &&
                (argv[i][2] >= '1') && (argv[i][2] <= '3') &&
                (argv[i][3] >= '0') && (argv[i][3] <= '9') &&
                (argv[i][4] >= '0') && (argv[i][4] <= '9')){

                 tempo = (argv[i][2] - 0x30) * 100 + (argv[i][3] - 0x30) * 10 + (argv[i][4] - 0x30); 

            }

            else if ((strlen(argv[i])) == 4 && (argv[i][0] == '-') && (argv[i][1] == 't') &&
                (argv[i][2] >= '3') && (argv[i][2] <= '9') &&
                (argv[i][3] >= '0') && (argv[i][3] <= '9')){

                 tempo = (argv[i][2] - 0x30) * 10 + (argv[i][3] - 0x30); 

            }

            /* time signature */
            else if (strcmp(argv[i], "-ts44") == 0){

                ts_numerator = 4;
                ts_denominator = 4;
            } 

            else if (strcmp(argv[i], "-ts4") == 0){

                ts_numerator = 4;
                ts_denominator = 4;
            } 

            else if (strcmp(argv[i], "-ts34") == 0){

                ts_numerator = 3;
                ts_denominator = 4;
            } 

            else if (strcmp(argv[i], "-ts3") == 0){

                ts_numerator = 3;
                ts_denominator = 4;
            } 

            else if (strcmp(argv[i], "-ts68") == 0){

                ts_numerator = 6;
                ts_denominator = 8;
            } 

            /* midi program */
            else if ((strlen(argv[i])) == 5 && (argv[i][0] == '-') && (argv[i][1] == 'p') &&
                (argv[i][2] >= '1') && (argv[i][2] <= '2') &&
                (argv[i][3] >= '0') && (argv[i][3] <= '9') &&
                (argv[i][4] >= '0') && (argv[i][4] <= '9')){

                 midi_program = (argv[i][2] - 0x30) * 100 + (argv[i][3] - 0x30) * 10 + (argv[i][4] - 0x30); 

            }

            else if ((strlen(argv[i])) == 4 && (argv[i][0] == '-') && (argv[i][1] == 'p') &&
                (argv[i][2] >= '1') && (argv[i][2] <= '9') &&
                (argv[i][3] >= '0') && (argv[i][3] <= '9')){

                 midi_program = (argv[i][2] - 0x30) * 10 + (argv[i][3] - 0x30); 

            }

            else if ((strlen(argv[i])) == 3 && (argv[i][0] == '-') && (argv[i][1] == 'p') &&
                (argv[i][2] >= '1') && (argv[i][2] <= '9')){

                 midi_program = (argv[i][2] - 0x30); 

            }

            /* midi channel */
            else if ((strlen(argv[i])) == 4 && (argv[i][0] == '-') && (argv[i][1] == 'c') &&
                (argv[i][2] == '1') &&
                (argv[i][3] >= '0') && (argv[i][3] <= '6')){

                 midi_channel = (argv[i][2] - 0x30) * 10 + (argv[i][3] - 0x30); 

            }

            else if ((strlen(argv[i])) == 3 && (argv[i][0] == '-') && (argv[i][1] == 'c') &&
                (argv[i][2] >= '1') && (argv[i][2] <= '9')){

                 midi_channel = (argv[i][2] - 0x30); 

            }

            /* swing (midi ticks) */
            else if (strcmp(argv[i], "-sw0") == 0){

                swing = 0;
            } 

            else if (strcmp(argv[i], "-sw1") == 0){

                swing = 10;
            } 

            else if (strcmp(argv[i], "-sw2") == 0){

                swing = 20;
            } 

            else if (strcmp(argv[i], "-sw3") == 0){

                swing = 30;
            } 

            else if (strcmp(argv[i], "-sw4") == 0){

                swing = 40;
            } 

            else if (strcmp(argv[i], "-sw5") == 0){

                swing = 50;
            } 

            else if (strcmp(argv[i], "-sw6") == 0){

                swing = 60;
            } 

            /* drum kits */
            else if (strcmp(argv[i], "-k0") == 0){ /* note 35 - */

                note[1] = 35; note[2] = 36; note[3] = 37; note[4] = 38;
                note[5] = 39; note[6] = 40; note[7] = 41; note[8] = 42;
            } 

            else if (strcmp(argv[i], "-k1") == 0){ /* note 36 - */

                note[1] = 36; note[2] = 37; note[3] = 38; note[4] = 39;
                note[5] = 40; note[6] = 41; note[7] = 42; note[8] = 43;
            } 

            else if (strcmp(argv[i], "-k32") == 0){ /* General midi */

                note[1] = 35; note[2] = 38; note[3] = 45; note[4] = 47;
                note[5] = 50; note[6] = 51; note[7] = 42; note[8] = 46;
            } 

            else if (strcmp(argv[i], "-k33") == 0){ /* General midi - side stick */

                note[1] = 35; note[2] = 37; note[3] = 45; note[4] = 47;
                note[5] = 50; note[6] = 51; note[7] = 42; note[8] = 46;
            } 

            else if (strcmp(argv[i], "-k34") == 0){ /* General midi - hand clap */

                note[1] = 35; note[2] = 39; note[3] = 45; note[4] = 47;
                note[5] = 50; note[6] = 51; note[7] = 42; note[8] = 46;
            } 

            else if (strcmp(argv[i], "-k35") == 0){ /* General midi - electric snare */

                note[1] = 36; note[2] = 40; note[3] = 45; note[4] = 47;
                note[5] = 50; note[6] = 51; note[7] = 42; note[8] = 46;
            } 

            else if (strcmp(argv[i], "-k64") == 0){ /* Latin - General midi - w Maracas */

                note[1] = 39; note[2] = 64; note[3] = 63; note[4] = 66;
                note[5] = 65; note[6] = 68; note[7] = 67; note[8] = 70;
            } 

            else if (strcmp(argv[i], "-k65") == 0){ /* Latin - General midi - w Cabasa */

                note[1] = 39; note[2] = 64; note[3] = 63; note[4] = 66;
                note[5] = 65; note[6] = 68; note[7] = 67; note[8] = 69;
            } 

            else if (strcmp(argv[i], "-k66") == 0){ /* Latin - General midi - w Maracas, Woodblock */

                note[1] = 39; note[2] = 64; note[3] = 63; note[4] = 66;
                note[5] = 65; note[6] = 77; note[7] = 76; note[8] = 70;
            } 

            else if (strcmp(argv[i], "-k67") == 0){ /* Latin - General midi - w Cabasa, Woodblock */

                note[1] = 39; note[2] = 64; note[3] = 63; note[4] = 66;
                note[5] = 65; note[6] = 77; note[7] = 76; note[8] = 69;
            } 

            else if (strcmp(argv[i], "-k68") == 0){ /* Latin - General midi - w Maracas, Claves */

                note[1] = 75; note[2] = 64; note[3] = 63; note[4] = 66;
                note[5] = 65; note[6] = 68; note[7] = 67; note[8] = 70;
            } 

            else if (strcmp(argv[i], "-k69") == 0){ /* Latin - General midi - w Cabasa, Claves */

                note[1] = 75; note[2] = 64; note[3] = 63; note[4] = 66;
                note[5] = 65; note[6] = 68; note[7] = 67; note[8] = 69;
            } 

            /* velocities */
            else if (strcmp(argv[i], "-v0") == 0){ /* electronic */

                velocity[1] = 60; velocity[2] = 60; velocity[3] = 60; velocity[4] = 60;
                velocity[5] = 60; velocity[6] = 60; velocity[7] = 60; velocity[8] = 60;
                velocity[10] = 120; velocity[11] = 120; velocity[12] = 120; velocity[13] = 120;
                velocity[14] = 120; velocity[15] = 120; velocity[16] = 120; velocity[17] = 120;
            } 

            else if (strcmp(argv[i], "-v1") == 0){ /* rock */

                velocity[1] = 50; velocity[2] = 50; velocity[3] = 50; velocity[4] = 50;
                velocity[5] = 50; velocity[6] = 40; velocity[7] = 40; velocity[8] = 40;
                velocity[10] = 100; velocity[11] = 100; velocity[12] = 100; velocity[13] = 100;
                velocity[14] = 100; velocity[15] = 80; velocity[16] = 80; velocity[17] = 80;
            } 

            else if (strcmp(argv[i], "-v2") == 0){ /* funk */

                velocity[1] = 50; velocity[2] = 30; velocity[3] = 30; velocity[4] = 30;
                velocity[5] = 30; velocity[6] = 20; velocity[7] = 20; velocity[8] = 20;
                velocity[10] = 100; velocity[11] = 100; velocity[12] = 100; velocity[13] = 100;
                velocity[14] = 100; velocity[15] = 80; velocity[16] = 80; velocity[17] = 80;
            } 

            else if (strcmp(argv[i], "-v3") == 0){ /* jazz */

                velocity[1] = 30; velocity[2] = 30; velocity[3] = 30; velocity[4] = 30;
                velocity[5] = 30; velocity[6] = 50; velocity[7] = 50; velocity[8] = 50;
                velocity[10] = 80; velocity[11] = 80; velocity[12] = 80; velocity[13] = 80;
                velocity[14] = 80; velocity[15] = 100; velocity[16] = 100; velocity[17] = 100;
            } 

            else {

                 help();
            }
        } 

    }

    else {

         help();
    }


    /* ----- */

    status = scanf("%10s", command);
    while (status == 1){

        if (strlen(command) == 2){

            if ((command[0] == '#') && (command[1] >= '0') && (command[1] <= '9')){

                bank = command[1] - 0x30;

            }

            else if ((command[0] == '@') && (command[1] >= 'a') && (command[1] <= 'z')){

                pattern = command[1] - 0x61;

            }

            else if ((command[0] == '$') && (command[1] >= '0') && (command[1] <= '8')){

                instrument = command[1] - 0x30;

            }

            else if ((command[0] == '0') && (command[1] >= '1') && (command[1] <= '9')){

                patterns[command[1] - 0x31][instrument][pattern][bank] = 1;

            }

            else if ((command[0] == '1') && (command[1] >= '0') && (command[1] <= '6')){

                patterns[command[1] - 0x27][instrument][pattern][bank] = 1;

            }

            else if ((command[0] == 'a') && (command[1] == 'c')){

                instrument = 0;

            }

            else if ((command[0] == 'b') && (command[1] == 'd')){

                instrument = 1;

            }

            else if ((command[0] == 's') && (command[1] == 'd')){

                instrument = 2;

            }

            else if ((command[0] == 'l') && (command[1] == 't')){

                instrument = 3;

            }

            else if ((command[0] == 'm') && (command[1] == 't')){

                instrument = 4;

            }

            else if ((command[0] == 'h') && (command[1] == 't')){

                instrument = 5;

            }

            else if ((command[0] == 'c') && (command[1] == 'y')){

                instrument = 6;

            }

            else if ((command[0] == 'c') && (command[1] == 'h')){

                instrument = 7;

            }

            else if ((command[0] == 'o') && (command[1] == 'h')){

                instrument = 8;

            }

            else {

                fprintf(stderr, "warning: incorrect command %s!\n", command);
                exit(1);

            }

        }

        else {

            fprintf(stderr, "warning: incorrect command %s!\n", command);
            exit(1);
 
        }

        status = scanf("%10s", command);

    }

    /* Utskrift */

    step = 0;
    instrument = 0;
    pattern = 0;
    bank = 0;

    printf("MFile 0 1 480\nMTrk\n");

    if (ts_numerator != 0){

        printf("%lu TimeSig %u/%u 24 8\n", miditime, ts_numerator, ts_denominator);
    }

    if (tempo != 0){

        printf("%lu Tempo %lu\n", miditime, (long) (1000000 * 60 / tempo));
    }

    if (midi_program != 0){

        printf("%lu PrCh ch=%u p=%u\n", miditime,  midi_channel, midi_program);
    }


    for (i = 0; i < strlen(argv[1]); i++){

        if ((argv[1][i] >= 'a') && (argv[1][i] <= 'z')){

            pattern = argv[1][i] - 0x61;
            for (j = 0; j < 16; j++){

                for (k = 1; k < 9; k++){

                    if (patterns[j][k][pattern][bank] == 1){

                        if (j % 2 == 1){ 

                            if (patterns[j][0][pattern][bank] == 1){

                                printf("%lu On ch=%u n=%u v=%u\n", miditime + swing, midi_channel, note[k], velocity[k + 9]);

                            }

                            else {

                                printf("%lu On ch=%u n=%u v=%u\n", miditime + swing, midi_channel, note[k], velocity[k]);

                            }

                        }


                        else { 

                            if (patterns[j][0][pattern][bank] == 1){

                                printf("%lu On ch=%u n=%u v=%u\n", miditime, midi_channel, note[k], velocity[k + 9]);

                            }

                            else {

                                printf("%lu On ch=%u n=%u v=%u\n", miditime, midi_channel, note[k], velocity[k]);

                            }

                        }

                    }

                }

                for (k = 1; k < 9; k++){

                    if (patterns[j][k][pattern][bank] == 1){

                        printf("%lu Off ch=%u n=%u v=0\n", miditime + 110, midi_channel, note[k]);

                    }

                }

                miditime = miditime + 120;

            }

        }

        else if ((argv[1][i] >= '0') && (argv[1][i] <= '9')){

            bank = argv[1][i] - 0x30;
        }

        else if (argv[1][i] == '-'){

            miditime = miditime + 1920;

        }
    }

    printf("%lu Meta TrkEnd\nTrkEnd\n", miditime);

    return 0;
}



void help()
{

    fprintf(stderr, "Drumz: Drum sequence generator for t2mf\n");
    fprintf(stderr, "Version 0.01 \n\n");
    fprintf(stderr, "Usage: dz <pattern> < <patternfile> > <outfile> \n");
    fprintf(stderr, "Usage: dz <pattern> <parameters> < <patternfile> > <outfile> \n\n");

    fprintf(stderr, "Pattern: sequence (a - z, -, 0 - 9)  eg. abc-2daf\n\n");

    fprintf(stderr, "Optional parameters:\n");
    fprintf(stderr, "-t   Tempo (30 - 399)  eg. -t120\n");
    fprintf(stderr, "-ts  Time Signature  eg. -ts44 or -ts4\n");
    fprintf(stderr, "-p   Midi program (0 - 127)  eg. -p0\n");
    fprintf(stderr, "-c   Midi channel (1 - 16)  eg. -c10\n");
    fprintf(stderr, "-sw  Swing (0 - 6)  eg. -sw1\n");
    fprintf(stderr, "-k   Drum kit  (0 - 127)  eg. -k1\n");
    fprintf(stderr, "-v   Midi velocities (0 - 3)  eg. -v0\n\n");

    fprintf(stderr, "Sequence:\n");
    fprintf(stderr, "a - z  Patterns\n");
    fprintf(stderr, "0 - 9  Pattern bank\n");
    fprintf(stderr, "-      No pattern (silence)\n");

    exit(1);
}

