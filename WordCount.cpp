// WordCount.cpp
// Written by Richert Wang for CS 32, F18.

#include "WordCount.h"

using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
  int total=0;
  for(size_t i=0; i<CAPACITY; i++){
    vector<pair<string,size_t>>v=table[i];
    for(size_t j=0; j<v.size();j++){
      total+=v[j].second;
    }
  }
  return total;
}

int WordCount::getNumUniqueWords() const {
  int count = 0;
  for(size_t i=0; i<CAPACITY; i++){
    vector<pair<string,size_t>>v = table[i];
    count+=v.size();
  }
  return count;
}

int WordCount::getWordCount(std::string word) const {
  int count = 0;
  string validWord="";
  for(unsigned int i=0; i<stripWord(word).length();i++){
    char c=(stripWord(word))[i];
    validWord+=toupper(c);
  }
  size_t index = hash(validWord);
  vector<pair<string, size_t>> v = table[index];
  for(size_t i=0; i<v.size(); i++){
    if (v[i].first == validWord){
      count = v[i].second;
    }
  }
  return count;
}
	

int WordCount::incrWordCount(std::string word) {
  string validWord ="";
  for(unsigned int i=0; i<stripWord(word).length();i++){
    char c=(stripWord(word))[i];
    validWord+=toupper(c);
  }
  if(validWord=="")
    return 0;
  size_t index = hash(validWord);
  int newCount=0;
  if(getWordCount(validWord)==0){
    pair<string,size_t>p(validWord, 1);
    table[index].push_back(p);
    newCount = 1;
  }else{
    for(size_t i=0; i<table[index].size(); i++){
      if ((table[index])[i].first==validWord){
	(table[index])[i].second++;
	newCount = (table[index])[i].second;
      }
    }
  }
  return newCount;
}


bool WordCount::isWordChar(char c) {
  int i = isalpha(static_cast<unsigned char>(c));
  if (i!=0)
    return true;
  else
    return false;
}


std::string WordCount::stripWord(std::string word) {
  char c;
  string result="";
  for (unsigned int i=0; i<word.length(); i++){
    c = word[i];
    if (isWordChar(c)){
      result += word[i];
    }else if((c=='-' || c=='\'')&& i!=0 && i!=word.length()-1){
      if(isWordChar(word[i-1])&&isWordChar(word[i+1]))
	 result+=word[i];
    }
  }
  return result;
}


void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
  int total = this->getNumUniqueWords();
  string words[total];
  string result="";
  int ai=0;
  for(size_t i=0; i<CAPACITY; i++){
    vector<pair<string,size_t>>v=table[i];
    for(size_t j=0; j<v.size();j++){
      words[ai]=v[j].first;
      ai++;
      
    }
  }

  //start sorting here
  
  string item;
  int shiftIndex;
  for (int i=1;i<total;i++){
    item = words[i];
    shiftIndex = i-1;
 
    
    while(shiftIndex>=0 && lexicographical_compare(item.begin(),item.end(),words[shiftIndex].begin(),words[shiftIndex].end())){// item<words[shiftIndex]){
    
      words[shiftIndex+1]=words[shiftIndex];
      shiftIndex -= 1;

    }
    words[shiftIndex+1]=item;
  }
  
  
  for(int i=0; i<total;i++){
    out<<words[i]<<","<<getWordCount(words[i])<<"\n";
  }
  
  return;
}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
  int total = this->getNumUniqueWords();
  string words[total];
  string result="";
  int ai=0;
  for(size_t i=0; i<CAPACITY; i++){
    vector<pair<string,size_t>>v=table[i];
    for(size_t j=0; j<v.size();j++){
      words[ai]=v[j].first;
      ai++;
      
    }
  }

  //start sorting here
  
  string item;
  int shiftIndex;
  for (int i=1;i<total;i++){
    item = words[i];
    shiftIndex = i-1;
 
    while(shiftIndex>=0 && (getWordCount(item)>getWordCount(words[shiftIndex])||(getWordCount(item)==getWordCount(words[shiftIndex])&&lexicographical_compare(item.begin(),item.end(),words[shiftIndex].begin(),words[shiftIndex].end())))){
    
      words[shiftIndex+1]=words[shiftIndex];
      shiftIndex -= 1;

    }
    words[shiftIndex+1]=item;
  }
  
  
  for(int i=0; i<total;i++){
    out<<words[i]<<","<<getWordCount(words[i])<<"\n";
  }
  
  return;
}

void WordCount::addAllWords(std::string text) {
	// STUB
  char c;
  unsigned int lastIndex = 0;
  string word = "";
  if(text[text.length()-1]!=' ' && text[text.length()-1]!='\n')
    text+=" ";
  for(unsigned int i=0; i<text.length(); i++){
    c=text[i];
    if (c==' '||c=='\n'){
      if(i!=0){
	if (text[i-1]!=' ' && text[i-1]!='\n'){
	  word = text.substr(lastIndex, i-lastIndex);
	  incrWordCount(word);
	  //lastIndex=i+1;
	}
      }
      lastIndex=i+1;
    }
  }
  return;
}

