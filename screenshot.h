#include <iostream>
#include <string>
#include <random>
#include <thread>
#include <format>
#include <fstream>
#include <chrono>


#ifndef SCREENSHOTVDSPROGRAM_SCREENSHOT_H
#define SCREENSHOTVDSPROGRAM_SCREENSHOT_H

class MakeScreenshots {
private:
    std::string command = "screencapture -x"; // MacOS Screenshot command

    std::string random_filename () {
        // Alphabet to generate random filename
        char alphabet[62] = "AaBbCcDdEeFfGgHhIiJjKkLlMmOoPpQqRrSsTtUuVvWwXxYyZz1234567890";

        // Generate random length
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<int> distribution1(8, 20);
        int length = distribution1(generator);

        // Generate filename
        std::uniform_int_distribution<int> distribution2(0, 36);
        std::string filename = "";
        for (int i = 0; i < length; i++) {
            filename += alphabet[distribution2(generator)];
        }
        filename += ".png";

        return filename;
    }

    // Thread function for creating screenshots with random filename
    void private_screen_thread (std::string user, std::string hostname, std::string password, std::string port) {
        std::string filename = random_filename();
        while (true) {
            // Create screenshot
            screenshot(filename);

            // Copy file
            std::string copy_command = "scp -P " + port + " " + filename + " " + user + "@" + hostname + ":/data/data/com.termux/files/home/storage/pictures/VDSScreenshots/" + random_filename();
            system(copy_command.c_str());
            std::cout << "The image has been successfully copied! Wait 10 sec..." << std::endl;

            // Wait 10 seconds
            std::chrono::seconds duration(10);
            std::this_thread::sleep_for(duration);
        }
    }

    // Thread function for creating screenshots with user filename
    void private_screen_thread_user (std::string filename, std::string user, std::string hostname, std::string password, std::string port) {
        while (true) {
            // Create screenshot
            screenshot(filename);

            // Copy file
            std::string copy_command = "scp -P " + port + " " + filename + " " + user + "@" + hostname + ":/data/data/com.termux/files/home/storage/pictures/VDSScreenshots/" + random_filename();
            system(copy_command.c_str());
            std::cout << "The image has been successfully copied! Wait 10 sec..." << std::endl;

            // Wait 10 seconds
            std::chrono::seconds duration(10);
            std::this_thread::sleep_for(duration);
        }
    }


public:
    // Create screenshot with random filename
    std::string screenshot () {
        std::string filename = random_filename();

        command += " '" + filename + "'";
        std::system(command.c_str());
        return filename;
    }

    void screenshot (std::string filename) {
        command += " '" + filename + "'";
        std::system(command.c_str());
    }

    void start_screen_thread (std::string user, std::string hostname, std::string password, std::string port) {
        std::thread screenshoting(&MakeScreenshots::private_screen_thread, this, user, hostname, password, port);
        screenshoting.join();
    }

    void start_screen_thread (std::string filename, std::string user, std::string hostname, std::string password, std::string port) {
        std::thread screenshoting(&MakeScreenshots::private_screen_thread_user, this, filename, user, hostname, password, port);
        screenshoting.join();
    }

};

#endif
