# Ini File
Ini reader and writer class in C++

#### Usage
```C++

#include "ini.h"
...
IniFile ini("myfile.ini");
std::string value1 = ini["MySection"].getValue("MyKey");
std::string value2 = ini["MySection"]["MyKey"];          // same as above

ini["MySection"].setValue("MyKey","aaa");

```
