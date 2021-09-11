#include <iostream>
#include <memory>
#include "src/utils/include/driver.hpp"

using namespace std;
using namespace samilang;


int main(int argc, char* argv[]) {
    unique_ptr<Driver> driver = make_unique<Driver>(argv[1]);
    driver->launch();

    return 0;
}
