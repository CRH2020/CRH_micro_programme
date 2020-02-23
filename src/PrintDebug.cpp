#include <mbed.h>
mbed::Callback<int (const char * fmt)> PRINTDEBUG(&puts);