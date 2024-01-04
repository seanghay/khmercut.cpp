## khmercut.cpp

A portable Khmer word boundary detection library using CRFSuite.



### Build

```shell
git clone --recursive https://github.com/seanghay/khmercut.cpp.git

mkdir build

cd build

cmake ..

make -j

./khmercut

```


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

### License

`Apache-2.0`


### Reference

- [VietHoang1512/khmer-nltk](https://github.com/VietHoang1512/khmer-nltk) 
- [crf_ner_10000.crfsuite](./crf_ner_10000.crfsuite) is extracted from [here](https://github.com/VietHoang1512/khmer-nltk/blob/main/khmernltk/word_tokenize/sklearn_crf_ner_10000.sav) by using a script below:

```python
import khmernltk.word_tokenize import model_path, load_model
import shutil

model = load_model(model_path)
shutil.copy(model.modelfile.name, "crf_ner_10000.crfsuite")
```