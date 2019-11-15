#include <iostream>
#include <tensorflow/c/c_api.h>

int main() {
    std::cout << TF_Version() << std::endl;
    return 0;
}
