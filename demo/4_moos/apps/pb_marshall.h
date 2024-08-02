#ifndef MOOS_DAWG_PB_MARSHALL_H
#define MOOS_DAWG_PB_MARSHALL_H

#include <google/protobuf/message.h>
#include <google/protobuf/text_format.h>

namespace moos
{
namespace dawg
{

constexpr const char* MAGIC_PROTOBUF_HEADER{"@PB"};

// if using Goby, use goby::moos::MOOSTranslation<goby::moos::protobuf::TranslatorEntry::TECHNIQUE_PREFIXED_PROTOBUF_TEXT_FORMAT>::serialize(...)
inline void pb_serialize(std::string* out, const google::protobuf::Message& msg)
{
    *out = std::string() + MAGIC_PROTOBUF_HEADER + "[" + msg.GetDescriptor()->full_name() + "] ";
    *out += msg.ShortDebugString();
}

// if using Goby, use goby::moos::MOOSTranslation<goby::moos::protobuf::TranslatorEntry::TECHNIQUE_PREFIXED_PROTOBUF_TEXT_FORMAT>::parse(...)
// this simple implementation is missing error checking
inline void pb_parse(const std::string& in, google::protobuf::Message* msg)
{
    google::protobuf::TextFormat::Parser parser;
    parser.ParseFromString(in.substr(in.find(']') + 1), msg);
}
} // namespace dawg
} // namespace moos

#endif
