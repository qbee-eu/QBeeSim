#ifdef _MSC_VER

#include <iostream>
#include <iomanip>
#include <xpu/stdout.h>

std::ostream& operator<<(std::ostream& os, pthread_t pt)
{
    unsigned char *base = (unsigned char*)(void*)&pt;

    std::ios_base::fmtflags f(os.flags());
    os << std::setfill('0'); // fill with 0s
    for (size_t i = 0; i < sizeof(pt); i++) {
        os << std::hex << std::setw(2) << int(base[i]);
    }
    os.flags(f);
    return os;
}
#endif // _MSC_VER
