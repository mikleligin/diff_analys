
#include <iostream>
#include <vector>
#include <bitset>
#include <map>
#include <tuple>

std::vector<std::vector<uint8_t>> S1 = { 
    {1,5,2,6,2,6,7,3},
    {5,3,7,1,4,0,0,4}
};
std::vector<std::vector<uint8_t>> S2 = {
    {3,2,5,5,3,6,0,6},
    {1,7,1,4,0,2,7,4}
};
std::vector<std::vector<uint8_t>> S3 = {
    {3,2,2,1},
    {2,0,2,3},
    {1,0,3,1},
    {3,0,0,1}
};

std::vector<uint8_t > shuffleP8 = {4,7,5,3,6,8,2,1};
std::vector<uint8_t > shuffleP12 = {2,8,3,5,1,6,7,4,2,5,8,1};

std::vector<uint8_t> SBlockFirstSecondExit(std::vector<uint8_t> input1, std::vector<std::vector<uint8_t>> S) {
    std::vector<uint8_t> z;
    int i = 0;
    while (i<=15)
    {
        uint8_t x = input1[i] >> 3;
        std::bitset<4> bitI(input1[i]);
        std::bitset<3> res(S[x][input1[i] & 7]);
        //std::cout << "\tres:" << bitI << "<->" << res << std::endl;
        z.push_back(S[x][input1[i] & 7]);
        i++;
    }
    return z;
}

std::vector<uint8_t> SBlockThirdExit(std::vector<uint8_t> input1, std::vector<std::vector<uint8_t>> S) {
    std::vector<uint8_t> z;
    int i = 0;
    while (i <= 15)
    {
        uint8_t a1a4 = (input1[i] >> 2) & 2 | (input1[i] & 1) & 3;
        uint8_t a2a3 = (input1[i] >> 1) & 3;
        std::bitset<3> res(S3[a1a4][a2a3]);
        std::bitset<4> bitI(input1[i]);
        //std::cout << "\t third " << bitI << " " << res << "\n";
        z.push_back(S3[a1a4][a2a3]);
        i++;
    }
    return z;
}

#define exit1 15
#define exit3 3
#define DAi 15

std::vector<uint8_t> DifXor(uint8_t input_dif, std::vector<std::vector<uint8_t>> S) {
    std::vector<uint8_t> exit_2;
    for (size_t i = 0; i <= exit1; i++)
    {
        exit_2.push_back(input_dif ^ i);
    }
    //std::cout << "--------OUTPUT--" << static_cast<int>(input_dif) << "----------\n\n";
    return SBlockFirstSecondExit(exit_2, S);
}

std::vector<uint8_t> DifXorS3(uint8_t input_dif, std::vector<std::vector<uint8_t>> S) {
    std::vector<uint8_t> exit_2;
    for (size_t i = 0; i <= exit1; i++)
    {
        exit_2.push_back(input_dif ^ i);
    }
    //std::cout << "--------OUTPUT--" << static_cast<int>(input_dif) << "----------\n\n";
    return SBlockThirdExit(exit_2, S);
}

std::vector<std::vector<uint8_t>> GetInitCounterVector() {
    std::vector<std::vector<uint8_t>> input_vector;
    for (size_t i = 0; i <= 15; i++)
    {
        std::vector<uint8_t> str;
        for (size_t j = 0; j <= 7; j++)
        {
            str.push_back(0);
        }
        input_vector.push_back(str);
    }
    return input_vector;
}
std::vector<std::vector<uint8_t>> SblockCounterOfArray(std::vector<std::vector<uint8_t>> input_array, std::vector<std::vector<uint8_t>> sblock_arrays) {
    
    // i = 0 j = 1
    // 0 0 1 3 0 2    0 0 0 0 0 0 
    // 1 1 0 0 0 2
    int counter = 0;
    std::vector<std::vector<uint8_t>> z = input_array;
    for (size_t table = 0; table <= 15; table++) {
        for (size_t pos = 0; pos <= 15; pos++) {
            uint8_t digit = sblock_arrays[table][pos];
            z[table][digit]++;
        }
    }
    return z;
}
std::vector<std::vector<uint8_t>> SblockCounterOfArrayS3(std::vector<std::vector<uint8_t>> input_array, std::vector<std::vector<uint8_t>> sblock_arrays) {

    // i = 0 j = 1
    // 0 0 1 3 0 2    0 0 0 0 0 0 
    // 1 1 0 0 0 2
    int counter = 0;
    std::vector<std::vector<uint8_t>> z = input_array;
    for (size_t table = 0; table <= 15; table++) {
        for (size_t pos = 0; pos <= 7; pos++) {
            uint8_t digit = sblock_arrays[table][pos];
            z[table][digit]++;
        }
    }
    return z;
}

