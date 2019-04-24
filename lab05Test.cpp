#include "WordCount.h"
#include <iostream>
#include <sstream>
#include "tddFuncs.h"
using namespace std;

int main(){
  cout << "Testing WordCount.cpp...\n";

  WordCount t1;
  t1.addAllWords(" \nhel&lo \nmy - *name is ");
  //t1.addAllWords("hello my name is");
  ASSERT_EQUALS(1, t1.getWordCount("hello"));
  ASSERT_EQUALS(1, t1.getWordCount("my"));
  ASSERT_EQUALS(1, t1.getWordCount("name"));
  ASSERT_EQUALS(1, t1.getWordCount("is"));

  t1.addAllWords("one taught me love\none taught me patience\none taught me pain\n");

  std::ostringstream oss1;
  
  t1.dumpWordsSortedByWord(oss1);
  //cout <<oss1.str()<<endl;
  //cout << "-----------\n";

  std::ostringstream oss2;
  t1.dumpWordsSortedByOccurence(oss2);
  //cout << oss2.str()<<endl;


  ASSERT_EQUALS("HELLO,1\nIS,1\nLOVE,1\nME,3\nMY,1\nNAME,1\nONE,3\nPAIN,1\nPATIENCE,1\nTAUGHT,3\n", oss1.str());

  ASSERT_EQUALS("ME,3\nONE,3\nTAUGHT,3\nHELLO,1\nIS,1\nLOVE,1\nMY,1\nNAME,1\nPAIN,1\nPATIENCE,1\n", oss2.str());
  
  return 0;
}
