#include "Globals/Globals.hpp"
#include "Dumper/Dumper.hpp"

int main()
{
	printa->project<40>(xorstr_("Apex Legends Dumper by dhanax26 - v1.0.2"));

	__try
	{
		auto Once = false;

		while (!Memory::Initialize())
		{
			if (!Once)
			{
				printa->print<fail>(xorstr_("Waiting for Apex Legends, please rename the r5apex.exe to EasyAntiCheat_launcher.exe and run it.\r\n"));
				Once = true;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		std::thread SignatureDumper(Dumper::DumperThread);
		SignatureDumper.detach();
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {};

	return std::getchar();
}