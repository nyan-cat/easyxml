#if !defined (XML_ATTRIBUTE_HPP)
#define XML_ATTRIBUTE_HPP

#include <map>
#include <boost/format.hpp>
#include "node.hpp"

namespace xml
{

template <typename T>
class basic_attribute : public basic_node<T>
{
public:

    typedef typename basic_node::string_type string_type;
    typedef typename basic_node::ostream_type ostream_type;
    typedef std::shared_ptr<basic_attribute> pointer_type;
    typedef std::map<typename basic_node::string_type, pointer_type> container_type;
    typedef typename container_type::iterator iterator;
    typedef typename container_type::const_iterator const_iterator;
    typedef basic_range<iterator> range;
    typedef basic_range<const_iterator> const_range;
    typedef boost::basic_format<char_type> format_type;

    struct format
    {
        static format_type const attribute;
    };

    basic_attribute(string_type const& n, string_type const& v)
    : basic_node(n, v)
    {
    }

    virtual typename basic_node::pointer_type copy() const
    {
        return std::make_shared<basic_attribute>(*this);
    }

    virtual ostream_type& serialize(ostream_type& stream) const
    {
        return stream << format_type(format::attribute) % name() % value();
    }
};

basic_attribute<char>   ::format_type const basic_attribute<char>   ::format::attribute = boost::format ( " %1%=\"%2%\"");
basic_attribute<wchar_t>::format_type const basic_attribute<wchar_t>::format::attribute = boost::wformat(L" %1%=\"%2%\"");

} // namespace xml

#endif // XML_ATTRIBUTE_HPP