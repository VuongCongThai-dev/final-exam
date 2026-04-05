@echo off
cd /d "%~dp0"
echo Dang bien dich chuong trinh...
g++ -std=c++17 -Wall src/Product.cpp src/Customer.cpp src/Employee.cpp src/Order.cpp src/Menu.cpp src/CoffeeShop.cpp src/main.cpp -o coffee_shop.exe

if %ERRORLEVEL% == 0 (
    echo Bien dich thanh cong! File coffee_shop.exe da duoc tao.
) else (
    echo Bien dich failed! Check loi.
)
pause
