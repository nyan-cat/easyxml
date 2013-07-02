#if !defined (XML_ATTRIBUTE_HPP)
#define XML_ATTRIBUTE_HPP

#include <map>
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

    basic_attribute(string_type const& n, string_type const& v)
    : basic_node(n, v)
    {
    }

    virtual ostream_type& output(ostream_type& stream) const
    {
        return stream << entity_type::whitespace << name() << entity_type::equal << entity_type::quot << value() << entity_type::quot;
    }
};

} // namespace xml

#endif // XML_ATTRIBUTE_HPP