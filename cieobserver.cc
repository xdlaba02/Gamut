#include "cieobserver.h"

// 2 degree, 10 degree
const float observers[][2][3] { //360..365..830
  {{0.0001299,     3.917E-06,   0.0006061},     {1.222E-07,    1.3398E-08,   5.35027E-07},},
  {{0.0002321,     6.965E-06,   0.001086},      {9.1927E-07,   1.0065E-07,   4.0283E-06},},
  {{0.0004149,     1.239E-05,   0.001946},      {5.9586E-06,   6.511E-07,    2.61437E-05},},
  {{0.0007416,     2.202E-05,   0.003486},      {3.3266E-05,   3.625E-06,    0.00014622},},
  {{0.001368,      3.9E-05,     0.006450001},   {0.000159952,  1.7364E-05,   0.000704776},},
  {{0.002236,      6.4E-05,     0.01054999},    {0.00066244,   7.156E-05,    0.0029278},},
  {{0.004243,      0.00012,     0.02005001},    {0.0023616,    0.0002534,    0.0104822},},
  {{0.00765,       0.000217,    0.03621},       {0.0072423,    0.0007685,    0.032344},},
  {{0.01431,       0.000396,    0.06785001},    {0.0191097,    0.0020044,    0.0860109},},
  {{0.02319,       0.00064,     0.1102},        {0.0434,       0.004509,     0.19712},},
  {{0.04351,       0.00121,     0.2074},        {0.084736,     0.008756,     0.389366},},
  {{0.07763,       0.00218,     0.3713},        {0.140638,     0.014456,     0.65676},},
  {{0.13438,       0.004,       0.6456},        {0.204492,     0.021391,     0.972542},},
  {{0.21477,       0.0073,      1.0390501},     {0.264737,     0.029497,     1.2825},},
  {{0.2839,        0.0116,      1.3856},        {0.314679,     0.038676,     1.55348},},
  {{0.3285,        0.01684,     1.62296},       {0.357719,     0.049602,     1.7985},},
  {{0.34828,       0.023,       1.74706},       {0.383734,     0.062077,     1.96728},},
  {{0.34806,       0.0298,      1.7826},        {0.386726,     0.074704,     2.0273},},
  {{0.3362,        0.038,       1.77211},       {0.370702,     0.089456,     1.9948},},
  {{0.3187,        0.048,       1.7441},        {0.342957,     0.106256,     1.9007},},
  {{0.2908,        0.06,        1.6692},        {0.302273,     0.128201,     1.74537},},
  {{0.2511,        0.0739,      1.5281},        {0.254085,     0.152761,     1.5549},},
  {{0.19536,       0.09098,     1.28764},       {0.195618,     0.18519,      1.31756},},
  {{0.1421,        0.1126,      1.0419},        {0.132349,     0.21994,      1.0302},},
  {{0.09564,       0.13902,     0.8129501},     {0.080507,     0.253589,     0.772125},},
  {{0.05795001,    0.1693,      0.6162},        {0.041072,     0.297665,     0.5706},},
  {{0.03201,       0.20802,     0.46518},       {0.016172,     0.339133,     0.415254},},
  {{0.0147,        0.2586,      0.3533},        {0.005132,     0.395379,     0.302356},},
  {{0.0049,        0.323,       0.272},         {0.003816,     0.460777,     0.218502},},
  {{0.0024,        0.4073,      0.2123},        {0.015444,     0.53136,      0.159249},},
  {{0.0093,        0.503,       0.1582},        {0.037465,     0.606741,     0.112044},},
  {{0.0291,        0.6082,      0.1117},        {0.071358,     0.68566,      0.082248},},
  {{0.06327,       0.71,        0.07824999},    {0.117749,     0.761757,     0.060709},},
  {{0.1096,        0.7932,      0.05725001},    {0.172953,     0.82333,      0.04305},},
  {{0.1655,        0.862,       0.04216},       {0.236491,     0.875211,     0.030451},},
  {{0.2257499,     0.9148501,   0.02984},       {0.304213,     0.92381,      0.020584},},
  {{0.2904,        0.954,       0.0203},        {0.376772,     0.961988,     0.013676},},
  {{0.3597,        0.9803,      0.0134},        {0.451584,     0.9822,       0.007918},},
  {{0.4334499,     0.9949501,   0.008749999},   {0.529826,     0.991761,     0.003988},},
  {{0.5120501,     1,           0.005749999},   {0.616053,     0.99911,      0.001091},},
  {{0.5945,        0.995,       0.0039},        {0.705224,     0.99734,      0},},
  {{0.6784,        0.9786,      0.002749999},   {0.793832,     0.98238,      0},},
  {{0.7621,        0.952,       0.0021},        {0.878655,     0.955552,     0},},
  {{0.8425,        0.9154,      0.0018},        {0.951162,     0.915175,     0},},
  {{0.9163,        0.87,        0.001650001},   {1.01416,      0.868934,     0},},
  {{0.9786,        0.8163,      0.0014},        {1.0743,       0.825623,     0},},
  {{1.0263,        0.757,       0.0011},        {1.11852,      0.777405,     0},},
  {{1.0567,        0.6949,      0.001},         {1.1343,       0.720353,     0},},
  {{1.0622,        0.631,       0.0008},        {1.12399,      0.658341,     0},},
  {{1.0456,        0.5668,      0.0006},        {1.0891,       0.593878,     0},},
  {{1.0026,        0.503,       0.00034},       {1.03048,      0.527963,     0},},
  {{0.9384,        0.4412,      0.00024},       {0.95074,      0.461834,     0},},
  {{0.8544499,     0.381,       0.00019},       {0.856297,     0.398057,     0},},
  {{0.7514,        0.321,       0.0001},        {0.75493,      0.339554,     0},},
  {{0.6424,        0.265,       4.999999E-05},  {0.647467,     0.283493,     0},},
  {{0.5419,        0.217,       3E-05},         {0.53511,      0.228254,     0},},
  {{0.4479,        0.175,       2E-05},         {0.431567,     0.179828,     0},},
  {{0.3608,        0.1382,      1E-05},         {0.34369,      0.140211,     0},},
  {{0.2835,        0.107,       0},             {0.268329,     0.107633,     0},},
  {{0.2187,        0.0816,      0},             {0.2043,       0.081187,     0},},
  {{0.1649,        0.061,       0},             {0.152568,     0.060281,     0},},
  {{0.1212,        0.04458,     0},             {0.11221,      0.044096,     0},},
  {{0.0874,        0.032,       0},             {0.0812606,    0.0318004,    0},},
  {{0.0636,        0.0232,      0},             {0.05793,      0.0226017,    0},},
  {{0.04677,       0.017,       0},             {0.0408508,    0.0159051,    0},},
  {{0.0329,        0.01192,     0},             {0.028623,     0.0111303,    0},},
  {{0.0227,        0.00821,     0},             {0.0199413,    0.0077488,    0},},
  {{0.01584,       0.005723,    0},             {0.013842,     0.0053751,    0},},
  {{0.01135916,    0.004102,    0},             {0.00957688,   0.00371774,   0},},
  {{0.008110916,   0.002929,    0},             {0.0066052,    0.00256456,   0},},
  {{0.005790346,   0.002091,    0},             {0.00455263,   0.00176847,   0},},
  {{0.004106457,   0.001484,    0},             {0.0031447,    0.00122239,   0},},
  {{0.002899327,   0.001047,    0},             {0.00217496,   0.00084619,   0},},
  {{0.00204919,    0.00074,     0},             {0.0015057,    0.00058644,   0},},
  {{0.001439971,   0.00052,     0},             {0.00104476,   0.00040741,   0},},
  {{0.0009999493,  0.0003611,   0},             {0.00072745,   0.000284041,  0},},
  {{0.0006900786,  0.0002492,   0},             {0.000508258,  0.00019873,   0},},
  {{0.0004760213,  0.0001719,   0},             {0.00035638,   0.00013955,   0},},
  {{0.0003323011,  0.00012,     0},             {0.000250969,  9.8428E-05,   0},},
  {{0.0002348261,  8.48E-05,    0},             {0.00017773,   6.9819E-05,   0},},
  {{0.0001661505,  6E-05,       0},             {0.00012639,   4.9737E-05,   0},},
  {{0.000117413,   4.24E-05,    0},             {9.0151E-05,   3.55405E-05,  0},},
  {{8.307527E-05,  3E-05,       0},             {6.45258E-05,  2.5486E-05,   0},},
  {{5.870652E-05,  2.12E-05,    0},             {4.6339E-05,   1.83384E-05,  0},},
  {{4.150994E-05,  1.499E-05,   0},             {3.34117E-05,  1.3249E-05,   0},},
  {{2.935326E-05,  1.06E-05,    0},             {2.4209E-05,   9.6196E-06,   0},},
  {{2.067383E-05,  7.4657E-06,  0},             {1.76115E-05,  7.0128E-06,   0},},
  {{1.455977E-05,  5.2578E-06,  0},             {1.2855E-05,   5.1298E-06,   0},},
  {{1.025398E-05,  3.7029E-06,  0},             {9.41363E-06,  3.76473E-06,  0},},
  {{7.221456E-06,  2.6078E-06,  0},             {6.913E-06,    2.77081E-06,  0},},
  {{5.085868E-06,  1.8366E-06,  0},             {5.09347E-06,  2.04613E-06,  0},},
  {{3.581652E-06,  1.2934E-06,  0},             {3.7671E-06,   1.51677E-06,  0},},
  {{2.522525E-06,  9.1093E-07,  0},             {2.79531E-06,  1.12809E-06,  0},},
  {{1.776509E-06,  6.4153E-07,  0},             {2.082E-06,    8.4216E-07,   0},},
  {{1.251141E-06,  4.5181E-07,  0},             {1.55314E-06,  6.297E-07,    0},},
};

