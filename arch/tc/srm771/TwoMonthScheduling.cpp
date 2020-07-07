#include "../../../l/lib.h"
#include "../../../l/nsegtree.h"

class TwoMonthScheduling {
public:
    int minimumMonths(int workers, vector <int> firstMonth0, vector <int> firstMonth1, vector <int> secondMonth0, vector <int> secondMonth1) {
        int L0 = firstMonth0.size(), L1 = firstMonth1.size();
        vector<int> firstMonth(L0*L1), secondMonth(L0*L1);
        for (int i1 = 0; i1 < L1; ++i1) {
            for (int i0 = 0; i0 < L0; ++i0) {
                firstMonth [ i1 * L0 + i0 ] = min( workers,  firstMonth0[i0] ^  firstMonth1[i1] );
                secondMonth[ i1 * L0 + i0 ] = min( workers, secondMonth0[i0] ^ secondMonth1[i1] );
            }
        }

        int N = L0*L1;
        vector<ll> P1(N+1, 0), P2(N+1, 0);
        for (int i = 0; i < N; ++i) {
            P1[i+1] = P1[i] + firstMonth[i];
            P2[i+1] = P2[i] + secondMonth[i];
        }

        vector2<int> D(N+1, N+1, 1e9);
        ll f = 0, s = 0;
        for (int i = 0; i < N; ++i) {
            f += firstMonth[i];
            s += secondMonth[i];
            if (f <= workers && s <= workers) {
                D[i+1][0] = 1;
            } else {
                break;
            }
        }

        for (int i = 1; i < N; ++i) {
            int lo = 1e9;
            for (int j = 0; j < i; ++j) lo = min(lo, D[i][j]+1);
            D[i][i] = lo;

            for (int j = i-1; j >= 0; --j) {
                D[i][j] = min(D[i][j], D[i][j+1]);
            }
            
            ll f = 0, s = 0;
            int lok = 0;
            for (int j = i; j < N; ++j) {
                f += firstMonth[j];
                s += secondMonth[j];
                if (f <= workers && s <= workers) {
                    D[j+1][i] = min(D[j+1][i], lo+1);
                    while (P2[i] - P2[lok] + f > workers) ++lok;
                    D[j+1][i] = min(D[j+1][i], D[i][lok]+1);
                } else break;
            }
        }
        
        int ans = 1e9;
        for (int i = 0; i <= N; ++i) {
            ans = min(ans, D[N][i]);
        }
        return ans + 1;
    }

