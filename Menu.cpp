#include "Menu.h"
#include "Calculation.h"
#include "Convert.h"

void createMainMenu() {
    bool isInputValid = false;
    std::string validInput = "123456789Xx";
    std::string input;
    while(!isInputValid) {
        system("cls");
        std::cout << "                    MENU CHINH\n";
        std::cout << "---------------------------------------------------\n";
        std::cout << "BAI 1: \n";
        std::cout << "(1) a. Chuyen tu he 10 sang he 2.\n";
        std::cout << "(2) b. Chuyen tu he 10 sang he 16.\n";
        std::cout << "(3) c. Chuyen tu he 2 sang he 10.\n";
        std::cout << "(4) d. Chuyen tu he 16 sang he 10.\n";
        std::cout << "(5) e. Chuyen tu he 2 sang he 16.\n";
        std::cout << "---------------------------------------------------\n";
        std::cout << "BAI 2: (8bit, bu 2)\n";
        std::cout << "(6) a. Tinh tong hai day bit.\n";
        std::cout << "(7) b. Tinh hieu hai day bit.\n";
        std::cout << "(8) c. Tinh tich hai day bit.\n";
        std::cout << "(9) d. Tinh thuong hai day bit.\n";
        std::cout << "---------------------------------------------------\n";
        std::cout << "Chon cau (1-9) roi an Enter (Nhap \"x\" de thoat): ";
        std::cin >> input;

        if(input.size() != 1) {
            isInputValid = false;
            continue;
        }

        if(validInput.find(input) == -1) {
            isInputValid = false;
            continue;
        }

        bool isExit = input == "x" || input == "X";
        if (isExit) {
            break;
        }

        switch (std::stoi(input))
        {
        case 1:
            prob1_1();
            break;
        case 2:
            prob1_2();
            break;
        case 3:
            prob1_3();
            break;
        case 4:
            prob1_4();
            break;
        case 5:
            prob1_5();
            break;
        case 6:
            prob2_1();
            break;
        case 7:
            prob2_2();
            break;
        case 8:
            prob2_3();
            break;
        case 9:
            prob2_4();
            break;
        default:
            break;
        }
    }
}

//numberLength == 0 : infinite number of digits 
std::string inputAndCheck(std::string title, std::string message, int base, unsigned int numberLength = 0) {
    std::string input;
    std::string baseDigits = std::string("0123456789ABCDEF").substr(0, base);
    bool isShowAlert = false;
    bool isInputValid = false;

    while(!isInputValid) {
        system("cls");
        std::cout << title << std::endl;
        if(isShowAlert){
            std::cout << "Phai nhap trong he " << base;
            if(base) {
                std::cout << ", toi da " << numberLength << " chu so hoac it hon";
            }
            std::cout << ".\n";
        }
        std::cout << message << std::endl;
        std::cin >> input;
        for (char &c: input) c = toupper(c);

        isInputValid = true;
        if (numberLength > 0) {
            if (input.size() > numberLength)
            {
                isInputValid = false;
                continue;
            }        
        }

        for (int i = 0; i < input.size(); i++) {
            if(baseDigits.find(input[i]) == -1) {
                isInputValid = false;
                break;
            }
        }

        isShowAlert = true;
    }

    return input;
}

//decimal to binary
void prob1_1() {
    bool isContinue = true;
    while(isContinue){
        system("cls");
        std::string str_Num = inputAndCheck("Chuyen doi he co so 10 sang he co so 2", "Nhap so he 10: ", 10);
        std::cout << "Ket qua: " << convertDecToBin(str_Num) << ".\n";

        std::cout << "Nhap c de tiep tuc hoac nhap ky tu khac de thoat: ";
        std::string input;
        std::cin >> input;
        isContinue = input == "c";
    }
}

//decimal to hexadecimal
void prob1_2() {
    bool isContinue = true;
    while(isContinue){
        system("cls");
        std::string str_Num = inputAndCheck("Chuyen doi he co so 10 sang he co so 16", "Nhap so he 10: ", 10);
        std::cout << "Ket qua: " << convertDecToHex(str_Num) << ".\n";

        std::cout << "Nhap c de tiep tuc hoac nhap ky tu khac de thoat: ";
        std::string input;
        std::cin >> input;
        isContinue = input == "c";
    }
}

//binary to decimal
void prob1_3() {
    bool isContinue = true;
    while(isContinue){
        system("cls");
        std::string str_Num = inputAndCheck("Chuyen doi he co so 2 sang he co so 10", "Nhap so he 2:", 2);
        std::cout << "Ket qua: " << convertBinToDec(str_Num) << ".\n";

        std::cout << "Nhap c de tiep tuc hoac nhap ky tu khac de thoat: ";
        std::string input;
        std::cin >> input;
        isContinue = input == "c";
    }
}

