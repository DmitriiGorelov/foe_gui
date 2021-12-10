
#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

#include <cstddef>
#include <string>

//namespace global_namespace {
namespace gmas {

	
}// gmas

//} // global_namespace


/*int HexToInt(const char* s)
{
    char * x = strstr(const_cast<char*>(s), "x");
    if (x == NULL)
        x = const_cast<char*>(s);
    else
        x++;
    unsigned int v = 0;
    while (char c = *x++)
    {
        if (c < '0') return 0; //invalid character

        if (c > '9') //shift alphabetic characters down
        {
            if (c >= 'a') c -= 'a' - 'A'; //upper-case 'a' or higher
            if (c > 'Z') return 0; //invalid character

            if (c > '9') c -= 'A' - 1 - '9'; //make consecutive with digits
            if (c < '9' + 1) return 0; //invalid character
        }
        c -= '0'; //convert char to hex digit value
        v = v << 4; //shift left by a hex digit
        v += c; //add the current digit
    }

    return v;

}*/
