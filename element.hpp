#if !defined (XML_ELEMENT_HPP)
#define XML_ELEMENT_HPP

#include "attribute.hpp"

namespace xml
{

template <typename T>
class basic_element : public basic_node<T>
{
public:

    typedef std::shared_ptr<basic_element> pointer_type;
    typedef basic_attribute<char_type> attribute_type;
    
    basic_element(string_type const& n, string_type const& v = string_type())
    : basic_node(n, v)
    {
    }

    virtual ostream_type& output(ostream_type& stream) const
    {
        stream << entity_type::lt << name();
        for(auto attr : attributes())
        {
            stream << *attr.second;
        }

        stream << entity_type::gt;
        for(auto child : children())
        {
            stream << *child;
        }
        return stream << entity_type::lt << entity_type::slash << name() << entity_type::gt;
    }

    typename attribute_type::const_range attributes() const
    {
        return typename attribute_type::const_range(m_attributes.cbegin(), m_attributes.cend());
    }

    typename attribute_type::range attributes()
    {
        return typename attribute_type::range(m_attributes.begin(), m_attributes.end());
    }

    string_type attribute(string_type const& n) const
    {
        m_attributes[n] = std::make_shared<attribute_type>(n, v);
    }

    void attribute(string_type const& n, string_type const& v)
    {
        m_attributes[n] = std::make_shared<attribute_type>(n, v);
    }

private:
    
    typename attribute_type::container_type m_attributes;
};

} // namespace xml

#endif // XML_ELEMENT_HPP