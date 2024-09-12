@echo off
for %%a in (*.png) do (
    ffmpeg -i "%%a" "%%~na.jpg"
)
