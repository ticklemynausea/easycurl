#include "easycurl.h"

int main(int argc, char* argv[]) {

  if (argc < 2)
    return 0;
    
  EasyCurl* c = new EasyCurl(argv[1]);
  
  if (!c->requestWentOk) {
    cout << "  msg:" << c->error_message << endl;
    cout << "ccode:" << c->error_code << endl << "--" << endl;
  }
  
  cout << "  url:" << c->request_url << endl;
  cout << "ctype:" << c->response_content_type << endl;
  cout << " clen:" << c->response_content_length << endl;

  if (c->isHtml) {
     cerr << c->response_body << "--" << endl;
     cout << "Title: «" << c->html_title << "»" << endl;
  }
  return 0;
}
