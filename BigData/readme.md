


# BigData

BigData is C++ header file. used in arithmatic operation of large data (~upto 80000 digits)

  

## Feature

- Basic Arithematic Operation
- Conditional Operator
- Easy to use
- and many more...

  
## How to use

Download header file named(bigcpp.hpp) and put file in same directory
after that use below starter template

```bash
  #include<iostream>
  #include"bigcpp.hpp"
  int main(){
  
  }
```

Variable Declearation and initialization

```bash
  big x , y;
  x = "123";
  y = "456";
```

Use of cin and cout operator

```bash
  big x;
  cin>>x;
  cout<<x;
```

Arithematic Operation

```bash
  big x , y , z;
  x = "24";
  y = "365";
  z = x+y;
  z = x*y;
  z = x-y;
  z = x/y;
```

Changing datatype from int to big

```bash
  int x = 20;
  big y;
  y = to_big(x);
```

Conditional Operation

```bash
  big x,y;
  x ="-334";
  y = "234325";
  if(x<y){}
  if(x<=y){}
  if(x==y){}
  if(x>=y){}
  if(x>y){}
```

