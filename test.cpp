#include <iostream>
#include <assert.h>
#include <cstring>
#include "hash_table.hpp"

size_t hash_gnu_str (std::string key)
{
    size_t value = 5381;
    for (size_t i = 0; i < key.size(); i++) value = value*33 + key[i];
    return value;
}


size_t hash_gnu_chr (char* key)
{
    size_t value = 5381;
    for (size_t i = 0; key[i] != 0; i++) value = value*33 + key[i];
    return value;
}


int main()
{
    Hash_Tablet <int, 5, std::string> test_str (hash_gnu_str);
    Hash_Tablet <int, 5, char*> test_chr (hash_gnu_chr);

    test_str ["Denis"] = 17;
    test_chr ["Denis"] = 17;

    test_str ["Grachov"] = 20;
    test_chr ["Grachov"] = 20;

    std::cout << test_str ["Grachov"] << test_str ["Denis"] << "\n";
    std::cout << test_chr ["Grachov"] << test_chr ["Denis"] << "\n";

    return 0;
}
