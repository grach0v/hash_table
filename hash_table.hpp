#if !defined Hash_table_class
#define Hash_table_class

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

    size_t (*hash_func_str) (std::string);
    size_t (*hash_func_chr) (char*);

    bool hash_string;
    bool hash_char;

    public:

    Hash_Tablet (size_t (*that_hash_func) (std::string));
    Hash_Tablet (size_t (*that_hash_func) (char*));

    T& operator [] (std::string key);
    T& operator [] (char* key);

    void get_lengths (size_t lengths [Size]) {for (size_t i = 0; i < Size; i++) lengths [i] = tablet [i].size();}

};

template <class T, size_t Size>
Hash_Tablet <T, Size> :: Hash_Tablet (size_t (*that_hash_func) (char*)):
    hash_func_chr (that_hash_func),
    hash_string (false),
    hash_char (true)
{}

template <class T, size_t Size>
Hash_Tablet <T, Size> :: Hash_Tablet (size_t (*that_hash_func) (std::string)):
    hash_func_str (that_hash_func),
    hash_string (true),
    hash_char (false)
{}


template <class T, size_t Size>
T& Hash_Tablet <T, Size> :: operator [] (char* key)
{
    assert (!hash_string);
    assert (hash_char);

    size_t hash_value = hash_func_chr (key) % Size;

    for (auto i = tablet[hash_value].begin(); i != tablet[hash_value].end(); ++i)
    {
       if (strcmp (i->key_, key)) return i->value_;
    }

    tablet[hash_value].push_back (Str_pair<T> (key, 43));

    return tablet[hash_value].back().value_;
}


template <class T, size_t Size>
T& Hash_Tablet <T, Size> :: operator [] (std::string key)
{
    assert (hash_string);
    assert (!hash_char);

    size_t hash_value = hash_func_str (key) % Size;

    for (auto i = tablet[hash_value].begin(); i != tablet[hash_value].end(); ++i)
    {
       if (i->key_ == key) return i->value_;
    }

    tablet[hash_value].push_back (Str_pair<T> (key, 43));

    return tablet[hash_value].back().value_;
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