// lamda, Standard Illuminant A, Standard Illuminant D65, Illuminant C, IlluminantD50, IlluminantD55, IlluminantD75 */
const float illuminat_spectrum[][7] = {
  {300,0.00930f,0.00034f,0.00000f,0.00019f,0.00024f,0.00043f},
  {305,0.01128f,0.01664f,0.00000f,0.01035f,0.01048f,0.02588f},
  {310,0.01358f,0.03295f,0.00000f,0.02051f,0.02072f,0.05133f},
  {315,0.01622f,0.11765f,0.00000f,0.04914f,0.06648f,0.17470f},
  {320,0.01925f,0.20236f,0.00010f,0.07778f,0.11224f,0.29808f},
  {325,0.02270f,0.28645f,0.00200f,0.11263f,0.15936f,0.42369f},
  {330,0.02660f,0.37054f,0.00400f,0.14748f,0.20647f,0.54930f},
  {335,0.03099f,0.38501f,0.01550f,0.16348f,0.22266f,0.56095f},
  {340,0.03590f,0.39949f,0.02700f,0.17948f,0.23885f,0.57259f},
  {345,0.04136f,0.42430f,0.04850f,0.19479f,0.25851f,0.60000f},
  {350,0.04742f,0.44912f,0.07000f,0.21010f,0.27817f,0.62740f},
  {355,0.05411f,0.45775f,0.09950f,0.22476f,0.29219f,0.62861f},
  {360,0.06145f,0.46638f,0.12900f,0.23942f,0.30621f,0.62982f},
  {365,0.06947f,0.49364f,0.17200f,0.25451f,0.32464f,0.66647f},
  {370,0.07821f,0.52089f,0.21400f,0.26961f,0.34308f,0.70312f},
  {375,0.08770f,0.51032f,0.27500f,0.25724f,0.33446f,0.68507f},
  {380,0.09795f,0.49976f,0.33000f,0.24488f,0.32584f,0.66703f},
  {385,0.10900f,0.52312f,0.39920f,0.27179f,0.35335f,0.68333f},
  {390,0.12085f,0.54648f,0.47400f,0.29871f,0.38087f,0.69963f},
  {395,0.13354f,0.68702f,0.55170f,0.39589f,0.49518f,0.85946f},
  {400,0.14708f,0.82755f,0.63300f,0.49308f,0.60949f,1.01929f},
  {405,0.16148f,0.87120f,0.71810f,0.52910f,0.64751f,1.06911f},
  {410,0.17675f,0.91486f,0.80600f,0.56513f,0.68554f,1.11894f},
  {415,0.19291f,0.92459f,0.89530f,0.58273f,0.70065f,1.12346f},
  {420,0.20995f,0.93432f,0.98100f,0.60034f,0.71577f,1.12798f},
  {425,0.22788f,0.90057f,1.05800f,0.58926f,0.69746f,1.07945f},
  {430,0.24671f,0.86682f,1.12400f,0.57818f,0.67914f,1.03092f},
  {435,0.26643f,0.95774f,1.17750f,0.66321f,0.76760f,1.12145f},
  {440,0.28703f,1.04865f,1.21500f,0.74825f,0.85605f,1.21198f},
  {445,0.30851f,1.10936f,1.23450f,0.81036f,0.91799f,1.27104f},
  {450,0.33086f,1.17008f,1.24000f,0.87247f,0.97993f,1.33010f},
  {455,0.35407f,1.17410f,1.23600f,0.88930f,0.99228f,1.32682f},
  {460,0.37812f,1.17812f,1.23100f,0.90612f,1.00463f,1.32355f},
  {465,0.40300f,1.16336f,1.23300f,0.90990f,1.00188f,1.29838f},
  {470,0.42869f,1.14861f,1.23800f,0.91368f,0.99913f,1.27322f},
  {475,0.45517f,1.15392f,1.24090f,0.93238f,1.01326f,1.27061f},
  {480,0.48242f,1.15923f,1.23900f,0.95109f,1.02739f,1.26800f},
  {485,0.51042f,1.12367f,1.22920f,0.93536f,1.00409f,1.22291f},
  {490,0.53913f,1.08811f,1.20700f,0.91963f,0.98078f,1.17783f},
  {495,0.56854f,1.09082f,1.16900f,0.93843f,0.99379f,1.17186f},
  {500,0.59861f,1.09354f,1.12100f,0.95724f,1.00680f,1.16589f},
  {505,0.62932f,1.08578f,1.06980f,0.96169f,1.00688f,1.15146f},
  {510,0.66064f,1.07802f,1.02300f,0.96613f,1.00695f,1.13702f},
  {515,0.69253f,1.06296f,0.98810f,0.96871f,1.00341f,1.11181f},
  {520,0.72496f,1.04790f,0.96900f,0.97129f,0.99987f,1.08659f},
  {525,0.75790f,1.06239f,0.96780f,0.99614f,1.02098f,1.09552f},
  {530,0.79133f,1.07689f,0.98000f,1.02099f,1.04210f,1.10445f},
  {535,0.82519f,1.06047f,0.99940f,1.01427f,1.03156f,1.08367f},
  {540,0.85947f,1.04405f,1.02100f,1.00755f,1.02102f,1.06289f},
  {545,0.89412f,1.04225f,1.03950f,1.01536f,1.02535f,1.05596f},
  {550,0.92912f,1.04046f,1.05200f,1.02317f,1.02968f,1.04904f},
  {555,0.96442f,1.02023f,1.05670f,1.01159f,1.01484f,1.02452f},
  {560,1.00000f,1.00000f,1.05300f,1.00000f,1.00000f,1.00000f},
  {565,1.03582f,0.98167f,1.04110f,0.98868f,0.98608f,0.97808f},
  {570,1.07184f,0.96334f,1.02300f,0.97735f,0.97216f,0.95616f},
  {575,1.10803f,0.96061f,1.00150f,0.98327f,0.97482f,0.94914f},
  {580,1.14436f,0.95788f,0.97800f,0.98918f,0.97749f,0.94213f},
  {585,1.18080f,0.92237f,0.95430f,0.96208f,0.94590f,0.90605f},
  {590,1.21731f,0.88686f,0.93200f,0.93499f,0.91432f,0.86997f},
  {595,1.25386f,0.89346f,0.91220f,0.95593f,0.92926f,0.87112f},
  {600,1.29043f,0.90006f,0.89700f,0.97688f,0.94419f,0.87227f},
  {605,1.32697f,0.89803f,0.88830f,0.98478f,0.94780f,0.86684f},
  {610,1.36346f,0.89599f,0.88400f,0.99269f,0.95140f,0.86140f},
  {615,1.39988f,0.88649f,0.88190f,0.99155f,0.94680f,0.84861f},
  {620,1.43618f,0.87699f,0.88100f,0.99042f,0.94220f,0.83581f},
  {625,1.47235f,0.85494f,0.88060f,0.97382f,0.92334f,0.81164f},
  {630,1.50836f,0.83289f,0.88000f,0.95722f,0.90448f,0.78747f},
  {635,1.54418f,0.83494f,0.87860f,0.97290f,0.91389f,0.78587f},
  {640,1.57979f,0.83699f,0.87800f,0.98857f,0.92330f,0.78428f},
  {645,1.61516f,0.81863f,0.87990f,0.97262f,0.90592f,0.76614f},
  {650,1.65028f,0.80027f,0.88200f,0.95667f,0.88854f,0.74801f},
  {655,1.68510f,0.80121f,0.88200f,0.96929f,0.89586f,0.74562f},
  {660,1.71963f,0.80215f,0.87900f,0.98190f,0.90317f,0.74324f},
  {665,1.75383f,0.81246f,0.87220f,1.00597f,0.92133f,0.74873f},
  {670,1.78769f,0.82278f,0.86300f,1.03003f,0.93950f,0.75422f},
  {675,1.82118f,0.80281f,0.85300f,1.01068f,0.91953f,0.73499f},
  {680,1.85429f,0.78284f,0.84000f,0.99133f,0.89956f,0.71576f},
  {685,1.88701f,0.74003f,0.82210f,0.93257f,0.84817f,0.67714f},
  {690,1.91931f,0.69721f,0.80200f,0.87381f,0.79677f,0.63852f},
  {695,1.95118f,0.70665f,0.78240f,0.89492f,0.81258f,0.64464f},
  {700,1.98261f,0.71609f,0.76300f,0.91604f,0.82840f,0.65076f},
  {705,2.01359f,0.72979f,0.74360f,0.92246f,0.83842f,0.66573f},
  {710,2.04409f,0.74349f,0.72400f,0.92889f,0.84844f,0.68070f},
  {715,2.07411f,0.67977f,0.70400f,0.84872f,0.77539f,0.62256f},
  {720,2.10365f,0.61604f,0.68300f,0.76854f,0.70235f,0.56443f},
  {725,2.13268f,0.65745f,0.66300f,0.81683f,0.74768f,0.60343f},
  {730,2.16120f,0.69886f,0.64400f,0.86511f,0.79301f,0.64242f},
  {735,2.18920f,0.72486f,0.62800f,0.89546f,0.82147f,0.66697f},
  {740,2.21667f,0.75087f,0.61500f,0.92580f,0.84993f,0.69151f},
  {745,2.24361f,0.69340f,0.60200f,0.85405f,0.78437f,0.63890f},
  {750,2.27000f,0.63593f,0.59200f,0.78230f,0.71880f,0.58629f},
  {755,2.29585f,0.55005f,0.58500f,0.67961f,0.62337f,0.50623f},
  {760,2.32115f,0.46418f,0.58100f,0.57692f,0.52793f,0.42617f},
  {765,2.34589f,0.56612f,0.58000f,0.70307f,0.64360f,0.51985f},
  {770,2.37008f,0.66805f,0.58200f,0.82923f,0.75927f,0.61352f},
  {775,2.39370f,0.65094f,0.58500f,0.80599f,0.73872f,0.59838f},
  {780,2.41675f,0.63383f,0.59100f,0.78274f,0.71818f,0.58324f}
};

void getCIEXYZ(float lambda, int observer, float &x, float &y, float &z) {
  int N = (830 - 360) / 5 + 1;

  x = getFunctionValue(360, 5, [&](int index) { return observers[index][observer][0]; }, N, lambda);
  y = getFunctionValue(360, 5, [&](int index) { return observers[index][observer][1]; }, N, lambda);
  z = getFunctionValue(360, 5, [&](int index) { return observers[index][observer][2]; }, N, lambda);
}

float getIlluminant(float lambda, int illuminant) {
  return getFunctionValue(300, 5, [&](int index) { return illuminat_spectrum[index][1 + illuminant]; }, (780 - 300) / 5 + 1, lambda);
}
