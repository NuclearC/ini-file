# Ini File
Ini reader and writer class in C++

#### Usage
```C++

#include "ini.h"
...
nc::Ini ini(".\\file.ini");

ini.Load();
// reading
auto node = ini["MySection"]; // returns IniNode
auto value = ini["MySection"]["MyProperty"]; // returns std::string
auto db = std::atoi(ini["MySection"]["MyNumber"].c_str()); // get value as signed 32-bit integer 

// writing
ini["MySection"].Set("property", "value"); // set new property with value

ini.Save(); // save ini file

```
