import glob
import os
import shutil
import subprocess
import sys

# Assuming your script is located in a subdirectory, adjust this path accordingly
SCRIPT_DIRECTORY = os.path.abspath(os.path.dirname(__file__))

# Navigate up one directory to get to the root of your repository
ROOT_PATH = os.path.abspath(os.path.join(SCRIPT_DIRECTORY, '..'))

# Define the path to your single lua script
LUA_SCRIPT = f'{ROOT_PATH}/scripts/config/workspace.lua'

# Define the supported platforms and their corresponding IDEs
TARGET_IDE = {
    'windows': {
        'vs2022': 'vs2022',
        'vscode': 'gmake2',
    }
}

def run_premake(platform, ide):
    if platform not in TARGET_IDE:
        print(f"Unsupported platform: {platform}")
        print(f"Available platforms: {', '.join(TARGET_IDE.keys())}")
        sys.exit(1)
    
    if ide not in TARGET_IDE[platform]:
        print(f"Target IDE '{ide}' is not supported on platform '{platform}'")
        print(f"Available IDEs for {platform}: {', '.join(TARGET_IDE[platform].keys())}")
        sys.exit(1)

    action = TARGET_IDE[platform][ide]

    if not os.path.exists(LUA_SCRIPT):
        print(f"Lua script not found: {LUA_SCRIPT}")
        sys.exit(1)

    # Build the executable path for premake5
    executable_path = f'{ROOT_PATH}/vendor/bin/premake/{platform}/premake5'

    try:
        result = subprocess.run([executable_path, f'--file={LUA_SCRIPT}', action], check=True, capture_output=True, text=True)
        print(result.stdout)
        print(result.stderr)
    except subprocess.CalledProcessError as e:
        print(f"An error occurred while running premake5: {e}")
        print(f"Executable: {executable_path}")
        print(f"Lua Script: {LUA_SCRIPT}")
        sys.exit(1)

def clean_premake_files():
    # Define the directories and file patterns to remove
    directories_to_remove = ['.vs', '.vscode', 'bin']
    files_to_remove = [
        '**/**.vcxproj',
        '**/**.vcxproj.user',
        '**/**.vcxproj.filters',
        '**/**.sln', 
        '**/**.log', 
        '**/Makefile'
    ]

    # Remove directories
    for directory in directories_to_remove:
        dir_path = os.path.join(ROOT_PATH, directory)
        if os.path.exists(dir_path):
            shutil.rmtree(dir_path)

    # Remove files
    for pattern in files_to_remove:
        file_paths = glob.glob(os.path.join(ROOT_PATH, pattern), recursive=True)
        for file_path in file_paths:
            os.remove(file_path)
    
    print("Cleaned repository")

if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1].lower() == 'clean':
        clean_premake_files()
        sys.exit(0)
    elif len(sys.argv) != 3:
        print("Usage: python run_premake.py <platform> <ide>")
        print(f"Available platforms and IDEs:")
        for platform, ides in TARGET_IDE.items():
            print(f"  {platform}: {', '.join(ides.keys())}")
        sys.exit(1)

    platform = sys.argv[1].lower()
    ide = sys.argv[2].lower()

    run_premake(platform, ide)
