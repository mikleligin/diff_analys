
#include <iostream>
#include <vector>
#include <bitset>

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
    std::cout << "Hello World!\n";
}