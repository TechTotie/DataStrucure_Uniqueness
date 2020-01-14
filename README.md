# Uniqueness - Simple C++17 Application to check if the given datastructure is uniue or has repeated entries.
This is a simple C++17 application to validate if a given data structure like a
std::vector<Type> or std::vector<<std::vector>> or std::pair<First,Second> or std::map<Key,Value> has unique entires or not.
The program uses template specialization for implementation and will validate if there are repeated entries or not.
It will return true if the passed argument is a standard or default datatype.
You need to include the templated class file isUnique.tcc in your application to use it.
Please refer the TestApplication provided.

The function isUnique validates the uniqueness of the given data structure and returns true if it is unique and has unique entries
FnName      <isUnique>
InputParam  <T>  => Any user defained or default data type
ReturnValue <bool> => true if file is unique false otherwise.

Compile and Execute
1. Make build directory and cd to it
2. cmake .. (It uses '-std=c++17' compiler option by default)
3. Execute UniquenessValidator application by
   ./UniquenessValidator
