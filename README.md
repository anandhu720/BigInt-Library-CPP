# BigInt-Library-CPP
BigInt Library in CPP,by using it you can create integers of length upto 1000
### Info
BigNumber is a header only library for working with integers values bigger than the hardware limit.
BigNumber has no addition dependencies and is as simple to use as possible.
### Installation<br><br>
Download the **BigIntHeaderfile.cpp** and use it in your cpp file<br>
```C++

 #include "BigIntHeaderfile.cpp"

```
### How to create BigInt Datatype<br><br>
```C++
BigInt a("1038347839482847574568374128348756983741902738938473");
BigInt b();
BigInt c("-483258973847567834");
BigInt d(234);

```
### Operations in BigInt<br><br>
All premitive operations can be done ```[  + , - , * , % , / , += , -= , *= , %= , /= , ++(x) , (x)++ , --(x) , (x)-- ]```

examples :<br>
```C++
BigInt a("3498357894758934");
BigInt b("8657847382785");
BigInt c = a+b;
a += b;
a %= b;
a *= c;
a--;

string s = string(a);
```

