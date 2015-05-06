

#include <allegro_flare/md5.h>
#include <allegro_flare/sha2.h>
#include <iostream>

#include <allegro_flare/useful_php.h>



int main(int argc, char **argv)
{
	// set the path to the location of the executable
	al_init();
	ALLEGRO_PATH *resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
	al_destroy_path(resource_path);

	// check that the file exists
	std::string filename = "data/bitmaps/pun_dog.jpg";
	if (!php::file_exists(filename))
	{
		std::cout << "File not found." << std::endl;
		return 1;
	}

	// generate the hashes
	std::string md5_hash = get_md5_hash_from_file(filename);
	std::string sha224_hash = get_sha224_hash_of_file(filename);
	std::string sha256_hash = get_sha256_hash_of_file(filename);
	std::string sha384_hash = get_sha384_hash_of_file(filename);
	std::string sha512_hash = get_sha512_hash_of_file(filename);

	//
	// output the results
	//

	std::cout << "expecting:" << std::endl << "f1c73dc3227a2a558cebb00716cb8fdc" << std::endl;
	std::cout << md5_hash << std::endl;

	std::cout << "expecting:" << std::endl << "7444158c86c29b8819210568ce2f57c626300a41d8518a8e9768b812" << std::endl;
	std::cout << sha224_hash << std::endl;

	std::cout << "expecting:" << std::endl << "73ea633f59d6d2c715361d1404f9abefb342c1acc1f871e887227bba9500191b" << std::endl;
	std::cout << sha256_hash << std::endl;

	std::cout << "expecting:" << std::endl << "eb2d32a9284d63f3f614540a693de87bcba94d014e99f626a64772e307610b498e3c796da839c8b453bbc5aa23a01148" << std::endl;
	std::cout << sha384_hash << std::endl;

	std::cout << "expecting:" << std::endl << "fb959abd4ddbc5a890b5837171bbcaaa2ef7ffd1601a97a528832a44995a93361402b87223187eb462c986cbfd79e74f767abd8af8d46165dbe387f5e8115cdf" << std::endl;
	std::cout << sha512_hash << std::endl;

	return 0;
}



