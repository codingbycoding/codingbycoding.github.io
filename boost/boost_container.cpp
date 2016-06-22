//g++ -g  -ID:\boost_1_47_0 -o  boost_container.exe boost_container.cpp D:\boost_1_47_0\mingw\stage\lib\libboost_system-mgw44-mt-1_47.a

#include <limits>

#include "boost/array.hpp"
#include "boost/assert.hpp"
#include "boost/typeof/typeof.hpp"
#include "boost/utility.hpp"
#include "boost/dynamic_bitset.hpp"

#include "boost/assign.hpp"
#include "boost/unordered_map.hpp"

#include "boost/bimap.hpp"
#include "boost/bimap/unordered_multiset_of.hpp"

#include "boost/tuple/tuple.hpp"

#include "boost/any.hpp"

#include "boost/shared_ptr.hpp"
#include "boost/make_shared.hpp"


#include "boost/variant.hpp"



#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/xml_parser.hpp"
#include "boost/property_tree/json_parser.hpp"

#include "boost/foreach.hpp"

#include "boost/algorithm/minmax.hpp"
#include "boost/algorithm/minmax_element.hpp"

#include "boost/integer_traits.hpp"
#include "boost/cstdint.hpp"

#include "boost/rational.hpp"

#include "boost/format.hpp"

#include "boost/crc.hpp"


#include "boost/random.hpp"
#include <ctime>


#include "boost/io/ios_state.hpp"

#include "boost/system/error_code.hpp"
#include "boost/system/system_error.hpp"

void logging(char* msg)
{
  std::cout << msg << std::endl;
}


boost::tuple<int, int, std::string> tupFun(){
  return boost::make_tuple(10,100,"tupFun");
}

