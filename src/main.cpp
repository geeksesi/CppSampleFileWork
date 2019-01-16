/** 
 * @Author: Mohammad Javd GHasemy - 972183065
 * @Date: 2019-01-15 
 * @Desc:  a sample to show how can we make personal simple DB by file in  c++ :D
 */


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <fstream>
#include <stdio.h>
#include <iomanip>

/**
 * 
 * Functions
 * 
 */
void get_data();
bool read_file();
void menu();
std::vector<std::string> explode(std::string const &s, char delim);

/**
 * 
 * var
 * 
 */
std::string std_name;
std::string std_code;
int class_count;
std::vector<std::string> unit_code;
std::vector<int> unit_unit;
std::vector<double> unit_mark;


std::vector<std::string> explode(std::string const &s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim);)
    {
        if (!token.empty())
           { result.push_back(std::move(token));}
    }

    return result;
}


/**
 * 
 * 
 */
void get_data()
{
    std::cout << "first i need your student code ( like : 972183065 ) \n";
    std::string std_code; std::cin >> std_code;
    std::cout << "\n Good... now can i ask your full name ? (like : mohammad_Javad_Ghasemy ) \n";
    std::string std_name; std::cin >> std_name;
    std::cout << "\n so now tell me how many class you have (like 5) \n";
    int class_count; std::cin >> class_count;

    
    std::stringstream write_to_file;
    write_to_file << std_code << "-" << std_name << "-" << class_count;
    

    std::string unit_codes[class_count];
    int         unit_units[class_count];
    double      unit_mark[class_count];

    std::cout << "\n";
    for(int i=0; i<class_count; ++i)
    {
        std::cout << "so now give me unit_code unit_units unit_mark (like : 2342 3 9.5) \n";
        std::cin >> unit_codes[i] >> unit_units[i] >> unit_mark[i];
        write_to_file <<"\n" << unit_codes[i] << "-" <<  unit_units[i] << "-" <<  unit_mark[i];
    }
    std::string write_it = write_to_file.str().c_str();

    std::ofstream myfile;
    myfile.open("StuID.txt");
    myfile << write_it;
    myfile.close();
    
    read_file();
}



bool read_file()
{
    std::ifstream in("StuID.txt");

    if (!in)
    {
        return false;
    }
    int i = 0;
    std::string str;
    while (std::getline(in, str))
    {
        if(i == 0)
        {
            auto exploded = explode(str, '-');
            std_name        = exploded[1];
            std_code        = exploded[0];
            std::stringstream iss(exploded[2]);
            iss >> class_count;
        }
        auto exploded = explode(str, '-');
        unit_code.push_back(exploded[0]);
        {
            int tmp;
            std::stringstream iss(exploded[1]);
            iss >> tmp;
            unit_unit.push_back(tmp);
            tmp = 0;
        }
        {
            double tmp1;
            std::stringstream iss(exploded[2]);
            iss >> tmp1;
            std::cout << tmp1;
            unit_mark.push_back(tmp1);

            tmp1 = 0;
        }

        ++i;
    }
    return true;
}

void menu()
{
    std::cout << "\n1_ Show your data in pretty style  :D \n";
    std::cout << "2_ you want to see yout Avg ?  @_@ \n";
    std::cout << "3_ Search by unit_code $....$...$..$.$  \n";
    std::cout << "4_ Change your data ... (it's extra position...just for you <3)   \n";
    std::cout << "F_ finish this dummy program ~~!!~~ \n";
    
    char choice;  std::cin >> choice;

    switch(choice)
    {
        case '1' :
        {
            std::cout << "\n" << std::setw(30) << std_code << " - " << std_name << "\n";
            std::cout << std::setw(20) << "Code" <<  std::setw(20)  << "Unit" << std::setw(20) << "Mark" << "\n";
            for(int i = 1; i <= (class_count); i++)
            {
                std::cout << std::setw(20) << unit_code[i] << std::setw(20) << unit_unit[i] << std::setw(20) << unit_mark[i] << "\n\n";
            }
            std::cout << "\n\n";
            std::cout << "\nMenu : i can't leave you <Press F to kill me>";
            menu();
        }break;
        case '2' :
        {
            std::cout << "\n\n";
            double this_avg = 0;
            for(int i = 1; i <= (class_count); i++)
            {
                this_avg += unit_mark[i];
            }
            this_avg = (this_avg / class_count);
            if (this_avg >= 15)
            {
                std::cout << "do you know what is respite befor exam ? it's for rest not eat book...*_*\n";
            }
            else if(this_avg >= 12)
            {
                std::cout << "Lucky man...go and enjoy... ^_^\n";
            }
            else if(this_avg >= 10)
            {
                std::cout << "Woow...wOOw...not bad :D\n";
            }
            else if(this_avg < 10)
            {
                std::cout << "units was maked to fail....don't worry  <3 \n";
            }
            std::cout << "your Average semester is : " << this_avg  << std::endl;
            std::cout << "\n\n";
            std::cout << "\nMenu : i can't leave you <Press F to kill me>";
            
            menu();
        }break;
        case '3' :
        {
            std::cout << "\n\n";
            std::cout << "enter What you need...(hit : give me unit_code) \n";
            std::string search_unit_code; std::cin >> search_unit_code;
            bool is_set = false;
            for(int i = 1; i <= (class_count); i++)
            {
                if (unit_code[i] == search_unit_code)
                {
                    is_set = true;
                    std::cout << std::setw(20) << "Code" << std::setw(20) << "Unit" << std::setw(20) << "Mark" << "\n\n";
                    std::cout << std::setw(20) << unit_code[i] << std::setw(20) << unit_unit[i] << std::setw(20) << unit_mark[i] << "\n";
                }
            }
            std::string nothing;
            std::cout << (nothing =(is_set == false) ? "i can't find this unit code\n" : "");
            std::cout << "\n\n";
            std::cout << "\nMenu : i can't leave you <Press F to kill me>";
            menu();
        }break;
        case '4' :
        {
            std::cout << "\n\n";
            get_data();
            std::cout << "\n\n";
            std::cout << "\nMenu : i can't leave you <Press F to kill me>";
            menu();
        }break;
        default :
        {
            std::cout << "\n\n";
            std::cout << "GoodLuck....i will happy to meet you again :)";

        }
        break;
    }
}   


int main(int argc, char const *argv[])
{
    std::cout << "._#_._#_._#_._HI_._#_._#_._#_.\n";
    if(read_file() == false)
    {
        std::cout << "there is no any data about you... so i think first you should give me some information \n";
        get_data();
    }
    std::cout << "Good...now tell me what u want to do ? \n";
    menu();

    return 0;
} 
