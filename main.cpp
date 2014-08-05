#include "LogCpp/Log.h"
#include "Scene.h"

#include <boost/program_options.hpp>
namespace po = boost::program_options;

int main(int argc, char** argv)
{
    logger->debug(logger->get() << "Command line arguments: " << argc-1);

    try {

        po::options_description desc("Allowed options");
        desc.add_options()
                ("help,h", "Produce help message")
                ("oculus,o", "Oculus mode")
                ("fullscreen,f", "Fullscreen mode")
                ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if(vm.count("help"))
        {
            std::cout << desc << std::endl;
            return 0;
        }

        Scene scene("Simulation", WINDOW_WIDTH, WINDOW_HEIGHT, vm.count("oculus"), vm.count("fullscreen"));
        scene.mainLoop();
    }
    catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch(...) {
        cerr << "Exception of unknown type!\n";
    }


    return 0;
}
