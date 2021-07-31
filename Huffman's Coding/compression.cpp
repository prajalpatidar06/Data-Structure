#include"hoffman.hpp"
#include<fstream>
#include<bitset>

int main(){
    char ch;
    fstream in ("test.txt");
    unordered_map<char , int> data;
    while(!in.eof()){
        in>>ch;
        if(ch >= 65 && ch <= 90)ch +=32;
        data[ch]++;
    }
    in.close();
    huffmanCodes(data);

    string code;
    fstream in2 ("test.txt");
    while(!in2.eof()){
        in2>>ch;
        if(ch >= 65 && ch <= 90)ch +=32;
        code += encrypt_keys[ch];
    }
    in2.close();

    string output_str;
    int itr = 0 , code_size = code.size();
    while(itr < code_size){
        bitset<8>bt(code.substr(itr , (itr+8 < code_size) ? itr+8 : code_size));
        unsigned long code_i = bt.to_ulong();
        output_str += static_cast<unsigned char>(code_i);
        itr = itr+8;
    }

    ofstream out("nenc.txt");
    out<<output_str;
    out.close();
    return 0;
}
