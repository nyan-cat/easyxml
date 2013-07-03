#if !defined (XML_PROCESSINGINSTRUCTION_HPP)
#define XML_PROCESSINGINSTRUCTION_HPP

#include <boost/format.hpp>
#include "node.hpp"

namespace xml
{

template <typename T>
class basic_processing_instruction : public basic_node<T>
{
public:

    typedef typename basic_node::string_type string_type;
    typedef typename basic_node::ostream_type ostream_type;
    typedef std::shared_ptr<basic_processing_instruction> pointer_type;
    typedef boost::basic_format<char_type> format_type;

    struct format
    {
        static format_type const processing_instruction;
    };

    basic_processing_instruction(string_type const& n, string_type const& v)
    : basic_node(n, v)
    {
    }

    virtual typename basic_node::pointer_type copy() const
    {
        return std::make_shared<basic_processing_instruction>(*this);
    }

    virtual ostream_type& serialize(ostream_type& stream) const
    {
        return stream << format_type(format::processing_instruction) % name() % value();
    }
};

basic_processing_instruction<char>   ::format_type const basic_processing_instruction<char>   ::format::processing_instruction = boost::format ( "<?%1% %2%?>");
basic_processing_instruction<wchar_t>::format_type const basic_processing_instruction<wchar_t>::format::processing_instruction = boost::wformat(L"<?%1% %2%?>");

} // namespace xml

#endif // XML_PROCESSINGINSTRUCTION_HPP