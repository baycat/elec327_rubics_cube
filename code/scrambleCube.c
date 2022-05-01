/*
 * scrambleCube.c
 *
 *  Created on: Apr 10, 2022
 *      Author: anyss
 */

/*
 * in:  scramble status
 * out: display faces for all faces
 */

unsigned int seed_var;

void srand(int seed) {
    seed_var = (seed);
}

int f_rand(void) {
    //linear feeback shift register as ~polynomial operation
    //use seed to determine lfsr
    //initialize variables
    unsigned int lfsr = seed_var;
    unsigned int bit;
    unsigned int random_value = 0;
    unsigned int i;

    do {
        for (i = 2; i > 0; i--) {
            //polynomial implementation
            bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
            //taking mixed up back half
            lfsr = (lfsr >> 1) | (bit << 15);

            random_value = (random_value << 1) + bit;
        }
        seed_var = lfsr;
        //for our 6 faces
    } while (random_value > 5);
    random_value++;

    return random_value;
}


int m_rand(void) {
    //linear feeback shift register as ~polynomial operation
    //use seed to determine lfsr
    //initialize variables
    unsigned int lfsr = seed_var;
    unsigned int bit;
    unsigned int random_value = 0;
    unsigned int i;

    do {
        for (i = 2; i > 0; i--) {
            //polynomial implementation
            bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
            //taking mixed up back half
            lfsr = (lfsr >> 1) | (bit << 15);

            random_value = (random_value << 1) + bit;
        }
        seed_var = lfsr;
        //for our 6 faces
    } while (random_value > 5);
    random_value++;

    return random_value;
}

/*
 * Scramble cube
 *
 * - random value between 1 and 6 to choose which face moves
 * 
 * */

/*
 * - random value for potentiometer delta
 *
 * display face
 */

    for (i = 0; i < 20; i++) {
        face = f_rand();
        move = m_rand();

        implement_move(face, move);

    }