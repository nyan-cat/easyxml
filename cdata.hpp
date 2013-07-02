#if !defined (XML_CDATA_HPP)
#define XML_CDATA_HPP

#include <boost/format.hpp>
#include "node.hpp"

namespace xml
{

template <typename T>
class basic_cdata : public basic_node<T>
{
public:

    typedef typename basic_node::string_type string_type;
    typedef typename basic_node::ostream_type ostream_type;
    typedef std::shared_ptr<basic_cdata> pointer_type;
    typedef boost::basic_format<char_type> format_type;

    struct format
    {
        static format_type const cdata;
    };

    basic_cdata(string_type const& c)
    : basic_node(string_type(), c)
    {
    }

    virtual typename basic_node::pointer_type copy() const
    {
        return std::make_shared<basic_cdata>(*this);
    }

    virtual ostream_type& serialize(ostream_type& stream) const
    {
        return stream << format_type(format::cdata) % value();
    }
};

basic_cdata<char>   ::format_type const basic_cdata<char>   ::format::cdata = boost::format ( "<![CDATA[%1%]]>");
basic_cdata<wchar_t>::format_type const basic_cdata<wchar_t>::format::cdata = boost::wformat(L"<![CDATA[%1%]]>");

} // namespace xml

#endif // XML_CDATA_HPP