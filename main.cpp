/*
*Read .ndx file
*Auburn University
*Yinbo Chen
*Date: 04/15/2024
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

vector<int> extractValue(string str,vector<int> int_v){
    stringstream ls;
    ls << str;
    string tempLine;
    int foundInt;
    while(!ls.eof()){
        ls >> tempLine;
        if (stringstream(tempLine) >> foundInt){
            //cout << foundInt << " ";
            int_v.push_back(foundInt);
        }
        tempLine = " ";
    }
    return int_v;
}

int readFile(string file_name, string key_name){
    ifstream in(file_name);
    const char* sub_string = "[";
    map<string, vector<int>> mp;

    if(!in){
        cout <<"Cannot open input file.\n";
        return 1;
    }
    char str[1024];
    //key
    std::vector<string> v;
    //value
    std::vector<int> int_v;
    bool detect_title = false;
    int flag = 0;
    while(in){
        in.getline(str,1024);
        string conv_string_char_arr = str;
        if(in){
            if(conv_string_char_arr.find(sub_string)!=string::npos){
                //cout<< str <<endl;
                v.push_back(str);
                if (flag > 0){
                    //ugly...
                    mp[(&v.back())[-1]] = int_v;
                    int_v.clear();
                    flag = 0;
                }
            }else{
                int_v = extractValue(str,int_v);
                flag++;
            }
        }
    }
    mp[v.back()] =int_v;
    int_v.clear();
    in.close();

    //inter all key values
    for (string n : v)
        std::cout << n << ' ';
    std::cout << '\n';

    //get the values from key value
    string test = "[ "+key_name+" ]";
    cout <<test<< ":" << ' ';
    for(int n: mp[test]){
        std::cout << n << ' ';
    }
    std::cout << '\n';
    return 0;
}

int main(int argc, char *argv[])
{
    string file_loc;
    string key_name;
    int error_code;
    if(argc == 3){
        file_loc = argv[1];
        key_name = argv[2];
    }else if(argc ==2){
        file_loc = argv[1];
        std::cout << "Enter Key Value: ";
        std::cin >> key_name;
    }else{
        std::cout << "Enter File Location: ";
        std::cin >> file_loc;
        std::cout << "Enter Key Value: ";
        std::cin >> key_name;
    }

    error_code = readFile(file_loc,key_name);

    return 0;
}
