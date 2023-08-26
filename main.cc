#include "crfsuite.hpp"
#include "crfsuite_api.hpp"

int main(int argc, const char *argv[])
{
	CRFSuite::Tagger tagger;
	tagger.open("crf_ner_10000.crfsuite");
	for (std::string label : tagger.labels())
	{
		printf("label=%s\n", label.c_str());
	}
	tagger.close();
}
