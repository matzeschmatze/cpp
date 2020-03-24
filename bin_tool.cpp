#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

string *arg_out(string arg_string) {
    char st[1000];
    strcpy(st, arg_string.c_str());
    string *args_out = new string[100], sst(st);
    int str_cou = 0, arg_out_cou = 0, str_beg, str_end;
    bool end_se_str = false, end_se_str1 = false, end_se_str2 = false;

    while(!end_se_str) {
        str_beg = 0, str_end = 0;
        end_se_str1 = false, end_se_str2 = false;
        while (!end_se_str1) {
            if (st[str_cou] == '"') {
                str_beg = str_cou;
                str_cou++;
                while (!end_se_str2) {
                    if (st[str_cou] == '"') {
                        str_end = str_cou;
                        end_se_str2 = true;
                    } else {
                        if (str_cou == sst.length()) {
                            end_se_str2 = true;
                        } else {
                            str_cou++;
                        }
                    }
                }
                end_se_str1 = true;
            } else {
                if (str_cou == sst.length()) {
                    end_se_str1 = true;
                } else {
                    str_cou++;
                }
            }
        }
        if (1 < str_end-str_beg-1) {
            args_out[arg_out_cou] = sst.substr(str_beg+1, str_end-str_beg-1);
            arg_out_cou++;
        }
        if (str_cou == sst.length()) {
            end_se_str = true;
        }
        str_cou++;
    }
    return args_out;
}

string decode(string decode_string, string string_coder, string bits_32_64) {
    int bit_length_or,
        bit_all[] = {1,2,4,8,16,32,64},
        bit_all_cou = 0,
        out_str_length = decode_string.length(),
        dec_cou = 1,
        dec_num = 0,
        dec_str_cou = 0,
        bit_length;
    bool decoded = false, dec_num_cou = false;
    string out_str;
    if (bits_32_64 == "32") {
        cout << "\033[32m(+) Using specified 32 Bit.\033[0m " << endl;
        bit_length = 6;
        bit_length_or = 5;
    } else if (bits_32_64 == "64") {
        cout << "\033[32m(+) Using specified 64 Bit.\033[0m " << endl;
        bit_length = 7;
        bit_length_or = 6;
    } else {
        cout << "\033[31m(!) No Bit specified. Using 64 Bit (default)\033[0m" << endl;
        bit_length = 7;
        bit_length_or = 6;
    }
    if (string_coder == "ERR:not_selected") {
        cout << "\033[31m(!) No decoder specified Using d1_64 (default)\033[0m" << endl;
        string_coder = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;#+-()_*!?=\"\'°§$&/";
    } else {
        cout << "\033[32m(+) Using specified decoder: \033[36m" << string_coder << "\033[0m" << endl;
    }

    while (!decoded) {
        while (!dec_num_cou) {
            if (decode_string.substr(dec_str_cou, 1) == "1") {
                dec_num = dec_num + bit_all[bit_all_cou];
            }
            if (bit_all_cou == bit_length_or) {
                dec_num_cou = true;
            }
            dec_str_cou++;
            bit_all_cou++;
        }
        out_str = out_str + string_coder.substr(dec_num - 1, 1);
        if (dec_cou >= out_str_length/bit_length) {
            decoded = true;
        }
        dec_cou++;
        dec_num = 0;
        dec_num_cou = false;
        bit_all_cou = 0;
    }
    return out_str;
}