//hexadecimal to decimal
void prob1_4() {
    bool isContinue = true;
    while(isContinue){
        system("cls");
        std::string str_Num = inputAndCheck("Chuyen doi he co so 16 sang he co so 10", "Nhap so he 16:", 16);
        std::cout << "Ket qua: " << convertHexToDec(str_Num) << ".\n";

        std::cout << "Nhap c de tiep tuc hoac nhap ky tu khac de thoat: ";
        std::string input;
        std::cin >> input;
        isContinue = input == "c";
    }
}

//binary to hexadecimal
void prob1_5() {
    bool isContinue = true;
    while(isContinue){
        system("cls");
        std::string str_Num = inputAndCheck("Chuyen doi he co so 2 sang he co so 16", "Nhap so he 2", 2);
        std::cout << "Ket qua: " << convertBinToHex(str_Num) << ".\n";

        std::cout << "Nhap c de tiep tuc hoac nhap ky tu khac de thoat: ";
        std::string input;
        std::cin >> input;
        isContinue = input == "c";
    }
}

//addition
void prob2_1() {
    bool isContinue = true;
    while(isContinue) {
        system("cls");
        std::string title = "Tinh tong hai so he nhi phan (8-bit, bu hai)";
        std::string str_Num1 = inputAndCheck(title, "Nhap so hang (he 2) thu nhat :", 2, MAX_BITSET);
        std::string str_Num2 = inputAndCheck(title, "Nhap so hang (he 2) thu hai :", 2, MAX_BITSET);

        system("cls");
        std::cout << str_Num1 << " + " << str_Num2 << " = " << addBinNum(str_Num1, str_Num2) << ".\n";

        std::cout << "Nhap c de tiep tuc hoac nhap ky tu khac de thoat: ";
        std::string input;
        std::cin >> input;
        isContinue = input == "c";
    }
}

//subtraction
void prob2_2() {
    bool isContinue = true;
    while(isContinue) {
        system("cls");
        std::string title = "Tinh hieu hai so he nhi phan (8-bit, bu hai)";
        std::string str_Num1 = inputAndCheck(title, "Nhap so bi tru (he 2) thu nhat :", 2, MAX_BITSET);
        std::string str_Num2 = inputAndCheck(title, "Nhap so tru (he 2) thu hai :", 2, MAX_BITSET);

        system("cls");
        std::cout << str_Num1 << " - " << str_Num2 << " = " << subtractBinNum(str_Num1, str_Num2) << ".\n";

        std::cout << "Nhap c de tiep tuc hoac nhap ky tu khac de thoat: ";
        std::string input;
        std::cin >> input;
        isContinue = input == "c";
    }
}

//Multiplication
void prob2_3() {
    bool isContinue = true;
    while(isContinue) {
        system("cls");
        std::string title =  "Tinh tich hai so he nhi phan (8-bit, bu hai)";
        std::string str_Num1 = inputAndCheck(title, "Nhap so thua so (he 2) thu nhat :", 2, MAX_BITSET);
        std::string str_Num2 = inputAndCheck(title, "Nhap so thua so (he 2) thu hai :", 2, MAX_BITSET);

        system("cls");
        std::cout << str_Num1 << " * " << str_Num2 << " = " << multiplyBinNum(str_Num1, str_Num2) << " (16-bit).\n";

        std::cout << "Nhap c de tiep tuc hoac nhap ky tu khac de thoat: ";
        std::string input;
        std::cin >> input;
        isContinue = input == "c";
    }
}

//Division
void prob2_4() {
    bool isContinue = true;
    while(isContinue) {
        system("cls");
        std::string title =  "Tinh thuong hai so he nhi phan (8-bit, bu hai)";
        std::string str_Num1 = inputAndCheck(title, "Nhap so bi chia (he 2) thu nhat :", 2, MAX_BITSET);
        std::string str_Num2 = inputAndCheck(title, "Nhap so chia (he 2) thu hai :", 2, MAX_BITSET);

        system("cls");
        auto divisionRes = divideBinNum(str_Num1, str_Num2);
        std::cout << str_Num1 << " / " << str_Num2 << " = " << divisionRes[0] << " (So du la: " << divisionRes[1] << ").\n";

        std::cout << "Nhap c de tiep tuc hoac nhap ky tu khac de thoat: ";
        std::string input;
        std::cin >> input;
        isContinue = input == "c";
    }
}