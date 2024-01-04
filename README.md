## khmercut.cpp

A portable Khmer word boundary detection library using CRFSuite.


### Usage

```cpp
#include "crfsuite.hpp"
#include "crfsuite_api.hpp"
#include "khmercut.h"

int main(int argc, const char *argv[])
{
	CRFSuite::Tagger tagger;
	tagger.open("../crf_ner_10000.crfsuite");

	std::string text = "ឃាត់ខ្លួនជនសង្ស័យ០៤នាក់ ករណីលួចខ្សែភ្លើង នៅស្រុកព្រៃនប់";
	CRFSuite::StringList tokens = khmercut::tokenize(tagger, text);
	
	for (const auto &token : tokens)
	{
		std::cout << token << std::endl;
	}
}
```

#### Result

```
ឃាត់ខ្លួន
ជនសង្ស័យ
០៤
នាក់
 
ករណី
លួច
ខ្សែភ្លើង
 
នៅ
ស្រុក
ព្រៃនប់
```


### Build binary

```shell
mkdir build

cd build

cmake ..

make -j

./khmercut

```


### License

`Apache-2.0`
