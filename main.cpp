#include <iostream>
#include <time.h>
#include <string.h>
#include <vector>
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
    float expandThreshold {0.75};
    list<list<node>> ht {maxSize};
public:
    void expand(){

    }
    int getHashKey(K key){
        int hashedKey = 0;
        if(typeid(key) == typeid(string)){
            for(int i = 0; i < key.length(); i++){
                hashedKey += (int)key[i]*(31^key.length()-(i+1));
            }
        }
        return hashedKey;
    }
//public:
    void add(K key, V value){
        int hashKey = getHashKey(key);
        if(hashKey < maxSize * expandThreshold){
            //if()
        }else{
            expand();
            add(key, value);
        }
    }
    V get(K key){

        return NULL;
    }
    bool del(K key){

        return false;
    }
    void clearAll(bool isValuePOD){

    }
    string to_string(bool isKeyPOD, bool isValuePOD){
        return "";
    }
    string sizeInfo(){
        return "";
    }
    string firstTenList(bool isKeyPOD, bool isValuePOD){
        return "";
    }
    string tableStats(){
        return "";
    }
};

void time_test(int loopSize){

}


int main()
{
    hash_table<string, string>* test = new hash_table<string, string>;

    cout << test->getHashKey("lol");
    return 0;
}
