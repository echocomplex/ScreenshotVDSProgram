#include "screenshot.h"
#include <string>


int main () {
    // Configuration
    std::string IP = "";  // Senior Machine IP
    std::string User = "";  // Senior Machine username
    std::string Password = "";  // Senior Machine password
    std::string Port = "8022";  // SSH Connection Port

    MakeScreenshots unit;
    unit.start_screen_thread(User, IP, Password, Port);
    return 0;
}
