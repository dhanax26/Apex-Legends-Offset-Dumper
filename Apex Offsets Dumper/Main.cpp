#include "Globals/Globals.hpp"
#include "Dumper/Dumper.hpp"

int main()
{
	SetConsoleTitle(xorstr_("Apex Legends Dumper by dhanax26 - v1.0.0"));
	printa->project<40>(xorstr_("Apex Legends Dumper by dhanax26 - v1.0.0"));

	__try
	{
		auto Once = false;

		while (!Memory::Initialize())
		{
			if (!Once)
			{
				printa->print<fail>(xorstr_("Apex Legends not found, please run the game first\r\n"));
				Once = true;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		Management::CreateDataFolder();

		std::thread SignatureDumper(Dumper::DumperThread);
		SignatureDumper.detach();
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {};

	return std::getchar();
}