void GetHexHexXorS1S2(std::vector<std::vector<uint8_t>> &output, std::vector<uint8_t> s_block_out, std::vector<std::vector<uint8_t>> S) {
    for (size_t i = 0; i <= DAi; i++)
    {
        std::vector<uint8_t> temp;
        std::vector<uint8_t> dci = DifXor(i, S);
        //std::cout << "\n\n";
        for (size_t j = 0; j < dci.size(); j++)
        {
            std::bitset<3> d1(dci[j]);
            std::bitset<3> s1(s_block_out[j]);
            std::bitset<3> xor_res(s_block_out[j] ^ dci[j]);
            //std::cout << "--->" << s1 << "^" << d1 << "<---" << xor_res << std::endl;
            temp.push_back((dci[j] ^ s_block_out[j]));
        }
        output.push_back(temp);
    }
}
void GetHexHexXorS3(std::vector<std::vector<uint8_t>>& output, std::vector<uint8_t> s_block_out, std::vector<std::vector<uint8_t>> S) {
    for (size_t i = 0; i <= DAi; i++)
    {
        std::vector<uint8_t> temp;
        std::vector<uint8_t> dci = DifXorS3(i, S);
        //std::cout << "\n\n";
        for (size_t j = 0; j < dci.size(); j++)
        {
            std::bitset<3> d1(dci[j]);
            std::bitset<3> s1(s_block_out[j]);
            std::bitset<3> xor_res(s_block_out[j] ^ dci[j]);
            //std::cout << "--->" << s1 << "^" << d1 << "<---" << xor_res << std::endl;
            temp.push_back((dci[j] ^ s_block_out[j]));
        }
        output.push_back(temp);
    }
}


// Считаем вероятности
uint8_t GetMaxCount(std::vector<std::vector<uint8_t>> table) {
    uint8_t max = 0;
    for (size_t i = 1; i < table.size(); i++)
    {
        for (size_t j = 0; j < table[i].size(); j++)
        {
            if (table[i][j] > max )
            {
                max = table[i][j];
            }
        }
    }
    return max;
}

// Берем кусок от DA
std::vector<uint8_t> GetDiffAnalys(std::vector<std::vector<uint8_t>> table, uint8_t num, std::string row) {
    std::vector<uint8_t> analys_array;
    for (size_t i = 1; i < table.size(); i++)
    {
        for (size_t j = 0; j < table[i].size(); j++)
        {
            if (table[i][j] == num)
            {
                if (row == "A")
                {
                    analys_array.push_back(i);
                }
                if (row == "C")
                {
                    analys_array.push_back(j);
                }
            }
        }
    }
    return analys_array;
}

// Найти повторяющиеся приколы в массиве
std::vector<std::vector<int>> findIdenticalGroups(const std::vector<uint8_t>& table) {
    std::map<uint8_t, std::vector<int>> groups;

    for (int i = 0; i < table.size(); i++) {
        groups[table[i]].push_back(i);
    }

    std::vector<std::vector<int>> result;
    for (auto& group : groups) {
        if (group.second.size() > 1) {
            result.push_back(group.second);
        }
    }

    return result;
}

