#include "Controller.h"
#include <csignal>

void wait_for_key ();

bool Controller::signalFlag  = false;

int main(int argc, char ** argv) {

    Controller c(
        std::string("/home/adria/TFG/SinglePendulumMPC/SinglePendulum_cpp/single_pendulum_description/urdf/single_pendulum.urdf"),//Model path
        std::string("/home/adria/TFG/SinglePendulumMPC/config.yaml")); // Configuration path

    std::signal(SIGINT, c.signalHandler);
        
    c.connectODrive();

    // Create a trajectory with 300 nodes.
    c.createDOCP(true);
    
    c.createTrajectory();
    c.initGraphs();
   
    // Refactor the class to have only 100 nodes for the MPC.
    c.createDOCP(false);

    c.controlLoop();
    
    c.stopMotors();
    c.stopGraphs();
    c.showGraphs();

    wait_for_key();
    return 0;
}

/*
int main(int argc, char ** argv) {

    Controller OCP;
    OCP.loadModel(std::string("/home/adria/TFG/SinglePendulumMPC/SinglePendulum_cpp/single_pendulum_description/urdf/single_pendulum.urdf"));
    OCP.loadConfig(std::string("/home/adria/TFG/SinglePendulumMPC/config_weight_terminal.yaml"));
    
    OCP.create(true);
    
    if(OCP.add_callback_verbose)
        OCP.addCallbackVerbose();
    
    OCP.connectODrive();
    OCP.createTrajectory();
    
    //c.initGraphs();
    //c.startGraphsThread();

    c.controlLoop(c.control_loop_iterations);

    //c.stopGraphs();
    c.stopMotors();
    //c.showGraphs();

    wait_for_key();

    return 0;
}
*/

void wait_for_key ()
{
    std::cout << std::endl << "Press ENTER to continue..." << std::endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
    return;
}
