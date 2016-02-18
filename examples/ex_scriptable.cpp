

#include <allegro_flare/allegro_flare.h>




class MyScriptableThing : public Scriptable<MyScriptableThing>
{
public:
	MyScriptableThing(std::string name)
		: Scriptable(name)
	{
		register_function("echo", &MyScriptableThing::echo);
	}

	void echo(std::string arg)
	{
		std::cout << arg << std::endl;
	}
};




int main(int argc, char *argv[])
{
	MyScriptableThing f("yada");

	f.call_func("echo", "hello_world");

	return 0;
}

