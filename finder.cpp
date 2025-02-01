#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_set>
#include <algorithm>
#include <sstream>
#include <vector>
int main()
{
    std::string basePath;
    std::cout << "Enter the project path : \n";
    // std::getline(std::cin, basePath);
    basePath = "D:\\Advanced Projects\\PvP WebApp\\pvp-webapp";

    std::unordered_set<std::string> validExtensions = {".js", ".jsx", ".html", ".css"};
    std::unordered_set<std::string> validImageExtensions = {".jpg", ".jpeg", ".png", ".webp"};

    // Find all the images first
    //  Contains only strings
    std::unordered_set<std::string> imageFiles;

    for (const auto &entry : std::filesystem::recursive_directory_iterator(basePath))
    {
        if (entry.path().string().find("node_modules") == std::string::npos && validImageExtensions.find(entry.path().extension().string()) != validImageExtensions.end())
        {
            std::string relativePath = std::filesystem::relative(entry.path(), basePath).string();
            // Check from public down the way to last
            // '' passing character "" passing string
            std::replace(relativePath.begin(), relativePath.end(), '\\', '/');
            imageFiles.insert(relativePath);
        }
    }
    // for (auto image : imageFiles)
    // {
    //     std::cout << image << "\n";
    // }

    try
    {
        for (const auto &entry : std::filesystem::recursive_directory_iterator(basePath))
        {
            // If the substring is not found the find function returns a large number which is nothing but the same value as the value in npos
            if (entry.path().string().find("node_modules") == std::string::npos && validExtensions.find(entry.path().extension().string()) != validExtensions.end())
            {

                // std::cout << "checking file : " << entry.path() << "\n";
                std::string fileName = entry.path().string();
                // std::cout << fileName << "\n";
                //  Opening the file using the if file stream
                std::ifstream file(fileName);
                if (!file)
                {
                    std::cerr << "Error opening file: " << fileName << std::endl;
                }
                std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                file.close();
                // Finding if any of the image file is used in this currently oponened file
                for (auto imageFile : imageFiles)
                {
                    std::stringstream ss(imageFile);
                    std::string folder;
                    std::vector<std::string> folders;

                    while (std::getline(ss, folder, '/'))
                    {
                        folders.push_back(folder);
                    }

                    // Generating all possible paths of the image
                    std::string path = "";
                    for (int i = folders.size() - 1; i >= 0; i--)
                    {

                        path = "/" + folders[i] + path;

                        // Here add all possiblity css , js , html (single and double quotes)
                        // With leading '/' and without leading '/'
                        // HTML , CSS and JS
                        if (fileContents.find("src=\"" + path + "\"") != std::string::npos || fileContents.find("src='" + path + "'") != std::string::npos || fileContents.find("src=\"" + path.substr(1) + "\"") != std::string::npos || fileContents.find("src='" + path.substr(1) + "'") != std::string::npos || fileContents.find("url(\"" + path + "\")") != std::string::npos || fileContents.find("url('" + path + "')") != std::string::npos || fileContents.find("url(\"" + path.substr(1) + "\")") != std::string::npos || fileContents.find("url('" + path.substr(1) + "')") != std::string::npos)
                        {
                            // std::cout << imageFile << " is found in " << fileName << "\n";
                            imageFiles.erase(imageFile);
                            break;
                        }
                    }
                    folder.clear();
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    if (imageFiles.size() == 0)
    {
        std::cout << "All images are used!";
        return 0;
    }
    std::cout << "Unused images are : \n";
    for (auto image : imageFiles)
    {
        std::cout << image << "\n";
    }
    // Pause the console before exiting
    std::cout << "\nPress Enter to exit..." << std::endl;
    std::cin.get();
    return 0;
}