// Проверяем 
bool checkNumber(uint16_t num, const std::vector<std::vector<int>>& groups) {
    std::bitset<12> bits(num);

    for (auto& group : groups) {
        bool firstBit = bits[11 - group[0]];

        for (int i = 1; i < group.size(); i++) {
            if (bits[11 - group[i]] != firstBit) {
                return false;
            }
        }
    }
    return true;
}

// Проверяем количество по p12
bool checkNumberAlt(uint16_t num, const std::vector<std::vector<int>>& groups) {
    for (auto& group : groups) {
        bool firstBit = num & (1 << (11 - group[0]));

        for (int i = 1; i < group.size(); i++) {
            bool currentBit = num & (1 << (11 - group[i]));
            if (currentBit != firstBit) {
                return false;
            }
        }
    }
    return true;
}

// Получаем DC
uint8_t GetCByMaxAndPieceOfA(std::vector<std::vector<uint8_t>> table, uint8_t piece, uint8_t max) {
    uint8_t x = 0;
    for (size_t i = 0; i <= piece; i++)
    {
        for (size_t j = 0; j < table[i].size(); j++)
        {
            x = table[i][j] == max ? j : x;
         }
    }
    return x;
}
uint8_t applyP12(uint16_t in12)
{
    uint8_t out = 0;
    for (int i = 0; i < 8; i++)
    {
        uint8_t bit = (in12 >> (12 - shuffleP12[i])) & 1;
        out |= bit << (7 - i);
    }
    std::cout << std::bitset<8>(out) << std::endl;
    return out;
}

uint8_t computeDXR(const std::vector<uint8_t>& P12, uint16_t DA)
{
    uint8_t invP[8] = { 0 };
    for (int i = 0; i < 8; i++)
    {
        uint8_t outPos = i + 1;
        uint8_t inPos = P12[i];
        invP[inPos - 1] = outPos;
    }

    uint8_t DXR = 0;
    for (int i = 0; i < 8; i++)
    {
        uint8_t srcBit = invP[i];
        uint8_t bit = (DA >> (12 - srcBit)) & 1;
        DXR |= bit << (7 - i);
    }

    return DXR;
}
uint8_t applyPermutation8(const std::vector<uint8_t>& P, uint8_t x)
{
    uint8_t out = 0;
    for (int i = 0; i < 8; i++)
    {
        uint8_t bit = (x >> (8 - P[i])) & 1;
        out |= bit << (7 - i);
    }
    return out;
}

uint16_t expandByTable(uint8_t input) {
    uint16_t result = 0;

    // 2,8,3,5,1,6,7,4,2,5,8,1
     //1 0 0 0 0 0 0 0 0 0 0 0
    // 01001011

    // 1

    for (size_t i = 0; i < shuffleP12.size(); i++) {
        int shift = 8 - shuffleP12[i];
        uint8_t temp = (input >> shift) & 1;
        
        result |= (temp << (11 - i));
    }

    return result;
}


std::vector<uint8_t> GetXorWithParameter(std::vector<uint8_t> s_block_out, uint8_t diff) {
    std::vector<uint8_t> output;
    for (size_t i = 0; i <= DAi; i++)
    {
        uint8_t temp = s_block_out[i] ^ diff;
        output.push_back(temp);
    }
    return output;
}

std::vector<uint8_t> GetXorWithParameterVector(std::vector<uint8_t> s_block_out, uint8_t diff) {
    std::vector<uint8_t> output;
    for (size_t i = 0; i < s_block_out.size(); i++)
    {
        uint8_t temp = s_block_out[i] ^ diff;
        output.push_back(temp);
    }
    return output;
}

void XorTwoTables(std::vector<uint8_t> &out, std::vector<uint8_t> first, std::vector<uint8_t> second) {
    std::vector<uint8_t> output;
    for (size_t i = 0; i < first.size(); i++)
    {
        uint8_t temp = first[i] ^ second[i];
        out.push_back(temp);
    }
}

