//bjam  --toolset=gcc --with-system --stagedir="D:\boost_1_47_0\mingw\stage" --build-dir="D:\boost_1_47_0\mingw\b2" link=static runtime-link=shared threading=multi debug release stage

//bjam  --toolset=gcc --with-filesystem --stagedir="D:\boost_1_47_0\mingw\stage" --build-dir="D:\boost_1_47_0\mingw\b2" link=static runtime-link=shared threading=multi debug release stage 


//g++ -g  -ID:\boost_1_47_0 -o  boost_filesystem.exe boost_filesystem.cpp D:\boost_1_47_0\mingw\stage\lib\libboost_filesystem-mgw44-mt-1_47.a  D:\boost_1_47_0\mingw\stage\lib\libboost_system-mgw44-mt-1_47.a



#include "boost/filesystem.hpp"
#include "boost/optional.hpp"
#include "boost/xpressive/xpressive_dynamic.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/typeof/typeof.hpp"

#include "boost/foreach.hpp"
#include "boost/progress.hpp"

#include "boost/program_options.hpp"


#include <vector>
#include <string>

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



void find_files( const boost::filesystem::path& p, const std::string& filename, std::vector<boost::filesystem::path>& r) 
{
  if(!boost::filesystem::exists(p) || !boost::filesystem::is_directory(p))
    {
      return;
    }
  
  static boost::xpressive::sregex_compiler  sc;
  if(!sc[filename].regex_id())
    {
      std::string str = boost::replace_all_copy(boost::replace_all_copy(filename, ".", "\\."), "*", ".*");
      sc[filename] = sc.compile(str);
    }
  
  boost::filesystem::recursive_directory_iterator rdend;
  for(boost::filesystem::recursive_directory_iterator pos(p); pos!=rdend; ++pos)
    {
      // if( !boost::filesystem::is_directory(*pos) && boost::xpressive::regex_match(pos->path().string(), sc[filename]) )
      if( !boost::filesystem::is_directory(*pos) && boost::xpressive::regex_match(pos->path().filename().string(), sc[filename]) )      
      // if( !boost::filesystem::is_directory(*pos) ) 
	{
	  std::cout << filename << "path is: " << (*pos).path() << std::endl; 
	  r.push_back((*pos).path());	  
	}

    }

      if(r.empty())
	{
	  std::cout << filename << " not found!" << std::endl;
	}
      else
	{
	  std::cout << "find_files succeed: " << std::endl;
	}
      
      for(BOOST_AUTO(it, r.begin()); it!=r.end(); ++it)
	{
	  std::cout << *it << std::endl;
	}
      
}

void copy_files(const boost::filesystem::path& from_dir, const boost::filesystem::path& to_dir, const std::string& filename = "*")
{
  if(!boost::filesystem::exists(from_dir) || !boost::filesystem::is_directory(from_dir) )
    {
      std::cout << from_dir << "dosent exist." << std::endl;
      return;
    }


  std::vector<boost::filesystem::path> filesFound;
  find_files(from_dir, filename, filesFound );

  if(filesFound.empty())
    {
      std::cout << "empty dont need copy" << std::endl; 
    }

  boost::progress_display pd(filesFound.size());  
  boost::filesystem::recursive_directory_iterator rdEnd;
  // for( BOOST_AUTO(pos, boost::filesystem::recursive_directory_iterator(
  boost::filesystem::path tmp;
  
  BOOST_FOREACH(boost::filesystem::path& each, filesFound)
    {
      tmp = to_dir / each.string().substr(from_dir.string().length()); 
      if(!boost::filesystem::exists(tmp.parent_path()))
	{
	  boost::filesystem::create_directories(tmp.parent_path());
	}
	boost::filesystem::copy_file(each, tmp);
	++pd;
    }
  

}


int main(int argc, char* argv[] )
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

  // std::vector<boost::filesystem::path> pv;
  // find_files("d:/codingbycoding", "boost*", pv);

  // copy_files("d:/codingbycoding/boost", "d:/test");


  boost::program_options::options_description opts("demo options");
  // boost::program_options po;
  opts.add_options()("help,h", "this is help command.")("test,t", boost::program_options::value<std::string>(), "this is test command.");
  boost::program_options::variables_map vm;

  try{
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, opts),vm );
  }
  catch(std::exception& e)
    {
      std::cout << e.what() << std::endl;
    }
  catch(...)
    {
      std::cout << "final catch..." << std::endl;
    }

  
  if(vm.count("help"))
    {
      std::cout << opts << std::endl;
      // return 0;
    }
    if(vm.count("test"))
      {
	std::cout << vm["test"].as<std::string>() << std::endl;
      }
    if(vm.size() == 0)
      {
	std::cout << "no args at all." << std::endl;
      }



    
  return 0; 
}
