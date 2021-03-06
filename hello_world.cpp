//  Copyright (c)      2015 Alireza Kheirkhahan
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <hpxio/local_file.hpp>

#include <hpx/hpx_init.hpp>
#include <hpx/include/components.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/include/runtime.hpp>

int hpx_main()
{
	{
		//defining a type for hpxio local file component, aka server.
		typedef hpx::io::server::local_file file_type;

		// creating a server and client at the same time
		// the constructor for client need the gid of component.
		// new_ returns the gid of component.
		hpx::io::local_file lf(
			hpx::components::new_<file_type>(hpx::find_here()));

		// this is the output file
		std::string filename = "output";

		// we open the file and write a small message
		lf.open_sync(filename, "w");
		std::string message = "Hellow World!\n";
		lf.write_sync(std::vector<char> (message.begin(), message.end()));

		lf.close_sync();

	}
	return hpx::finalize();
}



int main(int argc, char* argv[])
{
	std::vector<std::string> cfg;
 	cfg.push_back("hpx.os_threads=2");

	return hpx::init(argc, argv, cfg);
}