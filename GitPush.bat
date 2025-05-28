@echo off

if "%1"=="" (
    echo Parameter Error
    pause
)

cd /d %1

git push origin

pause