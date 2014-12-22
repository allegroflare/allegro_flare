
#include <allegro_flare/interprocess_through_files.h>









InterprocessThroughFiles::instruction_data_t::instruction_data_t(std::string filename, ALLEGRO_PATH *directory_location)
	: time_found(af::time_now)
	, filename(filename)
	, path(al_clone_path(directory_location))
	, found(false)
{
	al_set_path_filename(path, filename.c_str());
	if (exists())
	{
		found = true;
	}
	else
	{
		std::cout << "HMMMM" << std::endl;
	}
}



bool InterprocessThroughFiles::instruction_data_t::exists()
{
	return al_filename_exists(al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP));
}



bool InterprocessThroughFiles::instruction_data_t::delete_file()
{
	if (exists())
	{
		if (al_remove_filename(al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP)))
		{
			std::cout << "al_remove_filename was successful" << std::endl;
			return true;
		}
		else
		{
			std::cout << "al_remove_filename failed" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "could not find file (!exists())" << std::endl;
	}
	return false;
}



const char *InterprocessThroughFiles::instruction_data_t::get_full_path()
{
	return al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP);

}





bool InterprocessThroughFiles::instruction_file_exists(std::string &filename)
{
	for (unsigned i=0; i<instruction_filename.size(); i++)
		if (instruction_filename[i] == filename) return true;
	return false;
}



InterprocessThroughFiles::~InterprocessThroughFiles()
{
	ALLEGRO_FS_ENTRY *this_process_participant_file = al_create_fs_entry(al_path_cstr(participant_file_path, ALLEGRO_NATIVE_PATH_SEP));
	al_remove_fs_entry(this_process_participant_file);
	al_destroy_fs_entry(this_process_participant_file);
}



InterprocessThroughFiles::InterprocessThroughFiles(std::string directory)
	: directory_location(al_create_path(directory.c_str()))
	, this_controller_id(random_string(32))
	, instruction_filename()
	, participant_file_path(NULL)
	, log_output(NULL)
{
	std::cout << "InterprocessInstruction.this_controller_id == " << this_controller_id << std::endl;

	// check for participant files, if there are none, then erase all of the .ii files (start a new interprocess session)

	// create the participant file
	// PARTICIPANT FILE NOT TESTED
	participant_file_path = al_clone_path(directory_location);
	std::string filename = random_string(32);
	al_set_path_filename(participant_file_path, filename.c_str());
	al_set_path_extension(participant_file_path, ".ii_participant");

	php::file_put_contents(al_path_cstr(participant_file_path, ALLEGRO_NATIVE_PATH_SEP), tostring(time(0)));
}




void InterprocessThroughFiles::set_log_output(std::ostream *output)
{
	log_output = output;
}




void InterprocessThroughFiles::clear_folder()
{
	// do this tomorrow :)
	for (unsigned i=0; i<instruction_data.size(); i++)
	{
		instruction_data[i]->delete_file();
		instruction_data.erase(instruction_data.begin()+i);
		i--;
	}
}




void InterprocessThroughFiles::delete_interprocess_file(std::string &filename)
{
	for (unsigned i=0; i<instruction_data.size(); i++)
	{
		if (instruction_data[i]->filename == filename)
		{
			instruction_data[i]->delete_file();
			instruction_data.erase(instruction_data.begin()+i);
			i--;
			return;
		}
	}
}




void InterprocessThroughFiles::delete_interprocess_files_aged(double age_in_sec)
{
	double time_now = af::time_now;
	for (unsigned i=0; i<instruction_data.size(); i++)
	{
		if (instruction_data[i]->time_found + age_in_sec < time_now)
		{
			std::cout << "deleting interprocess file \"" << instruction_data[i]->get_full_path() << "\"" << std::endl;
			instruction_data[i]->delete_file();
			instruction_data.erase(instruction_data.begin()+i);
			i--;
		}
	}
}




void InterprocessThroughFiles::write_interprocess_instruction(std::string instruction)
{
	ALLEGRO_PATH *path = al_clone_path(directory_location);
	std::string filename = random_string(32) + "-" + tostring(time(0));
	al_set_path_filename(path, filename.c_str());
	al_set_path_extension(path, ".ii");
	if (log_output) (*log_output) << "sending II: " << instruction << std::endl;
	//std::cout << "sending II: " << instruction << std::endl;
	php::file_put_contents(al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP), instruction);
}



void InterprocessThroughFiles::process_interprocess_instruction(std::string &filename)
{
	std::string process_instruction = php::file_get_contents(filename);
	if (log_output) (*log_output) << "received II: " << process_instruction << std::endl;
	//std::cout << "received II: " << process_instruction << std::endl;
}



std::string InterprocessThroughFiles::get_controller_id()
{
	return this_controller_id;
}



void InterprocessThroughFiles::check_for_interprocess_instructions()
{
	std::vector<std::string> files_found = get_directory_listing(al_path_cstr(directory_location, ALLEGRO_NATIVE_PATH_SEP));
	for (unsigned i=0; i<files_found.size(); i++)
	{
		// should probably store the new ones in a list first, then process them after.
		if (!instruction_file_exists(files_found[i]))
		{
			ALLEGRO_PATH *path = al_create_path(files_found[i].c_str());
			if (al_get_path_extension(path) == ".ii_participant")
			{
				// skip participant files
				std::cout << "found participant file... skipping" << std::endl;
			}
			else
			{
				// take instruction files
				ALLEGRO_PATH *path = al_create_path(files_found[i].c_str());

				instruction_filename.push_back(files_found[i]);
				instruction_data.push_back(new instruction_data_t(al_get_path_filename(path), directory_location)); // test this
				std::cout << "found interprocess file." << std::endl;
				process_interprocess_instruction(files_found[i]);
			}
			al_destroy_path(path);
			continue;
		}
	}
}


