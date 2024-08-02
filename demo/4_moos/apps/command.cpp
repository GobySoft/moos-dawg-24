#include "MOOS/libMOOS/App/MOOSApp.h"
#include "pb_marshall.h"
#include "status.pb.h"
#include "updated_command.pb.h"
#include <boost/units/systems/si.hpp>

namespace moos
{
namespace dawg
{

class CommandApp : public CMOOSApp
{
    bool OnNewMail(MOOSMSG_LIST& mail)
    {
        for (CMOOSMsg& moos_msg : mail) {}
        return true;
    }

    bool OnConnectToServer() { return true; }

    bool Iterate()
    {
        auto now = MOOSTime();
        if (now > next_command_time_)
        {
            // send command
            send_command();
            next_command_time_ = now + dt_command_;
        }

        return true;
    }

    void send_command();

  private:
    double next_command_time_{0}; // MOOSTime
    double dt_command_{20};       // seconds between commands
};
} // namespace dawg
} // namespace moos

void moos::dawg::CommandApp::send_command()
{
    namespace si = boost::units::si;

    moos::dawg::Command command;
    command.set_action(moos::dawg::Command::SEARCH_FOR_MISSING_AIRPLANE);
    auto& plane_params = *command.mutable_airplane();
    plane_params.set_center_freq_with_units(37500 * si::hertz);
    plane_params.set_bandwidth_with_units(2000 * si::hertz);
    command.set_hash(0); // placeholder for required field - will be updated by hash codec

    std::string pb_serialized;
    pb_serialize(&pb_serialized, command);
    m_Comms.Notify("COMMAND_OUT", pb_serialized);
}

int main(int argc, char* argv[])
{
    //here we do some command line parsing ...
    MOOS::CommandLineParser p(argc, argv);

    //mission file could be first free parameter
    std::string mission_file = p.GetFreeParameter(0, "Mission.moos");

    //app name can be the second free parameter
    std::string app_name = p.GetFreeParameter(1, "Command");

    moos::dawg::CommandApp app;
    app.Run(app_name, mission_file, argc, argv);

    return 0;
}
