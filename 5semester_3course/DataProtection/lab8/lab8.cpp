#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>

using namespace std;

#define OUTPUT_FILE_NAME "output.txt"
#define KEY_FILE_NAME "key.txt"

// ---------------------------------------------------------
//                DES TABLES
// ---------------------------------------------------------

int IP[64] = {
    58,50,42,34,26,18,10,2,
    60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,
    64,56,48,40,32,24,16,8,
    57,49,41,33,25,17,9,1,
    59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,
    63,55,47,39,31,23,15,7
};

int FP[64] = {
    40,8,48,16,56,24,64,32,
    39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,
    37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,
    35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,
    33,1,41,9,49,17,57,25
};

int E[48] = {
    32,1,2,3,4,5,
    4,5,6,7,8,9,
    8,9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32,1
};

int P[32] = {
    16,7,20,21,29,12,28,17,
    1,15,23,26,5,18,31,10,
    2,8,24,14,32,27,3,9,
    19,13,30,6,22,11,4,25
};

int PC1[56] = {
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,
    19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,
    7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,
    21,13,5,28,20,12,4
};

int PC2[48] = {
    14,17,11,24,1,5,
    3,28,15,6,21,10,
    23,19,12,4,26,8,
    16,7,27,20,13,2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32
};

int SHIFTS[16] = {
    1,1,2,2,2,2,2,2,
    1,2,2,2,2,2,2,1
};

int SBOX[8][4][16] = {
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

// ---------------------------------------------------------
//                HELPERS
// ---------------------------------------------------------

string readFile(const string& path) {
    ifstream f(path);
    if (!f.is_open()) throw runtime_error("Cannot open file!");
    return string((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
}

void writeFile(const string& path, const string& content) {
    ofstream f(path);
    if (!f.is_open()) throw runtime_error("Cannot write file!");
    f << content;
}

bitset<64> stringToBlock(const string& s) {
    bitset<64> b(0);
    for (int i = 0; i < 8; i++) {
        unsigned char c = (i < s.size() ? s[i] : 0);
        for (int j = 0; j < 8; j++)
            b[63 - (i * 8 + j)] = (c >> (7 - j)) & 1;
    }
    return b;
}

string blockToString(bitset<64> b) {
    string s(8, '\0');
    for (int i = 0; i < 8; i++) {
        unsigned char c = 0;
        for (int j = 0; j < 8; j++)
            c |= b[63 - (i * 8 + j)] << (7 - j);
        s[i] = c;
    }
    return s;
}

bitset<64> permute(const bitset<64>& in, int* table, int size) {
    bitset<64> out;
    for (int i = 0; i < size; i++)
        out[size - 1 - i] = in[64 - table[i]];
    return out;
}

bitset<48> permute48(const bitset<32>& in) {
    bitset<48> out;
    for (int i = 0; i < 48; i++)
        out[47 - i] = in[32 - E[i]];
    return out;
}

bitset<32> SBox(bitset<48> in) {
    bitset<32> out;
    int bitPos = 31;

    for (int box = 0; box < 8; box++) {
        int row = in[47 - (box * 6)] * 2 + in[47 - (box * 6 + 5)];
        int col = 0;
        for (int i = 1; i <= 4; i++)
            col = col * 2 + in[47 - (box * 6 + i)];

        int val = SBOX[box][row][col];

        for (int k = 0; k < 4; k++)
            out[bitPos--] = (val >> (3 - k)) & 1;
    }
    return out;
}

bitset<32> permuteP(bitset<32> in) {
    bitset<32> out;
    for (int i = 0; i < 32; i++)
        out[31 - i] = in[32 - P[i]];
    return out;
}

vector<bitset<48>> generateKeys(bitset<64> key) {
    vector<bitset<48>> keys(16);

    bitset<56> k;
    for (int i = 0; i < 56; i++)
        k[55 - i] = key[64 - PC1[i]];

    bitset<28> C, D;
    for (int i = 0; i < 28; i++) {
        C[27 - i] = k[55 - i];
        D[27 - i] = k[27 - i];
    }

    for (int r = 0; r < 16; r++) {
        C = (C << SHIFTS[r]) | (C >> (28 - SHIFTS[r]));
        D = (D << SHIFTS[r]) | (D >> (28 - SHIFTS[r]));

        bitset<56> CD;
        for (int i = 0; i < 28; i++) {
            CD[55 - i] = C[27 - i];
            CD[27 - i] = D[27 - i];
        }

        for (int i = 0; i < 48; i++)
            keys[r][47 - i] = CD[56 - PC2[i]];
    }

    return keys;
}

bitset<64> DESencrypt(bitset<64> block, const vector<bitset<48>>& keys) {
    block = permute(block, IP, 64);

    bitset<32> L, R;
    for (int i = 0; i < 32; i++) {
        L[31 - i] = block[63 - i];
        R[31 - i] = block[31 - i];
    }

    for (int r = 0; r < 16; r++) {
        bitset<48> ER = permute48(R);
        ER ^= keys[r];

        bitset<32> f = permuteP(SBox(ER));

        bitset<32> newR = L ^ f;
        L = R;
        R = newR;
    }

    bitset<64> RL;
    for (int i = 0; i < 32; i++) {
        RL[63 - i] = R[31 - i];
        RL[31 - i] = L[31 - i];
    }

    return permute(RL, FP, 64);
}

bitset<64> DESdecrypt(bitset<64> block, const vector<bitset<48>>& keys) {
    vector<bitset<48>> revKeys = keys;
    reverse(revKeys.begin(), revKeys.end());
    return DESencrypt(block, revKeys);
}

// ---------------------------------------------------------
//                    MAIN
// ---------------------------------------------------------

int main() {
    cout << "=== DES Cipher ===\n1. Encrypt\n2. Decrypt\nChoose: ";
    int mode;
    cin >> mode;
    cin.ignore();

    cout << "Enter file path: ";
    string path;
    getline(cin, path);

    string input = readFile(path);

    cout << "\nFILE CONTENT:\n" << input << "\n\n";

    cout << "Enter 8-byte key: ";
    string keystr;
    getline(cin, keystr);
    while (keystr.size() < 8) keystr.push_back(0x01);

    writeFile(KEY_FILE_NAME, keystr);

    bitset<64> key = stringToBlock(keystr);
    vector<bitset<48>> keys = generateKeys(key);

    string output;
    if (mode == 1) {
        cout << "Encrypting...\n";
        for (size_t i = 0; i < input.size(); i += 8) {
            bitset<64> b = stringToBlock(input.substr(i, 8));
            auto e = DESencrypt(b, keys);

            stringstream ss;
            ss << hex << setw(16) << setfill('0') << e.to_ullong();
            output += ss.str() + " ";
        }
    }
    else {
        cout << "Decrypting...\n";
        stringstream ss(input);
        string hexblock;

        while (ss >> hexblock) {
            unsigned long long val = stoull(hexblock, nullptr, 16);
            bitset<64> b(val);

            auto d = DESdecrypt(b, keys);
            output += blockToString(d);
        }
    }

    cout << "\nRESULT:\n" << output << "\n";
    writeFile(OUTPUT_FILE_NAME, output);
    cout << "\nSaved to " OUTPUT_FILE_NAME "\n";

    return 0;
}
