#include "Calculation.h"

std::string addBinNum(std::string str_binNum1, std::string str_binNum2) {
    std::bitset<MAX_BITSET> binNum1(str_binNum1);
    std::bitset<MAX_BITSET> binNum2(str_binNum2);
    std::bitset<MAX_BITSET> carry{0};
    std::bitset<MAX_BITSET> res{0};

    res = binNum1 ^ binNum2;
    carry = binNum1 & binNum2;
    
    while (carry != 0b0) {
        std::bitset<MAX_BITSET> oldRes{res};
        carry <<= 1;
        res ^= carry;
        carry &= oldRes;
    }
    //check overflow
    if(binNum1[MAX_BITSET-1] == binNum2[MAX_BITSET-1]) {
        if (binNum1[MAX_BITSET-1] ^ res[MAX_BITSET-1]) {
            return "Tran so!";
        }
    }

    return res.to_string();
}

std::string subtractBinNum(std::string str_binNum1, std::string str_binNum2) {
    std::bitset<MAX_BITSET> binNum2(str_binNum2);
    binNum2 = convertToNegative_2Complement(binNum2);
    return addBinNum(str_binNum1, binNum2.to_string());
}

std::bitset<MAX_BITSET> addBinNum_IgnoreOverFlowCheck(std::string str_binNum1, std::string str_binNum2) {
    std::bitset<MAX_BITSET> binNum1(str_binNum1);
    std::bitset<MAX_BITSET> binNum2(str_binNum2);
    std::bitset<MAX_BITSET> carry{0};
    std::bitset<MAX_BITSET> res{0};

    res = binNum1 ^ binNum2;
    carry = binNum1 & binNum2;

    while (carry != 0b0) {
        std::bitset<MAX_BITSET> oldRes{res};
        carry <<= 1;
        res ^= carry;
        carry &= oldRes;
    }

    return res;
}

std::bitset<MAX_BITSET> subtractBinNum_IgnoreOverflowCheck(std::string str_binNum1, std::string str_binNum2) {
    std::bitset<MAX_BITSET> binNum2(str_binNum2);
    //convert num2 to "2's complement negative number" 
    binNum2 = ~binNum2;
    for (int i = 0; i < MAX_BITSET; i++) {
        binNum2[i] = binNum2[i] ^ 0b1;
        if(binNum2[i] == 0b1) {
            break;
        }
    }
    //
    return addBinNum_IgnoreOverFlowCheck(str_binNum1, binNum2.to_string());
}

//Booth's multiplication algorithm
std::string multiplyBinNum(std::string str_binNum1, std::string str_binNum2) {
    std::bitset<MAX_BITSET> M(str_binNum1); 
    std::bitset<MAX_BITSET+1> Q(str_binNum2 + "0"); //add 1 bit at LSB
    std::bitset<MAX_BITSET> A{0};

    for (int k = MAX_BITSET; k > 0; k--) {
        std::bitset<2> twoLSB;
        twoLSB[0] = Q[0];
        twoLSB[1] = Q[1];

        std::bitset<MAX_BITSET> tempRes;

        if(twoLSB == 0b10) {
            tempRes = subtractBinNum_IgnoreOverflowCheck(A.to_string(), M.to_string());
            A = tempRes;
        }
        else if (twoLSB == 0b01) {
            tempRes = addBinNum_IgnoreOverFlowCheck(A.to_string(), M.to_string());
            A = tempRes;
        }

        //Shift right [AQQ-1]
        Q >>= 1;
        Q[MAX_BITSET] = A[0];
        A >>= 1;
        A[MAX_BITSET-1] = A[MAX_BITSET-2]; //restore sign bit
    }

    std::string res = A.to_string() + Q.to_string();
    res.pop_back();
    return res;
}

//quotient : res[0]
//remainder : res[1]
std::vector<std::string> divideBinNum(std::string str_binNum1, std::string str_binNum2) {
    std::bitset<MAX_BITSET> Q(str_binNum1); 
    std::bitset<MAX_BITSET> M(str_binNum2);
    std::bitset<MAX_BITSET> A;

    bool signBit_Q = Q[MAX_BITSET-1];
    bool signBit_M = M[MAX_BITSET-1];

    /* Checking if the sign bit of Q is 1 or 0. 
    -If it is 1, then A is set to all 1s. 
    -If it is 0, then A is set to all 0s. */
    if (Q[MAX_BITSET-1] & 1) {
        A.set();
    } else {
        A.reset();
    }

    // case 1000_0000 (-128) -> assume Q = 128 -> set A = 00..00
    std::bitset<MAX_BITSET> maxNegative("1" + std::string(MAX_BITSET-1, '0'));
    if(Q == maxNegative) {
        A.reset();
    }
    Q = convertToPositive_2Complement(Q);
    M = convertToPositive_2Complement(M);

    for (int k = MAX_BITSET; k > 0; k--) {
        //shift left [A, Q]
        A <<= 1;
        A[0] = Q[MAX_BITSET-1];
        Q <<= 1;

        std::bitset<MAX_BITSET> tempRes(subtractBinNum_IgnoreOverflowCheck(A.to_string(), M.to_string()));
        if (tempRes[MAX_BITSET-1] & 1) {
            Q[0] = 0;
        }
        else {
            Q[0] = 1;
            A = tempRes;
        }
    }

    //correct sign bit of quotient(Q) and remainder(A)
    bool signBit_Res = signBit_Q ^ signBit_M;
    bool signBit_Remainder = signBit_Q;
    if(signBit_Res) {
        Q = convertToNegative_2Complement(Q);
    }
    if(signBit_Remainder) {
        A = convertToNegative_2Complement(A);
    }
    std::vector<std::string> res;
    res.push_back(Q.to_string());
    res.push_back(A.to_string());

    return res;
}

std::bitset<MAX_BITSET> convertToPositive_2Complement(std::bitset<MAX_BITSET> binNum) {
    // case 1000_0000 (-128) -> leave the binNum untouched
    std::bitset<MAX_BITSET> maxNegative("1" + std::string(MAX_BITSET-1, '0'));
    if(binNum == maxNegative) {
        return binNum;
    }
    //check if sign bit is 1
    if(binNum[MAX_BITSET-1] & 1) {
        //subtract 1
        int i = 0;
        while(!(binNum[i] & 1) && i < MAX_BITSET) {
            binNum[i] = 1;
            i++;
        }
        binNum[i] = 0;
        //reverse bits in binNum
        binNum = ~binNum;
    }
    return binNum;
}

std::bitset<MAX_BITSET> convertToNegative_2Complement(std::bitset<MAX_BITSET> binNum) {
    if(!(binNum[MAX_BITSET-1] & 1)) {
        binNum = ~binNum;
        //add 1 to reversed binNum
        for (int i = 0; i < MAX_BITSET; i++) {
            binNum[i] = binNum[i] ^ 0b1;
            if(binNum[i] == 0b1) {
                break;
            }
        }
    }
    return binNum;
}