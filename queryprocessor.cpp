#include <iostream>
#include <sstream>
#include <algorithm>

#include "queryprocessor.h"
#include "stemming/english_stem.h"

QueryProcessor::QueryProcessor()
{
    myIndexHandler = nullptr;
    queryWords = "";
    useAvl = false;
    index = nullptr;
    outputLL = new LinkedList();
    parentheses = "";
    nestCounter = 0;
    //temp = "veda";
}

QueryProcessor::QueryProcessor(IndexHandler*& ih ,std::string& searchText,
                               bool& avlTree)
{
    myIndexHandler = ih;
    queryWords = searchText;
    useAvl = avlTree;
    index = nullptr;
    outputLL = new LinkedList();
    parentheses = "";
    nestCounter = 0;
    //temp = "veda";
    toLower();
}

void QueryProcessor::toLower()
{
    std::stringstream ss(queryWords);
    std::string lowerQueryWords = "";
    std::string temp = "";
    int keywordCounter = 1;

    while (ss)
    {
        ss >> temp;
        if (ss && (temp == "AND" || temp == "(AND"))
        {
            if (keywordCounter == 1)
            {
                lowerQueryWords = temp;
                keywordCounter++;
            }
            else
            {
                lowerQueryWords += " " + temp;
                keywordCounter++;
            }
        }
        else if (ss && (temp == "OR" || temp == "(OR"))
        {
            if (keywordCounter == 1)
            {
                lowerQueryWords = temp;
                keywordCounter++;
            }
            else
            {
                lowerQueryWords += " " + temp;
                keywordCounter++;
            }
        }
        else if (ss && (temp == "NOT" || temp == "(NOT"))
        {
            if (keywordCounter == 1)
            {
                lowerQueryWords = temp;
                keywordCounter++;
            }
            else
            {
                lowerQueryWords += " " + temp;
                keywordCounter++;
            }
        }
        else if (ss)
        {
            std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if (keywordCounter == 1)
                lowerQueryWords = temp;
            else
                lowerQueryWords += " " + temp;
        }
    }

    queryWords = lowerQueryWords;
    separateKeywords(queryWords);
}

void QueryProcessor::separateKeywords(std::string& searchQuery)
{
    cout<<searchQuery<<endl;
    std::vector<std::string> keywords = {};
    std::stringstream ss(searchQuery);
    std::string temp = "";

    while (ss)
    {
        ss >> temp;

        if (ss && (temp == "AND" || temp == "(AND")) {}
        else if (ss && (temp == "OR" || temp == "(OR")) {}
        else if (ss && (temp == "NOT" || temp == "(NOT")) {}
        else if (ss)
        {
            removeParenthesesFromWord(temp);
            cout<<temp<<endl;
            keywords.push_back(temp);
        }
    }

    removeStopWords(keywords);
    removeStems(keywords);

    if (useAvl == true)
        index = myIndexHandler->searchHash(keywords);
    else
        index = myIndexHandler->searchHash(keywords);

    separateKeywordsBool(queryWords);
}

