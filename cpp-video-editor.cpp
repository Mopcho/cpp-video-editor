#include <string>
#include <iostream>
#include <vector>

static void cut_from_video(std::string from, std::string to, std::string input_file_location, std::string output_location);

std::string ffmpeg = "ffmpeg";

int main(int argc, char* argv[]) {
    int i = 1;

    std::vector<std::string> timestamps = {};
    std::string output;
    std::string input;
    std::string format;

    while (i < argc) {
        std::string argument = argv[i];

        if (argument == "--input") {
            input = argv[i + 1];
            format = input.substr(input.rfind(".") + 1, input.length());
            std::cout << format;
            i = i + 2;
            continue;
        }

        if (argument == "--output") {
            output = argv[i + 1];
            i = i + 2;
            continue;
        }

        timestamps.push_back(argument);

        i++;
    }

    int counter = 1;
    for (std::string timestamp : timestamps) {
        std::string delimiter = "-";
        std::string from = timestamp.substr(0, timestamp.find(delimiter));
        std::string to = timestamp.substr(timestamp.find(delimiter) + 1, timestamp.length());
        std::string output_numbered = output + "-" + std::to_string(counter) + "." + format;

        cut_from_video(from, to, input, output_numbered);

        counter++;
    }
}

static void cut_from_video(std::string from, std::string to, std::string input, std::string output) {
    std::string command = ffmpeg + " -i " + "\"" + input + "\"" + " -ss " + from + " -to " + to + " -async 1 " + "\"" + output + "\"";
    std::cout << command << '\n';
    system(command.c_str());
}

