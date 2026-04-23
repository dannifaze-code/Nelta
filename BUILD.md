# Build Instructions for Windows Development

## Prerequisites
- **Windows 10 or later**
- **Visual Studio 2019 or later** with Desktop development with C++ and .NET desktop development workloads installed.
- **CMake** (version 3.10 or higher)

## Steps to Build

1. **Clone the Repository**  
   Open the Command Prompt and run:
   ```bash
   git clone https://github.com/dannifaze-code/Nelta.git
   cd Nelta
   ```

2. **Install Dependencies**  
   Ensure you have all necessary dependencies installed. You can manage them via NuGet or vcpkg, based on the project’s requirements.

3. **Create Build Directory**  
   It’s a good practice to build in a separate directory:
   ```bash
   mkdir build
   cd build
   ```

4. **Configure the Project with CMake**  
   Run the following command to configure the build:
   ```bash
   cmake .. -G "Visual Studio 16 2019"
   ```
   Adjust the generator based on your Visual Studio version.

5. **Build the Project**  
   You can either build the project using Visual Studio or by running:
   ```bash
   cmake --build . --config Release
   ```
   This will generate the final binaries in the `build` directory.

6. **Run the Application**  
   Navigate to the output directory (e.g., `Release`) and run your application.

## Troubleshooting
- Ensure that all environment variables are set correctly for Visual Studio.
- Check the output logs for any missing dependencies or errors during build.

## Additional Resources  
Refer to the project documentation for specific configuration options and features specific to the project.