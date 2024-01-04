#include <string>
#include <vector>
#include "khmercut.h"

namespace khmercut
{

  double ClusterValue::ns_value()
  {
    if (type == "NS")
      return 1.0;
    return 0.0;
  }

  // everything except vowels
  bool iskcc(const utf8::utfchar32_t &c)
  {
    return !(c >= 0x17B6 && c <= 0x17D3 || c == 0x17DD);
  }

  bool isns(const utf8::utfchar32_t &c)
  {
    return c < 0x1780 || c > 0x17dd;
  }

  const char *get_type(const utf8::utfchar32_t &c)
  {
    if (c >= 0x1780 && c <= 0x17B5)
      return "C";
    return "NS";
  }

  void set_kcc_type(ClusterValue &g)
  {
    if (g.length == 1)
    {
      g.type = get_type(g.codepoint);
      return;
    }

    g.type = std::string("K") + std::to_string(g.length);
  }

  const std::vector<ClusterValue> graphemes(const std::string &value)
  {
    std::string::const_iterator it = value.begin();
    std::string::const_iterator end = value.end();

    ClusterValue chunk;

    utf8::utfchar32_t last_cp = 0;
    std::vector<ClusterValue> items;

    while (it != end)
    {
      utf8::utfchar32_t cp = utf8::next(it, end);
      bool num = isns(last_cp) && isns(cp);
      if (iskcc(cp) && last_cp != 0x17D2 && !num)
      {
        if (!chunk.value.empty())
        {
          set_kcc_type(chunk);
          items.push_back(chunk);
        }

        chunk = {"", "", 0, 0};
      }

      // insert the first codepoint for later checking
      if (chunk.length == 0)
      {
        chunk.codepoint = cp;
      }

      chunk.length += 1;
      utf8::append(cp, std::back_inserter(chunk.value));
      last_cp = cp;
    }

    if (!chunk.value.empty())
    {
      set_kcc_type(chunk);
      items.push_back(chunk);
    }

    return items;
  }

  CRFSuite::Item create_item(std::vector<ClusterValue> &kccs, const size_t &i)
  {
    using namespace CRFSuite;
    ClusterValue &kcc = kccs[i];
    const int maxi = kccs.size();

    Item item{
        Attribute(std::string("kcc:") + kcc.value, 1.0),
        Attribute(std::string("t:") + kcc.type, 1.0),
        Attribute(std::string("ns"), kcc.ns_value()),
    };

    item.reserve(7);
    if (i >= 1)
    {
      item.push_back(Attribute(std::string("kcc[-1]:") + kccs[i - 1].value, 1.0));
      item.push_back(Attribute(std::string("kcc[-1]t:") + kccs[i - 1].type, 1.0));
      item.push_back(Attribute(std::string("kcc[-1:0]:") + kccs[i - 1].value + kccs[i].value, 1.0));
      item.push_back(Attribute("ns-1", kccs[i - 1].ns_value()));
    }
    else
    {
      item.push_back(Attribute("BOS", 1.0));
    }

    if (i >= 2)
    {
      item.push_back(Attribute(std::string("kcc[-2]:") + kccs[i - 2].value, 1.0));
      item.push_back(Attribute(std::string("kcc[-2]t:") + kccs[i - 2].type, 1.0));
      item.push_back(Attribute(std::string("kcc[-2:-1]:") + kccs[i - 2].value + kccs[i - 1].value, 1.0));
      item.push_back(Attribute(std::string("kcc[-2:0]:") + kccs[i - 2].value + kccs[i - 1].value + kccs[i].value, 1.0));
    }

    if (i >= 3)
    {
      item.push_back(Attribute(std::string("kcc[-3]:") + kccs[i - 3].value, 1.0));
      item.push_back(Attribute(std::string("kcc[-3]t:") + kccs[i - 3].type, 1.0));
      item.push_back(Attribute(std::string("kcc[-3:0]:") + kccs[i - 3].value + kccs[i - 2].value + kccs[i - 1].value + kccs[i].value, 1.0));
      item.push_back(Attribute(std::string("kcc[-3:-1]:") + kccs[i - 3].value + kccs[i - 2].value + kccs[i - 1].value, 1.0));
      item.push_back(Attribute(std::string("kcc[-3:-2]:") + kccs[i - 3].value + kccs[i - 2].value, 1.0));
    }

    if (i < maxi - 1)
    {
      item.push_back(Attribute(std::string("kcc[+1]:") + kccs[i + 1].value, 1.0));
      item.push_back(Attribute(std::string("kcc[+1]t:") + kccs[i + 1].type, 1.0));
      item.push_back(Attribute(std::string("kcc[+1:0]:") + kccs[i].value + kccs[i + 1].value, 1.0));
      item.push_back(Attribute("ns+1", kccs[i + 1].ns_value()));
    }
    else
    {
      item.push_back(Attribute("EOS", 1.0));
    }

    if (i < maxi - 2)
    {
      item.push_back(Attribute(std::string("kcc[+2]:") + kccs[i + 2].value, 1.0));
      item.push_back(Attribute(std::string("kcc[+2]t:") + kccs[i + 2].type, 1.0));
      item.push_back(Attribute(std::string("kcc[+1:+2]:") + kccs[i + 1].value + kccs[i + 2].value, 1.0));
      item.push_back(Attribute(std::string("kcc[0:+2]:") + kccs[i].value + kccs[i + 1].value + kccs[i + 2].value, 1.0));
      item.push_back(Attribute("ns+2", kccs[i + 2].ns_value()));
    }

    if (i < maxi - 3)
    {
      item.push_back(Attribute(std::string("kcc[+3]:") + kccs[i + 3].value, 1.0));
      item.push_back(Attribute(std::string("kcc[+3]t:") + kccs[i + 3].type, 1.0));
      item.push_back(Attribute(std::string("kcc[+2:+3]:") + kccs[i + 2].value + kccs[i + 3].value, 1.0));
      item.push_back(Attribute(std::string("kcc[+1:+3]:") + kccs[i + 1].value + kccs[i + 2].value + kccs[i + 3].value, 1.0));
      item.push_back(Attribute(std::string("kcc[0:+3]:") + kccs[i].value + kccs[i + 1].value + kccs[i + 2].value + kccs[i + 3].value, 1.0));
    }

    return item;
  }

  CRFSuite::ItemSequence create_seq(std::vector<ClusterValue> &kccs)
  {
    CRFSuite::ItemSequence xseq;
    for (size_t i = 0; i < kccs.size(); i++)
    {
      xseq.push_back(create_item(kccs, i));
    }
    return xseq;
  }

  std::vector<std::string> tokenize(CRFSuite::Tagger &tagger, const std::string &text)
  {
    std::vector<ClusterValue> kccs = graphemes(text);
    CRFSuite::ItemSequence xseq = create_seq(kccs);
    CRFSuite::StringList results = tagger.tag(xseq);
    std::vector<std::string> tokens;
    std::string s;

    for (int i = 0; i < results.size(); i++)
    {
      std::string tag = results[i];
      if (tag == "1" || i == 0)
      {
        if (!s.empty())
          tokens.push_back(s);
        s = kccs[i].value;
        continue;
      }
      s += kccs[i].value;
    }

    if (!s.empty())
      tokens.push_back(s);
    return tokens;
  }
}
