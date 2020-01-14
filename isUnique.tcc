/****************************************************
* @file                isUnique.tcc
* @brief               Template implementation of isUnique
* @created             14/01/2020
* @author              Amogh Kudari
*****************************************************/
#ifndef _ISUNIQUE_TCC_
#define _ISUNIQUE_TCC_

#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <memory>
#include <string>
#include <list>
#include <typeinfo>

/**
 * @brief Check if it is specialization and declares of either false_type or true_type
 */
template<typename Test, template<typename...> class Ref>
struct is_specialization : std::false_type {};

/**
 * @brief Check if it is specialization for templated types and declares of either false_type or true_type
 */
template<template<typename...> class Ref, typename... Args>
struct is_specialization<Ref<Args...>, Ref>: std::true_type {};

/**
 * @brief General enable_if datatype based on conditions
 */
template<bool Condition, typename T1, typename T2>
struct enable_if;

/**
 * @brief T1 enabled if true
 */
template<typename T1, typename T2>
struct enable_if<true, T1, T2>;

/**
 * @brief T2 enabled if false
 */
template<typename T1, typename T2>
struct enable_if<false, T1, T2>;

template<bool Condition, typename T1, typename T2>
struct enable_if
{
};

template<typename T1, typename T2>
struct enable_if<true, T1, T2>
{
    typedef T1 type;
};

template<typename T1, typename T2>
struct enable_if<false, T1, T2>
{
    typedef T2 type;
};

/**
 * @brief checks uniqueness of argument passed
 * @return true if argument is unique false otherwise
 */
template<typename T>
bool is_unique(T& arg);

/**
 * @brief template specialization for std::pair
 * @return true if argument is of default type false otherwise
 */
template<typename First, typename Second>
bool is_unique(std::pair<First, Second>& arg);

/**
 * @brief template specialization for std::pair of const type
 * @return true if argument is of default type false otherwise
 */
template<typename First, typename Second>
bool is_unique(const std::pair<First, Second>& arg);

/**
 * @brief template specialization for std::map
 * all keys should be unique as well as values.
 * This is achieved by making a vector one for Keys other for Values
 * and checking if there is no repition of either Keys or Values
 * @return true if argument is of default type false otherwise
 */
template<typename Key, typename Value>
bool is_unique(std::map<Key, Value>& arg);

/**
 * @brief template specialization for std::vector of vector
 * @return true if argument is of default type false otherwise
 */
template<typename T>
bool is_unique(std::vector<std::vector<T>>& arg);

/**
 * @brief template specialization for std::vector
 * @return true if argument is of default type false otherwise
 */
template <typename T>
typename std::enable_if<! is_specialization<T, std::vector>::value, bool>::type is_unique(std::vector<T>& arg);

/**
 * @brief checks if argument passed is default type(includes shared and weak pointers)
 * @return true if argument is of default type false otherwise
 */
template<typename T>
bool is_default_type(T& arg) {
  if(typeid(arg) == typeid(char) ||  typeid(arg) == typeid(short) || typeid(arg) == typeid(int) || typeid(arg) == typeid(long) || typeid(arg) == typeid(float) || typeid(arg) == typeid(double) || typeid(arg) == typeid(long double) ||
     typeid(arg) == typeid(unsigned char) ||  typeid(arg) == typeid(unsigned short) || typeid(arg) == typeid(unsigned int) || typeid(arg) == typeid(unsigned long) || typeid(arg) == typeid(std::string) ||
     typeid(arg) == typeid(std::shared_ptr<T>) ||  typeid(arg) == typeid(std::unique_ptr<T>) || typeid(arg) == typeid(std::weak_ptr<T>) || typeid(arg) == typeid(T*) || typeid(arg) == typeid(T&)) {
    return true;
  }
}

template<typename T>
bool is_unique(T& arg) {
  if(is_default_type(arg)) {
    return true;
  }
  return is_unique<T>(arg);
}

template <typename T>
bool is_unique(std::vector<std::vector<T>> & arg) {
  std::cout << "is_unique vector of vectors size: " << arg.size() <<"\n";
    std::vector<T> vec;
    for(auto& outer_vec_ele: arg) {
      for(auto& inner_vec_ele : outer_vec_ele) {
        vec.push_back(inner_vec_ele);
      }
    }
    std::cout << "Size of vec: " << vec.size() << std::endl;
    return is_unique(vec);
 }

template <typename T>
typename std::enable_if<! is_specialization<T, std::vector>::value, bool>::type is_unique(std::vector<T>& arg) {
  std::cout << "is_unique for vector size: " << arg.size() << "\n";
  std::vector<T> temp = arg;
  for(int i = 0; i < arg.size(); i++ ) {
    for(int j = 0; j < temp.size(); j++) {
      if(!is_unique(arg[i]) || !is_unique(temp[j])) {
        return false;
      }
      if(i == j) {
        continue;
      }
      if(arg[i] == temp[j]) {
        return false;
      }
    }

  }
  return true;
}

template<typename First, typename Second>
bool is_unique(std::pair<First, Second>& arg) {
  if(!is_unique(arg.first)){
    return false;
  }
  if(!is_unique(arg.second)){
    return false;
  }
  return true;
}

template<typename First, typename Second>
bool is_unique(const std::pair<First, Second>& arg) {
  if(!is_unique(arg.first)){
    return false;
  }
  if(!is_unique(arg.second)){
    return false;
  }
  return true;
}

template<typename T>
std::vector<typename T::type>* get_vec_container(T& arg) {
 std::vector<typename T::type> *vec;
 vec = new std::vector<typename T::type>;
 return vec;
}

template<typename Key, typename Value>
bool is_unique(std::map<Key, Value>& arg) {
  std::cout << "is_unique for map arg size: " << arg.size() << "\n";
  std::vector<Key> vec_key;
  std::vector<Value> vec_value;
  for( auto& map_element : arg) {
    vec_key.push_back(map_element.first);
    vec_value.push_back(map_element.second);

  }
  std::cout << "vec_key size: " << vec_key.size() << "\n";
  if(!is_unique(vec_key)) {
    return false;
  };
  std::cout << "vec_value size: " << vec_value.size() << "\n";
  if(!is_unique(vec_value)) {
    return false;
  };
  return true;
}

#endif /*_ISUNIQUE_TCC_*/