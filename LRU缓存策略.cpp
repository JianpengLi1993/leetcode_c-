为最近最少使用（LRU）缓存策略设计一个数据结构，它应该支持以下操作：获取数据和写入数据。
get(key) 获取数据：如果缓存中存在key，则获取其数据值（通常是正数），否则返回-1。
set(key, value) 写入数据：如果key还没有在缓存中，则写入其数据值。当缓存达到上限，它应该在写入新数据之前删除最近最少使用的数据用来腾出空闲位置。
最终, 你需要返回每次 get 的数据.

class KeyValue {
public:
    int key, value;
    KeyValue *next;
    KeyValue(int key, int value) {
        next = NULL;
        this->key = key;
        this->value = value;
    }
    KeyValue() {
        this->next = NULL;
        this->key = 0;
        this->value = 0;
    }
};

class LRUCache{
private:
    void moveToTail(KeyValue *prev) {     //将节点移动至尾部
        if (prev->next == tail) {
            return;
        }
        
        KeyValue *node = prev->next;
        prev->next = node->next;
        if (node->next != NULL) {
            hash[node->next->key] = prev;
        }
        tail->next = node;
        node->next = NULL;
        hash[node->key] = tail;
        tail = node;
    }
    
public:
    unordered_map<int, KeyValue *> hash;
    KeyValue *head, *tail;
    int capacity, size;
    
    LRUCache(int capacity) {
        this->head = new KeyValue(0, 0);
        this->tail = head;
        this->capacity = capacity;
        this->size = 0;
        hash.clear();
    }
    
    int get(int key) {
        if (hash.find(key) == hash.end()) {
            return -1;
        }
        
        moveToTail(hash[key]);    		//每次get，使用次数+1，最近使用，放于尾部
        return hash[key]->next->value;
    }
    
    void set(int key, int value) {       //数据放入缓存
        if (hash.find(key) != hash.end()) {      //key可以找到
            hash[key]->next->value = value;
            moveToTail(hash[key]);
        } else {
            KeyValue *node = new KeyValue(key, value);   //新建节点
            tail->next = node;							//放于尾部
            hash[key] = tail;
            tail = node;
            size++;
            if (size > capacity) {						//超出缓存上限
                hash.erase(head->next->key);			//删除头部数据
                head->next = head->next->next;
                if (head->next != NULL) {
                    hash[head->next->key] = head;
                }
                size--;
            }
        }
    }
};
