#ifndef _easycurl_h_
#define _easycurl_h_

#include <iostream>
#include <string>

#include <curl/curl.h>

#define USERAGENT_STR "Opera/12.80 (Windows NT 5.1; U; en) Presto/2.10.289 Version/12.02"
#define ISPRINT_LOCALE "pt_PT"
#define DOWNLOAD_SIZE (10*1024)

class EasyCurl {

  private:
    CURL* curl;
    CURLcode curlCode;

    int bufferTotal;

    static bool is_not_printable(char c);
    static std::string filterUnprintables(std::string str);
    static std::string translateHtmlEntities(std::string str);
    static std::string parseFor(std::string buffer, std::string expr, int match_no);
    bool determineIfHtml();

    static int bodyWriter(char *data, size_t size, size_t nmemb, EasyCurl* instance);
    int instanceBodyWriter(char*data, size_t size, size_t nmemb);

    static int headerWriter(char *data, size_t size, size_t nmemb, EasyCurl* instance);
    int instanceHeaderWriter(char*data, size_t size, size_t nmemb);

    int curlSetup();
    int curlRequest();

    bool extractContentType();
    bool extractTitle();
    bool extractPrntscr();
    bool extractMetadata();

    void fail();

  public:
    bool requestWentOk;
    bool isHtml;

    std::string error_message;

    std::string request_url;
    std::string redirect_count;
    std::string response_content_type;
    std::string response_content_length;
    std::string response_code;
    std::string response_body;
    std::string html_title;
    std::string prntscr_url;

    EasyCurl(std::string url);
    ~EasyCurl();
};

#endif
