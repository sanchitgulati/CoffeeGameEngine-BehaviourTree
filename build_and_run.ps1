# Execute CMake
cmake .

# Build the project
cmake --build .

# Change directory to the build folder of your project
Set-Location -Path ".\build\Debug\"

# Execute the resulting executable
Start-Process -FilePath "SDL_project.exe"


# Resets the directory to the root of the project
Set-Location -Path "../../"