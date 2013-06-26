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
using namespace boost::assign;
boost::unordered_map<int, std::string> unmap = map_list_of(1,"one")(2,"two")(3,"three");

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




return 0; 
}