    void solve(istream& cin, ostream& cout) {
        cout << minimumMonths(1000, {900, 150, 300, 200}, {0}, {400, 300, 600, 150}, {0}) << endl;
        cout << minimumMonths(1000,{900, 150, 300, 200},{0},{400, 600, 300, 150},{0}) << endl;
        cout << minimumMonths(1000, {350, 172, 24},{998, 54},{513, 119, 0},{24, 118}) << endl;
        cout << minimumMonths(47, {0,0,0,0,0,0,1,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,0}  ) << endl;
        cout << minimumMonths(1000000000,
                {914,730,953,110,150,266,437,828,19,681,678,620,283,101,628,119,467,936,409,525,158,822,284,422,143,784,255,207,320,817,786,473,914,742,793,474,490,308,388,132,154,724,293,564,854,988,188,814,321,153,233,658,300,960,811,132,169,869,618,847,984,456,930,115,331,515,398,155,138,304,32,999,87,822,720,185,859,654,212,51,210,538,325,738,414,0,19,6,521,814,423,873,519,417,209,653,328,954,980,340,387,906,198,222,219,212,444,445,171,677,697,197,944,312,647,347,139,974,123,378,959,443,961,700,554,449,970,654,355,30,263,957,490,939,57,433,18,57,302,720,433,267,724,757,802,332,299,924,559,258,669,815,180,397,160,901,97,746,39,660,144,775,921,69,951,290,834,259,528,759,652,888,957,47,237,187,208,366,23,282,382,954,878,1000,776,148,111,90,26,669,220,158,153,599,863,566,12,806,68,457,910,724,369,48,951,426,618,618,555,919,445,727,636,86,914,865,467,736,599,583,731,127,581,203,342,101,132,12,849,314,957,832,694,264,451,295,430,694,648,536,899,712,644,449,68,431,760,96,94,36,533,958,297,398,491,432,495,438,20,149,747,248,64,194,594,434,939,634,413,210,505,673,240,111,648,78,338,917,725,211,460,786,272,389,811,878,514,472,573,712,431,400,413,818,563,476,549,990,908,283,363,677,268,152,887,719,146,751,573,428,55,355,848,287,311,240,57,4,596,374,777,371,453,808,551,494,371,421,560,983,841,786,62,802,149,194,79,130,792,385,380,991,15,373,299,215,183,262,730,916,210,175,521,32,964,849,454,845,52,252,543,374,840,459,459,759,47,245,239,248,74,802,534,794,577,582,214,589,856,944,425,924,285,473,995,834,323,313,201,253,615,113,479,156,343,336,356,737,256,943,682,812,232,194,142,943,995,285,402,678,447,596,587,541,513,430,687,791,899,255,965,440,817,725,292,326,357,268,407,83,965,76,999,128,586,77,15,735,847,361,514,89,895,789,337,854,568,612,415,887,41,55,289,286,131,857,378,802,646,295,420,265,362,347,692,145,226,472,220,996,341,260,536,826,519,691,766,745,288,856,243,426,965,511,993,869,686,657,654,439,215,743,999,242,897,585,245,621,884,239},
                              {192,826,562,938,830,485,352,353,13,884},
                              {867,454,61,663,555,277,914,375,258,637,704,421,636,502,975,130,823,915,366,933,35,949,240,703,768,648,890,777,729,274,471,408,301,927,705,298,873,123,230,561,762,175,465,146,398,189,53,107,836,870,736,556,754,274,480,68,373,877,343,733,714,813,707,599,344,259,908,920,29,504,157,500,526,39,204,959,744,99,549,213,738,722,677,504,765,75,683,781,716,451,714,182,179,414,769,23,1,251,884,449,850,327,585,992,111,859,178,320,43,974,604,632,603,865,324,531,275,177,265,696,733,310,894,778,248,103,399,716,843,322,321,704,26,327,131,255,348,546,127,24,312,342,674,413,756,705,905,638,731,619,543,153,886,801,665,917,755,353,576,664,912,273,86,151,976,815,884,561,203,938,346,260,142,425,284,359,185,828,380,564,296,577,54,301,241,670,905,261,333,774,338,544,969,797,615,268,989,318,740,135,113,39,508,910,254,240,304,779,606,47,91,937,747,76,829,563,793,969,962,743,934,674,567,822,651,446,982,292,506,735,67,559,654,5,963,918,188,922,285,942,790,365,561,636,949,871,681,611,934,683,859,686,811,528,914,950,641,531,601,517,392,937,570,284,991,135,761,157,149,371,913,229,592,358,801,563,468,258,475,745,160,543,547,260,171,778,139,204,256,820,165,18,39,957,88,441,148,667,844,778,497,106,617,683,34,324,749,625,461,414,994,79,562,845,419,532,539,695,124,300,763,714,264,729,867,874,536,827,867,992,313,616,446,47,909,412,705,441,214,672,349,36,433,937,296,829,743,955,92,686,465,275,144,171,608,267,377,722,26,918,749,686,797,204,875,876,307,97,524,84,960,3,340,798,686,523,478,705,988,73,732,342,89,636,598,282,667,935,854,454,596,268,450,614,983,636,580,726,911,480,890,343,106,16,530,784,934,808,624,286,934,103,955,564,369,529,27,570,971,421,793,605,177,398,626,101,427,614,32,789,849,466,587,76,237,562,425,944,813,748,253,501,195,529,40,153,258,50,100,688,559,494,790,408,270,275,481,995,674,282,580,912,590,965,916,296,989,410,253,896,800,192,9,336,555,572,492,130,107,999,874,858,52,862,201,967,563,975,116,852,958,999,92,997,629,726,852,428,613,4},
                              {426,914,169,881,5,366,12,122,42,668}) << endl;
    }
};