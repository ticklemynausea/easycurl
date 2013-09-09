#include <easycurl.h>
#include "stripper.h"

void assertEqual (const std::string& a_output, const std::string& a_expected)
{
  if (a_output != a_expected) {
    std::cout << "Fail:" << std::endl;
    std::cout << "  Expected: " << a_expected << std::endl;
    std::cout << "  Received: " << a_output << std::endl;
  }
}

void stripWhitespaceTest (const std::string& a_source, const std::string& a_expected)
{
  assertEqual(stripWhitespace(a_source), a_expected);
}

int main(int argc, char* argv[])
{
  stripWhitespaceTest("  Hello   ", "Hello");
  stripWhitespaceTest("Hello   ", "Hello");
  stripWhitespaceTest("   Hello", "Hello");
  stripWhitespaceTest("Hello,    world", "Hello, world");
  stripWhitespaceTest("Hello,    pretty  world  ", "Hello, pretty world");
  stripWhitespaceTest(" ", "");

  if (argc < 2)
    return 0;
    
  EasyCurl* c = new EasyCurl(argv[1]);
  
  if (!c->requestWentOk) {
    cout << "  msg:" << c->error_message << endl;
  }
  
  cout << " code:" << c->response_code << endl;
  cout << "error:" << c->error_message << endl;
  cout << "  url:" << c->request_url << endl;
  cout << "ctype:" << c->response_content_type << endl;
  cout << " clen:" << c->response_content_length << endl;

  if (c->isHtml) {
     cerr << c->response_body << "--" << endl;
     cout << "Title: «" << c->html_title << "»" << endl;
  }
  return 0;
}
