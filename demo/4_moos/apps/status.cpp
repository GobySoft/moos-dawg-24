#include "MOOS/libMOOS/App/MOOSApp.h"
#include "pb_marshall.h"
#include "status.pb.h"
#include "updated_command.pb.h"

namespace moos
{
namespace dawg
{

class StatusApp : public CMOOSApp
{
    bool OnNewMail(MOOSMSG_LIST& mail)
    {
        for (CMOOSMsg& moos_msg : mail)
        {
            if (moos_msg.GetKey() == "COMMAND_IN")
            {
                std::cout << "Received COMMAND_IN: " << moos_msg.GetString() << std::endl;
                // respond with status for demo purposes
                respond_to_command(moos_msg);
            }
        }

        return true;
    }

    bool OnConnectToServer() { return Register("COMMAND_IN", 0.0); }

    bool Iterate() { return true; }

    void respond_to_command(CMOOSMsg& moos_msg);
};
} // namespace dawg
} // namespace moos

void moos::dawg::StatusApp::respond_to_command(CMOOSMsg& moos_msg)
{
    moos::dawg::Command command;
    pb_parse(moos_msg.GetString(), &command);

    switch (command.action())
    {
        case moos::dawg::Command::MEASURE_THERMOCLINE:
            // unimplemented
            break;
        case moos::dawg::Command::SEARCH_FOR_OCEAN_FRONT:
            // unimplemented
            break;
        case moos::dawg::Command::SEARCH_FOR_MISSING_AIRPLANE:
        {
            namespace si = boost::units::si;
            moos::dawg::Status status;
            status.set_type(moos::dawg::Status::AUV_WITH_SONAR);
            auto* loc = status.mutable_location();
            static int x = 500;
            static int y = 700;
            x += 10;
            y += 10;
            
            loc->set_x_with_units(x * si::meters);
            loc->set_y_with_units(y * si::meters);
            loc->set_depth_with_units(10 * si::meters);

            status.mutable_airplane_detection()->set_detected_depth_with_units(4100 * si::meters);
            status.mutable_airplane_detection()->set_detected_freq_with_units(38000 * si::hertz);

            std::string pb_serialized;
            pb_serialize(&pb_serialized, status);
            m_Comms.Notify("STATUS_OUT", pb_serialized);
        }
        break;
        case moos::dawg::Command::FIND_LIFE_ON_MARS:
            // unimplemented
            break;
    }
}

int main(int argc, char* argv[])
{
    //here we do some command line parsing ...
    MOOS::CommandLineParser p(argc, argv);

    //mission file could be first free parameter
    std::string mission_file = p.GetFreeParameter(0, "Mission.moos");

    //app name can be the second free parameter
    std::string app_name = p.GetFreeParameter(1, "Status");

    moos::dawg::StatusApp app;
    app.Run(app_name, mission_file, argc, argv);

    return 0;
}