std::vector<uint8_t> getRightCOutputs(std::vector<uint8_t> input_array, std::vector<uint8_t> input_c_row, uint8_t c) {
    std::vector<uint8_t> temp;
    for (size_t i = 0; i < input_c_row.size(); i++)
    {
        if (input_c_row[i] == c)
        {
            temp.push_back(input_array[i]);
        }
        
    }
    return temp;
}

std::vector<uint8_t> GetSameValsVector(std::vector<uint8_t> a, std::vector<uint8_t> b)
{
    std::vector<uint8_t> temp;
    for (size_t i = 0; i < a.size(); i++)
    {
        for (size_t j = 0; j < b.size(); j++)
        {
            if (a[i] == b[j])
            {
                temp.push_back(a[i]);
            }
        }
    }
    return temp;
}

std::vector<uint8_t> GetKeyVariants(
    const std::vector<uint8_t>& neededKeysExit1,
    const std::vector<uint8_t>& neededKeysExit2,
    uint32_t xR,
    uint32_t xRS,
    int shiftAmount)
{
    uint8_t param1 = (xR >> shiftAmount) & 15;
    uint8_t param2 = (xRS >> shiftAmount) & 15;

    std::vector<uint8_t> variantsInp1 = GetXorWithParameterVector(neededKeysExit1, param1);
    std::vector<uint8_t> variantsInp2 = GetXorWithParameterVector(neededKeysExit2, param2);

    return GetSameValsVector(variantsInp1, variantsInp2);
}

uint8_t applyInversePermutation8(const std::vector<uint8_t>& P, uint8_t x)
{
    std::vector<uint8_t> P_inv(8);
    for (int i = 0; i < 8; i++) {
        P_inv[P[i] - 1] = i + 1;
    }
    uint8_t out = 0;
    for (int i = 0; i < 8; i++) {
        uint8_t bit = (x >> (8 - P_inv[i])) & 1;
        out |= bit << (7 - i);
    }
    return out;
}