int main()
{
  boost::array<int, 5> a = {0,1,2,3,4};
  a[3] = 10;

  for(BOOST_AUTO(it, a.begin()); it!=a.end(); it++)
    {
      std::cout << *it << " ";
    }

  BOOST_ASSERT(a[3] == 10);


  boost::dynamic_bitset<> db(10, BOOST_BINARY(10010));
  std::cout << "std::hex: " << std::hex << db.to_ulong()  << std::endl;

  for(int i=0; i<db.size(); i++)
    {
      std::cout << db[i] << " "; 
    }

  
  
  std::cout << "db[0]: " << db[0] << std::endl;

  db.resize(20,true);
  std::cout << db << std::endl;
  
  for(int i=0; i<db.size(); i++)
    {
      std::cout << db[i] << " "; 
    }
  std::cout << std::endl;

  std::cout << std::dec;


  std::cout << "<short>::max(): " << std::numeric_limits<short>::max() << std::endl;
  std::cout << "<unsigned long>::max(): " << std::numeric_limits<unsigned long>::max() << std::endl;
  std::cout << "<float>::max(): " << std::numeric_limits<float>::max() << std::endl;

  std::cout << "<double>::max(): " << std::numeric_limits<double>::max() << std::endl;




  {
    // using namespace boost::assign;
    boost::unordered_map<int, std::string> unmap = boost::assign::map_list_of(1,"one")(2,"two")(3,"three");

    std::cout << unmap[2] << std::endl;

    
    for(BOOST_AUTO(p, unmap.begin()); p!=unmap.end(); ++p)
      {
	std::cout << p->first << "-" << p->second << " ";
      }
  }
  std::cout << std::endl;

  boost::bimap<int, std::string> bi;
  bi.left.insert(std::make_pair<int,std::string>(3,"ThreeX"));
  // bi.left.insert(std::make_pair<int,std::string>(3,"ThreeXX")); //error key duplicated
  bi.left.insert(std::make_pair<int,std::string>(8,"EightX"));
  bi.left.insert(std::make_pair<int,std::string>(9,"NineX"));

  bi.right.insert(std::make_pair<std::string,int>("ThreeX", 5));

  for(BOOST_AUTO(pos, bi.left.begin()); pos!=bi.left.end(); ++pos)
    {
      std::cout << pos->first << "-" << pos->second << " ";
    }
  std::cout << std::endl;
  

  boost::bimap<boost::bimaps::unordered_multiset_of<int>, boost::bimaps::unordered_multiset_of<std::string> > biUn;

  biUn.left.insert(std::make_pair<int,std::string>(3,"ThreeX"));
  biUn.left.insert(std::make_pair<int,std::string>(3,"ThreeXX"));
  biUn.left.insert(std::make_pair<int,std::string>(3,"ThreeXXX"));  
  for(BOOST_AUTO(pos, biUn.left.begin()); pos!=biUn.left.end(); ++pos)
    {
      std::cout << pos->first << "-" << pos->second << " ";
    }
  std::cout << std::endl;



  // boost::bimap< boost::bimaps::tagged<boost::bimaps::unordered_multiset_of<int>, struct id>, boost::bimaps::tagged<boost::bimaps::unordered_multiset_of<std::string>, struct name> > biUnTag;

  boost::bimap< boost::bimaps::tagged<int, struct id>, boost::bimaps::tagged<std::string, struct name> > biUnTag;

  biUnTag.by<id>().insert(std::make_pair<int,std::string>(5,"FiveX"));
  biUnTag.by<name>().insert(std::make_pair<std::string, int>("TwoX", 2));

  biUnTag.left.insert(std::make_pair<int,std::string>(3,"ThreeX"));
  // biUnTag.left.insert(std::make_pair<int,std::string>(3,"ThreeXX"));
  // biUnTag.left.insert(std::make_pair<int,std::string>(3,"ThreeXXX"));  
  for(BOOST_AUTO(pos, biUnTag.left.begin()); pos!=biUnTag.left.end(); ++pos)
    {
      std::cout << pos->first << "-" << pos->second << " ";
    }
  std::cout << std::endl;  

  BOOST_AUTO(posF, biUnTag.left.find(5));
  biUnTag.left.replace_key(posF, 50);
  std::cout << "replace_key::::";
  for(BOOST_AUTO(pos, biUnTag.left.begin()); pos!=biUnTag.left.end(); ++pos)
    {
      std::cout << pos->first << "-" << pos->second << " ";
    }
  std::cout << std::endl;


  boost::tuple<int, int, std::string> tupVar(1,11,"tupVar");
  std::cout << tupVar.get<0>() << " ## ";
  std::cout << tupVar.get<1>() << " ## ";
  std::cout << tupVar.get<2>() << " ## ";


  std::cout << boost::get<0>(tupVar) << " ## " << std::endl;

  int tieI1, tieI2;
  std::string tieStr; 
  boost::tie(tieI1, tieI2, tieStr) = tupFun();

  std::string tieStrE;
  boost::tie(boost::tuples::ignore, boost::tuples::ignore, tieStrE) = tupFun();

  std::cout << "tieI1: " << tieI1 << " tieI2: " << tieI2 << " tieStr: " << tieStr << " tieStrE: " << tieStrE;

  std::cout << std::endl;



  boost::any anyI(65);
  try{
    std::cout << "anyI: " << boost::any_cast<std::string>(anyI);
  }
  catch(boost::bad_any_cast& e)
    {
      std::cout << e.what() << std::endl; 
    }
  catch(...)
    {
      std::cout << "catch(...)" << std::endl; 
    }

  boost::any anyP = boost::any( boost::shared_ptr<std::string>(boost::make_shared<std::string>("ptr_any")) );
  std::cout << "make_ptr_any: " << *(boost::any_cast<boost::shared_ptr<std::string> >(anyP)) << std::endl;

  std::cout << std::endl;









  boost::variant<int, double, std::string> var;
  var = "123";
  std::cout << "var: " << var << std::endl; 





  boost::property_tree::ptree pt;
  boost::property_tree::read_xml("ptree.conf", pt);
  std::cout << pt.get<std::string>("conf.title") << std::endl;
  std::cout << "<xmlattr> : " << pt.get<std::string>("conf.title.<xmlattr>.id") << std::endl;
  std::cout << pt.get<int>("conf.number") << std::endl;
  std::cout << pt.get("conf.number", 20000) << std::endl;
  std::cout << pt.get("conf.numbers", 50000) << std::endl;

  std::cout << "<xmlcomment> : " << pt.get<std::string>("conf.urls.<xmlcomment>") << std::endl;
  BOOST_AUTO(child, pt.get_child("conf.urls"));
  for(BOOST_AUTO(pos, child.begin()); pos!=child.end(); ++pos)
    {
      std::cout << pos->second.get_value<std::string>() << " ";
    }
  std::cout << std::endl;

 
  pt.put("conf.put", "puttest");
  // write_xml(std::cout, pt);


 
  boost::property_tree::ptree ptjson;
  boost::property_tree::read_json("ptree.json", ptjson);
 



  {
    using namespace boost::assign;
    std::vector<int> vint = list_of(10)(20)(30)(40);

    BOOST_FOREACH(int itech, vint)
      {
	std::cout << itech << " , ";
      }
    std::cout << std::endl;
  }



  {
    using namespace boost::assign;
    std::vector<int> vint = list_of(10)(20)(30)(40);

    BOOST_FOREACH(int& itech, vint)
      {
	// std::cout << itech*=2 << " , ";
	itech *= 2;
      }
   
    BOOST_FOREACH(int itech, vint)
      {
	std::cout << itech << " , ";
      }
    std::cout << std::endl;    
  }




  {
    BOOST_AUTO(var, boost::minmax(1,2));
    std::cout << "min: " << var.get<0>() << "     max :" << var.get<1>() << std::endl;
  }


  {
    using namespace boost::assign;
    std::vector<int> vInt = (list_of(2),30,50,100,20,2,50);
    BOOST_AUTO(var, boost::minmax_element(vInt.begin(), vInt.end()) );

    
    // std::cout << "min_element: " << var->first << "     max_element :" << var->second << std::endl;
    std::cout << "min_element: " << *var.first << "     max_element :" << *var.second << std::endl;    
  }




  std::cout << boost::integer_traits<int>::const_min << std::endl;
  std::cout << boost::integer_traits<int>::const_max << std::endl;

  boost::uint8_t u8;
  std::cout << typeid(u8).name() << std::endl;

  std::string str;
  std::cout << typeid(str).name() << std::endl;


  boost::rational<int> raI(10,3);
  boost::rational<int> raI2(20,3);
  
  std::cout << raI << std::endl;

  std::cout << boost::rational_cast<double>(raI) << std::endl;
  std::cout << raI.numerator() << "/" << raI.denominator() << std::endl;


  int raa=34, rab=17;
  boost::format fmt("gcd(%1%, %2%)=%3%  lcm(%1%, %2%)=%4%");
  std::cout << fmt % raa % rab % boost::gcd(raa,rab) % boost::lcm(raa,rab);
  std::cout << std::endl;




  std::cout << std::hex;
  boost::crc_32_type crc32;
  crc32.process_bytes("abcd", 4);
  std::cout << "crc32: " << crc32.checksum();

  
  crc32.reset();
  std::cout << std::endl;
  
  char ch4[] = {'a', 'b', 'c', 'd'};
  crc32.process_block(ch4, ch4+4);
  std::cout << "crc32: " << crc32.checksum();
  std::cout << std::endl;
  std::cout << std::dec;


  boost::mt19937 mtran(time(0));
  for(int i=0; i<10; ++i)
    {
      std::cout << mtran() << ", ";
    }
  std::cout << std::endl;
  
  boost::uniform_int<> uni(0, 255);
  for(int i=0; i<10; ++i)
    {
      std::cout << uni(mtran) << ", ";
    }
  std::cout << std::endl;
  
  boost::variate_generator<boost::mt19937&, boost::uniform_int<> > vargen(mtran, uni);
  for(int i=0; i<10; ++i)
    {
      std::cout << vargen() << ", ";
    }  
  std::cout << std::endl;

  unsigned char chBuf[10];
  // boost::rand_bytes<boost::mt19937>(chBuf, 10);
  // for(int i=0; i<10; ++i)
  //   {
  //     std::cout << (short)chBuf[i] << ", ";
  //   }  
  // std::cout << std::endl;  


  std::string fsstr ("./logging.log");
  std::cout << "log start..." << std::endl;
  if(!fsstr.empty())
    {
      boost::io::ios_all_saver ifs(std::cout);  
      std::ofstream fs(fsstr.c_str());
      std::cout.rdbuf(fs.rdbuf());
      logging("fatal msg!");
    }
      logging("logging log end!");  
  std::cout << "log end..." << std::endl;
  

  boost::system::error_code ec;
  // boost::system::error_category ecat = boost::system::system_category();
  std::cout << ec.category().name() << std::endl;
  ec.assign(3, boost::system::system_category());
  std::cout << ec.message() << std::endl;

  boost::system::error_condition econd = ec.default_error_condition();
  std::cout << econd.message() << std::endl; 
  // std::cout << boost::system::system_category.name() << std::endl;


  try{
    throw boost::system::system_error(boost::system::error_code(8, boost::system::system_category()) );
  }
  catch(boost::system::system_error& e)
    {
      std::cout << "system_error e.what(): " << e.what() << std::endl;
    }


  
  std::cout << std::endl;
  
  return 0; 
}
