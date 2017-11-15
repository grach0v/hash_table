#include "hash_table.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

//hash function initialization
//=============================================================================
//{

size_t hash_one (std::string key) {return 1;}
size_t hash_one (char* key) {return 1;}

size_t hash_0 (std::string key) {return key[0];}
size_t hash_0 (char* key) {return key [0];}

size_t hash_size (std::string key) {return key.size();}
size_t hash_size (char* key) {return strlen (key);}

size_t hash_sum (std::string key);
size_t hash_sum (char* key);

size_t hash_bit (std::string key);
size_t hash_bit (char* key);

size_t hash_gnu (std::string key);
size_t hash_gnu (char* key);

//}
//=============================================================================

const size_t SIZE = 5000;
double distances (size_t lengths [SIZE], double avarage);

int main()
{
    Hash_Tablet <char*, int, SIZE> test_one (hash_one);
    Hash_Tablet <char*, int, SIZE> test_0 (hash_0);
    Hash_Tablet <char*, int, SIZE> test_size (hash_size);
    Hash_Tablet <char*, int, SIZE> test_sum (hash_sum);
    Hash_Tablet <char*, int, SIZE> test_bit (hash_bit);
    Hash_Tablet <char*, int, SIZE> test_gnu (hash_gnu);

    /*
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
    */

    FILE *f = fopen("textfile.txt", "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = (char *)malloc(fsize + 1);
    fread(string, fsize, 1, f);
    fclose(f);

    string[fsize] = 0;

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

//hash_gnu
//{

size_t hash_gnu (std::string key)
{
    size_t value = 5381;
    for (size_t i = 0; i < key.size(); i++) value = value*33 + key[i];
    return value;
}

size_t hash_gnu (char* key)
{
    size_t value = 5381;
    for (size_t i = 0; key [i] != 0; i++) value = value*33 + key[i];
    return value;
}

//}

//hash_bit
//{

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

size_t hash_bit (char* key)
{
    size_t value = 0;
    for (size_t i = 0; key[i] != 0; i++)
    {
        value = _rotr (value, 1);
        value = value ^ key[i];
    }
    return value;
}

//}

//hash_sum
//{

size_t hash_sum (char* key)
{
    size_t sum = 0;
    for (size_t i = 0; key[i] != 0 i++) sum+= key[i];
    return sum;
}

size_t hash_sum (std::string key)
{
    size_t sum = 0;
    for (size_t i = 0; i < key.size(); i++) sum+= key[i];
    return sum;
}

//}

//}
//=============================================================================

double distances (size_t lengths [SIZE], double avarage)
{
    double distance = 0;
    for (size_t i = 0; i < SIZE; i++) distance += (lengths [i] - avarage)*(lengths [i] - avarage);
    return distance;
}
