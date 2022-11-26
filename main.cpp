#include <iostream>
#include <time.h>
#include <string.h>
#include <list>

using namespace std;

template <class K, class V>
class hash_table{
    struct node{
        K key;
        V value;
    };
    int hashFunction;
    int currSize {0};
    int maxSize {1024};
    int arraySizeMultipl {2};
    float expandThreshold {0.75};
    list<list<node>>* ht;
public:
    void expand(){
        int newMaxSize = maxSize * arraySizeMultipl;
        list<list<node>> temp[newMaxSize];
        for(int i = 0; i < maxSize; i++){
            temp[i] = ht[i];
        }
        maxSize = newMaxSize;
        *ht = *temp;
    }
    int getHashKey(K key){
        int hashedKey = 0;
        if(typeid(key) == typeid(string)){
            for(long long unsigned i = 0; i < key.length(); i++){
                hashedKey += key[i]*(31^(key.length()-(i+1)));
            }
        }
        return hashedKey;
    }
public:
    hash_table(){
        ht = new list<list<node>>[maxSize];
    }
    ~hash_table(){
        delete[] ht;
    }
    void add(K key, V value){
        int hashKey = getHashKey(key);
        if(hashKey < maxSize * expandThreshold){
            node newNode;
            newNode.key = key;
            newNode.value = value;
            ht[hashKey].push_back(newNode);
            currSize++;
        }else{
            expand();
            add(key, value);
        }
    }
    V get(K key){
        int hashKey = getHashKey(key);
        V returnValue = NULL;

        if(ht[hashKey]){
            for(auto i = ht[hashKey].begin(); i != ht[hashKey].end(); ++i){
                if(*i.key = key) returnValue = *i.value;
            }
        }

        return returnValue;
    }
    bool del(K key){
        bool returnValue = false;
        int hashKey = getHashKey(key);

        if(ht[hashKey]){
            for(auto i = ht[hashKey].begin(); i != ht[hashKey].end(); ++i){
                if(*i.key = key){
                    *i = nullptr;
                    currSize--;
                    returnValue = true;
                }
            }
        }

        return returnValue;
    }
    void clearAll(bool isValuePOD){
        if(isValuePOD){
            for(int i = 0; i < maxSize; i++){
                ht[i] = NULL;
            }
        }
    }
    string to_string(bool isKeyPOD, bool isValuePOD){
        string header = sizeInfo();
        string body = firstTenList(isKeyPOD, isValuePOD);
        string footer = tableStats();
        string raport = header + "\n" + body + "\n" + footer;
        return raport;
    }
    string sizeInfo(){
        string header = "hash table:";
        string usedSize = "current_size: " + currSize;
        string maxS = "max_size: " + maxSize;
        return header + "\n\t" + usedSize + "\n\t" + maxS;
    }
    string firstTenList(bool isKeyPOD, bool isValuePOD){
        string header = "\ttable\n\t{\n";
        string body = "";
        int counter = 0;
        for(int i = 0; i < maxSize; i++){
            if(ht[i]){
                for(auto j = ht[i].begin(); j != ht[i].end(); ++j){
                    string keyRef = (string)*j.key;
                    string valRef = (string)*j.value;
                    cout << keyRef << endl;
                    cout << valRef << endl;
                    //body += "\t\t" + i + ": " + keyRef + " -> " + valRef + ";\n";
                    counter++;
                }
            }
            if(counter < 10) break;
        }
        body += "}";
        return header + body;
    }
    string tableStats(){
        return "";
    }
};

void time_test(int loopSize){

}


int main()
{
    hash_table<string, string> test;

    test.add("testKey", "testValue");

    return 0;
}
