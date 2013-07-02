#if !defined (XML_ELEMENT_HPP)
#define XML_ELEMENT_HPP

#include <boost/format.hpp>
#include "attribute.hpp"

namespace xml
{

template <typename T>
class basic_element : public basic_node<T>
{
public:

    typedef std::shared_ptr<basic_element> pointer_type;
    typedef basic_attribute<char_type> attribute_type;
    typedef boost::basic_format<char_type> format_type;

    struct format
    {
        static format_type const open;
        static format_type const attributes;
        static format_type const close;
        static format_type const collapsed;
    };
    
    basic_element(string_type const& n, string_type const& v = string_type())
    : basic_node(n, v)
    {
    }

    basic_element(basic_element const& other)
    : basic_node(other.name(), other.value())
    {
        for(auto attr : other.attributes())
        {
            attribute(attr.first, attr.second->value());
        }
    }

    virtual typename basic_node::pointer_type copy() const
    {
        return std::make_shared<basic_element>(*this);
    }

    virtual ostream_type& serialize(ostream_type& stream) const
    {
        stream << format_type(format::open) % name();

        for(auto attr : m_attributes)
        {
            stream << *attr.second;
        }

        stream << format_type(format::attributes) << value();

        return basic_node::serialize(stream) << format_type(format::close) % name();
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

basic_element<char>   ::format_type const basic_element<char>   ::format::open = boost::format ( "<%1%");
basic_element<wchar_t>::format_type const basic_element<wchar_t>::format::open = boost::wformat(L"<%1%");

basic_element<char>   ::format_type const basic_element<char>   ::format::attributes = boost::format ( ">");
basic_element<wchar_t>::format_type const basic_element<wchar_t>::format::attributes = boost::wformat(L">");

basic_element<char>   ::format_type const basic_element<char>   ::format::close = boost::format ( "</%1%>");
basic_element<wchar_t>::format_type const basic_element<wchar_t>::format::close = boost::wformat(L"</%1%>");

basic_element<char>   ::format_type const basic_element<char>   ::format::collapsed = boost::format ( "<%1%/>");
basic_element<wchar_t>::format_type const basic_element<wchar_t>::format::collapsed = boost::wformat(L"<%1%/>");

} // namespace xml

#endif // XML_ELEMENT_HPP