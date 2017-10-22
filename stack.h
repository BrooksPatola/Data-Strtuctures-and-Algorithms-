#pragma once
template <typename T>
class Stack{
	T* theStack_;
	int max_;
	int size_;
	void grow(){
		T* tmp=new T[max_*2];
		for(int i=0;i<size_;i++){
			tmp[i]=theStack_[i];
		}
		max_=max_*2;
		delete [] theStack_;
		theStack_=tmp;
	}
public:
	Stack(){
		theStack_=new T[50];
		max_=50;
		size_=0;
	}
	void push (const T& data){
		if(size_==max_){
			grow();
		}
		theStack_[size_]=data;
		size_++;
	}
	void pop(){
		if(!isEmpty()){
			size_--;
		}
	}
	//removed top() const
	T top()  {
		if(!isEmpty()){
			return theStack_[size_-1];
		}
		return T{};
	}
	bool isEmpty(){
		return size_==0;
	}
	~Stack(){
		delete [] theStack_;
	}
};