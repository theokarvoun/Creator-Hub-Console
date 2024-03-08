@echo off
echo This will make the chub command accessible through the commandline
echo This will be done by adding it to your systems environment variables
echo If you don't want that close this window
pause
setx PATH "%PATH%;C:\path\to\chub.exe"