
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2019 John Maddock
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DETIAL_1F1_MAP_NEG_B_HPP
#define BOOST_MATH_DETIAL_1F1_MAP_NEG_B_HPP

namespace boost {
   namespace math {
      namespace detail {
         //
         // hypergeometric_1F1_negative_b_recurrence_region maps out the domains over which
         // forward and backwards recurrences are stable when b < 0.
         // Returns -1, 0, or 1:
         // -1:  Backwards recurrence is stable.
         // +1:  Forwards recurrence is stable.
         //  0:  Neither recurrence is stable.
         //
         template <class T>
         int hypergeometric_1F1_negative_b_recurrence_region(const T& a, const T& b, const T& z)
         {
            BOOST_MATH_STD_USING
            static const double domain[][4] = {
               { 1e-300, -1000000.1, 278609.88983674475, 465687},
               { 1e-300, -400000.03999999998, 111530.83622048119, 111544},
               { 1e-300, -160000.016, 44699.113858309654, 44712},
               { 1e-300, -64000.006399999998, 17966.035866477272, 17980},
               { 1e-300, -25600.002560000001, 7273.793013139204, 7287},
               { 1e-300, -10240.001024000001, 2998.0791015625, 3012},
               { 1e-300, -4096.0004096000002, 1291.0461647727273, 1306},
               { 1e-300, -1638.40016384, 619.421875, 636},
               { 1e-300, -655.36006553599998, 374.62926136363637, 397},
               { 1e-300, -262.14402621440001, 335.29958677685943, 370},
               { 1e-300, -104.85761048576001, 412.83057851239664, 462},
               { 1e-300, -41.943044194304001, 513.00603693181824, 570},
               { 1e-300, -16.777217677721602, 584.14449896694214, 644},
               { 1e-300, -6.7108870710886404, 623.30417097107443, 684},
               { 1e-300, -2.6843548284354561, 642.31960227272725, 704},
               { 1e-300, -1.0737419313741825, 650.20738636363626, 711},
               { 1.0000000000000001e-275, -1000000.1, 278597.3203069513, 448872},
               { 1.0000000000000001e-275, -400000.03999999998, 111518.14741654831, 111531},
               { 1.0000000000000001e-275, -160000.016, 44686.621781782669, 44700},
               { 1.0000000000000001e-275, -64000.006399999998, 17953.944740988994, 17967},
               { 1.0000000000000001e-275, -25600.002560000001, 7261.1431107954559, 7274},
               { 1.0000000000000001e-275, -10240.001024000001, 2985.014559659091, 2999},
               { 1.0000000000000001e-275, -4096.0004096000002, 1277.4573863636363, 1292},
               { 1.0000000000000001e-275, -1638.40016384, 603.88778409090912, 620},
               { 1.0000000000000001e-275, -655.36006553599998, 354.10653409090912, 376},
               { 1.0000000000000001e-275, -262.14402621440001, 303.91367510330571, 337},
               { 1.0000000000000001e-275, -104.85761048576001, 367.0454545454545, 416},
               { 1.0000000000000001e-275, -41.943044194304001, 460.06028861053716, 516},
               { 1.0000000000000001e-275, -16.777217677721602, 528.36389462809916, 588},
               { 1.0000000000000001e-275, -6.7108870710886404, 566.33555010330565, 627},
               { 1.0000000000000001e-275, -2.6843548284354561, 585.32541322314046, 646},
               { 1.0000000000000001e-275, -1.0737419313741825, 593.0082967458676, 654},
               { 1.0000000000000002e-250, -1000000.1, 278584.75303113955, 431059},
               { 1.0000000000000002e-250, -400000.03999999998, 111505.53022349965, 111519},
               { 1.0000000000000002e-250, -160000.016, 44674.060190374199, 44687},
               { 1.0000000000000002e-250, -64000.006399999998, 17941.25452769886, 17954},
               { 1.0000000000000002e-250, -25600.002560000001, 7248.2002840909081, 7262},
               { 1.0000000000000002e-250, -10240.001024000001, 2972.017267400568, 2985},
               { 1.0000000000000002e-250, -4096.0004096000002, 1263.6363636363637, 1278},
               { 1.0000000000000002e-250, -1638.40016384, 588.35369318181824, 604},
               { 1.0000000000000002e-250, -655.36006553599998, 334.18039772727275, 355},
               { 1.0000000000000002e-250, -262.14402621440001, 273.7357954545455, 306},
               { 1.0000000000000002e-250, -104.85761048576001, 323.05010330578506, 370},
               { 1.0000000000000002e-250, -41.943044194304001, 407.41541838842977, 463},
               { 1.0000000000000002e-250, -16.777217677721602, 472.78376807851242, 532},
               { 1.0000000000000002e-250, -6.7108870710886404, 509.47443181818176, 570},
               { 1.0000000000000002e-250, -2.6843548284354561, 528.11466942148763, 589},
               { 1.0000000000000002e-250, -1.0737419313741825, 535.52815082644634, 596},
               { 1.0000000000000003e-225, -1000000.1, 278572.12184906006, 278585},
               { 1.0000000000000003e-225, -400000.03999999998, 111493.21068649805, 551165},
               { 1.0000000000000003e-225, -160000.016, 44661.126509232956, 44674},
               { 1.0000000000000003e-225, -64000.006399999998, 17928.069602272728, 17942},
               { 1.0000000000000003e-225, -25600.002560000001, 7235.550426136364, 7249},
               { 1.0000000000000003e-225, -10240.001024000001, 2959.153053977273, 2973},
               { 1.0000000000000003e-225, -4096.0004096000002, 1250.2649147727275, 1264},
               { 1.0000000000000003e-225, -1638.40016384, 573.37073863636363, 589},
               { 1.0000000000000003e-225, -655.36006553599998, 315.21946022727275, 335},
               { 1.0000000000000003e-225, -262.14402621440001, 245.11137654958674, 275},
               { 1.0000000000000003e-225, -104.85761048576001, 280.71022727272725, 326},
               { 1.0000000000000003e-225, -41.943044194304001, 355.45519111570246, 411},
               { 1.0000000000000003e-225, -16.777217677721602, 417.41670971074382, 476},
               { 1.0000000000000003e-225, -6.7108870710886404, 452.71984762396687, 513},
               { 1.0000000000000003e-225, -2.6843548284354561, 470.45648243801656, 532},
               { 1.0000000000000003e-225, -1.0737419313741825, 478.06438855888422, 539},
               { 1.0000000000000004e-200, -1000000.1, 278559.54284667969, 278573},
               { 1.0000000000000004e-200, -400000.03999999998, 111480.15247691762, 111493},
               { 1.0000000000000004e-200, -160000.016, 44648.944635564636, 44662},
               { 1.0000000000000004e-200, -64000.006399999998, 17916.076071999294, 17929},
               { 1.0000000000000004e-200, -25600.002560000001, 7223.06005859375, 7236},
               { 1.0000000000000004e-200, -10240.001024000001, 2946.222301136364, 2960},
               { 1.0000000000000004e-200, -4096.0004096000002, 1236.0916193181818, 1251},
               { 1.0000000000000004e-200, -1638.40016384, 558.40909090909076, 574},
               { 1.0000000000000004e-200, -655.36006553599998, 297.05220170454544, 316},
               { 1.0000000000000004e-200, -262.14402621440001, 218.16438533057845, 247},
               { 1.0000000000000004e-200, -104.85761048576001, 239.76949896694211, 283},
               { 1.0000000000000004e-200, -41.943044194304001, 304.40728305785115, 359},
               { 1.0000000000000004e-200, -16.777217677721602, 362.01349431818181, 421},
               { 1.0000000000000004e-200, -6.7108870710886404, 396.18123708677683, 456},
               { 1.0000000000000004e-200, -2.6843548284354561, 413.36518595041321, 474},
               { 1.0000000000000004e-200, -1.0737419313741825, 420.31249999999994, 482},
               { 1.0000000000000006e-175, -1000000.1, 278547.12638697342, 465687},
               { 1.0000000000000006e-175, -400000.03999999998, 111468.15407492899, 111481},
               { 1.0000000000000006e-175, -160000.016, 44636.134832208802, 44649},
               { 1.0000000000000006e-175, -64000.006399999998, 17903.091796875, 17917},
               { 1.0000000000000006e-175, -25600.002560000001, 7210.247247869318, 7223},
               { 1.0000000000000006e-175, -10240.001024000001, 2933.2915482954545, 2947},
               { 1.0000000000000006e-175, -4096.0004096000002, 1223.600497159091, 1237},
               { 1.0000000000000006e-175, -1638.40016384, 544.06640625, 559},
               { 1.0000000000000006e-175, -655.36006553599998, 279.11931818181813, 298},
               { 1.0000000000000006e-175, -262.14402621440001, 192.94921875, 220},
               { 1.0000000000000006e-175, -104.85761048576001, 200.78641528925618, 242},
               { 1.0000000000000006e-175, -41.943044194304001, 254.19679752066114, 308},
               { 1.0000000000000006e-175, -16.777217677721602, 307.10227272727263, 366},
               { 1.0000000000000006e-175, -6.7108870710886404, 339.36918904958679, 400},
               { 1.0000000000000006e-175, -2.6843548284354561, 356.1554106404958, 417},
               { 1.0000000000000006e-175, -1.0737419313741825, 363.13694473140492, 424},
               { 1.0000000000000007e-150, -1000000.1, 278534.48812689661, 448872},
               { 1.0000000000000007e-150, -400000.03999999998, 111455.15580610794, 111468},
               { 1.0000000000000007e-150, -160000.016, 44623.643454811798, 44637},
               { 1.0000000000000007e-150, -64000.006399999998, 17891.00373493541, 17904},
               { 1.0000000000000007e-150, -25600.002560000001, 7197.631392045454, 7211},
               { 1.0000000000000007e-150, -10240.001024000001, 2920.3607954545455, 2934},
               { 1.0000000000000007e-150, -4096.0004096000002, 1210.3267045454545, 1224},
               { 1.0000000000000007e-150, -1638.40016384, 530.0033735795455, 545},
               { 1.0000000000000007e-150, -655.36006553599998, 262.37215909090907, 280},
               { 1.0000000000000007e-150, -262.14402621440001, 169.07024793388427, 194},
               { 1.0000000000000007e-150, -104.85761048576001, 164.12706611570246, 203},
               { 1.0000000000000007e-150, -41.943044194304001, 206.02079028925615, 258},
               { 1.0000000000000007e-150, -16.777217677721602, 253.0191115702479, 311},
               { 1.0000000000000007e-150, -6.7108870710886404, 283.23056559917353, 343},
               { 1.0000000000000007e-150, -2.6843548284354561, 299.29041838842977, 360},
               { 1.0000000000000007e-150, -1.0737419313741825, 305.7925490702479, 367},
               { 1.0000000000000008e-125, -1000000.1, 278522.04145396838, 285024},
               { 1.0000000000000008e-125, -400000.03999999998, 111443.00279374557, 111456},
               { 1.0000000000000008e-125, -160000.016, 44611.143155184654, 44624},
               { 1.0000000000000008e-125, -64000.006399999998, 17878.306263316765, 17891},
               { 1.0000000000000008e-125, -25600.002560000001, 7185.1384943181802, 7198},
               { 1.0000000000000008e-125, -10240.001024000001, 2907.430042613636, 2921},
               { 1.0000000000000008e-125, -4096.0004096000002, 1197.0621448863635, 1211},
               { 1.0000000000000008e-125, -1638.40016384, 516.05983664772725, 531},
               { 1.0000000000000008e-125, -655.36006553599998, 246.17897727272725, 263},
               { 1.0000000000000008e-125, -262.14402621440001, 147.2197830578512, 171},
               { 1.0000000000000008e-125, -104.85761048576001, 130.599173553719, 166},
               { 1.0000000000000008e-125, -41.943044194304001, 159.12190082644628, 209},
               { 1.0000000000000008e-125, -16.777217677721602, 199.5635330578512, 256},
               { 1.0000000000000008e-125, -6.7108870710886404, 227.1807205578512, 287},
               { 1.0000000000000008e-125, -2.6843548284354561, 242.41670971074376, 303},
               { 1.0000000000000008e-125, -1.0737419313741825, 248.39036673553716, 309},
               { 1.0000000000000009e-100, -1000000.1, 278509.36086203833, 278546},
               { 1.0000000000000009e-100, -400000.03999999998, 111430.10303574696, 551165},
               { 1.0000000000000009e-100, -160000.016, 44598.652055220169, 44612},
               { 1.0000000000000009e-100, -64000.006399999998, 17865.125532670456, 17879},
               { 1.0000000000000009e-100, -25600.002560000001, 7172.046519886364, 7186},
               { 1.0000000000000009e-100, -10240.001024000001, 2895.015980113636, 2908},
               { 1.0000000000000009e-100, -4096.0004096000002, 1184.2329545454545, 1198},
               { 1.0000000000000009e-100, -1638.40016384, 502.04403409090901, 517},
               { 1.0000000000000009e-100, -655.36006553599998, 231.13849431818178, 247},
               { 1.0000000000000009e-100, -262.14402621440001, 128.02290482954544, 149},
               { 1.0000000000000009e-100, -104.85761048576001, 100.76188016528923, 133},
               { 1.0000000000000009e-100, -41.943044194304001, 115.10072314049584, 162},
               { 1.0000000000000009e-100, -16.777217677721602, 147.05255681818178, 203},
               { 1.0000000000000009e-100, -6.7108870710886404, 171.19963842975204, 231},
               { 1.0000000000000009e-100, -2.6843548284354561, 185.58367768595039, 246},
               { 1.0000000000000009e-100, -1.0737419313741825, 191.0575929752066, 252},
               { 1.0000000000000009e-75, -1000000.1, 278497.00512279174, 278510},
               { 1.0000000000000009e-75, -400000.03999999998, 111417.96751369131, 111431},
               { 1.0000000000000009e-75, -160000.016, 44586.151478160507, 44599},
               { 1.0000000000000009e-75, -64000.006399999998, 17853.128506747154, 17866},
               { 1.0000000000000009e-75, -25600.002560000001, 7160.0009918212891, 7173},
               { 1.0000000000000009e-75, -10240.001024000001, 2882.563210227273, 2896},
               { 1.0000000000000009e-75, -4096.0004096000002, 1171.4037642045455, 1185},
               { 1.0000000000000009e-75, -1638.40016384, 489.03941761363637, 503},
               { 1.0000000000000009e-75, -655.36006553599998, 216.05113636363637, 232},
               { 1.0000000000000009e-75, -262.14402621440001, 110.08296745867767, 129},
               { 1.0000000000000009e-75, -104.85761048576001, 74.400826446280988, 102},
               { 1.0000000000000009e-75, -41.943044194304001, 75.619834710743788, 118},
               { 1.0000000000000009e-75, -16.777217677721602, 96.373966942148741, 150},
               { 1.0000000000000009e-75, -6.7108870710886404, 116.33910123966942, 175},
               { 1.0000000000000009e-75, -2.6843548284354561, 129.00947507747935, 189},
               { 1.0000000000000009e-75, -1.0737419313741825, 134.06379132231399, 195},
               { 1.0000000000000011e-50, -1000000.1, 278484.14271457132, 465687},
               { 1.0000000000000011e-50, -400000.03999999998, 111405.16246448863, 111418},
               { 1.0000000000000011e-50, -160000.016, 44573.165838068184, 44587},
               { 1.0000000000000011e-50, -64000.006399999998, 17840.147727272728, 17854},
               { 1.0000000000000011e-50, -25600.002560000001, 7147.375887784091, 7160},
               { 1.0000000000000011e-50, -10240.001024000001, 2869.888583096591, 2883},
               { 1.0000000000000011e-50, -4096.0004096000002, 1158.1576704545455, 1172},
               { 1.0000000000000011e-50, -1638.40016384, 476.00257457386363, 490},
               { 1.0000000000000011e-50, -655.36006553599998, 202.20170454545453, 217},
               { 1.0000000000000011e-50, -262.14402621440001, 94.02682722107437, 111},
               { 1.0000000000000011e-50, -104.85761048576001, 53.0810950413223, 76},
               { 1.0000000000000011e-50, -41.943044194304001, 42.355371900826441, 78},
               { 1.0000000000000011e-50, -16.777217677721602, 50.051652892561975, 100},
               { 1.0000000000000011e-50, -6.7108870710886404, 63.174070247933884, 120},
               { 1.0000000000000011e-50, -2.6843548284354561, 72.956805268595033, 132},
               { 1.0000000000000011e-50, -1.0737419313741825, 77.104855371900811, 138},
               { 1.0000000000000012e-25, -1000000.1, 278471.90274041548, 448844},
               { 1.0000000000000012e-25, -400000.03999999998, 111392.85056374289, 111423},
               { 1.0000000000000012e-25, -160000.016, 44561.0361328125, 44574},
               { 1.0000000000000012e-25, -64000.006399999998, 17828.149314186794, 17841},
               { 1.0000000000000012e-25, -25600.002560000001, 7134.765625, 7148},
               { 1.0000000000000012e-25, -10240.001024000001, 2857.211647727273, 2870},
               { 1.0000000000000012e-25, -4096.0004096000002, 1146.1576704545453, 1159},
               { 1.0000000000000012e-25, -1638.40016384, 463.0625, 476},
               { 1.0000000000000012e-25, -655.36006553599998, 189.27556818181819, 203},
               { 1.0000000000000012e-25, -262.14402621440001, 79.163223140495859, 95},
               { 1.0000000000000012e-25, -104.85761048576001, 36.15702479338843, 54},
               { 1.0000000000000012e-25, -41.943044194304001, 19.008264462809912, 44},
               { 1.0000000000000012e-25, -16.777217677721602, 14.220686983471072, 53},
               { 1.0000000000000012e-25, -6.7108870710886404, 15.207081141998497, 66},
               { 1.0000000000000012e-25, -2.6843548284354561, 19.000046957175051, 76},
               { 1.0000000000000012e-25, -1.0737419313741825, 21.00738364892468, 81},
               { 1, -1000000.1, 278455, 285026},
               { 1, -400000.03999999998, 111376, 111392},
               { 1, -160000.016, 44544, 44561},
               { 1, -64000.006399999998, 17812, 17828},
               { 1, -25600.002560000001, 7119, 7135},
               { 1, -10240.001024000001, 2841, 2858},
               { 1, -4096.0004096000002, 1130, 1147},
               { 1, -1638.40016384, 447, 464},
               { 1, -655.36006553599998, 174, 190},
               { 1, -262.14402621440001, 64, 81},
               { 1, -104.85761048576001, 21, 37},
               { 1, -41.943044194304001, 5, 20},
               { 1, -16.777217677721602, 0, 16},
               { 1, -6.7108870710886404, 0, 17},
               { 1, -2.6843548284354561, 0, 20},
               { 1, -1.0737419313741825, 0, 21},
               { 2.5, -1000000.1, 278450, 278466},
               { 2.5, -400000.03999999998, 111372, 111388},
               { 2.5, -160000.016, 44540, 44557},
               { 2.5, -64000.006399999998, 17808, 17824},
               { 2.5, -25600.002560000001, 7115, 7131},
               { 2.5, -10240.001024000001, 2838, 2854},
               { 2.5, -4096.0004096000002, 1127, 1144},
               { 2.5, -1638.40016384, 445, 461},
               { 2.5, -655.36006553599998, 172, 188},
               { 2.5, -262.14402621440001, 63, 79},
               { 2.5, -104.85761048576001, 20, 35},
               { 2.5, -41.943044194304001, 4, 19},
               { 2.5, -16.777217677721602, 0, 13},
               { 2.5, -6.7108870710886404, 0, 13},
               { 2.5, -2.6843548284354561, 0, 15},
               { 2.5, -1.0737419313741825, 2, 16},
               { 6.25, -1000000.1, 278440, 278456},
               { 6.25, -400000.03999999998, 111362, 111378},
               { 6.25, -160000.016, 44531, 44548},
               { 6.25, -64000.006399999998, 17800, 17816},
               { 6.25, -25600.002560000001, 7108, 7124},
               { 6.25, -10240.001024000001, 2831, 2848},
               { 6.25, -4096.0004096000002, 1121, 1138},
               { 6.25, -1638.40016384, 440, 456},
               { 6.25, -655.36006553599998, 167, 183},
               { 6.25, -262.14402621440001, 59, 75},
               { 6.25, -104.85761048576001, 18, 32},
               { 6.25, -41.943044194304001, 3, 16},
               { 6.25, -16.777217677721602, 0, 10},
               { 6.25, -6.7108870710886404, 0, 9},
               { 6.25, -2.6843548284354561, 0, 9},
               { 6.25, -1.0737419313741825, 4, 9},
               { 15.625, -1000000.1, 278415, 278432},
               { 15.625, -400000.03999999998, 111339, 111425},
               { 15.625, -160000.016, 44510, 44527},
               { 15.625, -64000.006399999998, 17781, 17797},
               { 15.625, -25600.002560000001, 7091, 7107},
               { 15.625, -10240.001024000001, 2816, 2833},
               { 15.625, -4096.0004096000002, 1108, 1125},
               { 15.625, -1638.40016384, 429, 445},
               { 15.625, -655.36006553599998, 159, 174},
               { 15.625, -262.14402621440001, 53, 67},
               { 15.625, -104.85761048576001, 14, 27},
               { 15.625, -41.943044194304001, 2, 11},
               { 15.625, -16.777217677721602, 0, 7},
               { 15.625, -6.7108870710886404, 0, 5},
               { 15.625, -2.6843548284354561, 5, 5},
               { 15.625, -1.0737419313741825, 5, 5},
               { 39.0625, -1000000.1, 278359, 431061},
               { 39.0625, -400000.03999999998, 111287, 111304},
               { 39.0625, -160000.016, 44463, 44480},
               { 39.0625, -64000.006399999998, 17738, 17755},
               { 39.0625, -25600.002560000001, 7053, 7069},
               { 39.0625, -10240.001024000001, 2784, 2800},
               { 39.0625, -4096.0004096000002, 1081, 1097},
               { 39.0625, -1638.40016384, 407, 422},
               { 39.0625, -655.36006553599998, 143, 157},
               { 39.0625, -262.14402621440001, 43, 56},
               { 39.0625, -104.85761048576001, 10, 19},
               { 39.0625, -41.943044194304001, 0, 7},
               { 39.0625, -16.777217677721602, 0, 4},
               { 39.0625, -6.7108870710886404, 0, 3},
               { 39.0625, -2.6843548284354561, 3, 3},
               { 39.0625, -1.0737419313741825, 3, 3},
               { 97.65625, -1000000.1, 278230, 278277},
               { 97.65625, -400000.03999999998, 111170, 111425},
               { 97.65625, -160000.016, 44358, 44374},
               { 97.65625, -64000.006399999998, 17645, 17661},
               { 97.65625, -25600.002560000001, 6972, 6988},
               { 97.65625, -10240.001024000001, 2715, 2731},
               { 97.65625, -4096.0004096000002, 1026, 1041},
               { 97.65625, -1638.40016384, 366, 380},
               { 97.65625, -655.36006553599998, 117, 129},
               { 97.65625, -262.14402621440001, 30, 40},
               { 97.65625, -104.85761048576001, 5, 12},
               { 97.65625, -41.943044194304001, 0, 4},
               { 97.65625, -16.777217677721602, 0, 3},
               { 97.65625, -6.7108870710886404, 0, 1},
               { 97.65625, -2.6843548284354561, 0, 1},
               { 97.65625, -1.0737419313741825, 0, 1},
               { 244.140625, -1000000.1, 277936, 796691},
               { 244.140625, -400000.03999999998, 110906, 110923},
               { 244.140625, -160000.016, 44124, 44141},
               { 244.140625, -64000.006399999998, 17442, 17458},
               { 244.140625, -25600.002560000001, 6801, 6816},
               { 244.140625, -10240.001024000001, 2577, 2593},
               { 244.140625, -4096.0004096000002, 924, 938},
               { 244.140625, -1638.40016384, 300, 312},
               { 244.140625, -655.36006553599998, 82, 92},
               { 244.140625, -262.14402621440001, 17, 24},
               { 244.140625, -104.85761048576001, 2, 7},
               { 244.140625, -41.943044194304001, 0, 3},
               { 244.140625, -16.777217677721602, 0, 1},
               { 244.140625, -6.7108870710886404, 0, 1},
               { 244.140625, -2.6843548284354561, 0, 1},
               { 244.140625, -1.0737419313741825, 0, 1},
               { 610.3515625, -1000000.1, 277277, 277294},
               { 610.3515625, -400000.03999999998, 110322, 111647},
               { 610.3515625, -160000.016, 43617, 43633},
               { 610.3515625, -64000.006399999998, 17014, 17030},
               { 610.3515625, -25600.002560000001, 6456, 6471},
               { 610.3515625, -10240.001024000001, 2321, 2335},
               { 610.3515625, -4096.0004096000002, 757, 769},
               { 610.3515625, -1638.40016384, 212, 221},
               { 610.3515625, -655.36006553599998, 48, 55},
               { 610.3515625, -262.14402621440001, 8, 13},
               { 610.3515625, -104.85761048576001, 0, 4},
               { 610.3515625, -41.943044194304001, 0, 1},
               { 610.3515625, -16.777217677721602, 0, 1},
               { 610.3515625, -6.7108870710886404, 0, 1},
               { 610.3515625, -2.6843548284354561, 0, 1},
               { 610.3515625, -1.0737419313741825, 0, 1},
               { 1525.87890625, -1000000.1, 275817, 431061},
               { 1525.87890625, -400000.03999999998, 109054, 109070},
               { 1525.87890625, -160000.016, 42546, 42562},
               { 1525.87890625, -64000.006399999998, 16151, 16167},
               { 1525.87890625, -25600.002560000001, 5814, 5828},
               { 1525.87890625, -10240.001024000001, 1902, 1914},
               { 1525.87890625, -4096.0004096000002, 535, 545},
               { 1525.87890625, -1638.40016384, 125, 131},
               { 1525.87890625, -655.36006553599998, 23, 28},
               { 1525.87890625, -262.14402621440001, 3, 7},
               { 1525.87890625, -104.85761048576001, 0, 1},
               { 1525.87890625, -41.943044194304001, 0, 1},
               { 1525.87890625, -16.777217677721602, 0, 1},
               { 1525.87890625, -6.7108870710886404, 0, 1},
               { 1525.87890625, -2.6843548284354561, 0, 1},
               { 1525.87890625, -1.0737419313741825, 0, 1},
               { 3814.697265625, -1000000.1, 272645, 272661},
               { 3814.697265625, -400000.03999999998, 106377, 106393},
               { 3814.697265625, -160000.016, 40390, 40406},
               { 3814.697265625, -64000.006399999998, 14545, 14560},
               { 3814.697265625, -25600.002560000001, 4765, 4777},
               { 3814.697265625, -10240.001024000001, 1346, 1356},
               { 3814.697265625, -4096.0004096000002, 316, 323},
               { 3814.697265625, -1638.40016384, 61, 66},
               { 3814.697265625, -655.36006553599998, 9, 13},
               { 3814.697265625, -262.14402621440001, 0, 4},
               { 3814.697265625, -104.85761048576001, 0, 1},
               { 3814.697265625, -41.943044194304001, 0, 1},
               { 3814.697265625, -16.777217677721602, 0, 1},
               { 3814.697265625, -6.7108870710886404, 0, 1},
               { 3814.697265625, -2.6843548284354561, 0, 1},
               { 3814.697265625, -1.0737419313741825, 0, 1},
               { 9536.7431640625, -1000000.1, 265953, 266155},
               { 9536.7431640625, -400000.03999999998, 100987, 101002},
               { 9536.7431640625, -160000.016, 36374, 36388},
               { 9536.7431640625, -64000.006399999998, 11921, 11934},
               { 9536.7431640625, -25600.002560000001, 3374, 3384},
               { 9536.7431640625, -10240.001024000001, 795, 802},
               { 9536.7431640625, -4096.0004096000002, 157, 162},
               { 9536.7431640625, -1638.40016384, 27, 30},
               { 9536.7431640625, -655.36006553599998, 3, 6},
               { 9536.7431640625, -262.14402621440001, 0, 1},
               { 9536.7431640625, -104.85761048576001, 0, 1},
               { 9536.7431640625, -41.943044194304001, 0, 1},
               { 9536.7431640625, -16.777217677721602, 0, 1},
               { 9536.7431640625, -6.7108870710886404, 0, 1},
               { 9536.7431640625, -2.6843548284354561, 0, 1},
               { 9536.7431640625, -1.0737419313741825, 0, 1},
            };
            static const unsigned total_elements = sizeof(domain) / sizeof(domain[0]);
            static const unsigned stride = 16;
            //static const unsigned a_elements = total_elements / stride;
            BOOST_ASSERT(total_elements % stride == 0);

            static const double a_max = domain[total_elements - 1][0];
            static const double a_min = domain[0][0];
            static const double b_max = domain[stride - 1][1];
            static const double b_min = domain[0][1];

            if (a < a_min)
               return 0; // TODO: Use series?
            if (b < b_min)
            {
               //
               // This is a general heuristic that's more or less correct,
               // but a bit too safe in most cases.  Checked OK with
               // random testing.
               //
               if (z > -b)
                  return 1;
               if (a < 100)
                  return z < -b / (4 - 5 * (log(a)) * a / b) ? -1 : 0;
               else
                  return z < -b / (4 - 5 * sqrt(log(a)) * a / b) ? -1 : 0;
            }
            if (a > a_max)
            {
               //
               // Crossover point is decreasing with increasing a
            // upper limit is fine, lower limit is not:
               //
               if (b > b_max)
                  return 0;  // TODO: don't know what else to do???
               unsigned index = total_elements - stride;
               BOOST_ASSERT(domain[index][0] == a_max);
               while (domain[index][1] < b)
                  ++index;
               double b0 = domain[index - 1][1];
               double b1 = domain[index][1];
               double z0 = domain[index - 1][3];
               double z1 = domain[index][3];
               T upper_z_limit = static_cast<T>((z0 * (b1 - b) + z1 * (b - b0)) / (b1 - b0));
               if (z > upper_z_limit)
                  return 1;
               return z < -b / (4 - 5 * sqrt(log(a)) * a / b) ? -1 : 0;

            }
            if (b > b_max)
            {
               return 0;  // TODO: is there a better way???
            }
            //
            // Bi-linear interpolation case:
            //
            unsigned index = 0;
            while (domain[index][0] < a)
               index += stride;
            while (domain[index][1] < b)
               ++index;
            //
            // We now have 4 corners:
            //
            double x1 = domain[index - stride - 1][0];
            double x2 = domain[index][0];
            double y1 = domain[index - 1][1];
            double y2 = domain[index][1];
            double f11 = domain[index - stride - 1][2];
            BOOST_ASSERT(domain[index - stride - 1][0] == x1);
            BOOST_ASSERT(domain[index - stride - 1][1] == y1);
            double f12 = domain[index - stride][2];
            BOOST_ASSERT(domain[index - stride][0] == x1);
            BOOST_ASSERT(domain[index - stride][1] == y2);
            double f21 = domain[index - 1][2];
            BOOST_ASSERT(domain[index - 1][0] == x2);
            BOOST_ASSERT(domain[index - 1][1] == y1);
            double f22 = domain[index][2];
            BOOST_ASSERT(domain[index][0] == x2);
            BOOST_ASSERT(domain[index][1] == y2);
            //
            // Interpolation is a crude tool and our corners have quite tight bounds,
            // and the "impossible region" is bounded by convex planes.  For the upper
            // bound this is fine - bilinear interpolation will be over-conservative
            // but safe.  For the lower limit though we may calculate that the "safe"
            // zone is in an unsafe place.  To work around this we move our coordinates
            // closer to the lowest corner of our bounding box by an amount
            // proportional to the distance from the nearest corner.  This has the effect
            // of making our lower bound smaller than it would otherwise be, and more so nearer
            // the centre of the bounding box.
            //
            T effective_x = static_cast<T>(a + (std::min)(T(a - x1), T(x2 - a)) * 0.25);
            T effective_y = static_cast<T>(b + (std::min)(T(b - y1), T(y2 - b)) * 0.25);

            T lower_limit = static_cast<T>(1 / ((x2 - x1) * (y2 - y1)) * (f11 * (x2 - effective_x) * (y2 - effective_y) + f21 * (effective_x - x1) * (y2 - effective_y) + f12 * (x2 - effective_x) * (effective_y - y1) + f22 * (effective_x - x1) * (effective_y - y1)));

            //
            // If one f value was zero, take the whole box as zero:
            //
            double min_f = (std::min)((std::min)(f11, f12), (std::min)(f21, f22));
            if (min_f == 0)
               lower_limit = 0;
            //
            // Now we can test!
            //
            if (z < lower_limit)
               return -1;

            BOOST_ASSERT(f11 <= domain[index - stride - 1][3]);
            f11 = domain[index - stride - 1][3];
            BOOST_ASSERT(f12 <= domain[index - stride][3]);
            f12 = domain[index - stride][3];
            BOOST_ASSERT(f21 <= domain[index - 1][3]);
            f21 = domain[index - 1][3];
            BOOST_ASSERT(f22 <= domain[index][3]);
            f22 = domain[index][3];

            T upper_limit = static_cast<T>(1 / ((x2 - x1) * (y2 - y1)) * (f11 * (x2 - a) * (y2 - b) + f21 * (a - x1) * (y2 - b) + f12 * (x2 - a) * (b - y1) + f22 * (a - x1) * (b - y1)));
            if (z > upper_limit)
               return 1;
            return 0;
         }

} } }


#endif   // BOOST_MATH_DETIAL_1F1_MAP_NEG_B_HPP
