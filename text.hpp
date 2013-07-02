#if !defined (XML_TEXT_HPP)
#define XML_TEXT_HPP

#include "node.hpp"

namespace xml
{

template <typename T>
class basic_text : public basic_node<T>
{
public:

    typedef typename basic_node::string_type string_type;
    typedef typename basic_node::ostream_type ostream_type;
    typedef std::shared_ptr<basic_text> pointer_type;

    basic_text(string_type const& t)
    : basic_node(string_type(), t)
    {
    }

    virtual typename basic_node::pointer_type copy() const
    {
        return std::make_shared<basic_text>(*this);
    }

    virtual ostream_type& output(ostream_type& stream) const
    {
        return stream << value();
    }
};

} // namespace xml

#endif // XML_TEXT_HPP