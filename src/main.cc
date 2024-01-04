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
		std::cout << "\"" << token << "\"" << std::endl;
	}
}
