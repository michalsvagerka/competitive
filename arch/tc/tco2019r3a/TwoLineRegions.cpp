#include "../l/lib.h"
#include "../l/geo.h"
#include "../l/mod.h"

class TwoLineRegions {
public:
    int count(vector <int> a, vector <int> b, vector <int> c) {
        int N = a.size();
        vector<Line<long double>> L;
        for (int i = 0; i < N; ++i) {
            L.push_back(Line<long double>{{0, -(long double)(c[i])/b[i]}, {-(long double)(c[i])/a[i], 0}});
        }
        vector<vector<pair<Point<long double>, int>>> I(N);
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                auto p = L[i].intersection(L[j]);
                I[i].push_back({p, j});
                I[j].push_back({p, i});
            }
        }
        for (int i = 0; i < N; ++i) sort(I[i].begin(),I[i].end());
        vector2<bitset<1000>> D(N, N);
        vector2<bitset<1000>> E(N, N);

        for (int i = 0; i < N; ++i) {
            bitset<1000> B;
            for (auto j: I[i]) {
                D[i][j.y] = B;
                B.set(j.y);
            }
            reverse(I[i].begin(),I[i].end());
            bitset<1000> C;
            for (auto j: I[i]) {
                E[i][j.y] = C;
                C.set(j.y);
            }
        }

        FieldMod ans = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                ans += FieldMod{2}.pow(N - 2 - (D[i][j] | D[j][i]).count());
                ans += FieldMod{2}.pow(N - 2 - (D[i][j] | E[j][i]).count());
                ans += FieldMod{2}.pow(N - 2 - (E[i][j] | D[j][i]).count());
                ans += FieldMod{2}.pow(N - 2 - (E[i][j] | E[j][i]).count());
            }
        }
        return (ui)ans;
    }

    void solve(istream& cin, ostream& cout) {
//        cout << count({-123, -9594, -5724, -6887, -3067, 8004, 7286, -8966, 4222, 4722, 2464, -6726, -7227, -6043, 4067, -7660, -6360, 53, 1247, 1977, -1439, -8073, 2061, -9461, 3748, -7906, -816, -3448, 9725, -5718, 8588, 1338, 6663, 7342, -8858, -7213, 513, 1961, -4829, -2127, -9465, 9961, 5398, 9399, -6614, -6487, -9404, 4791, 3007, 3614, 8395, -8624, -1136, 3468, -8732, -6357, 7899, 3206, 2722, 3365, 7633, -2587, -3072, 3291, 9423, -3570, -1164, 9240, 1688, -3745, 4781, -6039, 3225, 71, 6099, -922, -3660, 7041, 66, 8659, -1465, 968, -6352, 9672, 9850, 2788, 6137, 580, 743, -3441, -3314, 9762, 2503, -1267, 2073, -9786, 8681, -5057, 8693, 6174, -8065, -2575, 892, 802, 5921, -639, 5140, -7984, -3524, 88, 6402, 5817, -9621, 7038, 9240, 3118, 3328, 6664, -8267, 7151, -8483, -2707, -4721, -6125, 3375, -8025, 7609, 7670, 9453, 8850, -9916, 8684, -587, -9592, -6612, 6811, -4741, -8744, -1842, -9880, -397, 6560, 8945, -7106, -3227, 355, 1053, -9945, -7062, -5754, -9591, -9172, -827, -7296, 6508, -5138, 8530, -8669, -2157, 8863, -5333, -1112, 7903, 890, 5502, 2745, 7865, -6919, 549, 630, -413, 1391, 5298, 9167, 9303, 3298, 9946, 1633, -1392, -8955, 3189, 3760, 4905, 9017, 4544, 7070, 8412, -713, 785, 4393, 7152, 9149, 3585, -8362, 5039, 8577, 6347, -6233, 1232, 4145, 8438, 1120, -8618, -1195, -5307, 4874, -6790, -5785, 7042, -2660, -9965, 4002, 3499, -5800, 6454, 2314, 7513, 1473, -9703, -7488, 7788, -9891, -5660, 5554, -4787, -4398, 9864, 6825, -598, 8811, 2325, 3733, -7414, 7461, -3241, 4207, 3271, -4650, -2618, -1367, 6037, 8276, 2065, 4334, 7243, -7962, 7891, 2774, 9180, -1373, -1031, -4916, 7305, 1732, 1994, 1276, -3273, 2270, 8705, -7345, -5027, -1595, -2495, -4466, 8329, -7198, -1083, -2810, -1341, 2419, 1367, 2344, 6658, 3142, 4998, -9919, -4208, 2916, 1756, 7167, -967, -7299, 9956, 4119, -2480, -5234, 840, -4794, -3117, -7800, 3335, 2660, -7240, 2478, 1267, 8967, -7654, -8964, 4772, 8991, 3420, 8502, 4405, 5961, -3701, -2877, 2694, -7952, 7561, 8343, 3401, -4759, 7113, 4141, 3743, -312, -7676, -84, -903, -3567, 4444, 6094, -6555, -4360, 3400, -450, -8155, 9929, 7334, 4119, -6313, 1365, 2845, 2075, 7283, -8072, 942, -4547, 7547, 8945, -7956, 7402, -906, -7010, 1183, -505, 7006, -3791, 1608, 1040, -3168, 3760, -8412, 864, 4128, 246, -4992, 939, -8182, -3434, -8337, -5603, -8793, -9515, -2251, 8114, -811, -3465, 1071, 1994, 467, 7518, 8868, 3445, -875, 903, 8897, -3761, -1164, -1171, -3442, -1906, 5320, -9788, 2336, -9286, -1643, 7610, 4727, 9955, -6287, 35, -5939, 1932, 7780, -4179, 2262, 3546, 9569, 6922, -7407, -7190, -4136, 7694, -8178, -4210, -4089, 7239, 4965, -7399, 1974, 4813, -55, -4914, -8609, -7448, 5963, -6788, -5528, 8983, -4738, 6100, -9387, -9744, -6735, 6824, 2494, -5973, 6620, -2306, 4982, 3100, -7243, -5261, -8377, -7291, -2086, -3575, 7103, 6278, 3323, 2382, -962, 9926, 1422, -6979, 6796, 5789, -4584, 361, 8651, -1627, -3571, -5730, -8238, 6690, 2702, -3468, -8194, -2169, 4962, -2268, -9046, 4955, -8933, 8971, 4090, 4254, 1405, -8297, 3687, 1591, -5697, -5216, -6241, -172, -2189, 7853, 2552, 2691, -9262, -5322, 2396, 185, -8304, -1046, 3171, -5919, 148, -1794, 3277, -81, 8123, -868, -1162, 4265, 5206, -383, 8044, 2603, -7145, 9046, 3098, -5703, 6797, -766, -2796, 6455, -1597, -6570, 8307, -1703, 7481, -9734, -4985, 1850, 9726, 3428, -6781, 3237, 2404, -3995, -5710, 1823, 1420, 1110, -2338, 1709, 1947, 7290, 1688, -8246, 3166, 8636, 7317, -3673, -4575, -4797, -987, 9406, -4754, 9452, -3314, -569, -9878, -1112, 1100, -8533, 919, -6041, 3266, -3223, 4956, -6578, -4203, 7806, 7455, 7080, -9010, 8881, 3079, 7672, -3378, 9569, -7377, 125, 5981, 8682, -7291, 7040, 3625, 2331, -1559, -5592, -7343, -793, -9513, 1041, -6995, 440, -1042, 9005, 3254, -99, 6648, 612, 1035, 3751, -6101, -9902, -1221, -4703, -3682, -4908, -7172, 2901, 4941, 4326, 4486, 4699, 6235, 3784, -8490, 4318, -3569, 3537, 7878, -3451, -8834, 2030, 8332, -8888, 7350, -6591, -7691, -3850, -651, 6711, -736, 1048, 6294, 3321, 4228, 414, -8769, -8898, -1354, 7742, 6302, -85, -2905, -1688, 821, 4000, 5404, -3722, 1298, -8231, 54, 697, -6071, -6955, 2406, 9403, -9036, -2394, 4357, 8165, 2621, -2836, -5502, 5478, 5836, -4557, 5638, -9367, 149, -1952, -4242, -5650, 9406, -4870, 5043, -2689, 5687, 5595, 1529, 2334, -945, 1680, -2704, 720, -6853, -2768, 5761, 2447, -7413, 1814, -1282, 3450, 3386, -3953, 9232, -8900, -7826, -8847, -6734, 1320, 4086, -2356, 9168, -2606, 2504, 4473, -361, 1607, 6625, 645, 5833, -3794, 4937, -3565, 7474, 29, -5791, 769, 6615, 1229, -5547, 5238, -4283, 5138, 594, -6605, -6828, -858, -8796, -3417, -8815, 3809, 3660, -5450, 2180, -8915, 3452, -9599, -9625, 6492, 3161, -4778, -4783, -7401, 3696, -2257, -7430, -4113, -3061, 8938, -1647, 8221, 4794, 269, -2709, 7745, -5108, -2481, -3029, 1883, 7860, 9757, 4132, -2579, -4994, 4941, -3619, 9314, -1256, -9963, -1966, -9102, -9271, -5788, 3766, 3589, -5107, 8802, 8043, 3925, 4016, 7203, -7990, -9982, 9380, -8319, -7409, -2061, 3294, -7662, -9047, -8459, 3902, -3965, 9366, 6471, -9301, -9915, -3379, -9211, 7562, 6860, -7213, -9332, 7839, -8855, -6022, 6, 3194, 2252, 7169, 7645, -5612, 7280, -6252, -5024, 8062, 834, 8589, 297, -1159, -300, 8849, -5840, 720, 8572, -6475, 2280, 5671, -5081, 994, 9176, -9186, 7407, -2693, -3195, 8235, 3017, -7004, -2170, -6346, -6878, -9589, -7060, 1697, -1785, 7335, -4149, -3681, -5132, 5683, 8068, -4721, 6703, -3479, 8498, 7117, -6242, -5515, -9811, 8123, -8386, -4185, 8225, 5183, 2971, -5131, -1256, -1923, -9889, -6162, 9569, -7976, -3221, -232, 7606, -2310, 2457, 1631, -2572, -8205, 907, -1699, -1064, -3278, -1976, 5701, 9911, -7895, 1674, 8207, 1573, -4548, 8163, -4393, 1919, 2160, -3693, 2459, -7392, -1900, 831, 1628, 649, -9969, -8124, -1871, 5843, 639, -3072, 3064, 9167, 5847, 5256, 514, -4220, -7682, -6757, -7288, -759, 2704, 1537, 596, -9157, -4837, 1941, 8074, -397, -7901, -6680, 8878, -5527, -9216, 1512, 4825, -9199, -4323, 8308, -6368, -2221, 8763, -895, -6890, 2833, 81, -2401, -3371, -7564, -4079, 9164, 2206, -3294, 6724, 2150, 4361, -2530, -9212, -1710, 4086, -3878, -6747, -225, -2156, -1374, -7476, -8744, -8547, 449, 8533, 149, 9019, 3979, -1364, -1912, -9220, -4862, 7906, 202, -3195, 4461, -9242, 7141, -4109, 780, 565, -2648, 866, -7014, -7193, -5911, -7340, 6962, 5817, 2988, -3893, 832, -9204, 1752, -9662, 2092, 28, 3615, -4013, -5051, 8621, -9324, 91, -4629, 1064, 2108, -2346, 4890}, {5144, 7944, -3946, -7141, -1767, 5537, -1624, -3087, 7292, 2727, 5909, -417, -7199, 4692, -7861, 6225, -1364, -8689, 8337, 4536, 3220, -5636, -6555, 750, 5238, 1644, -5949, -3920, -7088, -1279, 3051, -3451, 8735, -1306, 8318, -8877, 8879, -685, -441, -5714, 8131, 5202, -7015, 9749, -2749, 643, -950, -8075, 50, -4378, -1302, 1129, 2291, -5831, 7970, 7131, -6359, -9942, -307, -6211, -2511, 110, -5800, -5096, 1292, -32, 8617, 8259, 2449, -8728, 6227, -8991, -8659, 2460, -6220, -4847, 4209, 8253, -4667, -3271, -6057, 4961, 6276, 6747, 6693, 276, 743, 5508, -3733, 7066, 9368, -4932, -3042, -9007, 2626, -2982, 8204, -8654, 7594, -5423, 1898, -6482, -7108, 9204, 4740, -62, -2010, -7541, -5912, 4000, -1299, 3844, -3807, -1317, -9139, -5403, -9557, 8045, -1396, 6189, 2455, -4352, -7477, 254, -7656, -733, -3765, 4203, -7569, 5784, 7429, 3521, 934, -5731, 1489, -2018, -5156, -1451, 2116, 4580, 6223, -6643, -5914, -5129, -8430, -9710, -1612, -1181, -6303, 1277, 9470, -9163, 9689, 8164, 8143, -3143, -2901, 7272, -8063, 3656, -6598, -2599, 7292, -6488, -8963, 8766, 4937, 8433, 2015, 8730, -8830, 8778, 2119, 7958, -6544, -8965, 5128, 7723, -1126, 8837, 2261, -4370, -1589, -41, -8762, -7116, -1060, 173, -7145, 1470, 7969, 2189, -9108, -5721, -6209, -5184, -6534, -4812, -4276, -6405, 589, 9480, 5370, 9778, -6273, 7759, 647, -581, -1414, -1351, 9380, 8717, -7900, 7041, 8723, 5377, 8793, 5548, -9439, -1118, -9808, 7110, 1218, 4961, -6087, -3748, -3577, 1392, -3725, -4421, -525, -6553, 4019, -7596, -8163, -2129, -3303, 8215, 1181, 4189, -8280, 767, 1948, 1523, -1144, 5134, 8004, 7715, -9900, 5892, -4218, 5660, -5603, 7893, 9549, -794, -5401, -2301, 8019, 7748, -3683, 1757, -6472, 4880, -4993, -9239, 1303, -7984, 8643, -7557, -2906, 2829, 8747, -2914, -3439, -1325, -7647, -8350, -774, -1125, -8398, -798, 3708, -7223, -3774, -9355, -876, 2965, 7095, -4661, -9806, -9202, 6266, 6235, -9491, -3322, 644, -6499, 9799, 7951, -7599, 8394, 6760, 7372, 9709, -3769, -915, -5703, -3887, 3859, -3188, 9524, 6072, 2855, -6026, -7289, 7665, -5019, -3266, -1184, -8559, 1021, 3806, -3279, 6621, -1857, 6905, 9505, -7457, 4311, 5360, -8710, 4300, -8986, 9712, -9378, 6866, -2275, 4222, 4581, -8135, 2976, 7708, 1565, -4752, -2143, -4058, 3747, 2694, 7976, 7115, -7395, 2463, -480, 4388, -7191, 2720, 4140, -3364, 880, -8020, 5654, -273, -4360, 7412, 9421, -3530, -2601, 6080, 2292, 3457, -7867, 9061, 7584, -2546, 5628, 7478, 5393, -7096, 583, 3046, 3826, -4727, -2824, 3653, -8674, 2612, 4326, 6753, -5667, 9639, -4842, 29, 7818, 5041, 5696, 9821, -937, 3364, 755, -6803, 7140, -1993, -4658, -618, -7954, 1269, 3541, 345, 8364, -8725, 9941, 8971, 8527, -6182, 1101, 6062, 444, 9731, -3636, 4772, -6799, -4573, -1487, -7304, 2955, -4457, 5352, 7882, -1105, -7643, 3214, 5444, 6263, -3227, 2720, -3747, 9933, 113, -4185, 8315, -2067, -5200, -8838, -5004, 9534, -4726, 2411, -7818, 7178, 8028, 701, 8705, -4495, -8324, -1084, 1062, 4127, -5722, -9194, -5515, -6458, -4130, 2998, 7804, -4273, -712, -7733, -644, 2428, 1768, -5872, -4636, 5069, 3745, 1827, -9312, -9566, 9415, 7328, 4839, 5931, 6272, 7650, -6637, 7210, -2205, -8883, -3588, 9344, 4787, 8665, -7685, 468, 6609, 5258, -5591, 3969, 3662, -4173, 4139, -8245, 6911, -1202, -7377, -2914, -898, 8345, 6416, -9389, 5580, -6010, 1072, 7994, 157, 2919, -1542, -8598, -6503, 6624, 378, -9390, 7811, -953, -7886, 2145, -7619, -1693, -5069, 7084, -460, 8439, -3673, -405, 187, 1266, 1010, -810, -8214, 1572, 4109, 9916, 7, 1192, -8976, 9341, -2239, 9467, -4390, -792, 2378, 8684, 72, 7970, 2991, 3694, -4059, 3218, -4071, -5153, 5959, 9123, 6042, 2692, -8563, -9502, 6285, -8419, -1135, 1021, -3164, -2590, -6976, -1669, 8148, 2103, 1830, 3422, 9987, -5644, 361, 5710, 488, -7736, 8226, 8543, -4439, -930, 5439, -7322, -250, -1796, 7391, 7382, -5282, 8086, -710, 309, -8989, -9125, -5407, 8195, -7387, 2413, -9499, -9356, 1998, 3007, 6500, -1046, 6018, 611, 9185, -9133, 9907, 9033, 8325, -9425, 8058, -5528, -4912, -8976, -4081, -6449, 3822, 2699, -2504, -4619, -6483, 9581, 7363, 8847, 4295, -1156, 4997, 4394, 7732, 6112, -7580, 7030, -2193, 2718, -6236, 4070, 1501, 5431, -2681, -2662, 4746, -7524, -2993, -4870, -9522, 2436, 915, 4147, -9073, -5258, -369, 5962, 6078, 1991, 6604, 6239, -5592, 5167, -3412, 8030, 515, -6872, -3534, 2869, 7178, 7346, 5311, -4757, 6685, 1864, -2415, -2811, -2107, 6867, -5366, -9683, -8440, -8061, -4556, -7439, 6852, 2308, -2348, 6179, 6768, 7768, -5664, 2321, 9341, -34, 911, -4534, 5021, -1107, 9702, -1477, 8572, 4118, 7371, 6171, -3920, -9741, 2319, -9764, 4339, -384, -4443, 6456, 914, 7577, 9265, 6907, 8595, 8611, 2315, 6720, 7732, -7902, -8422, 7371, 4109, 8191, 1602, -8075, -1445, 4081, 3535, 28, 7376, 755, -3269, 2270, 11, -746, -6540, 4753, 1954, -6110, 8489, 5217, -2991, 7572, -8988, -7930, -6601, -8426, 6551, 6952, -7026, 8552, 836, 152, 1974, 3484, -3379, -3693, 5315, 2508, 7534, -4821, -5717, 4211, 701, -799, 9793, 1955, 1850, 5616, 47, -807, -7070, 6632, -7535, -7502, 3022, 5943, 5137, -869, -1587, 4286, -7126, -2503, -2822, -9603, -2922, 9720, 7444, -3202, 7158, 5799, -3245, 2268, 4190, 8468, 2565, 4713, 4744, 6848, -9197, 9282, -5494, 5408, 880, -2807, -2686, 2451, 1152, 647, 5692, 9508, -973, 8528, 3695, 9520, 4310, 6287, 2085, 7553, -6741, -8525, -643, -6942, 4068, 3811, 69, 7322, -7970, 5506, 4199, -6280, 4685, 3774, 7927, 1843, 3524, 2965, 7263, -790, -389, 8775, -8647, -3477, 5543, 1235, -7909, -6160, -4353, 6930, 810, 5954, -9823, -6085, -8633, 5536, -2525, 5278, 1871, -7815, 674, -915, 4517, -5419, 2481, -6343, -5246, 1272, 2940, 7685, -3047, -6590, 782, -5391, -5800, -120, -920, 72, 4633, -8268, 392, -156, 5862, -1239, -4582, 3792, -7416, 6294, 2443, -1174, 398, -5125, 2397, -9388, 1097, -425, -3624, -9976, -8580, 8979, 8794, -4132, -1775, -3289, -9959, -9638, 8485, 457, -2321, 8166, 2302, -5060, -5394, 3437, 1278, 6216, -3480, 2491, 3108, 4877, 9220, -7972, -3801, -4595, -1134, -5232, -4612, 7900, -4672, 5469, -8523, -3202, 42, 919, 3379, -1041, -4410, -2599, 2022, 602, -5749, 8461, 15, 9099, -2716, -5512, -9839, 1509, 5531, -6292, 9502, 6981, 5161, 1604, 3455, -5219, 9973, 2602, 6902, 3729, -6362, -5928, 5738, 2164, -8373, -1771, -6567, -9637, -6727, -7521, -7423, 9425, -476, 3076, -8869, 2146, -8572, 625, 7316, 2323, -1787, 9061, 5558, 9117, -7942, -7852, -1139, -7209, 9273, -6612, -9778, -2876, 4529, -3620}, {1226, -1132, -1237, -6132, -6525, -3565, 4544, 6016, -7868, 2879, 2962, 2411, -9449, -4411, 6666, -4083, 9758, -1628, 8027, -8942, 5344, -9297, 8891, -8239, -1429, -9476, -4478, -7478, 5418, -2144, 1626, -3525, -7038, -2469, 5101, 4579, 7370, -5252, -3700, -4776, -7899, -3049, -2915, 3040, 8640, -319, 822, 9524, 5096, 2597, 3751, -3654, -9491, -5229, 7757, 4786, 4462, 5632, -6400, -8309, 2818, -393, -7976, -6241, -9025, -1439, -2071, 7612, 5952, 6492, -90, 3251, -2063, 5785, -6018, -7036, -9346, -6540, -3816, -3423, 7913, 9370, 3991, -2805, 1202, -3759, 1136, 9150, -21, 3734, -5604, 1854, -7512, 5326, -5689, -373, -9464, -2095, 4549, 8239, -3429, -671, 6746, 4054, -4272, 9020, -816, 1123, -775, -9199, 8507, 5395, 8509, -4255, 3972, -6528, -7954, 5674, 3326, -4086, 8424, 5288, 8434, 2074, -9343, 2504, 7124, -5210, 7129, -7331, 5525, 9002, -5441, 2693, -7772, 8412, -2295, -4068, 2186, 8845, 9176, 7849, 4075, 5759, 827, -4052, 145, 6605, -4360, 5466, 2193, 6316, 5800, -5486, -8715, -3789, -1132, 9094, 2276, 2902, 9554, 9386, -3138, -5455, 9465, 4163, 1118, 6877, 1604, 9942, 4870, -9084, 12, -4351, -8762, 8118, 8054, 2134, 4860, -3093, 1289, -1267, -3035, 7211, -7340, -3588, 4498, 6502, 8958, -1352, 8795, 2255, -1963, -2728, -2829, 1435, -3721, -9137, -2190, -2278, -4985, -1874, -5079, 1664, -6603, -2207, -3035, 7784, -6768, -9852, 6026, 5903, -1269, 3200, 1027, -8474, -9027, -1233, 1499, -7874, -6965, -9546, 1970, 2482, 7337, 6493, -169, -7017, -8327, -4161, 1625, -107, 4743, 5736, 4246, 6020, -4364, -6951, 8377, -5866, -5142, -9710, -8212, 3650, 6873, -9919, 9711, 3710, 5969, -834, -1474, -7212, -1531, 4672, -2607, 6254, -5157, -8578, -9836, -925, -4779, 9452, 7104, -9048, -8843, -4304, -7613, -4399, 5150, 3002, -706, 4810, 7496, 3075, 190, 1065, 7516, 7979, -6913, -9822, -7004, -2992, -9465, -2713, 7860, 2469, 10000, -4021, -6311, -1092, 7605, 991, -4366, -4242, 9299, -9968, 7555, -6869, -5052, 9783, 4965, 4687, 1780, 4912, 7372, -5, -6159, 7249, 4090, -8244, -6236, -5233, 9385, -9485, -7872, -2908, 4024, -8843, -1886, 5507, -9148, 1527, -7144, 1230, 1991, -6097, -5931, 5784, 4508, -5134, -2996, 1771, 184, 8230, 2682, -8793, 2991, 9281, -411, -8194, 5381, -3566, 9675, -819, -8707, -1255, 3462, 4917, -26, -5666, -7506, -3183, -9736, -4148, 73, -1664, -31, 4505, -6629, 9327, -775, 3942, -8476, 9682, 476, -520, 5175, 1321, -9264, 6662, -6818, -7823, -5738, -3927, 1873, 8440, -4434, 8603, 1171, -1706, -6098, 7013, -9630, 1730, 911, 5713, -5980, 6723, -6927, 1039, 5554, -7807, 9905, 9131, 2790, -7394, 7550, 7650, -4693, 7938, -4524, -8869, 8945, 5953, 1429, 7662, 7324, 1330, 6594, 6852, -5715, 8148, 9155, -4236, -5510, 8597, 9943, -9544, -7759, 1495, 8867, 6229, 648, 9288, -4912, 9442, -5191, -8304, 7634, -2049, -6462, -1996, -3832, 5708, -5566, 8207, 4121, 2, -3299, 5853, 8162, -2876, 5147, -7631, -783, 3849, -2838, -5994, 777, -1790, -7769, 8273, -9800, -6573, -9334, 6823, -1980, 3635, 4737, -3772, 8966, 9232, -8716, -3077, -3533, 3192, -9879, -6185, 9859, 7600, -2825, -323, 309, 1939, -4670, -5607, -2308, 1360, 9298, -521, -3794, 4142, 3601, -1980, -8552, -6990, 4887, -4721, -4000, 4735, 1294, -5316, 4260, -3391, -7536, -2243, 327, -3066, -5951, 4783, 5175, 9545, 208, -4418, 1185, 9705, -3444, 6767, -6718, 353, -5545, -6833, 6501, -6278, 5243, 6865, -268, 3758, -9847, 7353, -5260, -459, 8184, -9178, -1800, -886, 36, -4575, -7389, -3407, -8494, 2567, 9339, -6596, -5653, -8088, -6098, 6737, 6613, -272, 9769, -5014, 7883, -3445, 2515, -9011, 7507, 923, 1154, 9244, -3835, 897, 7719, -6862, -7491, 4754, -88, -7682, 7546, 5902, 4693, 8898, 9691, 5402, -6908, 4106, 3018, 8025, -1605, -5731, -9725, -5223, -9009, 6661, 558, -3841, -6206, -8197, -642, 6127, -7973, -779, 5773, 6883, 536, -1588, -1807, -986, 445, 5982, -4332, -9583, 5066, 3409, -2621, -9381, 2380, -2177, 7317, 4735, 8271, -9537, 5217, 3257, -9169, -5851, 8236, 224, -8322, 2117, 553, 3044, -4894, -3991, -9735, 2338, 272, -9447, 4395, 9641, -4744, 6678, -6252, 4658, -5057, 3284, 9600, 1980, 7074, 868, -6198, 9774, -7333, -2576, -7064, 9917, 8191, 8739, 5489, 424, -2590, 1232, -1196, 6706, 819, 5880, 9670, 8304, 9839, 6580, 8926, 2244, -8314, 5440, 6346, -7038, 8870, 1033, -2709, 1993, -5289, -6429, 7291, 8229, 3112, -6796, -5334, 1496, 6971, -5635, 4752, -1435, -4764, -9942, -8053, -8572, -6506, -4555, -1961, -7222, 7339, 9839, -3327, -6917, 1444, -9609, 4780, 7523, 324, -713, 1979, 9239, 9223, -828, 8648, -2002, 5370, 8827, -7700, 294, 1056, -7248, 362, -1724, -9484, 4385, -4888, 639, 2593, -6956, -6250, -1329, -9583, -475, -6987, -4858, -1917, 4387, 3668, -7416, -7678, -3447, -4563, 696, -5341, -2295, -2420, -9762, -3693, -9716, -5698, 2744, 4291, -6457, -2396, 1716, -7174, -6869, -7113, 1701, -1059, -4871, -5208, -3252, 5622, 5188, 2232, 9199, -514, 7647, 2472, -6356, -6973, -2019, 4362, -933, 3927, 4886, 434, -5188, 5739, 5563, 6633, 2990, 5464, 9443, 6754, -8731, 4068, 1617, -3511, 5735, -4042, -2349, -940, 3583, 2752, 6249, -9062, -97, -4659, 5394, -7959, -8352, -3647, -8877, 32, 5099, -7485, -4002, 2980, -9259, 3290, -3357, 8658, 1458, 8286, -3648, 2117, -3754, -8434, -182, 5931, -7555, -4114, -7553, 9651, 4506, -5779, -3495, -3511, -3148, -372, 491, 6154, 2196, 7567, 6697, -7013, -5092, -2771, -5219, 8212, 1653, -9750, -3479, -5924, -1569, -3629, -1495, 6079, 4581, 6185, -4369, -2810, -57, 1025, 8631, 5154, 1553, -592, -6352, 404, 662, 8091, -8924, -1940, -269, -6100, 4344, -7315, 2308, -82, 7317, -863, -3772, -3574, -8788, -3168, -7373, 3219, -1396, -1858, -468, 5424, -6864, -5623, -429, 9956, -1028, -5057, 6416, -5989, -6225, 6779, -5960, 726, -6799, 2024, 6751, 151, 3395, -7822, 6127, -3795, 913, 6573, -6346, 2001, 6770, 2032, 4767, 7190, -7042, 8971, 1381, 1528, -4145, 6900, -4271, -1223, -8711, -525, -1613, 4412, -9105, 5711, -2134, 9257, 8469, -128, 7997, 9288, -1369, -2224, 2540, 9223, 7995, 1932, -5928, 4385, 1289, 1866, 6152, -8509, -8379, -565, -5869, -5407, -4984, -8363, -9304, 7336, 4836, -4428, 7318, 7017, 1447, 1715, -7741, 9619, -3336, -7473, 9660, 8059, 1044, 3716, 2388, 8337, -5014, -4974, -5975, -9923, 1927, -3475, -7761, 9156, 3525, 4652, -2792, -9330, 2817, 102, -5545, -9548, -8317, 6728, 1556, -7374, -6195, 7136, 2657, -564, -6599, -3438, 3574, -2406, 3599, -8171, -6499, -7120, -3795, -3150, 6908, -8485, 6909, 118, 1214, -6979, 6618, 3029, 2158, 4872, -9322, -9389, -483, -5846, 3110, -1612, 907}) << endl;

        cout << count({1,1},{1,-1},{0,0}) << endl;
    }
};
