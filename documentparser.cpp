#include <sstream>
#include <cctype>
#include <algorithm>
#include <utility>
#include <chrono>
#include <iostream>

#include "documentparser.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "stemming/english_stem.h"

DocumentParser::DocumentParser()
{
    myIndexHandler = nullptr;
}

DocumentParser::DocumentParser(IndexHandler*& ih)
{
    myIndexHandler = ih;
}

void DocumentParser::readDocument(char*& filename)
{
    rapidxml::file<> xmlFile(filename);
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    rapidxml::xml_node<>* root = doc.first_node("mediawiki");
    rapidxml::xml_node<>* page = root->first_node("page");
    rapidxml::xml_node<>* title = page->first_node("title");
    rapidxml::xml_node<>* revision = page->first_node("revision");
    rapidxml::xml_node<>* date = revision->first_node("timestamp");
    rapidxml::xml_node<>* contributor = revision->first_node("contributor");
    rapidxml::xml_node<>* username = contributor->first_node("username");
    rapidxml::xml_node<>* text = revision->first_node("text");

    std::string documentTitle = title->value();
    std::string documentDate = date->value();
    std::string documentContributor = username->value();
    std::string documentContents = text->value();
    int documentNumber = 1;

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    removeStopwords(documentContents, documentNumber, documentTitle,
                    documentDate, documentContributor);

    while (page->next_sibling("page") != nullptr)
    {
        page = page->next_sibling("page");
        title = page->first_node("title");
        revision = page->first_node("revision");
        date = revision->first_node("timestamp");
        contributor = revision->first_node("contributor");
        username = contributor->first_node("username");
        text = revision->first_node("text");

        documentTitle = title->value();
        documentDate = date->value();

        // some documents don't have a contributor username
        if (username == nullptr)
            documentContributor = "N/A";
        else
            documentContributor = username->value();

        documentContents = text->value();
        documentNumber++;

        removeStopwords(documentContents, documentNumber, documentTitle,
                        documentDate, documentContributor);
    }

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> parseTime = end - start;
    std::cout << "xml parse time: " << parseTime.count() << std::endl;

    root = nullptr;
    page = nullptr;
    title = nullptr;
    revision = nullptr;
    date = nullptr;
    contributor = nullptr;
    username = nullptr;
    text = nullptr;
}

void DocumentParser::removeStopwords(std::string& pageText, int docNumber,
                                     std::string& pageTitle,
                                     std::string& pageDate,
                                     std::string& pageContributor)
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
    int stopWordsSize = 637;
    std::vector<std::string> docWords = {};

    splitString(pageText, docWords);
    toLower(docWords);

    for (int i = 0; i <= stopWordsSize; i++)
    {
        for (int j = 0; j < docWords.size(); j++)
        {
            if (stopWords[i] == docWords.at(j))
                docWords.erase(docWords.begin() + j);
        }
    }

    removeStems(docWords);
    calculateTermFrequency(docWords, docNumber, pageTitle, pageDate,
                           pageContributor);
}

void DocumentParser::splitString(std::string& text,
                                 std::vector<std::string>& pageWords)
{
    std::stringstream ss(text);
    std::string temp = "";

    while (ss)
    {
        ss >> temp;
        if (ss)
            pageWords.push_back(temp);
    }
}

void DocumentParser::toLower(std::vector<std::string>& pageWords)
{
    for (int i = 0; i < pageWords.size(); i++)
    {
        std::transform(pageWords.at(i).begin(), pageWords.at(i).end(),
                       pageWords.at(i).begin(), ::tolower);
    }
}

void DocumentParser::removeStems(std::vector<std::string>& words)
{
    stemming::english_stem<> wordStemmer;

    // have to convert between wstring and string because the stemming library
    // uses wstrings
    for (int i = 0; i < words.size(); i++)
    {
        std::wstring temp(words.at(i).length(), L' ');
        std::copy(words.at(i).begin(), words.at(i).end(), temp.begin());
        wordStemmer(temp);
        words.at(i).assign(temp.begin(), temp.end());
    }
}

void DocumentParser::calculateTermFrequency(std::vector<std::string>& terms,
                                            int& pageNumber,
                                            std::string& docTitle,
                                            std::string& date,
                                            std::string& contributor)
{
    // the string represents the word and the int represents the number of
    // occurences on that page for the pageTermFrequency map
    std::map<std::string, int> pageTermFrequency;
    static int numberOfCalculations = 1;

    // no terms for the current document
    if (terms.size() == 0)
    {
        numberOfCalculations++;
    }

    while (numberOfCalculations == pageNumber)
    {
        static int termNumber = 1;

        if (termNumber == 1)
        {
            // page map is empty so no need to check for duplciates
            pageTermFrequency.insert(std::pair<std::string, int>
                                    (terms.at(0), 1));
            termNumber++;

            // only 1 word was in the document
            if (terms.size() == 1)
            {
                termNumber = 1;
                numberOfCalculations++;
            }
        }
        else if (termNumber > 1)
        {
            for (int i = 1; i < terms.size(); i++)
            {
                checkForDuplicateTerm(terms.at(i), pageTermFrequency);

                // all terms have been added
                if (i == terms.size() - 1)
                {
                    termNumber = 1;
                    numberOfCalculations++;
                }
            }
        }
    }

    myIndexHandler->addWord(pageTermFrequency, pageNumber, docTitle, date,
                            contributor);
}

void DocumentParser::checkForDuplicateTerm(std::string& word,
                                           std::map<std::string, int>& terms)
{
    std::map<std::string, int>::iterator duplicateItr = terms.find(word);

    if (duplicateItr != terms.end())
    {
        int frequency = duplicateItr->second;
        frequency++;
        terms[word] = frequency;
    }
    else
        terms.insert(std::pair<std::string, int>(word, 1));
}

void DocumentParser::getPageNumber(char*& file)
{
    int pageToView = 0;
    std::cout << "\nEnter the page number of the document you want to view? " <<
                 "(enter -1 to exit): ";
    cin >> pageToView;

    if (pageToView == 0 || pageToView < -1)
    {
        std::cout << "Invalid page number. Please try again." << std::endl;
        getPageNumber(file);
    }
    else if (pageToView > 0)
    {
        getDocumentContents(file, pageToView);
        getPageNumber(file);
    }
}

void DocumentParser::getDocumentContents(char*& docFilename,
                                         int& documentNumber)
{
    rapidxml::file<> xmlFile(docFilename);
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    rapidxml::xml_node<>* root = doc.first_node("mediawiki");
    rapidxml::xml_node<>* page = root->first_node("page");
    rapidxml::xml_node<>* revision = page->first_node("revision");
    rapidxml::xml_node<>* text = revision->first_node("text");
    int pageNumber = 1;

    while (pageNumber != documentNumber)
    {
        page = page->next_sibling("page");
        revision = page->first_node("revision");
        text = revision->first_node("text");
        pageNumber++;
    }

    std::cout << "Document " << documentNumber << " Contents:\n" <<
                    text->value() << std::endl;

    root = nullptr;
    page = nullptr;
    revision = nullptr;
    text = nullptr;
}
