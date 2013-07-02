#if !defined (XML_ENTITY_HPP)
#define XML_ENTITY_HPP

#include <boost/format.hpp>
#include "node.hpp"

namespace xml
{

template <typename T>
class basic_entity : public basic_node<T>
{
public:

    typedef typename basic_node::string_type string_type;
    typedef typename basic_node::ostream_type ostream_type;
    typedef std::shared_ptr<basic_comment> pointer_type;
    typedef boost::basic_format<char_type> format_type;

    struct format
    {
        static format_type const entity;
    };

    basic_entity(string_type const& code)
    : basic_node(string_type(), code)
    {
    }

    virtual typename basic_node::pointer_type copy() const
    {
        return std::make_shared<basic_entity>(*this);
    }

    virtual ostream_type& serialize(ostream_type& stream) const
    {
        return stream << format_type(format::entity) % value();
    }
};

basic_entity<char>   ::format_type const basic_entity<char>   ::format::entity = boost::format ( "&#%1%;");
basic_entity<wchar_t>::format_type const basic_entity<wchar_t>::format::entity = boost::wformat(L"&#%1%;");

} // namespace xml

#endif // XML_ENTITY_HPP