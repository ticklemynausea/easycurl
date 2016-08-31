#include <easycurl.h>
#include "stripper.h"

void assertEqual(const std::string &a_output, const std::string &a_expected) {
  if (a_output != a_expected) {
    std::cout << "Fail:" << std::endl;
    std::cout << "  Expected: " << a_expected << std::endl;
    std::cout << "  Received: " << a_output << std::endl;
  }
}

void stripWhitespaceTest(const std::string &a_source,
                         const std::string &a_expected) {
  assertEqual(stripWhitespace(a_source), a_expected);
}

int main(int argc, char *argv[]) {
  stripWhitespaceTest("  Hello   ", "Hello");
  stripWhitespaceTest("Hello   ", "Hello");
  stripWhitespaceTest("   Hello", "Hello");
  stripWhitespaceTest("Hello,    world", "Hello, world");
  stripWhitespaceTest("Hello,    pretty  world  ", "Hello, pretty world");
  stripWhitespaceTest(" ", "");

  if (argc < 2)
    return 0;

  EasyCurl *c = new EasyCurl(argv[1]);

  if (!c->requestWentOk) {
    std::cout << "  msg:" << c->error_message << std::endl;
  }

  std::cout << "code :" << c->response_code << std::endl;
  std::cout << "error:" << c->error_message << std::endl;
  std::cout << "url  :" << c->request_url << std::endl;
  std::cout << "ctype:" << c->response_content_type << std::endl;
  std::cout << "clen :" << c->response_content_length << std::endl;

  if (c->isHtml) {
    std::cerr << c->response_body << "--" << std::endl;
    std::cout << "Title: «" << c->html_title << "»" << std::endl;
    std::cout << "Prntscr: «" << c->prntscr_url << "»" << std::endl;
  }

  return 0;
}
