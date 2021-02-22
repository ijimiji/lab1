#include <clocale>
#include "app.h"

int main() {
    std::locale::global(std::locale(""));
    App::Main();
    return 0;
}
