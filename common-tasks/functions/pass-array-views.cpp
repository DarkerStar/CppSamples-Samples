// Pass array views
// C++20

#include <array>
#include <span>
#include <vector>

void fixed_size(std::span<int, 3> array);

void dynamic_size(std::span<int> array);

int main()
{
  int builtin_array[] = {1, 2, 3};
  std::array<int, 3> fixed_sized_array = {1, 2, 3};
  std::vector<int> dynamic_array = {1, 2, 3};
  
  std::array large_array = {0, 0, 1, 2, 3, 0, 0};
  int* sub_array_begin = large_array.begin() + 2;
  int* sub_array_end = sub_array_begin + 3;
  
  fixed_size({1, 2, 3});
  fixed_size(builtin_array);
  fixed_size(fixed_sized_array);
  
  fixed_size(dynamic_array);
  fixed_size(std::span<int, 3>{sub_array_begin, 3});
  fixed_size(std::span<int, 3>{sub_array_begin, sub_array_end});
  
  dynamic_size({1, 2, 3});
  dynamic_size(builtin_array);
  dynamic_size(fixed_sized_array);
  dynamic_size(dynamic_array);
  dynamic_size({sub_array_begin, 3});
  dynamic_size({sub_array_begin, sub_array_end});
}

// Pass views of arrays of values to functions.
//
// While it is possible to pass arrays of values to functions, that
// requires copying every element of the array one-by-one. If all we
// want to do is *inspect* the values or *use* the values in some
// computation without keeping a copy, that can be needlessly
// inefficient. A better option is to use a *view* of the array, which
// is small (usually just a pointer and a size or two pointers) and
// very cheap to pass to functions.
//
// C++20 introduces [`std::span`](cpp/container/span), which can be
// used to create views of any contiguous array of values, either with
// a compile-time size or a run-time dynamic size.
//
// On [8] we create a function that expects a fixed-size array of
// values. We call that function with different types of compile-time
// fixed-size arrays on [22-24]. In all cases, if the size does not
// match, that will result in a compile-time error.
//
// We can also call the function with run-time dynamic-size arrays, as
// on [26-28]. However, in these cases, the compiler will not detect
// errors in size. It is our responsibility to ensure the size is
// correct, or we will trigger undefined behaviour.
//
// On [10] we create a function that can take an array of any size. We
// can use it with virtually anything that resembles an array, as
// shown on [30-35].
//
// While views like `span`s are extremely efficient, there are a few
// things we must keep in mind when using a view.
//
// First, any changes we make will be done to the original array. This
// may be what you what, but if it is not, you can prevent this by
// using `span<const T>` or `span<const T, Size>` instead of just
// `span<T>` or `span<T, Size>`.)
//
// Second, if anything else is changing the array concurrently, those
// changes may affect our view. (This is true even if our view is
// `span<const T>` or `span<const T, Size>`.)
//
// Third,  we must be sure that the lifetime of the array being
// viewed is longer than the lifetime of the view. If we fail to do
// this, we may be reading - or worse, writing - to random memory,
// triggering security issues, undefined behaviour, and possibly
// crashes.
//
// All of the above problems can be avoided by passing a copy of the
// array rather than using a view, but at the cost of efficiency.

void fixed_size(std::span<int, 3>)
{ }

void dynamic_size(std::span<int>)
{ }