string encoding(string encode_string, string string_coder, string bits_32_64) {
    bool string_encoded = false, encoded = false;
    int nums[encode_string.length()],
        char_count = 0, bit_all[8] = {64,32,16,8,4,2,1}, bit[8]= {0,0,0,0,0,0,0}, 
        bit_length = 0, num_cou = 0, bit_all_cou = 0, bit_cou = 0, out_str_cou = 0, out_strs_cou, bit_length_or = 0;
    if (bits_32_64 == "32") {
        cout << "\033[32m(+) Using specified 32 Bit.\033[0m" << endl;
        bit_length_or = 6;
        bit_all_cou++;
    } else if (bits_32_64 == "64") {
        cout << "\033[32m(+) Using specified 64 Bit.\033[0m" << endl;
        bit_length_or = 7;
    } else {
        cout << "\033[31m(!) No Bit specified. Using 64 Bit (default)\033[0m" << endl;
        bit_length_or = 7;
    }
    if (string_coder == "ERR:not_selected") {
        cout << "\033[31m(!) No encoder specified Using e1_64 (default)\033[0m" << endl;
        string_coder = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;#+-()_*!?=\"\'°§$&/";
    } else {
        cout << "\033[32m(+) Using specified encoder: \033[36m" << string_coder << "\033[0m" << endl;
    }
    string out_str[encode_string.length() * bit_length_or],
           out_all_str = "Error";
    while (!string_encoded) {
        if (char_count != encode_string.length()) {
            nums[char_count] = string_coder.find(encode_string[char_count])+1;
            if (string_coder.find(encode_string[char_count]) == string::npos) {
                cout << "\033[31m(!) \033[36m" << encode_string[char_count] << "\033[31m: Not found in encoder. Ignoring.\033[0m" << endl;
            }
            char_count++;
        } else {
            string_encoded = true;
        }
    }
    while (!encoded) {
        while (bit_length < bit_length_or) {
            if (nums[num_cou] >= bit_all[bit_all_cou]) {
                nums[num_cou] = nums[num_cou] - bit_all[bit_all_cou];
                bit[bit_cou] = 1;
            }
            bit_length++;
            bit_all_cou++;
            bit_cou++;
        }
        if (num_cou >= encode_string.length()) {
            encoded = true;
        } else {
            if (bits_32_64 == "32") {
                out_str[num_cou] = to_string(bit[5])+to_string(bit[4])+to_string(bit[3])+to_string(bit[2])+to_string(bit[1])+to_string(bit[0]);
            } else if (bits_32_64 == "64") {
                out_str[num_cou] = to_string(bit[6])+to_string(bit[5])+to_string(bit[4])+to_string(bit[3])+to_string(bit[2])+to_string(bit[1])+to_string(bit[0]);
            }
            out_all_str = out_all_str + out_str[num_cou];
            bit[0]=0,bit[1]=0,bit[2]=0,bit[3]=0,bit[4]=0,bit[5]=0,bit[6]=0,bit[7]=0,bit_length = 0,bit_cou = 0,bit_all_cou = 0;
            num_cou++;
        }
    }
    return out_all_str;
}

