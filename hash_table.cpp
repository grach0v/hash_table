#include <list>
#include <iostream>
#include <assert.h>
#include <cstring>

template <class T>
struct Str_pair
{
    std::string key_;
    T value_;

    Str_pair (std::string key, T value): key_ (key), value_ (value) {}
};

template <class T, size_t Size>
class Hash_Tablet
{
    std::list<Str_pair<T>> tablet [Size];

    size_t hash_func (std::string str);

    public:

//    void add_value (std::string key, T value);

    T& operator [] (std::string key);

};

template <class T, size_t Size>
T& Hash_Tablet <T, Size> :: operator [] (std::string key)
{
    size_t hash_value = hash_func (key);
    assert (hash_value < Size);

    for (auto i = tablet[hash_value].begin(); i != tablet[hash_value].end(); ++i)
    {
       if (i->key_ == key) return i->value_;
    }

    tablet[hash_value].push_back (Str_pair<T> (key, 43));

    return tablet[hash_value].back().value_;

    //assert (false);
}

/*
template <class T, size_t Size>
void Hash_Tablet <T, Size> :: add_value (std::string key, T value)
{
    size_t hash_value = hash_func (key);
    assert (hash_value < Size);
    tablet [hash_value].push_back (Str_pair<T> (key, value));
}
*/

template <class T, size_t Size>
size_t Hash_Tablet <T, Size> :: hash_func (std::string str)
{
    int sum = 0;
    for (size_t i = 0; i < str.size(); i++) sum += str [i];
    return sum % Size;
}

int main ()
{
    Hash_Tablet<int, 2> test;

    test.add_value ("Denis - 0", 17);
    test.add_value ("Denis - 1", 17);
    test.add_value ("Denis 1 -", -1);
    test.add_value ("Denis - 2", 15);
    test.add_value ("Denis - 3", 14);
    test.add_value ("Denis - 4", 13);


    test ["Denis 1 - 1"] = 42;

    std::cout << test ["Denis 1 - 1"] << "\n";
    std::cout << test ["Denis 1 -"] << "\n";


    return 0;
}
