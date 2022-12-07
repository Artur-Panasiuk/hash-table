#include <string>

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
    void lesserExpand(int index, int indexSize) {
        int newMaxSize = indexSize + 1;

        node* temp = new node[newMaxSize];

        for (int i = 0; i < indexSize; i++) {
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
    V get(string key) {
        int hashedKey = getHashKey(key);
        V retVal = NULL;

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
    string toString(bool isValuePOD) {
        string body = "hash table\n\t";
        body += "current size: " + to_string(currSize) + "\n\t";
        body += "max size: " + to_string(maxSize) + "\n\t";
        
                if(isValuePOD){
                    for(int i = 0; i < 10 && i < currSize; i++){
                        if((sizeof(ht[i]) / sizeof(ht[i][0])) > 0){
                            for(int j = 0; j < (sizeof(ht[i]) / sizeof(ht[i][0])); j++){
                                body += ht[i][j].key;
                                body += " -> ";
                                body += ht[i][j].value;
                                body += "\n";
                            }
                        }
                    }
                }
                

        return body;
    }
};

string random_key(int n) {
    string key;
    char letters[6] = { 'a','b', 'c', 'd', 'e', 'f', };
    key.reserve(n);

    for (int i = 0; i < n; i++) {
        key += letters[rand() % 6];
    }
    return key;
}



int main()
{
        const int MAX_ORDER = 7; // maksymalny rzad wielkosci dodawanych danych
        hash_table < int >* ht = new hash_table < int >();
        for (int o = 1; o <= MAX_ORDER; o++)
        {
            const int n = pow(10, o); // rozmiar danych
            // dodawanie do tablicy mieszajacej
            clock_t t1 = clock();
                for (int i = 0; i < n; i++)
                    ht->add(random_key(6), i); // klucze losowe 6 - znakowe , a jako wartosci indeks petli
            clock_t t2 = clock();
                const int m = pow(10, 4);
            int hits = 0;
            t1 = clock();
            for (int i = 0; i < m; i++)
            {
                auto entry = ht->get(random_key(6)); // wyszukiwanie wg losowego klucza
                if (entry != NULL)
                    hits++;
            }
            t2 = clock();
            ht-> toString(false);
            ht->clearAll(false); // czyszczenie tablicy mieszajacej
        }
    delete ht;
    return 0;
}
