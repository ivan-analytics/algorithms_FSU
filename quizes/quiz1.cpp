template <typename T>
class Vector {
    int arr_size = 10;
    int[arr_size]* arr;


};


// 1, 2, 3, 5

// 5, 3, 2, 1

template <typename T>
void Vector<T>::reverse() {
    int* temp = new int[this->arr_size]
    for (int i = 0; i < this->arr_size; i++) {
        *temp[i] = *arr[this->arr_size - 1 - i] // - i ?
    }
    delete this->arr;
    this->arr = temp;
    
    return;    
} // removes and discards the most recently added element of the Stack