void QueryProcessor::separateKeywordsBool(string &searchQuery)
{
    std::vector<std::string> keywords = {};
    std::vector<std::string> nestVector = {};
    std::stringstream ss(searchQuery);
    std::string temp = "";
    int closeCounter = 0;

    while (ss)
    {
        ss >> temp;
        seperateParenthesesFromWord(temp);
        if(parentheses == "(")
            keywords.push_back(parentheses);
        keywords.push_back(temp);
        if(parentheses == ")")
            keywords.push_back(parentheses);
    }
    keywords.pop_back();
    removeStems(keywords);
    removeStopWords(keywords);

    //changes duplicate to )
    int del1 = keywords.size()-3;
    int del2 = keywords.size()-1;
    if(keywords.size() > 3 && keywords[del1] == keywords[del2])
        keywords[del2] = ")";

    //adds ) if needed
    for(int i = 0; i < keywords.size(); i++)
    {
        //std::cout<<keywords[i]<<endl;
        if(keywords[i] == "(")
            nestCounter++;
        if(keywords[i] == ")")
            closeCounter++;
    }
    if(closeCounter != nestCounter)
    {
        int count = 0;
        for(vector<string>::iterator it = keywords.begin(); it != keywords.end(); it++)
        {
            if(*it == ")")
                count++;
            if(count == 1)
                keywords.insert(it, ")");
        }
    }


    if(nestCounter == 0)
    {
        noNest(keywords);
    }
    if(nestCounter == 1)
    {
        int parenthesesCount = 0;
        vector<string>::iterator first;
        vector<string>::iterator last;
        for(vector<string>::iterator it = keywords.begin(); it != keywords.end(); it++)
        {
            if(*it == "(")
                parenthesesCount++;
            if(parenthesesCount == 1)
            {
                 if(*it == "(")
                     first = it;
                 else if(*it == ")")
                 {
                     last = it;
                     parenthesesCount = 0;
                 }
                 else
                     nestVector.push_back(*it);
            }
        }
        keywords.erase(first, last+1);
        singleNest(keywords, nestVector);
    }
    if(nestCounter == 2)
    {
        int parenthesesCount = 0;
        vector<string>::iterator first;
        vector<string>::iterator last;
        for(vector<string>::iterator it = keywords.begin(); it != keywords.end(); it++)
        {
            if(*it == "(")
                parenthesesCount++;
            if(parenthesesCount == 2)
            {
                 if(*it == "(")
                     first = it;
                 else if(*it == ")")
                 {
                     last = it;
                     parenthesesCount = 0;
                 }
                 else
                     nestVector.push_back(*it);
            }
        }
        keywords.erase(first, last+1);
        doubleNest(keywords, nestVector);
    }

//    cout<<endl;

//    for(int i = 0; i < keywords.size(); i++)
//    {
//        std::cout<<keywords[i]<<endl;
//        if(keywords[i] == "(")
//            nestCounter++;
//    }

//    cout<<endl;

//    for(int i = 0; i < nestVector.size(); i++)
//    {
//        std::cout<<nestVector[i]<<endl;
//    }
}

void QueryProcessor::seperateParenthesesFromWord(string &word)
{
    bool hasParentheses = false;
    std::size_t bracePosition = word.find(")");

    if (bracePosition != std::string::npos)
    {
        word.erase(word.end() - 1);
        parentheses = ")";
        hasParentheses = true;
    }

    bracePosition = word.find("(");

    if (bracePosition != std::string::npos)
    {
        word.erase(word.begin());
        parentheses = "(";
        hasParentheses = true;
    }

    if(!hasParentheses)
        parentheses = "none";
}

void QueryProcessor::removeParenthesesFromWord(std::string& word)
{
    std::size_t bracePosition = word.find(")");

    if (bracePosition != std::string::npos)
        word.erase(word.end() - 1);

    bracePosition = word.find("(");

    if (bracePosition != std::string::npos)
        word.erase(word.begin());
}

