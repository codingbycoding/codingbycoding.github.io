//bjam  --toolset=gcc --with-system --stagedir="D:\boost_1_47_0\mingw\stage" --build-dir="D:\boost_1_47_0\mingw\b2" link=static runtime-link=shared threading=multi debug release stage

//bjam  --toolset=gcc --with-filesystem --stagedir="D:\boost_1_47_0\mingw\stage" --build-dir="D:\boost_1_47_0\mingw\b2" link=static runtime-link=shared threading=multi debug release stage 


//g++ -g  -ID:\boost_1_47_0 -o  boost_filesystem.exe boost_filesystem.cpp D:\boost_1_47_0\mingw\stage\lib\libboost_filesystem-mgw44-mt-1_47.a  D:\boost_1_47_0\mingw\stage\lib\libboost_system-mgw44-mt-1_47.a



#include "boost/filesystem.hpp"
#include "boost/optional.hpp"

void recursive_dir(const boost::filesystem::path& p)
{
  boost::filesystem::directory_iterator end;
  for(boost::filesystem::directory_iterator pos(p); pos!=end; ++pos)
    {
      if(boost::filesystem::is_directory(*pos))
	{
	  recursive_dir(*pos);
	}
      else
	{
	  std::cout << *pos << std::endl;
	}
	
    }
}


boost::optional<boost::filesystem::path> find_file( const boost::filesystem::path& p, const std::string filename) 
{
  typedef boost::optional<boost::filesystem::path> result_type;
  if(!boost::filesystem::exists(p) || !boost::filesystem::is_directory(p))
    {
      return result_type();
    }
  
  boost::filesystem::recursive_directory_iterator rdend;
  for(boost::filesystem::recursive_directory_iterator pos(p); pos!=rdend; ++pos)
    {
      if(!boost::filesystem::is_directory(*pos) && (*pos).path().filename() == filename)
	{
	  std::cout << filename << "path is: " << (*pos).path() << std::endl; 
	  return (*pos).path();	  
	}

    }

  std::cout << filename << " not found!" << std::endl;
  return result_type();  
  
}

int main()
{
  const int GB_BASE = 1024*1024*1024;
  boost::filesystem::space_info si = boost::filesystem::space("d:/");
  std::cout << "capacity: " << si.capacity/GB_BASE << " GB" << std::endl;
  std::cout << "available: " << si.available/GB_BASE << " GB"  << std::endl;
  std::cout << "free: " << si.free/GB_BASE << " GB" << std::endl;   

  
  boost::filesystem::path p("./boost_filesystem.cpp");
  std::cout << p.parent_path() << std::endl;
  std::cout << p.filename() << std::endl;
  std::cout << p.stem() << std::endl;
  std::cout << p.extension() << std::endl;
  std::cout << p.root_name() << std::endl;

  std::cout << boost::filesystem::file_size(p) << " bytes" << std::endl;
  // assert(boost::filesystem::status(p).type() == boost::filesystem::file_not_found);
  // assert(boost::filesystem::status(p).type() == boost::filesystem::directory_file);
  std::cout << boost::filesystem::initial_path() << std::endl;
  
  std::cout << "recursive dir: " << std::endl;
  recursive_dir("d:/codingbycoding/boost");

  std::cout << std::endl << std::endl;

  
  boost::filesystem::recursive_directory_iterator recurend;
  for(boost::filesystem::recursive_directory_iterator pos("d:/codingbycoding/stl"); pos!=recurend; ++pos)
    {
      if(boost::filesystem::is_directory(*pos))
	{
	  pos.no_push();
	}
      std::cout << *pos << std::endl;
    }


  find_file("d:/codingbycoding", "boostmain.cpp");
  
  return 0; 
}
