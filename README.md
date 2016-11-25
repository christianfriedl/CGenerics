# CGenerics

## A library for generic programming and OOP in C

This is one of my weekend self-education projects. My original intention was to base a BNF parser on this, and then a parser for an actual language on that... Obviously, this never came to fruition. Duh.

The project was to create a library of fundamental generic data structures in pure C. The basic idea was to use macros, especially *## expansion* (I forget the technical term), to create a C type from a base name and a type.

For example:

    cgArray(Int)* array = cgArray__new(Int, 20);

would expand to

    cgarrayOfInt* array = cgArrayOfInt__new(20);

by way of

    cgArrayOf##TYPENAME* cgArrayOf##TYPENAME##__new(const unsigned int initialCapacity);

So anyway, here are my learnings, and the principles I was trying to employ in this project:

### Design principles and coding style

* All functions are prefixed with cg
* Instance methods have one underscore between class name and method name (\<Typename\>\_doStuff(...))
* Static class methods have two underscores between class name and method name (\<Typename\>\_\_new(...))
* "Private" methods have static scope and *end* on an underscore (*end*, so vi's/ctag's keyword expansion can find it even if we change the visibility), e.g. `static cgAppState *cgAppState__new_(const char *name);`
* Constructors are named \<Typename\>\_\_new
* Alternative constructors are named \<Typename\>\_\_newFrom\<Foo\>
* Destructors are named \<Typename\>\_\_delete
* For each class there is a header named exactly like this class.
* For each generic class, there is a set of macros that will expand to declarations and definitions of the basic type and "methods" for that class.

### Example class: cgArray (defined in src/cgArray.h)

    #define DECLARE_ARRAY_TYPE(TYPENAME)
   
to create the typedef
    
    #define DECLARE_ARRAY_FUNCS(TYPENAME)
    
to create all the "methods"

    #define DECLARE_ARRAY(TYPENAME)
    
to unify the above two marcos for convenience

   #define DEFINE_ARRAY(TYPENAME)

to actually create the function definitions of our "methods"

    #define INIT_ARRAY(TYPENAME)
    
to unify the above two macros for convenience

### Takeaways and learnings

* You can achieve some limited success by way of macros. The major limitation is that macros don't recurse, so you can not do collections of collections (without using some hacks like pre-expanding some part of your headers...)
* You can not effectively do exceptions in C. I tried it by way of convention (see https://github.com/christianfriedl/CGenerics/blob/master/src/cgAppState.h), but then EVERY method call needs to check for "Exceptions" afterwards, and that is rather unseemly to say the least. The only other way I know would be to change the binary, so essentially write your own compiler.
* Of course, fundamental algorithms are extremely nasty with regards to edge cases, and you have to be sure you really covered them all. This library does not cover even the most fundamental issues. So in the extremely unlikely case that you intend to use any part of this for any serious business, please use utter caution, because I didn't. You have been warned! (And a pull request would be nice!)
* I have since come to the True Belief of never using unsigned int, because it only gives you one extra bit, but can get you in an awful lot of trouble if you're not extremely careful.

## License

CGenerics is Copyright (c) by Christian Friedl.

The License of CGEnerics is GPLv3. See https://github.com/christianfriedl/CGenerics/blob/master/COPYING