void QueryProcessor::removeStopWords(std::vector<std::string>& words)
{
    static const std::string stopWords[] = {"a", "able", "about", "above",
    "abroad", "according", "accordingly", "across", "actually", "adj", "after",
    "afterwards", "again", "against", "ago", "ahead", "ain't", "all", "allow",
    "allows", "almost", "alone", "along", "alongside", "already", "also",
    "although", "always", "am", "amid", "amidst", "among", "amongst", "an",
    "and", "another", "any", "anybody", "anyhow", "anyone", "anything",
    "anyway", "anyways", "anywhere", "apart", "appear", "appreciate",
    "appropriate", "are", "aren't", "around", "as", "a's", "aside", "ask",
    "asking", "associated", "at", "available", "away", "awfully", "back",
    "backward", "backwards", "be", "became", "because", "become", "becomes",
    "becoming", "been", "before", "beforehand", "begin", "behind", "being",
    "believe", "below", "beside", "besides", "best", "better", "between",
    "beyond", "both", "brief", "but", "by", "came", "can", "cannot", "cant",
    "can't", "caption", "cause", "causes", "certain", "certainly", "changes",
    "clearly", "c'mon", "co", "co.", "com", "come", "comes", "concerning",
    "consequently", "consider", "considering", "contain", "containing",
    "contains", "corresponding", "could", "couldn't", "course", "c's",
    "currently", "dare", "daren't", "definitely", "described", "despite",
    "did", "didn't", "different", "directly", "do", "does", "doesn't", "doing",
    "done", "don't", "down", "downwards", "during", "each", "edu", "eg",
    "eight", "eighty", "either", "else", "elsewhere", "end", "ending", "enough",
    "entirely", "especially", "et", "etc", "even", "ever", "evermore", "every",
    "everybody", "everyone", "everything", "everywhere", "ex", "exactly",
    "example", "except", "fairly", "far", "farther", "few", "fewer", "fifth",
    "first", "five", "followed", "following", "follows", "for", "forever",
    "former", "formerly", "forth", "forward", "found", "four", "from",
    "further", "furthermore", "get", "gets", "getting", "given", "gives",
    "go", "goes", "going", "gone", "got", "gotten", "greetings", "had",
    "hadn't", "half", "happens", "hardly", "has", "hasn't", "have", "haven't",
    "having", "he", "he'd", "he'll", "hello", "help", "hence", "her", "here",
    "hereafter", "hereby", "herein", "here's", "hereupon", "hers", "herself",
    "he's", "hi", "him", "himself", "his", "hither", "hopefully", "how",
    "howbeit", "however", "hundred", "i", "i'd", "ie", "if", "ignored", "i'll",
    "i'm", "immediate", "in", "inasmuch", "inc", "inc.", "indeed", "indicate",
    "indicated", "indicates", "inner", "inside", "insofar", "instead", "into",
    "inward", "is", "isn't", "it", "it'd", "it'll", "its", "it's", "itself",
    "i've", "just", "k", "keep", "keeps", "kept", "know", "known", "knows",
    "last", "lately", "later", "latter", "latterly", "least", "less", "lest",
    "let", "let's", "like", "liked", "likely", "likewise", "little", "look",
    "looking", "looks", "low", "lower", "ltd", "made", "mainly", "make",
    "makes", "many", "may", "maybe", "mayn't", "me", "mean", "meantime",
    "meanwhile", "merely", "might", "mightn't", "mine", "minus", "miss", "more",
    "moreover", "most", "mostly", "mr", "mrs", "much", "must", "mustn't", "my",
    "myself", "name", "namely", "nd", "near", "nearly", "necessary", "need",
    "needn't", "needs", "neither", "never", "neverf", "neverless",
    "nevertheless", "new", "next", "nine", "ninety", "no", "nobody", "non",
    "none", "nonetheless", "noone", "no-one", "nor", "normally", "not",
    "nothing", "notwithstanding", "novel", "now", "nowhere", "obviously", "of",
    "off", "often", "oh", "ok", "okay", "old", "on", "once", "one", "ones",
    "one's", "only", "onto", "opposite", "or", "other", "others", "otherwise",
    "ought", "oughtn't", "our", "ours", "ourselves", "out", "outside", "over",
    "overall", "own", "particular", "particularly", "past", "per", "perhaps",
    "placed", "please", "plus", "possible", "presumably", "probably",
    "provided", "provides", "que", "quite", "qv", "rather", "rd", "re",
    "really", "reasonably", "recent", "recently", "regarding", "regardless",
    "regards", "relatively", "respectively", "right", "round", "said", "same",
    "saw", "say", "saying", "says", "second", "secondly", "see", "seeing",
    "seem", "seemed", "seeming", "seems", "seen", "self", "selves", "sensible",
    "sent", "serious", "seriously", "seven", "several", "shall", "shan't",
    "she", "she'd", "she'll", "she's", "should", "shouldn't", "since", "six",
    "so", "some", "somebody", "someday", "somehow", "someone", "something",
    "sometime", "sometimes", "somewhat", "somewhere", "soon", "sorry",
    "specified", "specify", "specifying", "still", "sub", "such", "sup", "sure",
    "take", "taken", "taking", "tell", "tends", "th", "than", "thank", "thanks",
    "thanx", "that", "that'll", "thats", "that's", "that've", "the", "their",
    "theirs", "them", "themselves", "then", "thence", "there", "thereafter",
    "thereby", "there'd", "therefore", "therein", "there'll", "there're",
    "theres", "there's", "thereupon", "there've", "these", "they", "they'd",
    "they'll", "they're", "they've", "thing", "things", "think", "third",
    "thirty", "this", "thorough", "thoroughly", "those", "though", "three",
    "through", "throughout", "thru", "thus", "till", "to", "together", "too",
    "took", "toward", "towards", "tried", "tries", "truly", "try", "trying",
    "t's", "twice", "two", "un", "under", "underneath", "undoing",
    "unfortunately", "unless", "unlike", "unlikely", "until", "unto", "up",
    "upon", "upwards", "us", "use", "used", "useful", "uses", "using",
    "usually", "v", "value", "various", "versus", "very", "via", "viz", "vs",
    "want", "wants", "was", "wasn't", "way", "we", "we'd", "welcome", "well",
    "we'll", "went", "were", "we're", "weren't", "we've", "what", "whatever",
    "what'll", "what's", "what've", "when", "whence", "whenever", "where",
    "whereafter", "whereas", "whereby", "wherein", "where's", "whereupon",
    "wherever", "whether", "which", "whichever", "while", "whilst", "whither",
    "who", "who'd", "whoever", "whole", "who'll","", "whom", "whomever",
    "who's", "whose", "why", "will", "willing", "wish", "with", "within",
    "without", "wonder", "won't", "would", "wouldn't", "yes", "yet", "you",
    "you'd", "you'll", "your", "you're", "yours", "yourself", "yourselves",
    "you've", "zero"};
    static int stopWordsSize = 637;

    for (int i = 0; i <= stopWordsSize; i++)
    {
        for (int j = 0; j < words.size(); j++)
        {
            if (stopWords[i] == words.at(j))
                words.erase(words.begin() + j);
        }
    }
}

