## libpwcard

libpwcard is a library for generating [PasswordCards](https://www.passwordcard.org/). The algorithm is defined at https://www.passwordcard.org/algorithm.html

## Build and install

The project uses [CMake](https://cmake.org/) as build system, thus building process is trivial:

```shell
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_RELEASE_TYPE=Release ..
cmake --build . 
cmake --install .
```

Build options:
 * `BUILD_EXAMPLE` - build example CLI app (OFF by default)
 * `BUILD_TESTING` - build tests (ON by default)

## Usage

Add these lines to your CMakeLists.txt:

```cmake
find_package(PwCard REQUIRED)
target_link_libraries(sample_project PwCard::pwcard)
```

Then include `<pwcard/pwcard.h>` in your code:

```cpp
#include <pwcard/pwcard.h>

void print_password_card(uint64_t number)
{
    auto pwcard = PwCard::generate(number);
    std::cout << PwCard::to_utf8(pwcard.header) << std::endl;
    for (auto &&row : pwcard.rows)
        std::cout << PwCard::to_utf8(row) << std::endl;
}
```

## License

This library is distributed under the [MIT license](https://opensource.org/licenses/MIT).
