int operator[] (int index){
    if(size > 0){
        if(index>size){
            cout<<"err:index is bigger than size of vector;\nLast element is - ";
            return this->data[this->size];
        }else if(index < 0){
            if(this->size+index>=0){
                return this->data[this->size+index];
            } else{
                cout<<"err:index is bigger than size of vector;\nFirst element is - ";
                return this->data[0];
            }
        }
        return  this->data[index];
    }
    cout<<"err:size is ";
    return 0;
}