#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    cout
            << "Do you want to encrypt or decrypt?\n Type your choice (encryption or decryption): "; // const string mode(argv[1]); // Режим работы
    string mode;
    cin >> mode;
    string file_name; // Имя файла
    cout << endl << "Enter the password (integer number): ";
    int seed;
    cin >> seed;
    if (mode == "encryption") {     //////////////////////////////////// Режим шифрование
        srand(seed);
        cout << "Enter name of your file to write encrypted data: ";
        cin >> file_name;
        ofstream out;
        out.open(file_name, std::ios::binary);
        cout << "Enter text for encryption: ";
        string input;
        cin.get();
        getline(cin, input);
        const char *data = input.data();
        int sizing = input.length();
        vector<char> b(sizing);
        for (int i = 0; i < sizing; i++) {
            b[i] = data[i];
        }
        for (int i = 0; i < sizing; i += 2) {
            unsigned int gamma = rand();
            unsigned char b1 = b[i],
                    b2 = i + 1 < sizing ? b[i + 1] : 0u;
            unsigned int xored = ((static_cast<unsigned int>(b[i]) << 8u) | static_cast<unsigned int>(b[i + 1])) ^ gamma;
            unsigned int output = ((xored & 0x0000FFFF) >> 3) | (xored << 13);
            char ch = output >> 8;
            out.write(&ch, sizeof(ch));
            ch = output;
            out.write(&ch, sizeof(ch));
        }
    } else if (mode ==
               "decryption") {//////////////////////////////////////////////////////////////// Режим расшифрования
        srand(seed);
        cout << "Enter name of your file with data for decryption: ";
        cin >> file_name;
        ifstream in;
        in.open(file_name, ios::binary);
        vector<char> b((istreambuf_iterator<char>(in)), (istreambuf_iterator<char>()));
        for (int i = 0; i < static_cast<int>(b.size()); i += 2) {
            unsigned int gamma = rand();

            unsigned char b1 = b[i],
                    b2 = b[i + 1];

            unsigned int union1 = (static_cast<unsigned int>(b1) << 8u) | static_cast<unsigned int>(b2),
                         union2 =( union1 << 3) | ((union1 & 0x0000FFFF) >> 13),
                         output = union2 ^gamma;

            char ch = output >> 8;
            cout << ch;
            ch = output;
            cout << ch;
        }
        in.close();
    }
    return 0;
}
