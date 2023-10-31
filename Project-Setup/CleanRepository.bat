@echo off
echo Cleaning the repository...

REM Delete Visual Studio solution and project files in SandBox-Game and Uranium-Engine folders
for %%I in (SandBox-Game Uranium-Engine) do (
    del "%%I\*.sln" 2>nul
    del "%%I\*.vcxproj" 2>nul
    del "%%I\*.vcxproj.filters" 2>nul
    del "%%I\*.vcxproj.user" 2>nul
)

echo Repository cleaned.
