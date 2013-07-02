#if !defined (XML_COMMENT_HPP)
#define XML_COMMENT_HPP

#include <boost/format.hpp>
#include "node.hpp"

namespace xml
{

template <typename T>
class basic_comment : public basic_node<T>
{
public:

    typedef typename basic_node::string_type string_type;
    typedef typename basic_node::ostream_type ostream_type;
    typedef std::shared_ptr<basic_comment> pointer_type;
    typedef boost::basic_format<char_type> format_type;

    struct format
    {
        static format_type const comment;
    };

    basic_comment(string_type const& c)
    : basic_node(string_type(), c)
    {
    }

    virtual typename basic_node::pointer_type copy() const
    {
        return std::make_shared<basic_comment>(*this);
    }

    virtual ostream_type& serialize(ostream_type& stream) const
    {
        return stream << format_type(format::comment) % value();
    }
};

basic_comment<char>   ::format_type const basic_comment<char>   ::format::comment = boost::format ( "<!--%1%-->");
basic_comment<wchar_t>::format_type const basic_comment<wchar_t>::format::comment = boost::wformat(L"<!--%1%-->");

} // namespace xml

#endif // XML_COMMENT_HPP