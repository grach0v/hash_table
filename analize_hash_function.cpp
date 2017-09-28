#include "hash_table.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

//hash function initialization
//=============================================================================
//{

size_t hash_one (std::string key) {return 1;}
size_t hash_0 (std::string key) {return 0;}
size_t hash_size (std::string key) {return key.size();}
size_t hash_sum (std::string key);
size_t hash_bit (std::string key);
size_t hash_gnu (std::string key);

//}
//=============================================================================

const size_t SIZE = 5000;
double distances (size_t lengths [SIZE], double avarage);

int main()
{
    Hash_Tablet <int, SIZE> test_one (hash_one);
    Hash_Tablet <int, SIZE> test_0 (hash_0);
    Hash_Tablet <int, SIZE> test_size (hash_size);
    Hash_Tablet <int, SIZE> test_sum (hash_sum);
    Hash_Tablet <int, SIZE> test_bit (hash_bit);
    Hash_Tablet <int, SIZE> test_gnu (hash_gnu);

    std::string line;
    std::ifstream myfile ("myfile.txt");

    size_t counter = 0;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            test_one [line] = 2026;
            test_0 [line] = 2026;
            test_size [line] = 2027;
            test_sum [line] = 2027;
            test_bit [line] = 2027;
            test_gnu [line] = 2028;
            counter++;
        }
        myfile.close();
    }

    else std::cout << "Unable to open file";

    std::cout << counter;

    size_t stats_one [SIZE] = {};
    size_t stats_0 [SIZE] = {};
    size_t stats_size [SIZE] = {};
    size_t stats_sum [SIZE] = {};
    size_t stats_bit [SIZE] = {};
    size_t stats_gnu [SIZE] = {};   //everything must be made by cycle

    test_one.get_lengths (stats_one);
    test_0.get_lengths (stats_0);
    test_size.get_lengths (stats_size);
    test_sum.get_lengths (stats_sum);
    test_bit.get_lengths (stats_bit);
    test_gnu.get_lengths (stats_gnu);

    std :: cout << "one distance = " << distances (stats_one, counter/SIZE) << "\n";
    std :: cout << "0 distance = " << distances (stats_0, counter/SIZE) << "\n";
    std :: cout << "size distance = " << distances (stats_size, counter/SIZE) << "\n";
    std :: cout << "sum distance = " << distances (stats_sum, counter/SIZE) << "\n";
    std :: cout << "bit distance = " << distances (stats_bit, counter/SIZE) << "\n";
    std :: cout << "gnu distance = " << distances (stats_gnu, counter/SIZE) << "\n";

    std::ofstream stats;
    stats.open ("stats_one.txt");
    for (size_t i = 0; i < SIZE; i++) stats << i << " " << stats_one [i] << "\n";
    stats.close();

    stats.open ("stats_0.txt");
    for (size_t i = 0; i < SIZE; i++) stats << i << " " << stats_0 [i] << "\n";
    stats.close();

    stats.open ("stats_size.txt");
    for (size_t i = 0; i < SIZE; i++) stats << i << " " << stats_size [i] << "\n";
    stats.close();

    stats.open ("stats_sum.txt");
    for (size_t i = 0; i < SIZE; i++) stats << i << " " << stats_sum [i] << "\n";
    stats.close();

    stats.open ("stats_bit.txt");
    for (size_t i = 0; i < SIZE; i++) stats << i << " " << stats_bit [i] << "\n";
    stats.close();

    stats.open ("stats_gnu.txt");
    for (size_t i = 0; i < SIZE; i++) stats << i << " " << stats_gnu [i] << "\n";
    stats.close();

    return 0;
}

//hash function
//=============================================================================
//{

size_t hash_gnu (std::string key)
{
    size_t value = 5381;
    for (size_t i = 0; i < key.size(); i++) value = value*33 + key[i];
    return value;
}

size_t hash_bit (std::string key)
{
    size_t value = 0;
    for (size_t i = 0; i < key.size(); i++)
    {
        value = _rotr (value, 1);
        value = value ^ key[i];
    }
    return value;
}

double distances (size_t lengths [SIZE], double avarage)
{
    double distance = 0;
    for (size_t i = 0; i < SIZE; i++) distance += (lengths [i] - avarage)*(lengths [i] - avarage);
    return distance;
}

size_t hash_sum (std::string key)
{
    size_t sum = 0;
    for (size_t i = 0; i < key.size(); i++) sum+= key[i];
    return sum;
}

//}
//=============================================================================


