#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_set>
#include <algorithm>
#include <sstream>
#include <vector>
#include <regex>
int main()
{

    std::string publicFolderPath, projectFilePath;

    std::cout << "Enter the project path : \n";

    // std::getline(std::cin, publicFolderPath);
    publicFolderPath = "D:\\Advanced Projects\\PvP WebApp\\pvp-webapp\\public";
    projectFilePath = "D:\\Advanced Projects\\PvP WebApp\\pvp-webapp";
    std::unordered_set<std::string> validFileExtensions = {".js", ".jsx", ".html", ".css"};

    std::unordered_set<std::string> validImageExtensions = {".jpg", ".jpeg", ".png", ".webp", ".svg"};

    std::unordered_set<std::string> imageFiles;

    for (const auto &entry : std::filesystem::recursive_directory_iterator(publicFolderPath))
    {
        if (entry.path().string().find("node_modules") == std::string::npos && validImageExtensions.find(entry.path().extension().string()) != validImageExtensions.end())
        {
            //  "D:\\Advanced Projects\\PvP WebApp\\pvp-webapp\\public";
            //  "D:\\Advanced Projects\\PvP WebApp\\pvp-webapp\\public\\courosal\\animals.webp"

            std::string relativePath = std::filesystem::relative(entry.path(), publicFolderPath).string();
            std::replace(relativePath.begin(), relativePath.end(), '\\', '/');
            imageFiles.insert(relativePath);
        }
    }

    try
    {
        for (const auto &entry : std::filesystem::recursive_directory_iterator(projectFilePath))
        {
            // If the substring is not found the find function returns a large number which is nothing but the same value as the value in npos
            if (entry.path().string().find("node_modules") == std::string::npos && validFileExtensions.find(entry.path().extension().string()) != validFileExtensions.end())
            {

                std::string fileName = entry.path().string();
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

                    std::vector<std::string> possiblePaths = {imageFile, "/" + imageFile, "./" + imageFile, "../" + imageFile, "public" + '/' + imageFile, "/public/" + imageFile, "./public/" + imageFile, "../public/" + imageFile};
                    //* icons/logo.png , /icons/logo.png , ./icons/logo.png , ../icons/logo.png , public/icons/logo.png , /public/icons/logo.png , ./public/icons/logo.png , ../public/icons/logo.png

                    for (uint16_t i = 0; i < possiblePaths.size(); i++)
                    {
                        if (fileContents.find("\"" + possiblePaths[i] + "\"") != std::string::npos || fileContents.find("'" + possiblePaths[i] + "'") != std::string::npos)
                        {
                            std::cout << "\"" + possiblePaths[i] + "\"" << "\n"
                                      << "'" + possiblePaths[i] + "'" << "\n";
                            imageFiles.erase(imageFile);
                            // Found the image so break from generating all possible paths of the image
                            break;
                        }
                    }

                    // Generating all possible paths of the image
                    // std::regex filePathRegex(R"((?:src=['"]|href=['"]|url\(['"]?)(\.\.?/[^'")]+))");
                    // std::regex filePathRegex(R"((?:src=['"]|href=['"]|url\(['"]?)(/?[^'")]+))");

                    // std::smatch match;

                    // std::string::const_iterator searchStart(fileContents.cbegin());
                    // std::string::const_iterator searchEnd(fileContents.cend());
                    // while (std::regex_search(searchStart, searchEnd, match, filePathRegex))
                    // {
                    // for(uint16_t i=folders.size()-1;i>=0;i--){

                    // }
                    // std::cout << "Found path: " << match[1] << " for file name " << fileName << "\n";
                    // Moving the iterator past the last match
                    //     searchStart = match.suffix().first;
                    // }
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
