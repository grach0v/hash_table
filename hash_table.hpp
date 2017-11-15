#if !defined Hash_table_class
#define Hash_table_class

#include <list>
#include <iostream>
#include <assert.h>
#include <tuple>
#include <cstring>

/*
template <class T>
struct Str_pair
{
    std::string key_;
    T value_;

    Str_pair (std::string key, T value): key_ (key), value_ (value) {}
};
*/

template <class TKey, class TValue, size_t Size>
class Hash_Tablet
{
    std::list<std::tuple<TKey, TValue>> tablet [Size];

    size_t (*hash_func) (TKey);

    public:

    Hash_Tablet (size_t (*that_hash_func) (TKey));

    TValue& operator [] (TKey key);

    void get_lengths (size_t lengths [Size]) {for (size_t i = 0; i < Size; i++) lengths [i] = tablet [i].size();}

};

template <class TKey, class TValue, size_t Size>
Hash_Tablet <TKey, TValue, Size> :: Hash_Tablet (size_t (*that_hash) (TKey)): hash_func (that_hash)
{}

template <class TKey, class TValue, size_t Size>
TValue& Hash_Tablet <TKey, TValue, Size> :: operator [] (TKey key)
{
    size_t hash_value = hash_func (key) % Size;

    for (auto i = tablet[hash_value].begin(); i != tablet[hash_value].end(); ++i)
    {
       if (std::get<0> (*i) == key) return std::get<1> (*i);
    }

    return std::get<1> (tablet[hash_value].back());
}



/*
int main ()
{

    Hash_Tablet <int, 2> test (hash_func_one);

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
*/

#endif
