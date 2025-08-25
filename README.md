### **Unused Image Finder Tool**

This tool is designed to **scan a project directory** and identify **unused images** in the `public` folder. It checks for references to these images in files with specific extensions (`.html`, `.css`,`.js`, `.jsx`) and reports any images that are not referenced.

---

## **Features**

1. **Supports Multiple Image Formats**:

   - Scans for images with extensions: `.jpg`, `.jpeg`, `.png`, `.webp` , `.svg`.

2. **Checks Multiple File Types**:

   - Scans files with extensions: `.html`, `.css` , `.js`, `.jsx`.

3. **Handles Different Path Formats**:

   - **Root-Relative Paths** : `/images/logo.png`
   - **Relative Paths** : `./images/logo.png`, `../public/images/logo.png`
   - **Absolute Paths** : `public/images/logo.png`, `/public/images/logo.png`

4. **Excludes `node_modules`**:

   - Automatically skips the `node_modules` directory to improve performance.

5. **Output**:
   - Lists all unused images in the `public` folder.

---

## **How It Works**

1. **Image Discovery**:

   - Recursively scans the `public` folder for image files.
   - Stores the relative paths of these images.

2. **File Scanning**:

   - Recursively scans the project directory for files with valid extensions (`.js`, `.jsx`, `.html`, `.css`).
   - Checks if any of the discovered images are referenced in these files.

3. **Path Matching**:

   - Generates all possible path variations for each image (e.g., `/images/logo.png`, `./images/logo.png`, `../public/images/logo.png`).
   - Checks if any of these variations exist in the file contents.

4. **Unused Image Detection**:
   - If an image is not referenced in any file, it is marked as unused.

---

## **Usage**

### **Prerequisites**

- **C++ Compiler**: Ensure you have a C++ compiler installed (e.g., GCC, Clang, or MSVC).
- **C++17**: The tool uses features from C++17, such as `std::filesystem`.

### **Steps to Run**

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/DeepakCSGO23/Find-Unused-Images-in-VSCode-using-CPP.git

   ```

2. **Compile the Code**:

   ```bash
   g++ -o finder.cpp finder.cpp
   ```

3. **Run the Executable**:

   ```bash
   ./finder.exe
   ```

4. **Provide Project Path**:

   - When prompted, enter the path to your project directory.
   - Example:
     ```
     Enter the project path:
     D:\Advanced Projects\PvP WebApp\pvp-webapp
     ```

5. **View Results**:
   - The tool will output a list of unused images (if any).
   - Example:
     ```
     Unused images are:
     public/images/unused.png
     public/icons/unused.webp
     ```

---

## **Customization**

### **File Extensions**

- To add or remove file extensions, modify the `validFileExtensions` and `validImageExtensions` sets in the code:
  ```cpp
  std::unordered_set<std::string> validFileExtensions = {".js", ".jsx", ".ts", ".tsx", ".html", ".css"};
  std::unordered_set<std::string> validImageExtensions = {".jpg", ".jpeg", ".png", ".webp", ".svg"};
  ```

### **Path Variations**

- The tool checks for the following path variations:

  ```cpp
  std::vector<std::string> possiblePaths = {
      imageFile,               // Relative path (e.g., "images/logo.png")
      "/" + imageFile,         // Root-relative path (e.g., "/images/logo.png")
      "./" + imageFile,        // Relative path with ./
      "../" + imageFile,       // Relative path with ../
      "public/" + imageFile,   // Public folder path (e.g., "public/images/logo.png")
      "/public/" + imageFile,  // Absolute public folder path (e.g., "/public/images/logo.png")
      "./public/" + imageFile, // Relative public folder path with ./
      "../public/" + imageFile // Relative public folder path with ../
  };
  ```

- To add more path variations, modify the `possiblePaths` vector.

---

## **Example Output**

### **All Images Used**

```
All images are used!
```

### **Unused Images Found**

```
Unused images are:
public/images/unused.png
public/icons/unused.webp
```

---

## **Future Enhancements**

1. **Support for `../../` Paths**:

   - Extend the tool to handle paths with `../../`.

2. **Regex-Based Matching**:

   - Use `std::regex` for more accurate path matching.

3. **Parallel Processing**:

   - Use multithreading to improve performance for large projects.

---

## **Contributing**

Feel free to contribute to this project by:

- Reporting issues.
- Suggesting new features.
- Submitting pull requests.

---

## **License**

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## **Contact**

For questions or feedback, please contact:

- ** K.N Deepak **
- **Email**: kkvdhoorika@gmail.com
- **GitHub**: https://github.com/DeepakCSGO23
- **Buy Me A Coffee** https://buymeacoffee.com/deepakkn

---

Enjoy using the Unused Image Finder Tool!
