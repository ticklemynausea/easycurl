#include "easycurl.h"

int main(int argc, char* argv[]) {

  if (argc < 2)
    return 0;
    
  EasyCurl* c = new EasyCurl(argv[1]);
  
  if (!c->requestWentOk)
    cout << c->error_message << "--" << endl;
    
  cout << c->request_url << endl;
  cout << c->response_content_type << endl;
  cout << c->response_content_length << endl;
  
  if (c->isHtml) {
     cerr << c->response_body << "--" << endl;
     cout << "Title: «" << c->html_title << "»" << endl;
  }
  return 0;
}
