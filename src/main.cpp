#include "ers_game.h"
#include "main.h"

int main(int argc, char const *argv[])
{
    resizeWarning();
    EgyptianRatscrewGame game;
    game.play();
    return 0;
}

void resizeWarning() {
    std::cout << std::endl << "***********************************************" << std::endl;
    std::cout << "Important note: avoid resizing your terminal window or changing font size, "
                 "as this can cause unexpected behavior. " << std::endl << "Type \"ok\" to continue: ";
    std::string okay;
    std::cin >> okay;
    while (okay != "ok") {
        std::cout << "Type \"ok\" to continue: ";
        std::cin >> okay;
    }
    std::cout << std::endl;
}
