#if !defined (XML_ENTITY_HPP)
#define XML_ENTITY_HPP

namespace xml
{

template <typename T>
class basic_entity
{
public:

    typedef T char_type;
    typedef char_type const* const string_type;

    static string_type amp;
    static string_type quot;
    static string_type lt;
    static string_type gt;
    static string_type slash;
    static string_type equal;
    static string_type question;
    static string_type whitespace;
    static string_type xml;
};

basic_entity<char>::string_type basic_entity<char>::amp = "&";
basic_entity<char>::string_type basic_entity<char>::quot = "\"";
basic_entity<char>::string_type basic_entity<char>::lt = "<";
basic_entity<char>::string_type basic_entity<char>::gt = ">";
basic_entity<char>::string_type basic_entity<char>::slash = "/";
basic_entity<char>::string_type basic_entity<char>::equal = "=";
basic_entity<char>::string_type basic_entity<char>::question = "?";
basic_entity<char>::string_type basic_entity<char>::whitespace = " ";
basic_entity<char>::string_type basic_entity<char>::xml = "xml";

basic_entity<wchar_t>::string_type basic_entity<wchar_t>::amp = L"&";
basic_entity<wchar_t>::string_type basic_entity<wchar_t>::quot = L"\"";
basic_entity<wchar_t>::string_type basic_entity<wchar_t>::lt = L"<";
basic_entity<wchar_t>::string_type basic_entity<wchar_t>::gt = L">";
basic_entity<wchar_t>::string_type basic_entity<wchar_t>::slash = L"/";
basic_entity<wchar_t>::string_type basic_entity<wchar_t>::equal = L"=";
basic_entity<wchar_t>::string_type basic_entity<wchar_t>::question = L"?";
basic_entity<wchar_t>::string_type basic_entity<wchar_t>::whitespace = L" ";
basic_entity<wchar_t>::string_type basic_entity<wchar_t>::xml = L"xml";

} // namespace xml

#endif // XML_ENTITY_HPP