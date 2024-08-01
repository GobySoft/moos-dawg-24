#include "status.pb.h"
#include <dccl.h>
#include <iostream>

#include <boost/units/systems/si.hpp>
#include <boost/units/systems/temperature/celsius.hpp>

void encode_decode_demo(dccl::Codec& codec, const moos::dawg::Status& status)
{
    moos::dawg::StatusWithoutDynamicConditions statusv3;

    // this only works since they are fundamentally exactly the same Protobuf message type
    // don't do this normally
    statusv3.ParseFromString(status.SerializeAsString());

    std::cout << "- Original: **" << status.ShortDebugString() << "**" << std::endl;
    std::string encoded, encodedv3;
    codec.encode(&encoded, status);
    codec.encode(&encodedv3, statusv3);
    std::cout << "- Encoded (hex)" << std::endl;
    std::cout << "  - without dynamic conditions: " << dccl::hex_encode(encodedv3) << " ("
              << encodedv3.size() << " bytes)" << std::endl;
    std::cout << "  - dynamic conditions: " << dccl::hex_encode(encoded) << " (" << encoded.size()
              << " bytes)" << std::endl;

    moos::dawg::Status decoded;
    moos::dawg::StatusWithoutDynamicConditions decodedv3;

    codec.decode(encoded, &decoded);
    codec.decode(encodedv3, &decodedv3);

    std::cout << "- Decoded:" << std::endl;
    std::cout << "  - without dynamic conditions: " << decodedv3.ShortDebugString() << std::endl;
    std::cout << "  - dynamic conditions: " << decoded.ShortDebugString() << std::endl;
}

int main()
{
    namespace si = boost::units::si;
    namespace celsius = boost::units::celsius;

    moos::dawg::Status status;
    dccl::Codec codec;
    codec.set_strict(true);

    codec.load<moos::dawg::Status>();
    codec.load<moos::dawg::StatusWithoutDynamicConditions>();

    std::cout << "# Proto definition \n```" << std::endl;
    std::cout << moos::dawg::Status::descriptor()->DebugString() << std::endl;
    std::cout << moos::dawg::StatusWithoutDynamicConditions::descriptor()->DebugString()
              << std::endl;
    std::cout << "```" << std::endl;

    std::cout << "# Analyze (DCCL3: No dynamic conditions) \n```" << std::endl;
    codec.info<moos::dawg::StatusWithoutDynamicConditions>(&std::cout);
    std::cout << "```" << std::endl;

    std::cout << "# Analyze (DCCL4: Dynamic conditions) \n```" << std::endl;
    codec.info<moos::dawg::Status>(&std::cout);
    std::cout << "```" << std::endl;

    std::cout << "# Example 1 \n" << std::endl;
    {
        moos::dawg::Status status;
        status.set_type(moos::dawg::Status::USV);
        auto* loc = status.mutable_location();
        loc->set_x_with_units(500 * si::meters);
        loc->set_y_with_units(700 * si::meters);
        encode_decode_demo(codec, status);
    }

    std::cout << "# Example 2 \n" << std::endl;
    {
        std::cout << "## Example 2a  \n" << std::endl;
        moos::dawg::Status status;
        status.set_type(moos::dawg::Status::AUV_WITH_CTD);
        auto* loc = status.mutable_location();
        loc->set_x_with_units(500 * si::meters);
        loc->set_y_with_units(700 * si::meters);
        loc->set_depth_with_units(50 * si::meters);
        status.set_temperature_with_units(12.3 * boost::units::absolute<celsius::temperature>());
        encode_decode_demo(codec, status);

        try
        {
            std::cout << "## Example 2b  \n" << std::endl;
            loc->set_depth_with_units(2100 * si::meters);
            encode_decode_demo(codec, status);
        }
        catch (dccl::OutOfRangeException& e)
        {
            std::cout << "- Exception (expected) as we exceeded dynamic max on depth field: "
                      << std::endl;
            std::cout << "```\n" << e.what() << "\n```" << std::endl;
        }

        std::cout << "## Example 2c  \n" << std::endl;
        status.set_type(moos::dawg::Status::DEEP_AUV);
        encode_decode_demo(codec, status);
    }

    std::cout << "# Example 3 \n" << std::endl;
    {
        moos::dawg::Status status;
        status.set_type(moos::dawg::Status::AUV_WITH_SONAR);
        auto* loc = status.mutable_location();
        loc->set_x_with_units(500 * si::meters);
        loc->set_y_with_units(700 * si::meters);
        loc->set_depth_with_units(10 * si::meters);
        status.mutable_airplane_detection()->set_detected_depth_with_units(4100 * si::meters);
        status.mutable_airplane_detection()->set_detected_freq_with_units(38000 * si::hertz);

        encode_decode_demo(codec, status);
    }
}
