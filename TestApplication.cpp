/****************************************************
* @file                TestApplication.cpp
* @brief               Driver for isUnique Tcc
* @created             14/01/2020
* @author              Amogh Kudari
*****************************************************/
#include "isUnique.tcc"
/**
 * \brief enum of Network Address Classes
 */
enum class AddressClassType {
  CLASS_UNKNOWN = 0,
  CLASS_A = 1,
  CLASS_B = 2,
  CLASS_C = 3,
  CLASS_UNKNOWN_IPV6 = 60,
  CLASS_A_IPV6 = 61,
  CLASS_B_IPV6 = 62,
  CLASS_C_IPV6 = 63,
};

/**
 * \brief aliases
 */
using interface = std::string;
using InstanceString = std::string;

/**
 * \brief small structure
 */
using InstanceParams = struct {
  AddressClassType s_type;
  std::string s_instanceId;
}; //struct InstanceParams

/**
 * \brief Operator == overload required for is_unique to work properly
 */
inline bool operator==(const InstanceParams& arg1, const InstanceParams& arg2) {
   return((arg1.s_type == arg2.s_type) || (arg1.s_instanceId == arg2.s_instanceId));
}

/**
 * \brief Map having complex information.
 */
using ComplexDataStructure = std::map<std::pair<interface,std::shared_ptr<int>>,
                                                std::map<InstanceString,
                                                          std::vector<InstanceParams>>>;

std::shared_ptr<int> info_ptr;
/**
 * \brief DataStructure fails due to reipitition of values
 */
ComplexDataStructure g_instance_datastructure_fails({{{"FailingInterface", info_ptr = NULL},{{"DirectionLeft",{{AddressClassType::CLASS_A,std::to_string(12)},
                                                                                                              {AddressClassType::CLASS_B,std::to_string(15)}}},
                                                                                             {"DirectionRight",{{AddressClassType::CLASS_C,std::to_string(16)},
                                                                                                               {AddressClassType::CLASS_A,std::to_string(11)}}}
                                                                                         }}});

/**
 * \brief DataStructure passes as there are no values repeated
 */
ComplexDataStructure g_instance_datastructure_passes({{{"PassingInterface", info_ptr = NULL},{{"DirectionLeft",{{AddressClassType::CLASS_UNKNOWN,std::to_string(12)},
                                                                                                               {AddressClassType::CLASS_A,std::to_string(15)}}},
                                                                                              {"DirectionRight",{{AddressClassType::CLASS_B,std::to_string(16)},
                                                                                                                {AddressClassType::CLASS_C,std::to_string(11)}}}
                                                                                               }}});

/**
 * \brief DataStructure passes as there are no values repeated
 */
ComplexDataStructure g_instance_datastructure_two_entries({{{"FirstInterface", info_ptr = NULL},{{"DirectionLeft",{{AddressClassType::CLASS_UNKNOWN,std::to_string(12)},
                                                                                                               {AddressClassType::CLASS_A,std::to_string(15)}}},
                                                                                              {"DirectionRight",{{AddressClassType::CLASS_B,std::to_string(16)},
                                                                                                                {AddressClassType::CLASS_C,std::to_string(11)}}}
                                                                                               }},
                                                      {{"SecondInterface", info_ptr = NULL},{{"DirectionUp",{{AddressClassType::CLASS_UNKNOWN_IPV6,std::to_string(0)},
                                                                                                               {AddressClassType::CLASS_A_IPV6,std::to_string(1)}}},
                                                                                              {"DirectionDown",{{AddressClassType::CLASS_B_IPV6,std::to_string(2)},
                                                                                                                {AddressClassType::CLASS_C_IPV6,std::to_string(3)}}}
                                                                                               }}
                                                                                             });

/**
 * \brief main test application
 */
int main(int argc, char* argv[])
{
  std::map<int,std::vector<int>> simple_map_fails = {
                                            {10, {5,6}},
                                            {11, {7,5}}
                                        };
  std::map<int,std::vector<int>> simple_map_passes = {
                                            {10, {5,6}},
                                            {11, {7,8}}
                                        };
  std::cout << "is_unique for simple map failing due to repition: " <<  is_unique(simple_map_fails) << "\n*************"  << std::endl;

  std::cout << "is_unique for simple map passing due to non repitition: " <<  is_unique(simple_map_passes) << "\n*************"  << std::endl;

  std::cout << "is_unique for complex map that fails due to repition of an entity in value CLASS_A "
            <<  is_unique(g_instance_datastructure_fails) << "\n*************"  << std::endl;

  std::cout << "is_unique for complex map that passes due to no repitions in values"
            <<  is_unique(g_instance_datastructure_passes) << "\n*************"  << std::endl;

  std::cout << "is_unique for complex map with 2 entries that passes due to no repitions in values"
            <<  is_unique(g_instance_datastructure_two_entries) << "\n*************"  << std::endl;
}
