#include <iostream>
#include <time.h>
#include <string.h>

using namespace std;

template <class V>
class hash_table {
public:
    struct node {
        string key;
        V value;
    };
    int currSize{ 0 };
    int maxSize{ 1024 };
    int buffSize{ 2 };
    int arraySizeMultipl{ 2 };
    float expandThreshold{ 0.75 };

    node** ht;

    int getHashKey(string key) {
        long long int hashedKey = 0;
        if (typeid(key) == typeid(string)) {
            for (long long unsigned i = 0; i < key.length(); i++) {
                hashedKey += key[i] * (31 ^ (key.length() - (i + 1)));
            }
        }

        hashedKey %= maxSize;

        return hashedKey;
    }
    void lesserExpand(int index){
        int indexSize = sizeof(ht[index])/sizeof(ht[index][0]);
        int newMaxSize = indexSize + 1;

        node* temp = new node[newMaxSize];

        for(int i = 0; i < indexSize; i++){
            temp[i] = ht[index][i];
        }
        delete[] ht[index];

        ht[index] = temp;
    }

    void expand() {
        int newMaxSize = maxSize * arraySizeMultipl;

        node** tempHt = new node * [newMaxSize];

        for (int i = 0; i < newMaxSize; i++) {
            tempHt[i] = new node[buffSize];
        }
        for (int j = 0; j < maxSize; j++) {
            for (int k = 0; k < buffSize; k++) {
                tempHt[j][k] = ht[j][k];
            }
        }
        for (int l = 0; l < maxSize; l++) {
            delete[] ht[l];
        }
        delete[] ht;

        maxSize = newMaxSize;

        ht = tempHt;
    }
    hash_table() {
        ht = new node * [maxSize];
        for (int i = 0; i < maxSize; i++) {
            ht[i] = new node[buffSize];
        }
    }
    ~hash_table() {
        for (int i = 0; i < maxSize; i++) {
            delete[] ht[i];
        }
        delete[] ht;
    }

    void add(string key, V value) {
        int hashedKey = getHashKey(key);
        if (hashedKey < maxSize * expandThreshold) {
            node newNode;
            newNode.key = key;
            newNode.value = value;
            ht[hashedKey][0] = newNode;
            currSize++;
        }
        else {
            expand();
            add(key, value);
        }
    }
    string get(string key) {
        int hashedKey = getHashKey(key);
        string retVal = "";

        for (int i = 0; i < buffSize; i++) {
            if (ht[hashedKey][i].key == key) {
                retVal = ht[hashedKey][i].value;
            }
        }
        return retVal;
    }
    bool del(string key) {
        bool returnValue = false;
        int hashedKey = getHashKey(key);

        for (int i = 0; i < buffSize; i++) {
            if (ht[hashedKey][i].key == key) {
                node temp;
                ht[hashedKey][i] = temp;
                returnValue = true;
            }
        }

        return returnValue;
    }
    void clearAll(bool isValuePOD) {
        if (isValuePOD) {
            for (int i = 0; i < maxSize; i++) {
                delete[] ht[i];
                ht[i] = new node[buffSize];
            }
        }
    }

    string toString(bool isValuePOD){
        string body = "hash table\n\t";
        body += "current size: " + to_string(currSize) + "\n\t";
        body += "max size: " + to_string(maxSize) + "\n\t";

        if(isValuePOD){
            for(int i = 0; i < 10 && i < currSize; i++){
                if(ht[i].Size() > 0){
                    for(int j = 0; j < ht[i].Size(); j++){
                        body += ht[i][j].key;
                        body += " -> ";
                    }
                }
            }
        }

        return body;
    }

};



int main()
{
    hash_table<string> test;

    test.add("a", "b");

    cout<<test.toString(false);

    return 0;
}
