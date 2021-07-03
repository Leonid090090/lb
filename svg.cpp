#include <iostream>
#include <vector>
#include "svg.h"
#include <windows.h>
#include <sstream>
#include <string>
using namespace std;

    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const auto MAX_COUNT = 34;

void
svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end()
{
    cout << "</svg>\n";
}

void
svg_text(double left, double baseline, string text)
{

    cout << "<text x='" << left << "' y='"<< baseline <<"'>"<< text <<"</text>\n";

}

void svg_rect(double x, double y, double width, double height)
{
    cout << "<rect x='"<< x <<"' y='"<< y <<"' width='"<< width <<"' height='"<< height <<"'/>\n";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill )
{
    cout << "<rect x='"<< x <<"' y='"<< y <<"' width='"<< width <<"' height='"<< height <<"' stroke='"<<stroke<<"' fill='"<< fill<<"'/>\n";
}

double
opacity_factor (size_t bin, size_t max_count)
{
    double opacity = (double)bin / max_count;
    return opacity;
}

string
make_info_text()
{
    stringstream buffer;
    DWORD WINAPI GetVersion(void);

    DWORD info = GetVersion();
    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = info & mask;;
    DWORD platform = info >> 16;
    DWORD maska = 0b00000000'11111111;
    if ((info & 0x40000000) == 0)
    {
        DWORD version_major = version & maska;
        DWORD version_minor = version >> 8;
        DWORD build = platform;
        buffer << "Windows v" << version_major << "." << version_minor << "(build " << build << ")\n";
    }
    DWORD size = MAX_COMPUTERNAME_LENGTH + 1;
    char pc_n[MAX_COMPUTERNAME_LENGTH + 1];

    GetComputerNameA(pc_n, &size);
    buffer << "PC name: " << pc_n << '\n';
    return buffer.str();
}

double ind (const double bin_width)
{
    double xr;
    xr = IMAGE_WIDTH - TEXT_WIDTH - bin_width;
    return xr;
}

void
show_histogram_svg(const vector<size_t>& bins)
{
    double top = 0;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    size_t max_count = bins[0];
    for (size_t bin : bins)
    {
        if (bin > max_count)
        {
            max_count = bin;
        }
    }

    if (max_count > MAX_COUNT)
    {

        const double scaling_factor = (double)MAX_COUNT / max_count;

        for (size_t bin : bins)
        {
            auto height = (size_t)(bin * scaling_factor);
            const double bin_width = BLOCK_WIDTH * height;

            svg_rect(ind(bin_width), top, bin_width, BIN_HEIGHT, "blue", "#ff2233");
            svg_text(IMAGE_WIDTH - TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            top += BIN_HEIGHT;

        }
        svg_text(1, top + TEXT_BASELINE, make_info_text());

        svg_end();
    }
    else
    {
        for (size_t bin : bins)
        {

            const double bin_width = BLOCK_WIDTH * bin;

            svg_rect(ind(bin_width), top, bin_width, BIN_HEIGHT, "blue", "#aaffaa");
            svg_text(IMAGE_WIDTH - TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            top += BIN_HEIGHT;

        }
        svg_text(1, top + TEXT_BASELINE, make_info_text());
        svg_end();

    }

}