void QueryProcessor::removeStems(std::vector<std::string>& queryKeywords)
{

    stemming::english_stem<> stemmer;

    // have to convert between wstring and string because the stemming library
    // uses wstrings
    for (int i = 0; i < queryKeywords.size(); i++)
    {
        std::wstring temp(queryKeywords.at(i).length(), L' ');
        std::copy(queryKeywords.at(i).begin(), queryKeywords.at(i).end(),
                  temp.begin());
        stemmer(temp);
        queryKeywords.at(i).assign(temp.begin(), temp.end());
    }
}

void QueryProcessor::noNest(std::vector<string> &phrase)
{
    LinkedList* temp;
    LinkedList* tempOutput = new LinkedList();
    int it;

    if(phrase[0] == "AND")
    {
        phrase.erase(phrase.begin());
        if(outputLL->empty())
        {
            temp = index->findData(phrase[0]);
            phrase.erase(phrase.begin());
            for(int i = 0; i < temp->size(); i++)
                outputLL->push_back(temp->getPageNumber(i), temp->getFrequency(i), temp->getTitle(i), temp->getDate(i), temp->getUser(i));
        }
        while(!phrase.empty())
        {
            if(phrase[0] == "NOT")
            {
                phrase.erase(phrase.begin());
                temp = index->findData(phrase[0]);
                phrase.erase(phrase.begin());
                for(int i = 0; i < temp->size(); i++)
                {
                    if(outputLL->contains(temp->getPageNumber(i)))
                        outputLL->deleteAt(outputLL->findIterator(temp->getPageNumber(i)));
                }
            } else
            {
                temp = index->findData(phrase[0]);
                phrase.erase(phrase.begin());
                for(int i = 0; i < outputLL->size(); i++)
                {
                    if(temp->contains(outputLL->getPageNumber(i)))
                    {
                        it = temp->findIterator(outputLL->getPageNumber(i));
                        outputLL->findSet(outputLL->getPageNumber(i), temp->getFrequency(it));
                        tempOutput->push_back(outputLL->getPageNumber(i), outputLL->getFrequency(i), outputLL->getTitle(i), outputLL->getDate(i), outputLL->getUser(i));
                    }
                }
                outputLL->clear();
                for(int i = 0; i < tempOutput->size(); i++)
                    outputLL->push_back(tempOutput->getPageNumber(i), tempOutput->getFrequency(i), tempOutput->getTitle(i), tempOutput->getDate(i), tempOutput->getUser(i));
                tempOutput->clear();
            }
        }
    } else if(phrase[0] == "OR")
    {
        phrase.erase(phrase.begin());
        if(outputLL->empty())
        {
            temp = index->findData(phrase[0]);
            phrase.erase(phrase.begin());
            for(int i = 0; i < temp->size(); i++)
                outputLL->push_back(temp->getPageNumber(i), temp->getFrequency(i), temp->getTitle(i), temp->getDate(i), temp->getUser(i));
        }
        while(!phrase.empty())
        {
            if(phrase[0] == "NOT")
            {
                phrase.erase(phrase.begin());
                temp = index->findData(phrase[0]);
                phrase.erase(phrase.begin());
                for(int i = 0; i < temp->size(); i++)
                {
                    if(outputLL->contains(temp->getPageNumber(i)))
                        outputLL->deleteAt(outputLL->findIterator(temp->getPageNumber(i)));
                }
            } else
            {
                temp = index->findData(phrase[0]);
                phrase.erase(phrase.begin());
                for(int i = 0; i < temp->size(); i++)
                {
                    if(outputLL->contains(temp->getPageNumber(i)))
                        outputLL->findSet(temp->getPageNumber(i), temp->getFrequency(i));
                    else
                        outputLL->push_back(temp->getPageNumber(i), temp->getFrequency(i), temp->getTitle(i), temp->getDate(i), temp->getUser(i));
                }
            }
        }
    } else
    {
        if(phrase.size() == 1 && outputLL->empty())
        {
            temp = index->findData(phrase[0]);
            phrase.erase(phrase.begin());
            for(int i = 0; i < temp->size(); i++)
                outputLL->push_back(temp->getPageNumber(i), temp->getFrequency(i), temp->getTitle(i), temp->getDate(i), temp->getUser(i));
        } else
        {

        }
    }
    //outputLL->sort();
    outputLL->output();
    cout<<endl;
    delete tempOutput;
}

