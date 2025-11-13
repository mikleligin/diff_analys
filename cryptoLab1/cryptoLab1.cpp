
#include <iostream>
#include <vector>
#include <bitset>
#include <map>

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
        std::cout << "\n\n";
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
int main()
{
    std::cout << "S1";
    std::vector<uint8_t> input1 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    std::vector<uint8_t> s1_out = SBlockFirstSecondExit(input1, S1);
    std::cout << "\nS2";
    std::cout << "\n";
    std::vector<uint8_t> s2_out = SBlockFirstSecondExit(input1, S2);
    std::cout << "\nS3";
    std::cout << "\n";
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
            std::cout << "\t" << static_cast<int>(s1_count[i][j]);
        }
        std::cout << "\n----------------------------------------------------------------------------------\n";
    }
    std::cout << "\n========================================2========================================\n\n\n";
    for (size_t i = 0; i <= 15; i++)
    {
        std::vector<uint8_t> str;
        for (size_t j = 0; j <= 7; j++)
        {
            std::cout << "\t" << static_cast<int>(s2_count[i][j]);
        }
        std::cout << "\n----------------------------------------------------------------------------------\n";
    }
    std::cout << "\n========================================3========================================\n\niggers\n";
    
    for (size_t i = 0; i <= 15; i++)
    {
        std::vector<uint8_t> str;
        for (size_t j = 0; j <= 7; j++)
        {
            std::cout << "\t" << static_cast<int>(s3_count[i][j]);
        }
        std::cout << "\n----------------------------------------------------------------------------------\n";
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
            std::cout << std::bitset<12>(num) << "\n";
        }
    }
    std::vector<uint8_t> valid_numbers_C;
    for (uint8_t number : valid_numbers_A)
    {
        uint8_t first_4_bits = (number >> 7) & 0x0F;

        uint8_t second_4_bits = (number >> 4) & 0x0F; 
        uint8_t third_4_bits = number & 0x0F;

        std::cout << std::bitset<3>(GetCByMaxAndPieceOfA(s1_count, first_4_bits, max_S1)) << "\n";
        std::cout << std::bitset<3>(GetCByMaxAndPieceOfA(s2_count, second_4_bits, max_S2)) << "\n";
        std::cout << std::bitset<2>(GetCByMaxAndPieceOfA(s3_count, third_4_bits, max_S3)) << "\n";

        uint8_t concatenated = (GetCByMaxAndPieceOfA(s1_count, first_4_bits, max_S1) << 5) | (GetCByMaxAndPieceOfA(s2_count, second_4_bits, max_S2) << 2) | GetCByMaxAndPieceOfA(s3_count, third_4_bits, max_S3);

        valid_numbers_C.push_back(concatenated);

        std::cout << std::bitset<8>(concatenated) << "\n";
    }
    std::cout << "Hello World!\n";
}