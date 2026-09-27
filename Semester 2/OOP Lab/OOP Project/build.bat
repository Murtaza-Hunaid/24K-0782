@echo off
echo Installing Python...

REM Install Python silently with PATH option
python-3.12.1-amd64.exe /quiet InstallAllUsers=1 PrependPath=1 Include_test=0

REM Wait a moment for PATH to update
timeout /t 10

echo Installing required libraries...
python -m pip install --upgrade pip
python -m pip install openpyxl

echo Installation complete. Press any key to exit.
pause
