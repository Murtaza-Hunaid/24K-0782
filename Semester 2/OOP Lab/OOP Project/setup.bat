@echo off
echo ==== Hotel Management System Setup ====

REM Step 1: Download Python installer
echo Downloading Python...
curl -L -o python-installer.exe https://www.python.org/ftp/python/3.12.1/python-3.12.1-amd64.exe

REM Step 2: Install Python silently with PATH
echo Installing Python...
python-installer.exe /quiet InstallAllUsers=1 PrependPath=1 Include_test=0

REM Wait for PATH to update
timeout /t 10

REM Step 3: Install openpyxl
echo Installing required Python library (openpyxl)...
python -m pip install --upgrade pip
python -m pip install openpyxl

echo ==== Setup Complete! ====
pause
