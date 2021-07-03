#include <iostream>
#include <conio.h>
#include <math.h>
#include <vector>
#include "hisogram.h"
#include "svg.h"
#include <curl/curl.h>
#include <sstream>
#include <string>
#include <windows.h>
#include <locale.h>
#include <iomanip>
#include <ctime>
using namespace std;

    Input read_input(istream& in, bool prompt, int argc, char* argv[], bool flag) {

    Input data;
    size_t number_count;
     if (prompt)
     {
        cerr << "Enter number count: ";
        in >> number_count;

        cerr << "Enter numbers: ";
        data.numbers = input_numbers(in, number_count);

        cerr << "Enter bin count: ";
        size_t bin_count;
        in >> bin_count;
     }
     else
     {
         if (flag)
         {
             srand(time(0));
             int number_count=0;

             for (int i=0; i<argc; i++)
             if (string(argv[i]) == "-generate")
                {
                number_count = atoi(argv[i+1]);
                break;
                }
             vector<double>random_numbers(number_count);
             for (size_t i = 0; i < number_count; i++)
             {
                 random_numbers[i] = rand() % 10;
             }
                 data.numbers = random_numbers;
                 in >> data.bin_count;
             }
             else
             {
                 in >> number_count;
                 data.numbers = input_numbers(in, number_count);
                 in >> data.bin_count;}
             }

    return data;
}

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{

    size_t data_size = item_size * item_count;

    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(reinterpret_cast<const char*>(items), data_size);

    return data_size;
}

Input
download(const string& address, int  argc, char* argv[], bool flag)
{
    stringstream buffer;

            CURL *curl = curl_easy_init();
            if(curl)
            {
                CURLcode res;
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
                curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
                res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);
                if (res != CURLE_OK)
                {
                    cout << curl_easy_strerror(res);
                    exit(1);
                }
            }
    curl_global_init(CURL_GLOBAL_ALL);
    return read_input(buffer, false, argc, argv, flag);
}

int
main(int argc, char* argv[]) {
    Input input;
    int point;
    if (argc > 1){
    bool flag = false;
    bool flag2 = false;
    setlocale (0, "RUSSIAN");
        for (size_t i=0; i < argc; i++)
        {
            if (string(argv[i]) == "-generate")
            {
                flag2=true;
                if (i == argc-1)
                {
                    cerr << "¬ведите, пожалуйста, опцию <-generate>, а затем кол-во чисел, которые вы хотите сгенирировать";
                    flag = true;
                }
                if (! isdigit(argv[i+1][0]))
                {
                    cerr << "¬ведите, пожалуйста после опции <-generate> кол-во чисел";
                    flag = true;
                }
            }
            if (string(argv[i]).size()>10) point=i;
        }
        if ((!flag) && (!flag2)) input = download(argv[1], argc, argv, false);
        if ((!flag) && (flag2)) input = download(argv[point], argc, argv, true);}
        else read_input(cin, true, argc, argv, false);
        const auto bins = make_histogram(input);
        show_histogram_svg(bins);
}

