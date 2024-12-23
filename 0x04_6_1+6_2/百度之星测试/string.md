### size_t 和 stoi 函数

---

`stoi` is a function in the C++ Standard Library's `<string>` header. It stands for "string to integer". This function converts a string representation of an integer into an actual integer value. 

---

`size_t` is a data type in C and C++ programming languages. It is an unsigned integer type that is commonly used to represent sizes and indices of objects in memory.

The `size_t` type is guaranteed to be able to represent the maximum size of a theoretically possible object of any type (including arrays). This makes it useful for addressing memory and array sizes, as it ensures that variables of this type can hold the size of the largest possible object in the current environment.

---

```cpp
void solve(){
	string s = "123,456";
	size_t p = s.find(",");
	if(p == string::npos){
		cout << "Illegal inputs\n";
		return ; 
	}
	int leftPart = stoi(s.substr(0, p));
	int rightPart = stoi(s.substr(p + 1));
	cout << leftPart << ' ' << rightPart << '\n';
}
```