void QueryProcessor::singleNest(std::vector<string> &restOfPhrase, std::vector<string> &nestPhrase)
{
    LinkedList* temp;
    int it;

    if(nestPhrase[0] == "AND")
    {
        nestPhrase.erase(nestPhrase.begin());
        if(outputLL->empty())
        {
            temp = index->findData(nestPhrase[0]);
            nestPhrase.erase(nestPhrase.begin());
            for(int i = 0; i < temp->size(); i++)
                outputLL->push_back(temp->getPageNumber(i), temp->getFrequency(i), temp->getTitle(i), temp->getDate(i), temp->getUser(i));
        }
        while(!nestPhrase.empty())
        {
            if(nestPhrase[0] == "NOT")
            {
                nestPhrase.erase(nestPhrase.begin());
                temp = index->findData(nestPhrase[0]);
                nestPhrase.erase(nestPhrase.begin());
                for(int i = 0; i < temp->size(); i++)
                {
                    if(outputLL->contains(temp->getPageNumber(i)))
                        outputLL->deleteAt(outputLL->findIterator(temp->getPageNumber(i)));
                }
            } else
            {
                temp = index->findData(nestPhrase[0]);
                nestPhrase.erase(nestPhrase.begin());
                for(int i = 0; i < outputLL->size(); i++)
                {
                    if(temp->contains(outputLL->getPageNumber(i)))
                    {
                        it = temp->findIterator(outputLL->getPageNumber(i));
                        outputLL->set_at(i, temp->getFrequency(it));
                    } else
                    {
                        outputLL->deleteAt(i);
                    }
                }
            }
        }
    }

    if(nestPhrase[0] == "OR")
    {
        nestPhrase.erase(nestPhrase.begin());
        if(outputLL->empty())
        {
            temp = index->findData(nestPhrase[0]);
            nestPhrase.erase(nestPhrase.begin());
            for(int i = 0; i < temp->size(); i++)
                outputLL->push_back(temp->getPageNumber(i), temp->getFrequency(i), temp->getTitle(i), temp->getDate(i), temp->getUser(i));
        }
        while(!nestPhrase.empty())
        {
            if(nestPhrase[0] == "NOT")
            {
                nestPhrase.erase(nestPhrase.begin());
                temp = index->findData(nestPhrase[0]);
                nestPhrase.erase(nestPhrase.begin());
                for(int i = 0; i < temp->size(); i++)
                {
                    if(outputLL->contains(temp->getPageNumber(i)))
                        outputLL->deleteAt(outputLL->findIterator(temp->getPageNumber(i)));
                }
            } else
            {
                temp = index->findData(nestPhrase[0]);
                nestPhrase.erase(nestPhrase.begin());
                for(int i = 0; i < temp->size(); i++)
                {
                    if(outputLL->contains(temp->getPageNumber(i)))
                        outputLL->findSet(temp->getPageNumber(i), temp->getFrequency(i));
                    else
                        outputLL->push_back(temp->getPageNumber(i), temp->getFrequency(i), temp->getTitle(i), temp->getDate(i), temp->getUser(i));
                }
            }
        }
    }

//    outputLL->sort();
//    outputLL->output();
//    cout<<endl;

    noNest(restOfPhrase);

}

