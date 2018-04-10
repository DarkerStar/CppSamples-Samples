// Pass arrays
// C++11

#include <array>
#include <vector>

void fixed_size(std::array<int, 3> array);

void dynamic_size(std::vector<int> array);

int main()
{
  fixed_size({1, 2, 3});
  
  std::array<int, 3> fixed_sized_array;
  // ... fill fixed_sized_array with values somehow
  fixed_size(fixed_sized_array);
  
  dynamic_size({1, 2, 3, 4, 5});
  
  std::vector<int> dynamic_sized_array;
  // ... fill dynamic_sized_array with values somehow
  dynamic_size(dynamic_sized_array);
}

// Pass arrays of values to functions.
//
// Built-in array types are not copyable, and so cannot be passed to
// functions by value. The traditional approach is to pass both a
// pointer to an array's first element and the size of the array.
// However, C++ provides class types that represent copyable
// arrays.
//
// We can create functions that take a compile-time fixed-size array
// of values by using [`std::array`](cpp/container/array) as the
// parameter type, as on [7]. We can call such functions using an
// initializer list of values directly as on [13], or by copying
// values into an array that we can pass as an argument as on [15-17].
//
// With fixed-sized arrays, the compiler enforces that the correct
// number of values is passed. (So if less than 3 values are used on
// [13], the remainder will be value-initialized, which for `int`
// means they will be set to 0.)
//
// If the number of values is not known at compile time, a
// [`std::vector`](cpp/container/vector) must be used. A `vector` is
// a C++ run-time-sized or dynamically-sized array. [!9] illustrates a
// function accepting an array of any number of values. It can be
// called using an initializer list of any size as on [19], or by
// copying values into a `vector` that we can pass as an argument as
// on [21-23].
//
// Note that passing arrays of values is expensive, as it requires
// copying all the elements of the array one-by-one. Also, `vector`s
// require run-time memory allocations. For that reason it is usually
// preferable to pass array *views* rather than arrays.

void fixed_size(std::array<int, 3>)
{ }

void dynamic_size(std::vector<int>)
{ }
