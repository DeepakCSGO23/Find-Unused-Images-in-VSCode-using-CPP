#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_set>

int main()
{
    std::string basePath;
    std::cout << "Enter the project path : \n";
    std::getline(std::cin, basePath); // "D:\\Advanced Projects\\PvP WebApp\\pvp-webapp";

    std::unordered_set<std::string> validExtensions = {".js", ".jsx", ".html", ".css"};
    std::unordered_set<std::string> validImageExtensions = {".jpg", ".jpeg", ".png", ".webp"};

    // Find all the images first
    // std::string imageFilesPath;
    // std::cout << "Enter the path where all the images are available : \n";
    // std::getline(std::cin, imageFilesPath);
    // std::string imageFilesPath = "D:\\Advanced Projects\\PvP WebApp\\pvp-webapp\\public\\courosal";
    //  Contains only strings
    std::unordered_set<std::string> imageFiles;

    for (const auto &entry : std::filesystem::recursive_directory_iterator(basePath))
    {
        if (entry.path().string().find("node_modules") == std::string::npos && validImageExtensions.find(entry.path().extension().string()) != validImageExtensions.end())
        {
            imageFiles.insert(entry.path().string());
        }
    }
    for (auto image : imageFiles)
    {
        std::cout << image << "\n";
    }

    try
    {
        for (const auto &entry : std::filesystem::recursive_directory_iterator(basePath))
        {
            // If the substring is not found the find function returns a large number which is nothing but the same value as the value in npos
            if (entry.path().string().find("node_modules") == std::string::npos && validExtensions.find(entry.path().extension().string()) != validExtensions.end())
            {
                // std::cout << "checking file : " << entry.path() << "\n";
                std::string fileName = entry.path().string();
                // Opening the file using the if file stream
                std::ifstream file(fileName);
                if (!file)
                {
                    std::cerr << "Error opening file: " << fileName << std::endl;
                }
                std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                file.close();
                // Finding if any of the image file is used in this currently oponened file
                for (auto image : imageFiles)
                {
                    // Found the image file in the file so remove that image from the image list as the image is found (used)

                    if (fileContents.find(image) != std::string::npos)
                    {
                        imageFiles.erase(image);
                    }
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