void QueryProcessor::doubleNest(std::vector<string> &restOfPhrase, std::vector<string> &nestPhrase)
{
    LinkedList* temp;
    int it;

    if(nestPhrase[0] == "AND")
    {
        nestPhrase.erase(nestPhrase.begin());
        if(outputLL->empty())
        {
            temp = index->findData(nestPhrase[0]);
            nestPhrase.erase(nestPhrase.begin());
            for(int i = 0; i < temp->size(); i++)
                outputLL->push_back(temp->getPageNumber(i), temp->getFrequency(i), temp->getTitle(i), temp->getDate(i), temp->getUser(i));
        }
        while(!nestPhrase.empty())
        {
            if(nestPhrase[0] == "NOT")
            {
                nestPhrase.erase(nestPhrase.begin());
                temp = index->findData(nestPhrase[0]);
                nestPhrase.erase(nestPhrase.begin());
                for(int i = 0; i < temp->size(); i++)
                {
                    if(outputLL->contains(temp->getPageNumber(i)))
                        outputLL->deleteAt(outputLL->findIterator(temp->getPageNumber(i)));
                }
            } else
            {
                temp = index->findData(nestPhrase[0]);
                nestPhrase.erase(nestPhrase.begin());
                for(int i = 0; i < outputLL->size(); i++)
                {
                    if(temp->contains(outputLL->getPageNumber(i)))
                    {
                        it = temp->findIterator(outputLL->getPageNumber(i));
                        outputLL->set_at(i, temp->getFrequency(it));
                    } else
                    {
                        outputLL->deleteAt(i);
                    }
                }
            }
        }
    }

    if(nestPhrase[0] == "OR")
    {
        nestPhrase.erase(nestPhrase.begin());
        if(outputLL->empty())
        {
            temp = index->findData(nestPhrase[0]);
            nestPhrase.erase(nestPhrase.begin());
            for(int i = 0; i < temp->size(); i++)
                outputLL->push_back(temp->getPageNumber(i), temp->getFrequency(i), temp->getTitle(i), temp->getDate(i), temp->getUser(i));
        }
        while(!nestPhrase.empty())
        {
            if(nestPhrase[0] == "NOT")
            {
                nestPhrase.erase(nestPhrase.begin());
                temp = index->findData(nestPhrase[0]);
                nestPhrase.erase(nestPhrase.begin());
                for(int i = 0; i < temp->size(); i++)
                {
                    if(outputLL->contains(temp->getPageNumber(i)))
                        outputLL->deleteAt(outputLL->findIterator(temp->getPageNumber(i)));
                }
            } else
            {
                temp = index->findData(nestPhrase[0]);
                nestPhrase.erase(nestPhrase.begin());
                for(int i = 0; i < temp->size(); i++)
                {
                    if(outputLL->contains(temp->getPageNumber(i)))
                        outputLL->findSet(temp->getPageNumber(i), temp->getFrequency(i));
                    else
                        outputLL->push_back(temp->getPageNumber(i), temp->getFrequency(i), temp->getTitle(i), temp->getDate(i), temp->getUser(i));
                }
            }
        }
    }

//    outputLL->sort();
//    outputLL->output();
//    cout<<endl;

    int parenthesesCount = 0;
    vector<string>::iterator first;
    vector<string>::iterator last;
    for(vector<string>::iterator it = restOfPhrase.begin(); it != restOfPhrase.end(); it++)
    {
        if(*it == "(")
            parenthesesCount++;
        if(parenthesesCount == 1)
        {
             if(*it == "(")
                 first = it;
             else if(*it == ")")
             {
                 last = it;
                 parenthesesCount = 0;
             }
             else
                 nestPhrase.push_back(*it);
        }
    }
    restOfPhrase.erase(first, last+1);
    singleNest(restOfPhrase, nestPhrase);
}
