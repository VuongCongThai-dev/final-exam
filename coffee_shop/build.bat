@echo off
cd /d "%~dp0"
echo === DANG BUILD COFFEE SHOP ===

REM Tao thu muc build va data neu chua co
if not exist build mkdir build
if not exist data  mkdir data

REM Compile tat ca file .cpp
g++ -std=c++17 -Wall ^
    src/Product.cpp ^
    src/Customer.cpp ^
    src/Employee.cpp ^
    src/Order.cpp ^
    src/Menu.cpp ^
    src/CoffeeShop.cpp ^
    src/main.cpp ^
    -o build/coffee_shop.exe

if %ERRORLEVEL% == 0 (
    echo.
    echo === BUILD THANH CONG! ===
    echo Chay chuong trinh: build\coffee_shop.exe
    echo.
    build\coffee_shop.exe
) else (
    echo.
    echo === BUILD THAT BAI! Kiem tra loi o tren ===
)
pause
