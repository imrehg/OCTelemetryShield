/* 
 * ITS-90 conversion constants for K-type thermocouple
 * Based on: https://www.omega.com/temperature/Z/pdf/z198-201.pdf
 */

/* temperature -> voltage 
 * range: -200C < t <= 0C
 */
const float c_0 = 0.0;
const float c_1 = 3.9450128025e1;
const float c_2 = 2.3622373598e-2;
const float c_3 = -3.2858906784e-4;
const float c_4 = -4.9904828777e-6;
const float c_5 = -6.7509059173e-8;
const float c_6 = -5.7410327428e-10;
const float c_7 = -3.1088872894e-12;
const float c_8 = -1.0451609365e-14;
const float c_9 = -1.9889266878e-17;
const float c_10 = -1.6322697486e-20;

/* temperature -> voltage 
 * range: 0C < t
 */
const float d_0 = -1.7600413686e1;
const float d_1 = 3.8921204975e1;
const float d_2 = 1.8558770032e-2;
const float d_3 = -9.9457592874e-5;
const float d_4 = 3.1840945719e-7;
const float d_5 = -5.6072844889e-10;
const float d_6 = 5.6075059059e-13;
const float d_7 = -3.2020720003e-16;
const float d_8 = 9.7151147152e-20;
const float d_9 = -1.2104721275e-23;

const float f0 = 1.185976e2;
const float f1 = -1.183432e-4;


/* voltage -> temperature
 * range v <= 0 mV
 */
const float x_0 = 0;
const float x_1 = 2.5173462e-2;
const float x_2 = -1.1662878e-6;
const float x_3 = -1.0833638e-9;
const float x_4 = -8.9773540e-13;
const float x_5 = -3.7342377e-16;
const float x_6 = -8.6632643e-20;
const float x_7 = -1.0450598e-23;
const float x_8 = -5.1920577e-28;

/* voltage -> temperature
 * range 0 < v <= 20644 mV
 */
const float y_0 = 0.0;
const float y_1 = 2.508355e-2;
const float y_2 = 7.860106e-8;
const float y_3 = -2.503131e-10;
const float y_4 = 8.315270e-14;
const float y_5 = -1.228034e-17;
const float y_6 = 9.804036e-22;
const float y_7 = -4.413030e-26;
const float y_8 = 1.057734e-30;
const float y_9 = -1.052755e-35;

