#include <cassert> // Provides assert

template<class RecordType>
size_t Table<RecordType>::hash_function(int key) const {
    return (key % TABLE_SIZE);
}

template<class RecordType>
Table<RecordType>::Table() {
    total_records = 0;
    for (size_t i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = nullptr;
    }
}

template<class RecordType>
Table<RecordType>::~Table() {
    for (size_t i = 0; i < TABLE_SIZE; i++) {
        Node<RecordType>* curr = hash_table[i];
        while (curr != nullptr) {
            Node<RecordType>* temp = curr;
            curr = curr->link;
            delete temp;
        }
        hash_table[i] = nullptr; // Reset the head pointer to nullptr
    }
}

template<class RecordType>
Table<RecordType>::Table(const Table<RecordType>& source) {
    total_records = source.total_records;
    for (size_t i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = nullptr; // Initialize to nullptr before copying
        Node<RecordType>* source_curr = source.hash_table[i];
        Node<RecordType>* prev = nullptr;
        while (source_curr != nullptr) {
            Node<RecordType>* new_node = new Node<RecordType>;
            new_node->record = source_curr->record;
            new_node->link = nullptr; // New node will be at the end of the list
            if (prev == nullptr) {
                hash_table[i] = new_node; // First node in the list
            } else {
                prev->link = new_node; // Link the previous node to the new node
            }
            prev = new_node; // Move the previous pointer to the new node
            source_curr = source_curr->link; // Move to the next node in the source
        }
    }
}

template<class RecordType>
void Table<RecordType>::insert(const RecordType& entry) {
    assert(entry.key >= 0);  // Precondition: entry.key >= 0
    size_t index = hash_function(entry.key);
    bool found = false;
    RecordType result;
    find(entry.key, found, result);

    if (found) {
        // If a record with the same key exists, replace it with the new entry
        Node<RecordType>* curr = hash_table[index];
        while (curr != nullptr && curr->record.key != entry.key) {
            curr = curr->link;
        }
        if (curr != nullptr) {
            curr->record = entry;
        }
    } else {
        // If no record with the same key exists, add the new entry as a new record
        Node<RecordType>* new_node = new Node<RecordType>;
        new_node->record = entry;
        new_node->link = hash_table[index];
        hash_table[index] = new_node;
        total_records++;
    }
}

template<class RecordType>
void Table<RecordType>::remove(int key) {
    assert(key >= 0);
    size_t index = hash_function(key);
    Node<RecordType>* prev = nullptr;
    Node<RecordType>* curr = hash_table[index];
    while (curr != nullptr && curr->record.key != key) {
        prev = curr;
        curr = curr->link;
    }
    if (curr != nullptr) {
        if (prev != nullptr) {
            prev->link = curr->link;
        } else {
            hash_table[index] = curr->link;
        }
        delete curr;
        total_records--;
    }
}

template<class RecordType>
void Table<RecordType>::operator=(const Table<RecordType>& source) {
    // Self-assignment check
    if (this == &source) {
        return;
    }

    // Clear the current table
    for (size_t i = 0; i < TABLE_SIZE; i++) {
        Node<RecordType>* curr = hash_table[i];
        while (curr != nullptr) {
            Node<RecordType>* temp = curr;
            curr = curr->link;
            delete temp;
        }
        hash_table[i] = nullptr;
    }

    // Copy the source table
    total_records = source.total_records;
    for (size_t i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = nullptr; // Initialize to nullptr before copying
        Node<RecordType>* source_curr = source.hash_table[i];
        Node<RecordType>* prev = nullptr;
        while (source_curr != nullptr) {
            Node<RecordType>* new_node = new Node<RecordType>;
            new_node->record = source_curr->record;
            new_node->link = nullptr; // New node will be at the end of the list
            if (prev == nullptr) {
                hash_table[i] = new_node; // First node in the list
            } else {
                prev->link = new_node; // Link the previous node to the new node
            }
            prev = new_node; // Move the previous pointer to the new node
            source_curr = source_curr->link; // Move to the next node in the source
        }
    }
}

template<class RecordType>
bool Table<RecordType>::is_present(int key) const {
    assert(key >= 0);
    size_t index = hash_function(key);
    Node<RecordType>* curr = hash_table[index];
    while (curr != nullptr) {
        if (curr->record.key == key) {
            return true;
        }
        curr = curr->link;
    }
    return false;
}

template<class RecordType>
void Table<RecordType>::find(int key, bool& found, RecordType& result) const {
    assert(key >= 0);
    found = false;
    size_t index = hash_function(key);
    Node<RecordType>* curr = hash_table[index];
    while (curr != nullptr) {
        if (curr->record.key == key) {
            found = true;
            result = curr->record;
            return;
        }
        curr = curr->link;
    }
    // If not found, result will remain unchanged
}

template<class RecordType>
Node<RecordType>* Table<RecordType>::find_node(int key) const {
    size_t index = hash_function(key);
    Node<RecordType>* curr = hash_table[index];
    while (curr != nullptr) {
        if (curr->record.key == key) {
            return curr;
        }
        curr = curr->link;
    }
    return nullptr;
}
