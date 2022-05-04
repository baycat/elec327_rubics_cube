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
        //for cw and ccw
    } while (random_value > 1);
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

void scramble() {
    srand();
    for (i = 0; i < 20; i++) {
        face = f_rand();
        move = m_rand();

        if ((move == 1) && (face == 0)){ //counterclockwise face turn

            //front
             LED1copy = LED1;
             LED2copy = LED2;
             LED3copy = LED3;
             LED4copy = LED4;
             LED6copy = LED6;
             LED7copy = LED7;
             LED8copy = LED8;
             LED9copy = LED9;
             //top
             LED10copy = LED10;
             LED11copy = LED11;
             LED12copy = LED12;
             //left
             LED19copy = LED19;
             LED20copy = LED20;
             LED21copy = LED21;
             //right
             LED28copy = LED28;
             LED29copy = LED29;
             LED30copy = LED30;
             //base
             LED37copy = LED37;
             LED38copy = LED38;
             LED39copy = LED39;

             //face shift
             LED1 = LED7copy;
             LED2 = LED4copy;
             LED3 = LED1copy;
             LED4 = LED8copy;
             LED6 = LED2copy;
             LED7 = LED9copy;
             LED8 = LED6copy;
             LED9 = LED3copy;
             //top front 3 become right front 3
             LED10 = LED28copy;
             LED11 = LED29copy;
             LED12 = LED30copy;
             //left front 3 become top front 3
             LED19 = LED10copy;
             LED20 = LED11copy;
             LED21 = LED12copy;
             //base front 3 become left front 3
             LED37 = LED19copy;
             LED38 = LED20copy;
             LED39 = LED21copy;
             //right front 3 become base front 3
             LED28 = LED37copy;
             LED29 = LED38copy;
             LED30 = LED39copy;

             rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9,
                                          LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18,
                                          LED19, LED20, LED21, LED22, LED23, LED24, LED25, LED26, LED27,
                                          LED28, LED29, LED30, LED31, LED32, LED33, LED34, LED35, LED36,
                                          LED37, LED38, LED39, LED40, LED41, LED42, LED43, LED44, LED45,
                                          LED46, LED47, LED48, LED49, LED50, LED51, LED52, LED53, LED54);

            wait0 = 1;
            //rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18);

        }
        else if ((move == 0) && (face == 0)){ //clockwise face turn
                LED1copy = LED1;
                LED2copy = LED2;
                LED3copy = LED3;
                LED4copy = LED4;
                LED6copy = LED6;
                LED7copy = LED7;
                LED8copy = LED8;
                LED9copy = LED9;

                //top
                LED10copy = LED10;
                LED11copy = LED11;
                LED12copy = LED12;
                //left
                LED19copy = LED19;
                LED20copy = LED20;
                LED21copy = LED21;
                //right
                LED28copy = LED28;
                LED29copy = LED29;
                LED30copy = LED30;
                //base
                LED37copy = LED37;
                LED38copy = LED38;
                LED39copy = LED39;

                //rgb_set_LEDs(LED3, LED6, LED9, LED2, LED5, LED8, LED1, LED4, LED7, LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18);

                LED1 = LED3copy;
                LED2 = LED6copy;
                LED3 = LED9copy;
                LED4 = LED2copy;
                LED6 = LED8copy;
                LED7 = LED1copy;
                LED8 = LED4copy;
                LED9 = LED7copy;

                //top front 3 become left front 3
                LED10 = LED19copy;
                LED11 = LED20copy;
                LED12 = LED21copy;
                //left front 3 become base front 3
                LED19 = LED37copy;
                LED20 = LED38copy;
                LED21 = LED39copy;
                //base front 3 become right front 3
                LED37 = LED28copy;
                LED38 = LED29copy;
                LED39 = LED30copy;
                //right front 3 become top front 3
                LED28 = LED10copy;
                LED29 = LED11copy;
                LED30 = LED12copy;
                rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9,
                             LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18,
                             LED19, LED20, LED21, LED22, LED23, LED24, LED25, LED26, LED27,
                             LED28, LED29, LED30, LED31, LED32, LED33, LED34, LED35, LED36,
                             LED37, LED38, LED39, LED40, LED41, LED42, LED43, LED44, LED45,
                             LED46, LED47, LED48, LED49, LED50, LED51, LED52, LED53, LED54);
            wait0 = 1;
            //rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18);

        }
        else if ( (move == 1) && (face = 1)){
            wait0 = 0;
        }
        else if ((move == 0) && (face == 1)){ //counterclockwise top turn
            //top
            LED10copy = LED10;
            LED11copy = LED11;
            LED12copy = LED12;
            LED13copy = LED13;
            LED15copy = LED15;
            LED16copy = LED16;
            LED17copy = LED17;
            LED18copy = LED18;
            //face
            LED7copy = LED7;
            LED8copy = LED8;
            LED9copy = LED9;
            //left
            LED19copy = LED19;
            LED22copy = LED22;
            LED25copy = LED25;
            //right
            LED30copy = LED30;
            LED33copy = LED33;
            LED36copy = LED36;
            //back
            LED52copy = LED52;
            LED53copy = LED53;
            LED54copy = LED54;

            //top shift
            LED10 = LED12copy;
            LED11 = LED15copy;
            LED12 = LED18copy;
            LED13 = LED11copy;
            LED15 = LED17copy;
            LED16 = LED10copy;
            LED17 = LED13copy;
            LED18 = LED16copy;
            //right top 3 become front top 3
            LED30 = LED9copy;
            LED33 = LED8copy;
            LED36 = LED7copy;
            //front top 3 become left top 3
            LED7 = LED19copy;
            LED8 = LED22copy;
            LED9 = LED25copy;
            //left top 3 become back top 3
            LED19 = LED52copy;
            LED22 = LED53copy;
            LED25 = LED54copy;
            //back top 3 become right top 3
            LED52 = LED36copy;
            LED53 = LED33copy;
            LED54 = LED30copy;

            rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9,
                         LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18,
                         LED19, LED20, LED21, LED22, LED23, LED24, LED25, LED26, LED27,
                         LED28, LED29, LED30, LED31, LED32, LED33, LED34, LED35, LED36,
                         LED37, LED38, LED39, LED40, LED41, LED42, LED43, LED44, LED45,
                         LED46, LED47, LED48, LED49, LED50, LED51, LED52, LED53, LED54);
            wait1 = 1;
        }
        else if ((move == 0) && (face == 2)){ //clockwise top turn

            //top
            LED10copy = LED10;
            LED11copy = LED11;
            LED12copy = LED12;
            LED13copy = LED13;
            LED15copy = LED15;
            LED16copy = LED16;
            LED17copy = LED17;
            LED18copy = LED18;
            //face
            LED7copy = LED7;
            LED8copy = LED8;
            LED9copy = LED9;
            //left
            LED19copy = LED19;
            LED22copy = LED22;
            LED25copy = LED25;
            //right
            LED30copy = LED30;
            LED33copy = LED33;
            LED36copy = LED36;
            //back
            LED52copy = LED52;
            LED53copy = LED53;
            LED54copy = LED54;

            //top shift
            LED10 = LED12copy;
            LED11 = LED15copy;
            LED12 = LED18copy;
            LED13 = LED11copy;
            LED15 = LED17copy;
            LED16 = LED10copy;
            LED17 = LED13copy;
            LED18 = LED16copy;
            //right top 3 become back top 3
            LED30 = LED54copy;
            LED33 = LED53copy;
            LED36 = LED52copy;
            //front top 3 become right top 3
            LED7 = LED36copy;
            LED8 = LED33copy;
            LED9 = LED30copy;
            //left top 3 become front top 3
            LED19 = LED7copy;
            LED22 = LED8copy;
            LED25 = LED9copy;
            //back top 3 become left top 3
            LED52 = LED19copy;
            LED53 = LED22copy;
            LED54 = LED25copy;

            rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9,
                         LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18,
                         LED19, LED20, LED21, LED22, LED23, LED24, LED25, LED26, LED27,
                         LED28, LED29, LED30, LED31, LED32, LED33, LED34, LED35, LED36,
                         LED37, LED38, LED39, LED40, LED41, LED42, LED43, LED44, LED45,
                         LED46, LED47, LED48, LED49, LED50, LED51, LED52, LED53, LED54);
            wait1 = 1;
        }
        else if ((move == 1) && (face == 2)){
            wait1 = 0;
        }
        else if ((move == 0) && (face == 3)){ //counterclockwise left turn
            LED19copy = LED19;
            LED20copy = LED20;
            LED21copy = LED21;
            LED22copy = LED22;
            LED24copy = LED24;
            LED25copy = LED25;
            LED26copy = LED26;
            LED27copy = LED27;

            //front
            LED3copy = LED3;
            LED6copy = LED6;
            LED9copy = LED9;

            //top
            LED12copy = LED12;
            LED15copy = LED15;
            LED18copy = LED18;

            //base
            LED37copy = LED37;
            LED40copy = LED40;
            LED43copy = LED43;

            //back
            LED46copy = LED46;
            LED49copy = LED49;
            LED52copy = LED52;

            //left shift
            LED19 = LED21copy;
            LED20 = LED24copy;
            LED21 = LED27copy;
            LED22 = LED20copy;
            LED24 = LED26copy;
            LED25 = LED19copy;
            LED26 = LED22copy;
            LED27 = LED25copy;

            //top becomes front
            LED12 = LED3copy;
            LED15 = LED6copy;
            LED18 = LED3copy;

            //back becomes top
            LED46 = LED18copy;
            LED49 = LED15copy;
            LED52 = LED12copy;

            //base becomes back
            LED37 = LED46copy;
            LED40 = LED49copy;
            LED43 = LED52copy;

            //front becomes base
            LED3 = LED43copy;
            LED6 = LED40copy;
            LED9 = LED37copy;

            rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9,
                         LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18,
                         LED19, LED20, LED21, LED22, LED23, LED24, LED25, LED26, LED27,
                         LED28, LED29, LED30, LED31, LED32, LED33, LED34, LED35, LED36,
                         LED37, LED38, LED39, LED40, LED41, LED42, LED43, LED44, LED45,
                         LED46, LED47, LED48, LED49, LED50, LED51, LED52, LED53, LED54);
            wait3 = 1;
        }
        else if ((move == 1) && (face == 3)){ //clockwise left turn
            LED19copy = LED19;
            LED20copy = LED20;
            LED21copy = LED21;
            LED22copy = LED22;
            LED24copy = LED24;
            LED25copy = LED25;
            LED26copy = LED26;
            LED27copy = LED27;

            //front
            LED3copy = LED3;
            LED6copy = LED6;
            LED9copy = LED9;

            //top
            LED12copy = LED12;
            LED15copy = LED15;
            LED18copy = LED18;

            //base
            LED37copy = LED37;
            LED40copy = LED40;
            LED43copy = LED43;

            //back
            LED46copy = LED46;
            LED49copy = LED49;
            LED52copy = LED52;

            //left shift
            LED19 = LED25copy;
            LED20 = LED22copy;
            LED21 = LED19copy;
            LED22 = LED26copy;
            LED24 = LED20copy;
            LED25 = LED27copy;
            LED26 = LED24copy;
            LED27 = LED21copy;

            //top becomes back
            LED12 = LED52copy;
            LED15 = LED49copy;
            LED18 = LED46copy;

            //back becomes base
            LED46 = LED37copy;
            LED49 = LED40copy;
            LED52 = LED43copy;

            //base becomes front
            LED37 = LED9copy;
            LED40 = LED6copy;
            LED43 = LED3copy;

            //front becomes top
            LED3 = LED12copy;
            LED6 = LED15copy;
            LED9 = LED18copy;

            rgb_set_LEDs(LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9,
                         LED10, LED11, LED12, LED13, LED14, LED15, LED16, LED17, LED18,
                         LED19, LED20, LED21, LED22, LED23, LED24, LED25, LED26, LED27,
                         LED28, LED29, LED30, LED31, LED32, LED33, LED34, LED35, LED36,
                         LED37, LED38, LED39, LED40, LED41, LED42, LED43, LED44, LED45,
                         LED46, LED47, LED48, LED49, LED50, LED51, LED52, LED53, LED54);

        }
        }

        else if ((move == 0) && (face == 4)){ //counterclockwise right turn
            LED28copy = LED28;
            LED29copy = LED29;
            LED30copy = LED30;
            LED31copy = LED31;
            LED33copy = LED33;
            LED34copy = LED34;
            LED35copy = LED35;
            LED36copy = LED36;

            //top
            LED10copy = LED10;
            LED13copy = LED13;
            LED16copy = LED16;

            //front
            LED1copy = LED1;
            LED4copy = LED4;
            LED7copy = LED7;

            //back
            LED48copy = LED48;
            LED51copy = LED51;
            LED54copy = LED54;

            //base
            LED39copy = LED39;
            LED42copy = LED42;
            LED45copy = LED45;

            //right shift
            LED28 = LED30copy;
            LED29 = LED33copy;
            LED30 = LED36copy;
            LED31 = LED29copy;
            LED33 = LED35copy;
            LED34 = LED28copy;
            LED35 = LED31copy;
            LED36 = LED36copy;

            //front becomes top
            LED1 = LED10copy;
            LED4 = LED13copy;
            LED7 = LED16copy;

            //top becomes back
            LED10 = LED54copy;
            LED13 = LED51copy;
            LED16 = LED48copy;

            //back becomes base
            LED54 = LED45copy;
            LED51 = LED42copy;
            LED48 = LED39copy;

            //base becomes front
            LED45 = LED1copy;
            LED42 = LED4copy;
            LED39 = LED7copy;
        }
        else if ((move == 0) && (face == 5)){ //clockwise right turn
            LED28copy = LED28;
            LED29copy = LED29;
            LED30copy = LED30;
            LED31copy = LED31;
            LED33copy = LED33;
            LED34copy = LED34;
            LED35copy = LED35;
            LED36copy = LED36;

            //top
            LED10copy = LED10;
            LED13copy = LED13;
            LED16copy = LED16;

            //front
            LED1copy = LED1;
            LED4copy = LED4;
            LED7copy = LED7;

            //back
            LED48copy = LED48;
            LED51copy = LED51;
            LED54copy = LED54;

            //base
            LED39copy = LED39;
            LED42copy = LED42;
            LED45copy = LED45;

            //right shift
            LED28 = LED34copy;
            LED29 = LED31copy;
            LED30 = LED28copy;
            LED31 = LED35copy;
            LED33 = LED29copy;
            LED34 = LED36copy;
            LED35 = LED33copy;
            LED36 = LED30copy;

            //front becomes base
            LED1 = LED45copy;
            LED4 = LED42copy;
            LED7 = LED39copy;

            //top becomes front
            LED10 = LED1copy;
            LED13 = LED4copy;
            LED16 = LED7copy;

            //back becomes top
            LED54 = LED10copy;
            LED51 = LED13copy;
            LED48 = LED16copy;

            //base becomes back
            LED45 = LED54copy;
            LED42 = LED51copy;
            LED39 = LED48copy;

        }
        else if ((move == 1) && (face == 5)){
            wait5 = 0;
        }
        else if ((move == 0) && (face == 6)){ //counterclockwise base turn
            LED37copy = LED37;
            LED38copy = LED38;
            LED39copy = LED39;
            LED40copy = LED40;
            LED42copy = LED42;
            LED43copy = LED43;
            LED44copy = LED44;
            LED45copy = LED45;

            //front
            LED1copy = LED1;
            LED2copy = LED2;
            LED3copy = LED3;

            //right
            LED28copy = LED28;
            LED31copy = LED31;
            LED34copy = LED34;

            //left
            LED21copy = LED21;
            LED24copy = LED24;
            LED27copy = LED27;

            //back
            LED46copy = LED46;
            LED47copy = LED47;
            LED48copy = LED48;

            //base shift
            LED37 = LED39copy;
            LED38 = LED42copy;
            LED39 = LED45copy;
            LED40 = LED38copy;
            LED42 = LED44copy;
            LED43 = LED37copy;
            LED44 = LED40copy;
            LED45 = LED43copy;

            //front becomes right
            LED1 = LED34copy;
            LED2 = LED31copy;
            LED3 = LED28copy;

            //right becomes back
            LED28 = LED48copy;
            LED31 = LED47copy;
            LED34 = LED46copy;

            //back becomes left
            LED48 = LED27copy;
            LED47 = LED24copy;
            LED46 = LED21copy;

            //left becomes front
            LED21 = LED1copy;
            LED24 = LED2copy;
            LED27 = LED3copy;

        }
        else if ((move == 1) && (face == 6)){ //clockwise base turn
            LED37copy = LED37;
            LED38copy = LED38;
            LED39copy = LED39;
            LED40copy = LED40;
            LED42copy = LED42;
            LED43copy = LED43;
            LED44copy = LED44;
            LED45copy = LED45;

            //front
            LED1copy = LED1;
            LED2copy = LED2;
            LED3copy = LED3;

            //right
            LED28copy = LED28;
            LED31copy = LED31;
            LED34copy = LED34;

            //left
            LED21copy = LED21;
            LED24copy = LED24;
            LED27copy = LED27;

            //back
            LED46copy = LED46;
            LED47copy = LED47;
            LED48copy = LED48;

            //base shift
            LED37 = LED43copy;
            LED38 = LED40copy;
            LED39 = LED37copy;
            LED40 = LED44copy;
            LED42 = LED38copy;
            LED43 = LED45copy;
            LED44 = LED42copy;
            LED45 = LED39copy;

            //front becomes left
            LED1 = LED21copy;
            LED2 = LED24copy;
            LED3 = LED27copy;

            //right becomes front
            LED28 = LED3copy;
            LED31 = LED2copy;
            LED34 = LED1copy;

            //back becomes right
            LED48 = LED28copy;
            LED47 = LED31copy;
            LED46 = LED34copy;

            //left becomes back
            LED21 = LED46copy;
            LED24 = LED47copy;
            LED27 = LED48copy;

        }
        else if ( (ADC10MEM > 0x00F6) && (ADC10MEM < 0x02BF) && (ADC10CTL1 == INCH_6)){
            wait6 = 0;
        }
        else if ((ADC10MEM > 0x039F) && (wait7 == 0) && (ADC10CTL1 == INCH_7)){ //counterclockwise back turn
            LED46copy = LED46;
            LED47copy = LED47;
            LED48copy = LED48;
            LED49copy = LED49;
            LED51copy = LED51;
            LED52copy = LED52;
            LED53copy = LED53;
            LED54copy = LED54;

            LED16copy = LED16;
            LED17copy = LED17;
            LED18copy = LED18;

            LED25copy = LED25;
            LED26copy = LED26;
            LED27copy = LED27;

            LED43copy = LED43;
            LED44copy = LED44;
            LED45copy = LED45;

            LED34copy = LED34;
            LED35copy = LED35;
            LED36copy = LED36;

            //back shift
            LED46 = LED48copy;
            LED47 = LED51copy;
            LED48 = LED54copy;
            LED49 = LED47copy;
            LED51 = LED53copy;
            LED52 = LED46copy;
            LED53 = LED49copy;
            LED54 = LED52copy;

            //right becomes top
            LED36 = LED18copy;
            LED35 = LED17copy;
            LED34 = LED16copy;
            //base becomes right
            LED45 = LED36copy;
            LED44 = LED35copy;
            LED43 = LED34copy;
            //left becomes base
            LED25 = LED43copy;
            LED26 = LED44copy;
            LED27 = LED45copy;
            //top becomes left
            LED16 = LED25copy;
            LED17 = LED26copy;
            LED18 = LED27copy;
        }
        else if ((ADC10MEM < 0x002A) && (wait7 == 0) && (ADC10CTL1 == INCH_7)){ //clockwise back turn
            LED46copy = LED46;
            LED47copy = LED47;
            LED48copy = LED48;
            LED49copy = LED49;
            LED51copy = LED51;
            LED52copy = LED52;
            LED53copy = LED53;
            LED54copy = LED54;

            LED16copy = LED16;
            LED17copy = LED17;
            LED18copy = LED18;

            LED25copy = LED25;
            LED26copy = LED26;
            LED27copy = LED27;

            LED43copy = LED43;
            LED44copy = LED44;
            LED45copy = LED45;

            LED34copy = LED34;
            LED35copy = LED35;
            LED36copy = LED36;

            //back shift
            LED46 = LED52copy;
            LED47 = LED49copy;
            LED48 = LED46copy;
            LED49 = LED53copy;
            LED51 = LED47copy;
            LED52 = LED54copy;
            LED53 = LED51copy;
            LED54 = LED48copy;

            //right becomes base
            LED36 = LED45copy;
            LED35 = LED44copy;
            LED34 = LED43copy;
            //base becomes left
            LED45 = LED27copy;
            LED44 = LED26copy;
            LED43 = LED25copy;
            //left becomes top
            LED25 = LED16copy;
            LED26 = LED17copy;
            LED27 = LED18copy;
            //top becomes right
            LED16 = LED34copy;
            LED17 = LED35copy;
            LED18 = LED36copy;

        }

    }
}