int main()
{
    //std::cout << "S1";
    std::vector<uint8_t> input1 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    std::vector<uint8_t> s1_out = SBlockFirstSecondExit(input1, S1);
    //std::cout << "\nS2";
    //std::cout << "\n";
    std::vector<uint8_t> s2_out = SBlockFirstSecondExit(input1, S2);
    //std::cout << "\nS3";
   // std::cout << "\n";
    std::vector<uint8_t> s3_out = SBlockThirdExit(input1, S3);
    std::vector<std::vector<uint8_t>> final_out_xor_s1;
    std::vector<std::vector<uint8_t>> final_out_xor_s2;
    std::vector<std::vector<uint8_t>> final_out_xor_s3;
    GetHexHexXorS1S2(final_out_xor_s1, s1_out, S1);
    GetHexHexXorS1S2(final_out_xor_s2, s2_out, S2);
    GetHexHexXorS3(final_out_xor_s3, s3_out, S3);
    std::vector<std::vector<uint8_t>> s1_count = SblockCounterOfArray(GetInitCounterVector(), final_out_xor_s1);
    std::vector<std::vector<uint8_t>> s2_count = SblockCounterOfArray(GetInitCounterVector(), final_out_xor_s2);
    std::vector<std::vector<uint8_t>> s3_count = SblockCounterOfArray(GetInitCounterVector(), final_out_xor_s3);
    std::cout << "\n========================================1========================================\n\n\n";
    for (size_t i = 0; i <= 15; i++)
    {
        std::vector<uint8_t> str;
        for (size_t j = 0; j <= 7; j++)
        {
            //std::cout << "\t" << static_cast<int>(s1_count[i][j]);
        }
       //std::cout << "\n----------------------------------------------------------------------------------\n";
    }
    //std::cout << "\n========================================2========================================\n\n\n";
    for (size_t i = 0; i <= 15; i++)
    {
        std::vector<uint8_t> str;
        for (size_t j = 0; j <= 7; j++)
        {
            //std::cout << "\t" << static_cast<int>(s2_count[i][j]);
        }
        //std::cout << "\n----------------------------------------------------------------------------------\n";
    }
    //std::cout << "\n========================================3========================================\n\niggers\n";
    
    for (size_t i = 0; i <= 15; i++)
    {
        std::vector<uint8_t> str;
        for (size_t j = 0; j <= 7; j++)
        {
            //std::cout << "\t" << static_cast<int>(s3_count[i][j]);
        }
        //std::cout << "\n----------------------------------------------------------------------------------\n";
    }
    uint8_t max_S1 = GetMaxCount(s1_count);
    uint8_t max_S2 = GetMaxCount(s2_count);
    uint8_t max_S3 = GetMaxCount(s3_count);

    std::vector<uint8_t> diff_s1 = GetDiffAnalys(s1_count, GetMaxCount(s1_count), "A");
    std::vector<uint8_t> diff_s2 = GetDiffAnalys(s2_count, GetMaxCount(s2_count), "A");
    std::vector<uint8_t> diff_s3 = GetDiffAnalys(s3_count, GetMaxCount(s3_count), "A");
    std::vector<uint8_t> diff_s1_с = GetDiffAnalys(s1_count, GetMaxCount(s1_count), "C");
    std::vector<uint8_t> diff_s2_с = GetDiffAnalys(s2_count, GetMaxCount(s2_count), "C");
    std::vector<uint8_t> diff_s3_с = GetDiffAnalys(s3_count, GetMaxCount(s3_count), "C");


    std::cout << "SADFWEJRHWJERWER    " << static_cast<int>(diff_s2_с[0]) << "\n";


    std::vector<uint16_t> numbers;
    for (size_t i = 0; i < diff_s1.size(); i++)
    {
        for (size_t j = 0; j < diff_s2.size(); j++)
        {
            for (size_t k = 0; k < diff_s3.size(); k++)
            {
                uint16_t concatenated = (diff_s1[i] << 8) | (diff_s2[j] << 4) | diff_s3[k];
                numbers.push_back(concatenated);
            }
        }
    }

    auto groups = findIdenticalGroups(shuffleP12);
    std::vector<uint16_t> valid_numbers_A;
    for (uint16_t num : numbers) {
        if (checkNumber(num, groups)) {
            valid_numbers_A.push_back(num);
            std::cout << "delA " << std::bitset<12>(num) << "\n";
        }
    }
    std::vector<uint8_t> valid_numbers_C;
    for (uint8_t number : valid_numbers_A)
    {
        uint8_t first_4_bits = (number >> 7) & 0x0F;

        uint8_t second_4_bits = (number >> 4) & 0x0F; 
        uint8_t third_4_bits = number & 0x0F;
        uint8_t concatenated = (GetCByMaxAndPieceOfA(s1_count, first_4_bits, max_S1) << 5) | (GetCByMaxAndPieceOfA(s2_count, second_4_bits, max_S2) << 2) | GetCByMaxAndPieceOfA(s3_count, third_4_bits, max_S3);

        valid_numbers_C.push_back(concatenated);

        std::cout << "delC " << std::bitset<8>(concatenated) << "\n";
    }
    uint8_t delD = applyPermutation8(shuffleP8, valid_numbers_C[0]);
    uint8_t delXR = computeDXR(shuffleP12, valid_numbers_A[0]);

    std::cout << "----------------------\n";
    std::cout << "Delta D " << std::bitset<8>(delD) << "\n";
    std::cout << "Delta XR " << std::bitset<8>(delXR) << "\n\n";

    // ------------------------------------------------- После получения delD

    uint8_t delA1 = valid_numbers_A[0] >> 8 & 15;
    uint8_t delA2 = valid_numbers_A[0] >> 4 & 15;
    uint8_t delA3 = valid_numbers_A[0] & 15;
        
    std::cout << "delA1 " << std::bitset<4>(delA1) << std::endl;

    // ------------------------------------------------- Получили вход два с дельта А1
    std::vector<uint8_t> delA1Input2 = GetXorWithParameter(input1, delA1);
    std::vector<uint8_t> delA2Input2 = GetXorWithParameter(input1, delA2);
    std::vector<uint8_t> delA3Input2 = GetXorWithParameter(input1, delA3);

    // Этот вход константа
    std::vector<uint8_t> exit1DelConst = SBlockFirstSecondExit(input1, S1);
    std::vector<uint8_t> exit1DelConst2 = SBlockFirstSecondExit(input1, S2);
    std::vector<uint8_t> exit1DelConst3 = SBlockThirdExit(input1, S3);

    // Получили выход 2 для всего этого
    std::vector<uint8_t> exit2DelA1 = SBlockFirstSecondExit(delA1Input2, S1);
    std::vector<uint8_t> exit2DelA2 = SBlockFirstSecondExit(delA2Input2, S2);
    std::vector<uint8_t> exit2DelA3 = SBlockThirdExit(delA3Input2, S3);

    // Получаем дельта C
    std::vector<uint8_t> delC1;
    std::vector<uint8_t> delC2;
    std::vector<uint8_t> delC3;
    XorTwoTables(delC1, exit1DelConst, exit2DelA1);
    XorTwoTables(delC2, exit1DelConst2, exit2DelA2);
    XorTwoTables(delC3, exit1DelConst3, exit2DelA3); // !!!!!!!!!!!!!!!!!! ~~~~~~ три бита + два бита

    // Делаем выборку из имеющегося C
    uint8_t delC1Needed = (valid_numbers_C[0] >> 5) & 7;

    // Получаем первые два столбика (вход1 и вход2) для deltaC1 
    std::vector<uint8_t> c1NeededKeysExit1 = getRightCOutputs(input1, delC1, delC1Needed);
    std::vector<uint8_t> c1NeededKeysExit2 = getRightCOutputs(delA1Input2, delC1, delC1Needed);

    // Ксорим два этих столбика для с R и R штрих соответсвующими битами (в данном случае 4 первых)


    

    // -------------------------- 2
    uint8_t delC2Needed = (valid_numbers_C[0] >> 2) & 7;

    // Получаем первые два столбика (вход1 и вход2) для deltaC2 
    std::vector<uint8_t> c2NeededKeysExit1 = getRightCOutputs(input1, delC2, delC2Needed);
    std::vector<uint8_t> c2NeededKeysExit2 = getRightCOutputs(delA2Input2, delC2, delC2Needed);

    // Ксорим два этих столбика для с R и R штрих соответсвующими битами (в данном случае 4 первых)


    

    // -------------------------- 3
    uint8_t delC3Needed = valid_numbers_C[0] & 3;

    // Получаем первые два столбика (вход1 и вход2) для deltaC2 
    std::vector<uint8_t> c3NeededKeysExit1 = getRightCOutputs(input1, delC3, delC3Needed);
    std::vector<uint8_t> c3NeededKeysExit2 = getRightCOutputs(delA3Input2, delC3, delC3Needed);


    // -------------------------------------------------------------------------------------------------------- Подбор

    // Считаем xr/s
    /*std::cout << "Permutation xR " << std::bitset<12>(xR) << " XR is " << std::bitset<8>(R) << "\n";
    std::cout << "Permutation xRS " << std::bitset<12>(xRS) << " XR is " << std::bitset<8>(RS) << "\n";*/
    
    std::vector<std::pair<uint8_t, uint8_t>> pairs = {

        {0b01001011, 0b11010101},
        {0b01011101, 0b11000011},
        {0b11110111, 0b01101001},
        {0b00101000, 0b10110110},
        {0b00011111, 0b10000001},
        {0b10011110, 0b00000000},
        {0b00001000, 0b10010110},
        {0b01010100, 0b11001010},
        {0b10000010, 0b00011100},
        {0b11101100, 0b01110010},
        {0b01111111, 0b11100001},
        {0b01001010, 0b11010100},
        {0b11010110, 0b01001000},
        {0b01000010, 0b11011100},
        {0b01010101, 0b11001011},
    };



    /*{0b00111100, 0b10100010},
    {0b00111100, 0b10100010},
    {0b00111100, 0b10100010},
    {0b00111100, 0b10100010},
    {0b00111100, 0b10100010},
    {0b00111100, 0b10100010},
    {0b00111100, 0b10100010},
    {0b00111100, 0b10100010},
    };*/

    // Создаем таблицу статистики: 3 столбца (для K11, K12, K13), в каждом 16 счетчиков (0-15)
    // Инициализируем нулями
    std::vector<std::vector<int>> key_statistic(3, std::vector<int>(16, 0));

    for (const auto& pair : pairs) {
        uint8_t R = pair.first;
        uint8_t Rs = pair.second;

        uint16_t xR = expandByTable(R);
        uint16_t xRS = expandByTable(Rs);
        /*std::cout << "Permutation xR " << std::bitset<12>(xR) << " XR is " << std::bitset<8>(R) << "\n";
        std::cout << "Permutation xRS " << std::bitset<12>(xRS) << " XR is " << std::bitset<8>(Rs) << "\n";*/
        std::vector<uint8_t> k11Variants = GetKeyVariants(c1NeededKeysExit1, c1NeededKeysExit2, xR, xRS, 8);
        std::vector<uint8_t> k12Variants = GetKeyVariants(c2NeededKeysExit1, c2NeededKeysExit2, xR, xRS, 4);
        std::vector<uint8_t> k13Variants = GetKeyVariants(c3NeededKeysExit1, c3NeededKeysExit2, xR, xRS, 0);
        for (uint8_t value : k11Variants) {
            if (value < 16) {
                key_statistic[0][value]++;
            }
        }

        for (uint8_t value : k12Variants) {
            if (value < 16) {
                key_statistic[1][value]++;
            }
        }

        for (uint8_t value : k13Variants) {
            if (value < 16) {
                key_statistic[2][value]++;
            }
        }
    }

    std::cout << "Val\t\tk11\tk12\tk13" << std::endl;
    for (int value = 0; value < 16; ++value) {
        std::cout << std::bitset<4>(value) << "\t\t";
        std::cout << key_statistic[0][value] << "\t"
            << key_statistic[1][value] << "\t"
            << key_statistic[2][value] << std::endl;
    }
    //std::vector<uint8_t> delC3;

    std::vector<std::vector<int>> key_statistic3(3, std::vector<int>(16, 0));
        // Yr          YrS        // dYL
    std::vector<std::tuple<uint8_t, uint8_t, uint8_t>> pairsY = {
    { 0b01101011, 0b11110101, 0b10101111 },
    { 0b11011100, 0b01000010, 0b10101101 },
    { 0b01010010, 0b11001100, 0b10101101 },
    { 0b10011001, 0b00000111, 0b10001011 },
    { 0b11110010, 0b01101100, 0b10001101 },
    { 0b11001101, 0b01001011, 0b10101011 },
    { 0b11010101, 0b01001011, 0b10101111 },
    { 0b00000000, 0b10011110, 0b10101101 },
    { 0b00101100, 0b10110010, 0b10001101 },
    { 0b00010101, 0b10001011, 0b10101001 },
    { 0b01010011, 0b11001101, 0b10101011 },
    { 0b01111111, 0b11100001, 0b10101111 },
    { 0b00011010, 0b10000100, 0b10101101 },
    { 0b00010011, 0b10001101, 0b10101001 },
    };
    std::vector<uint8_t> delYL = { 0b10101111 };
    for (size_t i = 0; i < pairsY.size(); i++)
    {
        uint8_t YR = std::get<0>(pairsY[i]);
        uint8_t YRS = std::get<1>(pairsY[i]);
        uint8_t delYL = std::get<2>(pairsY[i]);


        std::vector<uint8_t> delA1Input2Y = GetXorWithParameter(input1, delA1);
        std::vector<uint8_t> delA2Input2Y = GetXorWithParameter(input1, delA2);
        std::vector<uint8_t> delA3Input2Y = GetXorWithParameter(input1, delA3);

        // Этот вход константа
        std::vector<uint8_t> exit1DelConstY = SBlockFirstSecondExit(input1, S1);
        std::vector<uint8_t> exit1DelConst2Y = SBlockFirstSecondExit(input1, S2);
        std::vector<uint8_t> exit1DelConst3Y = SBlockThirdExit(input1, S3);

        // Получили выход 2 для всего этого
        std::vector<uint8_t> exit2DelA1Y = SBlockFirstSecondExit(delA1Input2Y, S1);
        std::vector<uint8_t> exit2DelA2Y = SBlockFirstSecondExit(delA2Input2Y, S2);
        std::vector<uint8_t> exit2DelA3Y = SBlockThirdExit(delA3Input2Y, S3);

        // Получаем дельта C
        std::vector<uint8_t> delC1;
        std::vector<uint8_t> delC2;
        std::vector<uint8_t> delC3;
        XorTwoTables(delC1, exit1DelConst, exit2DelA1Y);
        XorTwoTables(delC2, exit1DelConst2, exit2DelA2Y);
        XorTwoTables(delC3, exit1DelConst3, exit2DelA3Y);

        uint8_t delYLShuffeled = applyInversePermutation8(shuffleP8, delYL);
        std::cout << "Shuffeled delYL " << std::bitset<8>(delYLShuffeled) << "\n";
        uint8_t delC1Needed = (delYLShuffeled >> 5) & 7;

        std::vector<uint8_t> c1NeededKeysExit1 = getRightCOutputs(input1, delC1, delC1Needed);
        std::vector<uint8_t> c1NeededKeysExit2 = getRightCOutputs(delA1Input2, delC1, delC1Needed);

        uint8_t delC2Needed = (delYLShuffeled >> 2) & 7;

        std::vector<uint8_t> c2NeededKeysExit1 = getRightCOutputs(input1, delC2, delC2Needed);
        std::vector<uint8_t> c2NeededKeysExit2 = getRightCOutputs(delA2Input2, delC2, delC2Needed);

        uint8_t delC3Needed = delYLShuffeled & 3;

        std::vector<uint8_t> c3NeededKeysExit1Y = getRightCOutputs(input1, delC3, delC3Needed);
        std::vector<uint8_t> c3NeededKeysExit2Y = getRightCOutputs(delA3Input2, delC3, delC3Needed);

        // Ксорим два этих столбика для с R и R штрих соответсвующими битами (в данном случае 4 первых)
        uint16_t EYR = expandByTable(YR);
        uint16_t EYRS = expandByTable(YRS);

        std::vector<uint8_t> k11Variants = GetKeyVariants(c1NeededKeysExit1, c1NeededKeysExit2, EYR, EYRS, 8);
        std::vector<uint8_t> k12Variants = GetKeyVariants(c2NeededKeysExit1, c2NeededKeysExit2, EYR, EYRS, 4);
        std::vector<uint8_t> k13Variants = GetKeyVariants(c3NeededKeysExit1Y, c3NeededKeysExit2Y, EYR, EYRS, 0);



        // -------------------------- 3

        // Получаем первые два столбика (вход1 и вход2) для deltaC2 
       

        for (uint8_t value : k11Variants) {
            if (value < 16) {
                key_statistic3[0][value]++;
            }
        }

        for (uint8_t value : k12Variants) {
            if (value < 16) {
                key_statistic3[1][value]++;
            }
        }

        for (uint8_t value : k13Variants) {
            if (value < 16) {
                key_statistic3[2][value]++;
            }
        }
    }

    std::cout << "Val\t\tk13\tk13\tk13" << std::endl;
    for (int value = 0; value < 16; ++value) {
        std::cout << std::bitset<4>(value) << "\t\t";
        std::cout << key_statistic3[0][value] << "\t"
            << key_statistic3[1][value] << "\t"
            << key_statistic3[2][value] << std::endl;
    }
        std::vector<uint8_t> c3NeededKeysExit24;

    std::cout << "Hello World!\n";
}