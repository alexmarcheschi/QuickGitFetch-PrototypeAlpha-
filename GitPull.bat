@echo off

echo Checking for updates...

if "%1"=="" (
    echo Parameter Error
    pause
)

cd /d %1

git pull