int main() {
    //encoding("  ", " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;#+-()_*!?=\"\'°§$&/", "64");
    //             12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012
    //                     10        20        30        40        50        60        70        80        90
    //               011001 111110 010101 010101 101101
    //     1 2 4 8163264
    //       1   1   1
    //decode("01000010100001", " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;#+-()_*!?=\"\'°§$&/", "64");
    string *set_en_args, *set_de_args, *set_dec_args, *set_enc_args;
    bool exit_sh = false, 
         back_en = false, 
         back_de = false,
         set_en_end = false;
    int set_en_b;
    string code_32_64 = "ERR:not_selected",
           dec_outer,
           enc_outer,
           code_string = "bit",
           code_32 = "32",
           code_64 = "64",
           coder = "ERR:not_selected",
           encode_string = "encoder",
           encode1_64 = "e1_64",
           encode1_32 = "e1_32",
           encode2_64 = "e2_64",
           encode2_32 = "e2_32",
           encoder_ind = "e_ind",
           decode_string = "decoder",
           decode1_64 = "d1_64",
           decode1_32 = "d1_32",
           decode2_64 = "d2_64",
           decode2_32 = "d2_32",
           decoder_ind = "d_ind",
           encoder_ind_sandbox,
           decode_out,
           encode_out,
           bef, 
           bef_en,
           bef_de;
    int set_en_pos, set_de_pos;
    char text;
    while(!exit_sh) {
        cout << "\033[46m\033[30mbin>\033[0m\033[36m";
        getline(cin, bef);
        cout << "\033[0m";
        if (bef == "help") {
            cout << endl << "\033[32mCommands:\033[0m" << endl
                 << "    \033[34mhelp                    \033[31mShows this help file.\033[0m" << endl
                 << "    \033[34mencode                  \033[31mGoes to encode shell.\033[0m" << endl
                 << "    \033[34mdecode                  \033[31mGoes to decode shell.\033[0m" << endl
                 << "    \033[34mexit                    \033[31mIs exitting shell.\033[0m" << endl
                 << "    \033[34mhex                     \033[31mThis command is made at the moment.\033[0m" << endl << endl;
        } else if (bef == "encode") {
            cout << "\033[32mEntering encode shell...\033[0m" << endl;
            while (!back_en) {
                cout << "\033[33mbin\033[0m\033[31m(\033[36mencode\033[31m)\033[33m> ";
                getline(cin, bef_en);
                cout << "\033[0m";
                if (bef_en == "help") {
                    cout << endl << "\033[32mCommands:\033[0m" << endl
                         << "    \033[34mhelp                    \033[31mShows this help file.\033[0m" << endl
                         << "    \033[34mset <value> <string>    \033[31mSet a value.\033[0m" << endl
                         << "    \033[34mencode <string>         \033[31mEncode a string.\033[0m" << endl
                         << "    \033[34mback                    \033[31mGo back to bin shell.\033[0m" << endl
                         << "    \033[34mexit                    \033[31mIs exitting shell.\033[0m" << endl << endl;
                } else if (bef_en.substr(0, 3) == "set") {
                    set_en_args = arg_out(bef_en.substr(3, bef_en.length()-3));
                    if (bef_en.find("help", 0) != string::npos) {
                        cout << endl << "\033[32mCommand:\033[0m" << endl
                             << "    \033[34mhelp                    \033[31mShows this help file.\033[0m" << endl
                             << "    \033[34mlist-encoders           \033[31mList encoders.\033[0m" << endl
                             << "    \033[34mvars                    \033[31mList all variables.\033[0m" << endl << endl
                             << "    \033[34mYou can set a value by typing: 'set <\"value\"> <\"string\">'. \033[0m" << endl
                             << "    \033[34mYou can set the values:\033[0m" << endl
                             << "          \033[34m-encoder         \033[31me1_64/e1_32/e2_64/e2_32/e_ind\033[0m" << endl
                             << "          \033[34m-bit             \033[31m32/64\033[0m" << endl << endl;
                    } else if (bef_en.find("vars", 0) != string::npos) {
                        cout << endl << "\033[32mValues:\033[0m" << endl << endl
                             << "\033[34m-Bit:        \033[32m" << code_32_64 << "\033[0m" << endl
                             << "\033[34m-Encoder:    \033[32m" << coder << endl << endl
                             << "\033[34mThe default values are 64 bit and e1_64 as encoder" << "\033[0m" << endl << endl;
                    } else if (bef_en.find("list-encoders", 0) != string::npos) {
                        cout << endl << "\033[32mEncoders:\033[0m" << endl << endl
                             << "\033[32m64 Bit:\033[0m" << endl
                             << "   \033[36m-e1_64\033[31m = \033[34m<space>ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;#+-()_*!?=\"\'°§$&/\033[0m" << endl
                             << "   \033[36m-e2_64\033[31m = \033[34m<space>0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz.,:;#+-()_*!?=\"\'°§$&/\033[0m" << endl
                             << "\033[32m32 Bit:\033[0m" << endl
                             << "   \033[36m-e1_32\033[31m = \033[34m<space>ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\033[0m" << endl
                             << "   \033[36m-e2_32\033[31m = \033[34m<space>0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz\033[0m" << endl
                             << "\033[32mOther:\033[0m" << endl
                             << "   \033[36m-e_ind\033[31m = \033[34mA individual encoder which you can specifi.\033[0m" << endl << endl;
                    } else if (set_en_args[0].find(code_string, 0) != string::npos) {
                        if (set_en_args[1].find(code_32, 0) != string::npos) {
                            code_32_64 = "32";
                            cout << set_en_args[0] << " -> " << set_en_args[1] << endl;
                        } else if (set_en_args[1].find(code_64, 0) != string::npos) {
                            code_32_64 = "64";
                            cout << "\033[36m" << set_en_args[0] << " \033[31m->\033[36m " << set_en_args[1] << "\033[0m" << endl;
                        } else {
                            cout << "\033[31mError: 'bit' can only be set to '32' or '64'.\033[0m" << endl
                                 << "\033[31mType 'set help' for help.\033[0m" << endl;
                        }
                    } else if (set_en_args[0].find(encode_string, 0) != string::npos) {
                        if (set_en_args[1].find(encode1_64, 0) != string::npos) {
                            coder = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;#+-()_*!?=\"\'°§$&/";
                            cout << "\033[36m" << set_en_args[0] << " \033[31m->\033[36m " << set_en_args[1] << "\033[0m" << endl;
                        } else if (set_en_args[1].find(encode1_32, 0) != string::npos) {
                            coder = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
                            cout << "\033[36m" << set_en_args[0] << " \033[31m->\033[36m " << set_en_args[1] << "\033[0m" << endl;
                        } else if (set_en_args[1].find(encode2_64, 0) != string::npos) {
                            coder = " 0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz.,:;#+-()_*!?=\"\'°§$&/";
                            cout << "\033[36m" << set_en_args[0] << " \033[31m->\033[36m " << set_en_args[1] << "\033[0m" << endl;
                        } else if (set_en_args[1].find(encode2_32, 0) != string::npos) {
                            coder = " 0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
                            cout << "\033[36m" << set_en_args[0] << " \033[31m->\033[36m " << set_en_args[1] << "\033[0m" << endl;
                        } else if (set_en_args[1].find(encoder_ind, 0) != string::npos) {
                            cout << "\033[32mEnter you'r encoder: \033[0m";
                            cin >> encoder_ind_sandbox;
                            //if (code_32_64 == "32" && encoder_ind_sandbox.length() > 63 || code_32_64 encode_string.IndexOf(set_en_args[0])== 64 && encoder_ind_sandbox.length() > 127)) {
                            //    cout << "Error: You'r encoder is " << encoder_ind_sandbox.length() << " long but you have selected a " << code_32_64 << " encoder." << endl;
                            //} else {
                                coder = encoder_ind_sandbox;
                                cout << "\033[36m" << set_en_args[0] << " \033[31m->\033[36m " << set_en_args[1] << "\033[0m" << endl;
                            //}
                        } else {
                            cout << "\033[31mError: Wrong input.\033[0m" << endl
                                 << "\033[31mType '\033[36mset help\033[31m' for help.\033[0m" << endl;
                        }
                    }
                } else if (bef_en.substr(0, 6) == "encode") {
                    set_enc_args = arg_out(bef_en.substr(3, bef_en.length()-3));
                    enc_outer = set_dec_args[0];
                    encode_out = decode(enc_outer, coder, code_32_64);
                    cout << encode_out << endl;
                } else if (bef_en == "back") {
                    back_en = true;
                } else if (bef_en == "exit") {
                    cout << "\033[31mExitting...\033[0m" << endl;
                    exit(0);
                } else if (bef_en == "") {} else {
                    cout << "\033[31mError: \033[36m" << bef_en << "\033[31m: Command not found.\033[0m" << endl
                         << "\033[31mType '\033[36mhelp\033[31m' for help.\033[0m" << endl;
                }
            }
            back_en = false;
        }  else if (bef == "decode") {
            cout << "\033[32mEntering decode shell...\033[0m" << endl;
            while (!back_en) {
                cout << "\033[33mbin\033[0m\033[31m(\033[36mdecode\033[31m)\033[33m> ";
                getline(cin, bef_en);
                cout << "\033[0m";
                if (bef_en == "help") {
                    cout << endl << "\033[32mCommands:\033[0m" << endl
                         << "    \033[34mhelp                    \033[31mShows this help file.\033[0m" << endl
                         << "    \033[34mset <value> <string>    \033[31mSet a value.\033[0m" << endl
                         << "    \033[34mdecode <string>         \033[31mDecode a string.\033[0m" << endl
                         << "    \033[34mback                    \033[31mGo back to bin shell.\033[0m" << endl
                         << "    \033[34mexit                    \033[31mIs exitting shell.\033[0m" << endl << endl;
                } else if (bef_en.substr(0, 3) == "set") {
                    set_en_args = arg_out(bef_en.substr(3, bef_en.length()-3));
                    if (bef_en.find("help", 0) != string::npos) {
                        cout << endl << "\033[32mCommand:\033[0m" << endl
                             << "    \033[34mhelp                    \033[31mShows this help file.\033[0m" << endl
                             << "    \033[34mlist-decoders           \033[31mList decoders.\033[0m" << endl
                             << "    \033[34mvars                    \033[31mList all variables.\033[0m" << endl << endl
                             << "    \033[34mYou can set a value by typing: 'set <\"value\"> <\"string\">'. \033[0m" << endl
                             << "    \033[34mYou can set the values:\033[0m" << endl
                             << "          \033[34m-decoder         \033[31me1_64/e1_32/e2_64/e2_32/e_ind\033[0m" << endl
                             << "          \033[34m-bit             \033[31m32/64\033[0m" << endl << endl;
                    } else if (bef_en.find("vars", 0) != string::npos) {
                        cout << endl << "\033[32mValues:\033[0m" << endl << endl
                             << "\033[34m-Bit:        \033[32m" << code_32_64 << "\033[0m" << endl
                             << "\033[34m-Decoder:    \033[32m" << coder << endl << endl
                             << "\033[34mThe default values are 64 bit and e1_64 as decoder" << "\033[0m" << endl << endl;
                    } else if (bef_en.find("list-decoders", 0) != string::npos) {
                        cout << endl << "\033[32mDecoders:\033[0m" << endl << endl
                             << "\033[32m64 Bit:\033[0m" << endl
                             << "   \033[36m-d1_64\033[31m = \033[34m<space>ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;#+-()_*!?=\"\'°§$&/\033[0m" << endl
                             << "   \033[36m-d2_64\033[31m = \033[34m<space>0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz.,:;#+-()_*!?=\"\'°§$&/\033[0m" << endl
                             << "\033[32m32 Bit:\033[0m" << endl
                             << "   \033[36m-d1_32\033[31m = \033[34m<space>ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\033[0m" << endl
                             << "   \033[36m-d2_32\033[31m = \033[34m<space>0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz\033[0m" << endl
                             << "\033[32mOther:\033[0m" << endl
                             << "   \033[36m-d_ind\033[31m = \033[34mA individual decoder which you can specifi.\033[0m" << endl << endl;
                    } else if (set_en_args[0].find(code_string, 0) != string::npos) {
                        if (set_en_args[1].find(code_32, 0) != string::npos) {
                            code_32_64 = "32";
                            cout << set_en_args[0] << " -> " << set_en_args[1] << endl;
                        } else if (set_en_args[1].find(code_64, 0) != string::npos) {
                            code_32_64 = "64";
                            cout << "\033[36m" << set_en_args[0] << " \033[31m->\033[36m " << set_en_args[1] << "\033[0m" << endl;
                        } else {
                            cout << "\033[31mError: 'bit' can only be set to '32' or '64'.\033[0m" << endl
                                 << "\033[31mType 'set help' for help.\033[0m" << endl;
                        }
                    } else if (set_en_args[0].find(decode_string, 0) != string::npos) {
                        if (set_en_args[1].find(decode1_64, 0) != string::npos) {
                            coder = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;#+-()_*!?=\"\'°§$&/";
                            cout << "\033[36m" << set_en_args[0] << " \033[31m->\033[36m " << set_en_args[1] << "\033[0m" << endl;
                        } else if (set_en_args[1].find(decode1_32, 0) != string::npos) {
                            coder = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
                            cout << "\033[36m" << set_en_args[0] << " \033[31m->\033[36m " << set_en_args[1] << "\033[0m" << endl;
                        } else if (set_en_args[1].find(decode2_64, 0) != string::npos) {
                            coder = " 0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz.,:;#+-()_*!?=\"\'°§$&/";
                            cout << "\033[36m" << set_en_args[0] << " \033[31m->\033[36m " << set_en_args[1] << "\033[0m" << endl;
                        } else if (set_en_args[1].find(decode2_32, 0) != string::npos) {
                            coder = " 0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
                            cout << "\033[36m" << set_en_args[0] << " \033[31m->\033[36m " << set_en_args[1] << "\033[0m" << endl;
                        } else if (set_en_args[1].find(decoder_ind, 0) != string::npos) {
                            cout << "\033[32mEnter you'r decoder: \033[0m";
                            cin >> encoder_ind_sandbox;
                            //if (code_32_64 == "32" && encoder_ind_sandbox.length() > 63 || code_32_64 encode_string.IndexOf(set_en_args[0])== 64 && encoder_ind_sandbox.length() > 127)) {
                            //    cout << "Error: You'r encoder is " << encoder_ind_sandbox.length() << " long but you have selected a " << code_32_64 << " encoder." << endl;
                            //} else {
                                coder = encoder_ind_sandbox;
                                cout << "\033[36m" << set_en_args[0] << " \033[31m->\033[36m " << set_en_args[1] << "\033[0m" << endl;
                            //}
                        } else {
                            cout << "\033[31mError: Wrong input.\033[0m" << endl
                                 << "\033[31mType '\033[36mset help\033[31m' for help.\033[0m" << endl;
                        }
                    }
                } else if (bef_en.substr(0, 6) == "decode") {
                    set_dec_args = arg_out(bef_en.substr(3, bef_en.length()-3));
                    dec_outer = set_dec_args[0];
                    decode_out = decode(dec_outer, coder, code_32_64);
                    cout << decode_out << endl;
                } else if (bef_en == "back") {
                    back_en = true;
                } else if (bef_en == "exit") {
                    cout << "\033[31mExitting...\033[0m" << endl;
                    exit(0);
                } else if (bef_en == "") {} else {
                    cout << "\033[31mError: \033[36m" << bef_en << "\033[31m: Command not found.\033[0m" << endl
                         << "\033[31mType '\033[36mhelp\033[31m' for help.\033[0m" << endl;
                }
            }
            back_en = false;
        } else if (bef == "exit") {
            cout << "\033[31mExitting...\033[0m" << endl;
            exit_sh = true;
        } else if (bef == "") {} else {
            cout << "\033[31mError: \033[36m" << bef << "\033[31m: Command not found.\033[0m" << endl
                 << "\033[31mType '\033[36mhelp\033[31m' for help.\033[0m" << endl;
        }
    }

    return 0;
}
