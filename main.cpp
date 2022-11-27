#include <iostream>
#include <time.h>
#include <string.h>

using namespace std;

template <class K, class V>
class hash_table{
    struct node{
        K key;
        V value;
    };
    int currSize {0};
    int maxSize {1024};
    int buffSize {1024};
    int arraySizeMultipl {2};
    float expandThreshold {0.75};

    node** ht;

    int getHashKey(K key){
        int hashedKey = 0;
        if(typeid(key) == typeid(string)){
            for(long long unsigned i = 0; i < key.length(); i++){
                hashedKey += key[i]*(31^(key.length()-(i+1)));
            }
        }
        return hashedKey;
    }
    void expand(){
        int newMaxSize = maxSize * arraySizeMultipl;

        node** tempHt = new node*[newMaxSize];
        for(int i = 0; i < newMaxSize; i++){
            tempHt[i] = new node[buffSize];
        }
        for(int j = 0; j < maxSize; j++){
            for(int k = 0; k < buffSize; k++){
                tempHt[j][k] = ht[j][k];
            }
        }
        for(int l = 0; l < maxSize; l++){
            delete[] ht[l];
        }
        delete[] ht;

        ht = tempHt;

        maxSize = newMaxSize;
    }
public:
    hash_table(){
        ht = new node*[maxSize];
        for(int i = 0; i < maxSize; i++){
            ht[i] = new node[buffSize];
        }
    }
    ~hash_table(){
        for(int i = 0; i < maxSize; i++){
            delete[] ht[i];
        }
        delete[] ht;
    }

    void add(K key, V value){
        int hashedKey = getHashKey(key);
        if(hashedKey < maxSize * expandThreshold){
            node newNode;
            newNode.key = key;
            newNode.value = value;
            ht[hashedKey][0] = newNode;
            currSize++;
        }else{
            expand();
            add(key, value);
        }
    }
    V get(K key){
        int hashedKey = getHashKey(key);

        for(int i = 0; i < buffSize; i++){
            if(ht[hashedKey][i].key == key){
                return ht[hashedKey][i].value;
            }
        }
    }
    bool del(K key){
        bool returnValue = false;
        int hashedKey = getHashKey(key);

        for(int i = 0; i < buffSize; i++){
            if(ht[hashedKey][i].key == key){
                node temp;
                ht[hashedKey][i] = temp;
                returnValue = true;
            }
        }

        return returnValue;
    }
    void clearAll(bool isValuePOD){
        if(isValuePOD){
            for(int i = 0; i < maxSize; i++){
                delete[] ht[i];
                ht[i] = new node[buffSize];
            }
        }
    }

};

int main()
{
    hash_table<string, string> test;

    test.add("!", "val");
    test.add("@", "lol");
    test.add("Adam", "lol");

    test.get("Adam");

    return 0;
}
