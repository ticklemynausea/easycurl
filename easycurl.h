#ifndef _easycurl_h_
#define _easycurl_h_

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <locale>

#include <boost/regex.hpp>
#include <curl/curl.h>

extern "C" size_t decode_html_entities_utf8(char *dest, const char *src);

#define USERAGENT_STR "Opera/12.80 (Windows NT 5.1; U; en) Presto/2.10.289 Version/12.02"
#define ISPRINT_LOCALE "pt_PT"
#define DOWNLOAD_SIZE (5*1024)

using namespace std;

class EasyCurl {

  private:

    CURL* curl;
    CURLcode curlCode;
    
    int bufferTotal;
    
    static bool is_not_printable(char c);
    static string translateHtmlEntities(string str);
    static string parseFor(string buffer, string expr, int match_no);
    
    static int writer(char *data, size_t size, size_t nmemb, EasyCurl* instance);    
    int instanceWriter(char*data, size_t size, size_t nmemb);

    int curlSetup(bool getBody);
    int curlRequest();
    
    bool determineIfHtml();    
    
    void fail();

  public:
    bool requestWentOk;
    bool isHtml;
    
    string error_message;
    
    string request_url;
    string redirect_count;
    string response_content_type;
    string response_content_length;
    string response_code;
    string response_body;
    string html_title;
    
    EasyCurl(string url);
};

#endif
