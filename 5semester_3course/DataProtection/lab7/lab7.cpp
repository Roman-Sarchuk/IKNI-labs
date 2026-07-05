#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;


#define OUTPUT_FILE_NAME "output.txt"


string readFileContent(const string& filePath) {
    ifstream fin(filePath);
    if (!fin.is_open()) {
        cout << "Cannot open " << filePath << "\n";
        return "";
    }

    stringstream buffer;
    buffer << fin.rdbuf();
    return buffer.str();
}


long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}


long long modInverse(long long e, long long phi) {
    long long d = 1;
    while ((d * e) % phi != 1) d++;
    return d;
}


long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        exp >>= 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    long long p = 61, q = 53;
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = 17;
    long long d = modInverse(e, phi);

    cout << "Public key: (" << e << ", " << n << ")\n";
    cout << "Private key: (" << d << ", " << n << ")\n";

    int choice;

    cout << "\n=== RSA cipher ===" << endl;
    cout << "1. Encryption" << endl;
    cout << "2. Decryption" << endl;
    cout << "Choose an option (1 or 2): ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        // --- Encrypting ---
        // Get the plaintext
        string plaintextPath;

        cout << "\nEnter the path to the plaintext file: ";
        getline(cin, plaintextPath);

        string plaintext = readFileContent(plaintextPath);

        cout << "\nPlaintext:\n" << plaintext << endl;

        // Encrypt
        vector<long long> encrypted;
        for (char ch : plaintext) {
            long long c = modPow((int)ch, e, n);
            encrypted.push_back(c);
        }

		cout << "\nEncrypted:\n";
        for (long long c : encrypted)
			cout << c << " ";
		cout << endl;

        // Save result
        ofstream fout(OUTPUT_FILE_NAME);
        for (long long c : encrypted)
            fout << c << " ";
        fout.close();
    }
    else if (choice == 2) {
        // --- Decrypting ---
        // Get the plaintext
        string ciphertextPath;

        cout << "\nEnter the path to the ciphertext file: ";
        getline(cin, ciphertextPath);

        string ciphertext = readFileContent(ciphertextPath);

		// Validate num data
        bool isNumData = true;
        for (char c : ciphertext) {  
            if (!isdigit(c) && c != ' ' && c != '\n') {
                isNumData = false;
                break;
            }
        }

        if (!isNumData) {
            cerr << "The ciphertext file does not contain valid numerical data!" << endl;
            return 1;
		}

        cout << "\nCiphertext (numbers):\n" << ciphertext << endl;
        cout << endl;

        // Parse & decrypt
        stringstream ss(ciphertext);
        long long num;
        string decrypted = "";

        while (ss >> num) {
            char ch = (char)modPow(num, d, n);
            decrypted.push_back(ch);
        }

        cout << "\nDecrypted:\n" << decrypted << endl;

        // Save result
        ofstream fout(OUTPUT_FILE_NAME);
        fout << decrypted;
        fout.close();
    }
    else {
        cerr << "Invalid option!" << endl;
        return 1;
    }

    return 0;
}
